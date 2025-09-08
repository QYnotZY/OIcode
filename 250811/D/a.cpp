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
const int N = 2.5e5 + 10;
const ll inf = 2e15;
struct smt {
    static int n;
    struct node {
        ll maxx;
        ll plustag, maxtag;
        node() {maxx = plustag = 0; maxtag = -inf;}
    } tr[N << 2];
    void pushup(int p) {tr[p].maxx = max(tr[p << 1].maxx, tr[p << 1 | 1].maxx);}
    void upd1(int p, ll plustag, ll maxtag) {
        tr[p].maxx += plustag, tr[p].plustag += plustag, tr[p].maxtag += plustag;
        tr[p].maxx = max(tr[p].maxx, maxtag), tr[p].maxtag = max(tr[p].maxtag, maxtag);
    }
    void pushdown(int p) {upd1(p << 1, tr[p].plustag, tr[p].maxtag), upd1(p << 1 | 1, tr[p].plustag, tr[p].maxtag); tr[p].plustag = 0, tr[p].maxtag = -inf;}
    void update(int ql, int qr, ll v, int p = 1, int l = 1, int r = n) {
        if(ql <= l && r <= qr) return upd1(p, v, 0);
        int mid = l + r >> 1;
        pushdown(p);
        if(ql <= mid) update(ql, qr, v, p << 1, l, mid);
        if(qr > mid) update(ql, qr, v, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    ll query(int x, int p = 1, int l = 1, int r = n) {
        if(l == r) return tr[p].maxx;
        int mid = l + r >> 1;
        pushdown(p);
        if(x <= mid) return query(x, p << 1, l, mid);
        else return query(x, p << 1 | 1, mid + 1, r);
    }
} t0, t1;
int smt::n;
struct MDF {
    int l, r, col, cnt;
} mdf[N]; int msz;
struct QRY {
    int t, x; ll cnt;
} qry[N]; int qsz;
int p[N], tmp[N];
bool cmp(int x, int y) {
    return qry[x].t < qry[y].t;
}
int ans[N];
namespace bit {
    int n; ll tr[N], res;
    inline int lowbit(int x) {return x & -x;}
    inline void init() {memset(tr, 0, sizeof tr);}
    inline void add(int x, int v) {for(; x <= n; x += lowbit(x)) tr[x] += v;}
    inline ll query(int x) {for(res = 0; x; x -= lowbit(x)) res += tr[x]; return res;}
}
void solve(int l, int r, int ql, int qr) {
    if(l == r) {
        for(int i = ql; i <= qr; i ++)
            ans[p[i]] = mdf[l].col;
        return;
    }
    sort(p + ql, p + qr + 1, cmp);
    int mid = l + r >> 1, i = ql, j = qr;
    for(int mi = l, qi = ql; ; mi ++) {
        for(; qi <= qr && qry[p[qi]].t < mi; qi ++) {
            ll key = bit::query(qry[p[qi]].x);
            if(qry[p[qi]].cnt <= key) tmp[i ++] = p[qi];
            else tmp[j --] = p[qi], qry[p[qi]].cnt -= key;
        }
        if(mi <= mid) bit::add(mdf[mi].l, mdf[mi].cnt), bit::add(mdf[mi].r + 1, -mdf[mi].cnt);
        if(mi == mid) {
            for(; qi <= qr; qi ++) {
                ll key = bit::query(qry[p[qi]].x);
                if(qry[p[qi]].cnt <= key) tmp[i ++] = p[qi];
                else tmp[j --] = p[qi], qry[p[qi]].cnt -= key;
            }
            break;
        }
    }
    for(int k = ql; k <= qr; k ++) p[k] = tmp[k];
    for(int k = l; k <= mid; k ++)
        bit::add(mdf[k].l, -mdf[k].cnt), bit::add(mdf[k].r + 1, mdf[k].cnt);
    solve(l, mid, ql, j), solve(mid + 1, r, i, qr);
}
int n, m, q;
void Hutao() {
    smt::n = bit::n = n = read(), m = read(), q = read();
    int op, l, r, c, k, a; ll b;
    for(int i = 1; i <= q; i ++) {
        op = read();
        if(op == 1) {
            l = read(), r = read(), c = read(), k = read();
            mdf[++ msz] = MDF{l, r, c, k};
            t0.update(l, r, k); t1.update(l, r, k);
        } else if(op == 2) {
            l = read(), r = read(), k = read();
            t1.update(l, r, -k);
        } else {
            a = read(), b = read<ll>();
            qry[++ qsz] = QRY{msz, a, b + t0.query(a) - t1.query(a)};
        }
    }
    for(int i = 1; i <= qsz; i ++) p[i] = i;
    solve(1, msz + 1, 1, qsz);
    for(int i = 1; i <= qsz; i ++) printf("%d\n", ans[i]);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}