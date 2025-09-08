#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
char buf[1 << 20], *p1, *p2;
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++)
template<typename T = int>
inline T read(){
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
}
using FastIO::read;
typedef long long ll;
namespace work {
const int N = 1e5 + 1000, sqN1 = 405, sqN2 = 670;
int T, n, q, a[N];
int pre[N], nxt[N], lst[N];
set<int> pos[N];
int bsz1, bcnt1, bsz2, bcnt2;
inline int block1_id(int x) {return x / bsz1 + 1;}
inline int block2_id(int x) {return x / bsz2 + 1;}
inline int block1_l(int x) {return (x - 1) * bsz1;}
inline int block2_l(int x) {return (x - 1) * bsz2;}
inline int block1_r(int x) {return x * bsz1 - 1;}
inline int block2_r(int x) {return x * bsz2 - 1;}
int y[N][2], v[N][2], value[sqN1][N][2], sum_in_block[sqN1][N][2], sum_of_block[sqN1][sqN2][2];
void build() {
    for(int i = 0; i <= block2_r(bcnt2); i ++)
        y[i][0] = n + 1, y[i][1] = 0, v[i][0] = v[i][1] = n + 1;
    for(int i = 1; i <= bcnt1; i ++) {
        for(int j = 0; j <= block2_r(bcnt2); j ++)
            sum_in_block[i][j][0] = sum_in_block[i][j][1] = n + 1, value[i][j][0] = value[i][j][1] = n + 1;
        for(int j = 0; j <= bcnt2 + 1; j ++)
            sum_of_block[i][j][0] = sum_of_block[i][j][1] = n + 1;
    }
}
void update(int typ, int x, int y1, int y2, int val) {
    y[x][typ] = y2, v[x][typ] = val;
    int xid = block1_id(x), y1id = block2_id(y1), y2id = block2_id(y2);
    if(typ == 0) {
        value[xid][y1][0] = n + 1;
        for(int i = block1_l(xid); i <= block1_r(xid); i ++)
            if(y[i][0] == y1) value[xid][y1][0] = min(value[xid][y1][0], v[i][0]);
        value[xid][y2][0] = n + 1;
        for(int i = block1_l(xid); i <= block1_r(xid); i ++)
            if(y[i][0] == y2) value[xid][y2][0] = min(value[xid][y2][0], v[i][0]);
        for(int i = y1; i <= block2_r(y1id); i ++)
            sum_in_block[xid][i][0] = min(i % bsz2 ? sum_in_block[xid][i - 1][0] : n + 1, value[xid][i][0]);
        for(int i = y2; i <= block2_r(y2id); i ++)
            sum_in_block[xid][i][0] = min(i % bsz2 ? sum_in_block[xid][i - 1][0] : n + 1, value[xid][i][0]);
        for(int i = min(y1id, y2id); i <= bcnt2; i ++)
            sum_of_block[xid][i][0] = min(i ^ 1 ? sum_of_block[xid][i - 1][0] : n + 1, sum_in_block[xid][block2_r(i)][0]);
    } else {
        value[xid][y1][1] = n + 1;
        for(int i = block1_l(xid); i <= block1_r(xid); i ++)
            if(y[i][1] == y1) value[xid][y1][1] = min(value[xid][y1][1], v[i][1]);
        value[xid][y2][1] = n + 1;
        for(int i = block1_l(xid); i <= block1_r(xid); i ++)
            if(y[i][1] == y2) value[xid][y2][1] = min(value[xid][y2][1], v[i][1]);
        for(int i = y1; i >= block2_l(y1id); i --)
            sum_in_block[xid][i][1] = min((i + 1) % bsz2 ? sum_in_block[xid][i + 1][1] : n + 1, value[xid][i][1]);
        for(int i = y2; i >= block2_l(y2id); i --)
            sum_in_block[xid][i][1] = min((i + 1) % bsz2 ? sum_in_block[xid][i + 1][1] : n + 1, value[xid][i][1]);
        for(int i = max(y1id, y2id); i; i --)
            sum_of_block[xid][i][1] = min(i ^ bcnt2 ? sum_of_block[xid][i + 1][1] : n + 1, sum_in_block[xid][block2_l(i)][1]);
    }
}
int query(int typ, int x1, int x2, int y0) {
    int i, id; int res = n + 1; int y0id = block2_id(y0);
    if(x1 > x2) return res;
    if(typ == 0) {
        for(i = x1; i % bsz1 && i <= x2; i ++)
            if(y[i][0] <= y0) res = min(res, v[i][0]);
        if(i > x2) return res;
        for(id = block1_id(i); id < block1_id(x2); id ++)
            res = min(res, min(sum_of_block[id][y0id - 1][0], sum_in_block[id][y0][0]));
        for(i = block1_l(id); i <= x2; i ++)
            if(y[i][0] <= y0) res = min(res, v[i][0]);
    } else { 
        for(i = x1; i % bsz1 && i <= x2; i ++)
            if(y[i][1] >= y0) res = min(res, v[i][1]);
        if(i > x2) return res;
        for(id = block1_id(i); id < block1_id(x2); id ++)
            res = min(res, min(sum_of_block[id][y0id + 1][1], sum_in_block[id][y0][1]));
        for(i = block1_l(id); i <= x2; i ++)
            if(y[i][1] >= y0) res = min(res, v[i][1]);
    }
    return res;
}
int buc[N];
set<int> non;
void Hutao() {
    T = read(), n = read(), q = read();
    bsz1 = 250, bsz2 = 200;
    bcnt1 = block1_id(n + 1), bcnt2 = block2_id(n + 1);
    build();
    for(int i = 0; i <= n; i ++) {
        buc[i] = 0, non.insert(i);
        lst[i] = 0;
        pos[i].insert(0), pos[i].insert(n + 1);
    }
    for(int i = 1; i <= n; i ++) {
        a[i] = read();
        if(buc[a[i]] == 0) non.erase(a[i]);
        ++ buc[a[i]];
        pos[a[i]].insert(i);
        pre[i] = lst[a[i]];
        update(0, i, n + 1, lst[a[i]], a[i]);
        if(lst[a[i]]){
            nxt[lst[a[i]]] = i;
            update(1, lst[a[i]], 0, i, a[i]);
        }
        lst[a[i]] = i;
    }
    for(int i = 0; i <= n; i ++) {
        if(!lst[i]) continue;
        nxt[lst[i]] = n + 1;
        update(1, lst[i], 0, n + 1, i);
    }
    int lstans = 0;
    for(; q --;) {
        int op = read(), x = read(), y = read();
        if(op == 0) {
            x = ll(x + T * lstans) % n + 1, y = ll(y + T * lstans) % n;
            if(buc[y] == 0) non.erase(y);
            ++ buc[y], -- buc[a[x]];
            if(buc[a[x]] == 0) non.insert(a[x]);
            pos[a[x]].erase(x);
            auto its = pos[a[x]].lower_bound(x); auto itp = (-- its) ++;
            update(0, *its, pre[*its], *itp, a[x]); pre[*its] = *itp;
            update(1, *itp, nxt[*itp], *its, a[x]); nxt[*itp] = *its;
            its = pos[y].lower_bound(x); itp = (-- its) ++;
            update(0, *its, pre[*its], x, y); pre[*its] = x;
            update(0, x, pre[x], *itp, y); pre[x] = *itp;
            update(1, *itp, nxt[*itp], x, y); nxt[*itp] = x;
            update(1, x, nxt[x], *its, y); nxt[x] = *its;
            pos[y].insert(x);
            a[x] = y;
        } else {
            x = ll(x + T * lstans) % n + 1, y = ll(y + T * lstans) % n + 1;
            if(x > y) swap(x, y);
            lstans = min(query(0, y + 1, n, x - 1), query(1, 1, x - 1, y + 1));
            lstans = min(lstans, *non.begin());
            printf("%d\n", lstans);
        }
    }
}
}
int main() {
    #ifndef db
    freopen("mex.in", "r", stdin);
    freopen("mex.out", "w", stdout);
    #endif
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}