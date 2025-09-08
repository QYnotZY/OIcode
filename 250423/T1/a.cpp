#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
char gc() {return getchar();}
template<typename T = int>
inline T readnum(){
    T res = 0; bool f = 0;
    char ch = gc();
    for(; !('0' <= ch && ch <= '9'); ch = gc())
        if(ch == '-') f = !f;
    for(; '0' <= ch && ch <= '9'; ch = gc())
        res = (res << 3) + (res << 1) + (ch ^ 48);
    return f ? ~res + 1 : res;
}
inline char readch(bool sp = 0){
    char ch = gc();
    for(; !(33 - sp <= ch && ch < 127); ch = gc()) ;
    return ch;
}
template<typename T = int>
T read() {return readnum<T>();}
}
using FastIO::read;
typedef long long ll;

namespace work{
const int N = 2e5 + 10;
int n, x1[N], y1[N], x2[N], y2[N];
int Vx[N << 1], Vy[N << 1], limx, limy;
struct node{
    int y, x1, x2, op, col;
    bool operator < (node obj){
        return y < obj.y;
    }
} mdf[N << 1];
void disc(){
    for(int i = 1; i <= n; i ++)
        Vx[i] = x1[i], Vx[n + i] = x2[i];
    sort(Vx + 1, Vx + (n << 1) + 1);
    limx = unique(Vx + 1, Vx + (n << 1) + 1) - Vx - 1;
    for(int i = 1; i <= n; i ++)
        x1[i] = lower_bound(Vx + 1, Vx + limx + 1, x1[i]) - Vx,
        x2[i] = lower_bound(Vx + 1, Vx + limx + 1, x2[i]) - Vx - 1;
    for(int i = 1; i <= n; i ++)
        Vy[i] = y1[i], Vy[n + i] = y2[i];
    sort(Vy + 1, Vy + (n << 1) + 1);
    limy = unique(Vy + 1, Vy + (n << 1) + 1) - Vy - 1;
    for(int i = 1; i <= n; i ++)
        y1[i] = lower_bound(Vy + 1, Vy + limy + 1, y1[i]) - Vy,
        y2[i] = lower_bound(Vy + 1, Vy + limy + 1, y2[i]) - Vy;
}
void init(){
    n = read();
    for(int i = 1; i <= n; i ++)
        x1[i] = read(), y1[i] = read(), x2[i] = read(), y2[i] = read();
    disc();
    for(int i = 1; i <= n; i ++)
        mdf[i * 2 - 1] = {y1[i], x1[i], x2[i], 1, i},
        mdf[i * 2] = {y2[i], x1[i], x2[i], -1, i};
    sort(mdf + 1, mdf + n * 2 + 1);
}
bool vis[N];
namespace smt{
    struct node{
        int maxx, lim;
        set<int> col; 
    } tr[N << 3];
    void pushup(int p, bool leaf){
        int lc = p << 1, rc = lc | 1;
        tr[p].maxx = leaf ? 0 : max(tr[lc].maxx, tr[rc].maxx);
        tr[p].lim = leaf ? 0 : min(tr[lc].lim, tr[rc].lim);
        if(tr[p].col.size()){
            int now = *(tr[p].col.rbegin());
            vis[now] ? tr[p].lim = max(tr[p].lim, now) : tr[p].maxx = max(tr[p].maxx, now);
        }
        if(tr[p].lim > tr[p].maxx)
            tr[p].maxx = 0;
    }
    void modify(int ql, int qr, int col, int op, int p = 1, int l = 1, int r = limx){
        int lc = p << 1, rc = lc | 1;
        if(ql <= l && r <= qr){
            if(!(op ^ 1)) tr[p].col.emplace(col);
            if(!~op) tr[p].col.erase(col);
            return pushup(p, l == r);
        }
        int mid = l + (r - l >> 1);
        if(ql <= mid) modify(ql, qr, col, op, lc, l, mid);
        if(mid < qr) modify(ql, qr, col, op, rc, mid + 1, r);
        return pushup(p, 0);
    }
    int query(){
        return tr[1].maxx;
    }
}
int ans;
int Main(){
    init();
    ans = 0;
    for(int i = 1, j = 1; i <= limy; i ++){
        for(; mdf[j].y == i; j ++)
        #ifdef db
        printf("%d %d %d %d %d\n", mdf[j].y, mdf[j].x1, mdf[j].x2, mdf[j].op, mdf[j].col),
        #endif
            smt::modify(mdf[j].x1, mdf[j].x2, mdf[j].col, mdf[j].op);
        for(; smt::query(); ++ ans){
            #ifdef db
            printf("%d %d\n", i, smt::query());
            #endif
            vis[smt::query()] = 1;
            smt::modify(x1[smt::query()], x2[smt::query()], 0, 0);
        }
        #ifdef db
        printf("\n");
        #endif
    }
    printf("%d", ++ ans);
    return 0;
}
}
int main(){
    #ifndef db
    freopen("paint.in", "r", stdin);
    freopen("paint.out", "w", stdout);
    #endif
    return work::Main();
}