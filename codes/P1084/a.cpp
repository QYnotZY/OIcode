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
const int N = 5e4 + 10, logn = 16;
const ll inf = 0x1f1f1f1f1f1f1f1fll;
int n, m, cnt[N];
vector<pair<int, int>> e[N];
int fa[N][logn]; ll dep[N], dis[N][logn];
void dfs(int u = 1, int f = 0) {
    fa[u][0] = f;
    for(int i = 1; i < logn; i ++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1], dis[u][i] = dis[u][i - 1] + dis[fa[u][i - 1]][i - 1];
    for(auto &ele : e[u]) {
        int &v = ele.first, &w = ele.second;
        if(v == f) continue;
        dis[v][0] = w; dep[v] = dep[u] + w;
        dfs(v, u);
    }
}
int up(int u, ll d) {
    for(int i = logn - 1; ~i; -- i)
        if(dis[u][i] <= d) d -= dis[u][i], u = fa[u][i];
    return u;
}
bool vis[N];
bool dfschk(int u, int f) {
    if(vis[u]) return false;
    if(e[u].size() == 1) return true;
    for(auto &ele : e[u]) {
        int &v = ele.first;
        if(v == f) continue;
        if(dfschk(v, u)) return true;
    }
    return false;
}
ll mina[N];
pair<ll, int> a1[N]; int a1sz;
ll a[N], b[N]; int asz, bsz;
bool check(ll mid) {
    memset(vis, 0, n + 1);
    memset(mina, 0x1f, n + 1 << 3);
    a1sz = 0, asz = 0, bsz = 0;
    for(int i = 1, t; i <= n; i ++) if(cnt[i]) {
        t = up(i, min(mid, dep[i] - 1));
        if(mid >= dep[i]) {
            mina[t] = min(mina[t], mid - dep[i]);
            for(int j = 1; j <= cnt[i]; j ++) a1[++ a1sz] = make_pair(mid - dep[i], t);
        } else vis[t] = 1;
    }
    for(auto &ele : e[1]) {
        int &v = ele.first, &w = ele.second;
        if(dfschk(v, 1)) {
            if(mina[v] > w) {
                b[++ bsz] = w;
                mina[v] = inf;
            }
        } else mina[v] = inf;
    }
    for(int i = 1; i <= a1sz; i ++) {
        if(a1[i].first == mina[a1[i].second])
            mina[a1[i].second] = inf;
        else a[++ asz] = a1[i].first;
    }
    sort(a + 1, a + asz + 1), sort(b + 1, b + bsz + 1);
    for(int i = 1, j = 1, k; i <= bsz; i ++) {
        k = lower_bound(a + j, a + asz + 1, b[i]) - a;
        if(k > asz) return false;
        j = k + 1;
    }
    return true;
}
void Hutao() {
    n = read();
    for(int i = 1, u, v, w; i < n; i ++) {
        u = read(), v = read(), w = read();
        e[u].push_back(make_pair(v, w)), e[v].push_back(make_pair(u, w));
    }
    m = read();
    for(int i = 1; i <= m; i ++) ++ cnt[read()];
    dfs();
    ll ub = 5e13, l = -1, r = ub;
    while(l + 1 < r) (check(l + r >> 1) ? r : l) = l + r >> 1;
    printf(r ^ ub ? "%lld" : "-1", r);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}