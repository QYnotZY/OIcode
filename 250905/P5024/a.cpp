#include "bits/stdc++.h"
using namespace std;
namespace FastIO {
    template <typename T = int> T read() {
        char ch = '\0'; bool f = 0; T res = 0;
        for(; !('0' <= ch && ch <= '9'); ch = getchar()) if(ch == '-') f = !f;
        for(; '0' <= ch && ch <= '9'; ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ '0');
        return f ? ~res + 1 : res;
    }
    char readch(const int acsp = 0) {
        char ch = '\0';
        for(; !(33 - acsp <= ch && ch < 127); ch = getchar()) ;
        return ch;
    }
} using FastIO::read; using FastIO::readch;
typedef long long ll;
namespace Qiuyu3600 {
#define rint register int
const int N = 1e5 + 10;
const ll inf = 1e11;
int n, m;
ll a[N];
vector<int> to[N];
int fa[N], dep[N], sz[N], hson[N];
int dfn[N], walk[N], dfntot, top[N];
struct matrix {
    int n, m; ll a[3][3];
    matrix() {}
    matrix(ll a1, ll a2) {n = 2, m = 1; a[1][1] = a1, a[2][1] = a2;}
    void init(int n0, int m0, int typ) {
        n = n0, m = m0;
        for(rint i = 1; i <= n; i ++)
            for(rint j = 1; j <= m; j ++)
                a[i][j] = inf;
        if(typ) a[1][1] = a[2][2] = 0;
    }
    void set(ll a11, ll a12, ll a21, ll a22) {
        n = m = 2;
        a[1][1] = a11, a[1][2] = a12, a[2][1] = a21, a[2][2] = a22;
    }
    matrix operator *(const matrix& obj) const {
        matrix res; res.init(n, obj.m, 0);
        for(rint i = 1; i <= n; i ++)
            for(rint j = 1; j <= obj.m; j ++)
                for(rint k = 1; k <= m; k ++)
                    res.a[i][j] = min(res.a[i][j], a[i][k] + obj.a[k][j]);
        return res;
    }
    void print() {
        for(int i = 1; i <= n; i ++) {
            for(int j = 1; j <= m; j ++)
                printf("%lld ", a[i][j]);
            printf("\n");
        }
    }
} ;
ll dp[N][2], ddp[N][2], stat[N][4];
struct node {
    int fa, lc, rc;
    matrix val, sum;
} tr[N];
void dfs(int u = 1, int f = 0) {
    fa[u] = f, dep[u] = dep[f] + 1, sz[u] = 1, hson[u] = 0;
    dp[u][0] = 0, dp[u][1] = a[u];
    for(auto v : to[u]) {
        if(v == f) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if(sz[v] > sz[hson[u]]) hson[u] = v;
        dp[u][0] += dp[v][1];
        dp[u][1] += min(dp[v][0], dp[v][1]);
    }
}
void getval(int p) {
    ll tmp0 = dp[p][0] - dp[hson[p]][1];
    ll tmp1 = dp[p][1] - min(dp[hson[p]][0], dp[hson[p]][1]);
    tie(stat[p][0], stat[p][1], stat[p][2], stat[p][3]) = tie(inf, tmp0, tmp1, tmp1);
    tr[p].val.set(stat[p][0], stat[p][1], stat[p][2], stat[p][3]);
}
void pushup(int p) {
    int &lc = tr[p].lc, &rc = tr[p].rc;
    tr[p].sum = tr[lc].sum * tr[p].val * tr[rc].sum;
}
int buildc(int dfnl, int dfnr) {
    if(dfnl > dfnr) return 0;
    int sum = 0, cur = 0;
    for(int i = dfnl; i <= dfnr; i ++)
        sum += sz[walk[i]] - sz[hson[walk[i]]];
    int mid;
    for(int i = dfnl; i <= dfnr; i ++) {
        cur += sz[walk[i]] - sz[hson[walk[i]]];
        if(cur << 1 >= sum) {mid = i; break;}
    }
    int u = walk[mid], lc = buildc(dfnl, mid - 1), rc = buildc(mid + 1, dfnr);
    tr[u].lc = lc, tr[u].rc = rc; tr[lc].fa = tr[rc].fa = u;
    getval(u); pushup(u);
    return u;
}
int build(int u = 1) {
    int x, v;
    for(x = u; x; v = x, x = hson[x]) top[x] = u, walk[dfn[x] = ++ dfntot] = x;
    for(x = v; x ^ fa[u]; x = fa[x]) {
        for(auto y : to[x]) {
            if(y == fa[x] || y == hson[x]) continue;
            tr[build(y)].fa = x;
        }
    }
    return buildc(dfn[u], dfn[v]);
}
int rt;
void init_pr() {
    tr[0].sum.init(2, 2, 1);
    for(int i = 1; i <= n; i ++)
        ddp[i][0] = dp[i][0], ddp[i][1] = dp[i][1];
}
ll query_pr() {
    matrix ans = tr[rt].sum * matrix(0, 0);
    return min(ans.a[1][1], ans.a[2][1]);
}
inline bool isroot(int u) {return tr[tr[u].fa].lc ^ u && tr[tr[u].fa].rc ^ u;}
void update_pr(int u) {
    pushup(u);
    int v = u; matrix tmp;
    for(u = tr[u].fa; u; v = u, u = tr[u].fa) {
        if(isroot(v)) {
            tmp = tr[v].sum * matrix(0, 0);
            ll d0 = tmp.a[2][1] - ddp[top[v]][1];
            ll d1 = min(tmp.a[1][1], tmp.a[2][1]) - min(ddp[top[v]][0], ddp[top[v]][1]);
            ddp[top[v]][0] = tmp.a[1][1], ddp[top[v]][1] = tmp.a[2][1];
            tr[u].val.a[1][2] += d0;
            tr[u].val.a[2][1] += d1;
            tr[u].val.a[2][2] += d1;
        }
        pushup(u);
    }
}
void undo_pr(int u) {
    for(; u; u = tr[u].fa) {
        if(isroot(u)) {
            ddp[top[u]][0] = dp[top[u]][0];
            ddp[top[u]][1] = dp[top[u]][1];
        }
        tr[u].val.set(stat[u][0], stat[u][1], stat[u][2], stat[u][3]);
        pushup(u);
    }
}
void query(int a, int x, int b, int y) {
    if(x) tr[a].val.a[1][1] = tr[a].val.a[1][2] = inf;
    else tr[a].val.a[2][1] = tr[a].val.a[2][2] = inf;
    update_pr(a);
    if(y) tr[b].val.a[1][1] = tr[b].val.a[1][2] = inf;
    else tr[b].val.a[2][1] = tr[b].val.a[2][2] = inf;
    update_pr(b);
    printf("%lld\n", query_pr());
    undo_pr(a);
    undo_pr(b);
}
void Hutao() {
    n = read(), m = read(), read();
    for(int i = 1; i <= n; i ++) a[i] = read();
    for(int i = 1, u, v; i < n; i ++) {
        u = read(), v = read();
        to[u].push_back(v), to[v].push_back(u);
    }
    dfs(); init_pr(); rt = build();
    for(int i = 1, a, x, b, y; i <= m; i ++) {
        a = read(), x = read(), b = read(), y = read();
        if(!x && !y && (fa[a] == b || fa[b] == a)) {
            printf("-1\n");
        } else {
            query(a, x, b, y);
        }
    }
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}