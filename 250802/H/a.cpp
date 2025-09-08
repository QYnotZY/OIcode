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
const int N = 150010;
struct line {
    ll k, b;
    line() {k = b = 0;}
    line(ll k0, ll b0) {k = k0; b = b0;}
    ll f(ll x) {return k * x + b;}
} ;
int n;
namespace lcsmt {
    line tr[N << 2]; bool vis[N << 2];
    void init(int p, int l, int r) {
        vis[p] = 0;
        if(l == r) return;
        int mid = l + r >> 1;
        init(p << 1, l, mid);
        init(p << 1 | 1, mid + 1, r);
    }
    void spread(line f, int p, int l, int r) {
        if(!vis[p]) {
            vis[p] = 1;
            tr[p] = f;
            return;
        }
        if(l == r) {
            if(tr[p].f(l) < f.f(l)) tr[p] = f;
            return;
        }
        int mid = l + r >> 1;
        if(tr[p].f(mid) < f.f(mid)) swap(tr[p], f);
        if(tr[p].f(l) < f.f(l)) spread(f, p << 1, l, mid);
        if(tr[p].f(r) < f.f(r)) spread(f, p << 1 | 1, mid + 1, r);
    }
    void update(line f, int p, int l, int r) {
        spread(f, p, l, r);
    }
    ll query(int x, int p, int l, int r) {
        ll res = vis[p] ? tr[p].f(x) : 0;
        if(l == r) return res;
        int mid = l + r >> 1;
        if(x <= mid) res = max(res, query(x, p << 1, l, mid));
        else res = max(res, query(x, p << 1 | 1, mid + 1, r));
        return res;
    }
}
ll a[N];
namespace g {
    int head[N], tail[N], tot;
    struct edge {
        int to;
        int nxt, pre;
    } e[N << 1];
    inline void add(int u, int v) {
        e[++ tot].to = v;
        e[tot].nxt = head[u];
        e[tot].pre = 0;
        if(head[u]) e[head[u]].pre = tot;
        else tail[u] = tot;
        head[u] = tot;
    }
}
ll ans;
bool del[N];
int rt;
int sz[N], sumsz, msz;
void find_root(int u, int f) {
    int maxsz = 0;
    sz[u] = 1;
    for(int i = g::head[u]; i; i = g::e[i].nxt) {
        int &v = g::e[i].to;
        if(v == f || del[v]) continue;
        find_root(v, u);
        sz[u] += sz[v];
        if(maxsz < sz[v]) maxsz = sz[v];
    }
    maxsz = max(maxsz, sumsz - sz[u]);
    if(msz > maxsz) msz = maxsz, rt = u;
}
int dep[N], maxdep;
int dfn[N], walk[N], top;
ll sum[N], up[N], down[N];
void getdis(int u, int f) {
    dep[u] = dep[f] + 1; maxdep = max(maxdep, dep[u]); sz[u] = 1;
    dfn[u] = ++ top, walk[top] = u;
    sum[u] = sum[f] + a[u]; up[u] = up[f] + sum[u]; down[u] = down[f] + dep[u] * a[u];
    for(int i = g::head[u]; i; i = g::e[i].nxt) {
        int &v = g::e[i].to;
        if(v == f || del[v]) continue;
        getdis(v, u);
        sz[u] += sz[v];
    }
}
void calc(int u) {
    ll tmp1, tmp2;
    maxdep = 1; top = 0;
    getdis(u, 0);
    lcsmt::init(1, 1, maxdep);
    lcsmt::update(line(a[u], a[u]), 1, 1, maxdep);
    for(int i = g::head[u]; i; i = g::e[i].nxt) {
        int &v = g::e[i].to;
        if(del[v]) continue;
        for(int j = dfn[v]; j ^ dfn[v] + sz[v]; j ++) {
            tmp1 = up[walk[j]] - dep[walk[j]] * a[u];
            tmp2 = dep[walk[j]] - 1;
            ans = max(ans, tmp1 + lcsmt::query(tmp2, 1, 1, maxdep));
        }
        for(int j = dfn[v]; j ^ dfn[v] + sz[v]; j ++) {
            tmp1 = down[walk[j]];
            tmp2 = sum[walk[j]];
            lcsmt::update(line(tmp2, tmp1), 1, 1, maxdep);
        }
    }
    lcsmt::init(1, 1, maxdep);
    for(int i = g::tail[u]; i; i = g::e[i].pre) {
        int &v = g::e[i].to;
        if(del[v]) continue;
        for(int j = dfn[v]; j ^ dfn[v] + sz[v]; j ++) {
            tmp1 = up[walk[j]];
            tmp2 = dep[walk[j]];
            ans = max(ans, tmp1 + lcsmt::query(tmp2, 1, 1, maxdep));
        }
        for(int j = dfn[v]; j ^ dfn[v] + sz[v]; j ++) {
            tmp1 = down[walk[j]] - sum[walk[j]];
            tmp2 = sum[walk[j]] - a[u];
            lcsmt::update(line(tmp2, tmp1), 1, 1, maxdep);
        }
    }
    ans = max(ans, a[u] + lcsmt::query(1, 1, 1, maxdep));
}
void devide(int u) {
    sumsz = msz = sz[u];
    find_root(u, 0);
    #ifdef db
    printf("%d %d\n", u, sz[u]);
    for(int i = 1; i <= n; i ++) printf("%d ", sz[i]); printf("\n");
    #endif
    calc(rt);
    del[rt] = 1;
    for(int i = g::head[rt]; i; i = g::e[i].nxt) {
        int &v = g::e[i].to;
        if(del[v]) continue;
        devide(v);
    }
}
void Hutao() {
    n = read();
    for(int i = 1, u, v; i < n; i ++) {
        u = read(), v = read();
        g::add(u, v); g::add(v, u);
    }
    for(int i = 1; i <= n; i ++) a[i] = read();
    sz[1] = n; devide(1);
    printf("%lld", ans);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}