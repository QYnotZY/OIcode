#include "bits/stdc++.h"
using namespace std;
namespace FastIO {
    template<typename T = int> T read() {
        char ch = getchar(); bool neg = 0; T res = 0;
        for(; !('0' <= ch && ch <= '9'); ch = getchar()) if(ch == '-') neg = !neg;
        for(; ('0' <= ch && ch <= '9'); ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ 48);
        return neg ? ~res + 1 : res;
    }
    char readch(bool acsp = 0) {
        char ch = getchar(); for(; !(33 - acsp <= ch && ch < 127); ch = getchar()); return ch;
    }
} using namespace FastIO;
typedef long long ll;
namespace Qiuyu3600 {
const int N = 1e4 + 10, M = 5e4 + 10, logn = 14;
int n, m;
struct edge {
    int u, v, w;
    bool operator<(const edge &obj) const {
        return w > obj.w;
    }
} ed[M];
int q;
struct node {int fa, lc, rc, w;} tr1[N << 1];
int tot;
namespace dsu {
    int fa[N], id[N];
    void init(int n) {
        for(int i = 1; i <= n; i ++)
            fa[i] = id[i] = i;
    }
    int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
    void merge(int x, int y, int z) {
        x = find(x), y = find(y);
        if(x == y) return;
        tr1[id[x]].fa = tr1[id[y]].fa = ++ tot;
        tr1[tot].lc = id[x], tr1[tot].rc = id[y];
        tr1[tot].w = z;
        fa[y] = x, id[x] = tot;
    }
}
int fa1[N << 1][logn], dep1[N << 1], rt1[N << 1];
void dfs(int u, int f = 0) {
    fa1[u][0] = f, dep1[u] = dep1[f] + 1, rt1[u] = f ? rt1[f] : u;
    for(int i = 1; i < logn; i ++) fa1[u][i] = fa1[fa1[u][i - 1]][i - 1];
    if(tr1[u].lc) dfs(tr1[u].lc, u);
    if(tr1[u].rc) dfs(tr1[u].rc, u);
}
int lca(int u, int v) {
    if(dep1[u] > dep1[v]) swap(u, v);
    for(int i = logn - 1; ~i; -- i)
        if(dep1[v] - dep1[u] >= 1 << i) v = fa1[v][i];
    if(u == v) return u;
    for(int i = logn - 1; ~i; -- i)
        if(fa1[u][i] ^ fa1[v][i]) u = fa1[u][i], v = fa1[v][i];
    return fa1[u][0];
}
int query(int u, int v) {
    return rt1[u] == rt1[v] ? tr1[lca(u, v)].w : -1;
}
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= m; i ++)
        ed[i] = {read(), read(), read()};
    sort(ed + 1, ed + m + 1);
    dsu::init(n); tot = n;
    for(int i = 1; i <= m; i ++)
        dsu::merge(ed[i].u, ed[i].v, ed[i].w);
    for(int i = 1; i <= tot; i ++) {
        if(!tr1[i].fa) dfs(i);
    }
    q = read();
    for(int i = 1; i <= q; i ++)
        printf("%d\n", query(read(), read()));
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}