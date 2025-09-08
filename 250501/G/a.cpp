#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// inline char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
inline char gc() {return getchar();}
template<typename T>
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
inline T read() {return readnum<T>();}
char wc[50]; int top;
template<typename T>
inline void writenum(T x, char sp){
    if(!x) return putchar('0'), void(putchar(sp));
    if(x < 0) putchar('-'), x = ~x + 1;
    top = 0;
    for(; x; x /= 10) wc[top ++] = x % 10 ^ 48;
    while(top --) putchar(wc[top]);
    putchar(sp);
}
template<typename T = int>
inline void write(T x, char sp = '\n'){
    writenum(x, sp);
}
}
using FastIO::read;
using FastIO::write;
typedef long long ll;
const int N = 2e5 + 10, inf = 1e9;
namespace work {
namespace hjtt {
    int tot, head[N];
    struct node {
        int lc, rc;
        int sum;
        ll ssum;
    } tr[N * 60];
    int newnode() {
        return ++ tot;
    }
    void pushup(int p) {
        int &lc = tr[p].lc, &rc = tr[p].rc;
        tr[p].sum = tr[lc].sum + tr[rc].sum;
        tr[p].ssum = tr[lc].ssum + tr[rc].ssum;
    }
    void modify(int x, int np, int p, int l = 1, int r = inf) {
        tr[np] = tr[p];
        if(l == r)
            return tr[np].sum ++, tr[np].ssum += l, void();
        int mid = l + r >> 1;
        if(x <= mid)
            modify(x, tr[np].lc = newnode(), tr[p].lc, l, mid);
        else
            modify(x, tr[np].rc = newnode(), tr[p].rc, mid + 1, r);
        pushup(np);
    }
    ll query(int rk, int p, int l = 1, int r = inf) {
        if(!p) return 0;
        if(l == r)
            return 1ll * l * rk;
        int lsz = tr[tr[p].lc].sum, mid = l + r >> 1;
        if(rk <= lsz)
            return query(rk, tr[p].lc, l, mid);
        else
            return tr[tr[p].lc].ssum + query(rk - lsz, tr[p].rc, mid + 1, r);
    }
    void add(int ver, int x) {
        modify(x, head[ver] = newnode(), head[ver - 1]);
    }
    ll qry(int ver, int rk) {
        return query(rk, head[ver]);
    }
}
int n, q;
int a[N], b[N], p[N];
bool cmp(int x, int y) {
    return a[x] + b[x] > a[y] + b[y];
}
ll suma[N];
ll calc(int k, int p) {return suma[p + 1] - hjtt::qry(p, k);}
pair<int, int> qry[N];
void init() {
    n = read(), q = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read(), b[i] = read(), p[i] = i;
    sort(p + 1, p + n + 1, cmp);
    for(int i = n; i >= 1; i --)
        suma[i] = suma[i + 1] + a[p[i]];
    for(int i = 1; i <= n; i ++)
        hjtt::add(i, b[p[i]]);
    for(int i = 1; i <= q; i ++)
        qry[i].first = read(), qry[i].second = i;
    sort(qry + 1, qry + q + 1);
}
ll ans[N];
void solve(int ql = 1, int qr = q, int l = 0, int r = n) {
    if(ql > qr) return;
    int qmid = ql + qr >> 1;
    int mid; ll curans = - 1ll * inf * n;
    for(int i = max(l, qry[qmid].first); i <= r; i ++) {
        if(calc(qry[qmid].first, i) > curans)
            mid = i, curans = calc(qry[qmid].first, i);
    }
    ans[qry[qmid].second] = curans;
    solve(ql, qmid - 1, l, mid);
    solve(qmid + 1, qr, mid, r);
}
void print() {
    for(int i = 1; i <= q; i ++)
        write<ll>(ans[i]);
}
int Main() {
    init();
    solve();
    print();
    return 0;
}
}
int main() {
    return work::Main();
}