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
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
int n, m;
vector<pair<int, int> > e[N], qry[N];
int ans[N];
int fa[N], dep[N], hson[N], maxdep[N];
int dis[N];
void dfs1(int u, int f) {
    fa[u] = f, dep[u] = dep[f] + 1, hson[u] = 0, maxdep[u] = dep[u];
    for(auto ele : e[u]) {
        int &v = ele.first, &w = ele.second;
        if(v == f) continue;
        dis[v] = Add(dis[u], w);
        dfs1(v, u);
        if(maxdep[v] > maxdep[u]) maxdep[u] = maxdep[v], hson[u] = v;
    }
}
int dfn[N], walk[N], totdfn;
int *f[N], *g[N], *h[N], pf[N], pg[N], ph[N];
void dfs2(int u) {
    walk[dfn[u] = ++ totdfn] = u;
    f[u] = pf + dfn[u], g[u] = pg + dfn[u], h[u] = ph + dfn[u];
    f[u][0] = 0, g[u][0] = dis[u], h[u][0] = 1;
    if(hson[u]) dfs2(hson[u]);
    for(auto ele : e[u]) {
        int &v = ele.first, &w = ele.second;
        if(v == fa[u] || v == hson[u]) continue;
        dfs2(v);
        for(int i = 1, tmp1, tmp2; i <= maxdep[v] - dep[v] + 1; i ++) {
            tmp1 = Mult(h[v][i - 1], Minus(g[u][i], Mult(dis[u], h[u][i])));
            tmp2 = Mult(h[u][i], Minus(g[v][i - 1], Mult(dis[u], h[v][i - 1])));
            f[u][i] = Add(Add(f[u][i], f[v][i - 1]), Add(tmp1, tmp2));
            g[u][i] = Add(g[u][i], g[v][i - 1]);
            h[u][i] = Add(h[u][i], h[v][i - 1]);
        }
    }
    for(auto q : qry[u]) {
        if(q.second > maxdep[u] - dep[u]) ans[q.first] = 0;
        else ans[q.first] = f[u][q.second];
    }
}
void Hutao() {
    n = read(), m = read();
    for(int i = 1, u, v, w; i < n; i ++) {
        u = read(), v = read(), w = read();
        e[u].push_back(make_pair(v, w));
        e[v].push_back(make_pair(u, w));
    }
    for(int i = 1, u, k; i <= m; i ++) {
        u = read(), k = read();
        qry[u].push_back(make_pair(i, k));
    }
    dfs1(1, 0);
    dfs2(1);
    for(int i = 1; i <= m; i ++) printf("%d\n", ans[i]);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}