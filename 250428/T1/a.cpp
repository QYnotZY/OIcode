#include "bits/stdc++.h"
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
typedef pair<int, int> pii;
const int N = 2e5 + 10, inf = 2e5;
namespace work{
int n, m, q;
struct SMTnode{
    ll sum;
    ll tag_k, tag_d;
};
struct SMT{
    SMTnode tr[N << 2];
    void upd1(int p, int l, int r, ll k, ll d){
        tr[p].sum += ((l + r) * k + 2 * d) * (r - l + 1) / 2;
        tr[p].tag_k += k;
        tr[p].tag_d += d;
    }
    void pushdown(int p, int l, int r){
        int lc = p << 1, rc = lc | 1, mid = l + r >> 1;
        upd1(lc, l, mid, tr[p].tag_k, tr[p].tag_d);
        upd1(rc, mid + 1, r, tr[p].tag_k, tr[p].tag_d);
        tr[p].tag_k = tr[p].tag_d = 0;
    }
    void pushup(int p){
        int lc = p << 1, rc = lc | 1;
        tr[p].sum = tr[lc].sum + tr[rc].sum;
    }
    void update(int ql, int qr, ll k, ll d, int p = 1, int l = 1, int r = N){
        if(ql > qr) return;
        if(ql <= l && r <= qr) return upd1(p, l, r, k, d);
        int lc = p << 1, rc = lc | 1, mid = l + r >> 1;
        pushdown(p, l, r);
        if(ql <= mid) update(ql, qr, k, d, lc, l, mid);
        if(qr > mid) update(ql, qr, k, d, rc, mid + 1, r);
        pushup(p);
    }
    ll query(int x, int p = 1, int l = 1, int r = N){
        if(l == r) return tr[p].sum;
        int lc = p << 1, rc = lc | 1, mid = l + r >> 1;
        pushdown(p, l, r);
        if(x <= mid) return query(x, lc, l, mid);
        else return query(x, rc, mid + 1, r);
    }
} row, col;
struct MDF{
    int x1, x2, y; ll k, d;
    bool operator < (MDF obj){
        return y < obj.y;
    }
} rowm[N], colm[N]; int rmn, cmn;
vector<pii> rowq[N], colq[N];
ll ans[N];
void solve_row(){
    for(int y = 1, ml = 0, mr = 0; y <= inf; y ++){
        while(ml <= rmn && rowm[ml].y < y) ml ++;
        while(mr <= rmn && rowm[mr].y <= y) mr ++;
        for(int i = ml; i < mr; i ++)
            row.update(rowm[i].x1, rowm[i].x2, rowm[i].k, rowm[i].d);
        for(auto ele : rowq[y])
            ans[ele.second] += row.query(ele.first);
    }
}
void solve_col(){
    for(int x = 1, ml = 0, mr = 0; x <= inf; x ++){
        while(ml <= cmn && colm[ml].y < x) ml ++;
        while(mr <= cmn && colm[mr].y <= x) mr ++;
        for(int i = ml; i < mr; i ++)
            col.update(colm[i].x1, colm[i].x2, colm[i].k, colm[i].d);
        for(auto ele : colq[x])
            ans[ele.second] += col.query(ele.first);
    }
}
int x1[N], x2[N], y1[N], y2[N];
void init(){
    n = read(), m = read(), q = read();
    for(int i = 1; i <= n; i ++){
        x1[i] = read(), x2[i] = read(), y1[i] = read(), y2[i] = read();
        rowm[++ rmn] = {x1[i], x2[i], y1[i], 0, 1};
        rowm[++ rmn] = {x1[i], x2[i], y2[i] + 1, 0, -1};
    }
    for(int i = 1; i <= m; i ++){
        int op = read(), id = read(), d = read();
        if(d == 0) continue;
        int dd = (d > 0 ? 1 : -1);
        if(op == 1){
            int tmp[4] = {x1[id] + dd, x2[id] + dd, x1[id] + d, x2[id] + d};
            sort(tmp, tmp + 4);
            rowm[++ rmn] = {tmp[0], tmp[1], y1[id], 1, 1 - tmp[0]};
            rowm[++ rmn] = {tmp[1] + 1, tmp[2], y1[id], 0, tmp[1] - tmp[0] + 1};
            rowm[++ rmn] = {tmp[2] + 1, tmp[3], y1[id], -1, 1 + tmp[3]};
            rowm[++ rmn] = {tmp[0], tmp[1], y2[id] + 1, -1, tmp[0] - 1};
            rowm[++ rmn] = {tmp[1] + 1, tmp[2], y2[id] + 1, 0, tmp[0] - tmp[1] - 1};
            rowm[++ rmn] = {tmp[2] + 1, tmp[3], y2[id] + 1, 1, - tmp[3] - 1};
            x1[id] += d; x2[id] += d;
        }
        if(op == 2){
            int tmp[4] = {y1[id] + dd, y2[id] + dd, y1[id] + d, y2[id] + d};
            sort(tmp, tmp + 4);
            #ifdef db
            for(int i = 0; i < 4; i ++) printf("%d ", tmp[i]);
            printf("%d %d\n", x1[id], x2[id]);
            #endif
            colm[++ cmn] = {tmp[0], tmp[1], x1[id], 1, 1 - tmp[0]};
            colm[++ cmn] = {tmp[1] + 1, tmp[2], x1[id], 0, tmp[1] - tmp[0] + 1};
            colm[++ cmn] = {tmp[2] + 1, tmp[3], x1[id], -1, 1 + tmp[3]};
            colm[++ cmn] = {tmp[0], tmp[1], x2[id] + 1, -1, tmp[0] - 1};
            colm[++ cmn] = {tmp[1] + 1, tmp[2], x2[id] + 1, 0, tmp[0] - tmp[1] - 1};
            colm[++ cmn] = {tmp[2] + 1, tmp[3], x2[id] + 1, 1, - tmp[3] - 1};
            y1[id] += d; y2[id] += d;
        }
    }
    sort(rowm + 1, rowm + rmn + 1);
    sort(colm + 1, colm + cmn + 1);
    for(int i = 1; i <= q; i ++){
        int x = read(), y = read();
        rowq[y].emplace_back(make_pair(x, i));
        colq[x].emplace_back(make_pair(y, i));
    }
}
void print(){
    for(int i = 1; i <= q; i ++)
        printf("%lld\n", ans[i]);
}
int main(){
    init();
    solve_row();
    solve_col();
    print();
    return 0;
}
}
int main(){
    #ifndef db
    freopen("rectangle.in", "r", stdin);
    freopen("rectangle.out", "w", stdout);
    #endif
    return work::main();
}