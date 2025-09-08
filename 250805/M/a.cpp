#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// inline char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
inline char gc() {return getchar();}
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
using FastIO::readch;
typedef long long ll;
namespace work {
const int N = 1e5 + 10, M = 3e5 + 10, inf = 1e9;
int n, m;
int a[N];
namespace bit {
    int tr[N], res;
    inline int lowbit(int x) {return x & -x;}
    void init() {for(int i = 1; i <= n; i ++) tr[i] = inf;}
    void add(int x, int v) {for(; x; x -= lowbit(x)) tr[x] = min(tr[x], v);}
    int query(int x) {for(res = inf; x <= n; x += lowbit(x)) res = min(res, tr[x]); return res;}
}
namespace smt {
    int rt = 1, tot = 1;
    struct node {
        int maxx;
        int lc, rc;
    } tr[N * 20];
    void pushup(int p) {
        tr[p].maxx = max(tr[tr[p].lc].maxx, tr[tr[p].rc].maxx);
    }
    void update(int x, int v, int p = rt, int l = 0, int r = inf) {
        if(l == r) return void(tr[p].maxx = max(tr[p].maxx, v));
        int mid = l + r >> 1;
        if(x <= mid) {if(!tr[p].lc) tr[p].lc = ++ tot; update(x, v, tr[p].lc, l, mid);}
        else {if(!tr[p].rc) tr[p].rc = ++ tot; update(x, v, tr[p].rc, mid + 1, r);}
        pushup(p);
    }
    int query(int ql, int qr, int p = rt, int l = 0, int r = inf) {
        if(ql > qr || !p) return 0;
        if(ql <= l && r <= qr) return tr[p].maxx;
        int mid = l + r >> 1; int res = 0;
        if(ql <= mid && tr[p].lc) res = max(res, query(ql, qr, tr[p].lc, l, mid));
        if(qr > mid && tr[p].rc) res = max(res, query(ql, qr, tr[p].rc, mid + 1, r));
        return res; 
    }
}
struct QRY {
    int l, r, id;
    bool operator < (const QRY &obj) const {
        return r < obj.r;
    }
} qry[M];
int ans[M];
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++) a[i] = read();
    m = read();
    for(int i = 1; i <= m; i ++)
        qry[i].l = read(), qry[i].r = read(), qry[i].id = i;
    sort(qry + 1, qry + m + 1);
    bit::init();
    for(int r = 1, qi = 1; r <= n; r ++) {
        for(int res = smt::query(0, a[r]); res; res = smt::query((a[res] + a[r] + 2) >> 1, a[r]))
            bit::add(res, a[r] - a[res]);
        for(int res = smt::query(a[r], inf); res; res = smt::query(a[r], (a[r] + a[res] - 1) >> 1))
            bit::add(res, a[res] - a[r]);
        smt::update(a[r], r);
        for(; qi <= m && qry[qi].r <= r; qi ++) ans[qry[qi].id] = bit::query(qry[qi].l);
    }
    for(int i = 1; i <= m; i ++) printf("%d\n", ans[i]);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}