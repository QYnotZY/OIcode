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
const int N = 1e5 + 10, M = 2e5 + 10, logN = 32;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int n, m, k, logkw;
int pwk[logN];
struct edge {int u, v, w;} ed[M];
int id[logN][N], idtot;
vector<pair<int, int>> to[N * logN];
bool vis[N * logN];
ll dis[N * logN];
int s, t;
void dij() {
    memset(dis, 0x3f, idtot + 1 << 3);
    dis[id[0][s]] = 0;
    priority_queue<pair<ll, int>> q;
    q.push(make_pair(0ll, id[0][s]));
    while(q.size()) {
        int u = q.top().second; q.pop();
        if(vis[u]) continue; vis[u] = 1;
        for(auto &ele : to[u]) {
            int &v = ele.first, &w = ele.second;
            if(dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push({-dis[v], v});
            }
        }
    }
}
void Case_k_1() {
    for(int i = 1; i <= n; i ++)
        id[0][i] = i;
    idtot = n;
    for(int i = 1; i <= m; i ++)
        to[ed[i].u].push_back(make_pair(ed[i].v, 1)), to[ed[i].v].push_back(make_pair(ed[i].u, 1));
    dij();
    printf("%lld", dis[t]);
}
void Hutao() {
    clock_t start = clock();
    n = read(), m = read(), k = read();
    int maxw = 0;
    for(int i = 1; i <= m; i ++) {
        ed[i] = {read(), read(), read()};
        maxw = max(maxw, ed[i].w);
    }
    s = read(), t = read();
    if(k == 1) return Case_k_1();
    pwk[0] = 1; while(maxw > k) {maxw /= k; ++ logkw; pwk[logkw] = pwk[logkw - 1] * k;}
    for(int i = 0; i <= logkw + 1; i ++) {
        for(int j = 1; j <= n; j ++) id[i][j] = ++ idtot;
        for(int j = 1; j <= m; j ++) {
            to[id[i][ed[j].u]].push_back(make_pair(id[i][ed[j].v], ed[j].w));
            to[id[i][ed[j].v]].push_back(make_pair(id[i][ed[j].u], ed[j].w));
        }
        if(i) for(int j = 1; j <= m; j ++) {
            to[id[i - 1][ed[j].u]].push_back(make_pair(id[i][ed[j].v], pwk[i - 1]));
            to[id[i - 1][ed[j].v]].push_back(make_pair(id[i][ed[j].u], pwk[i - 1]));
        }
    }
    dij();
    ll ans = inf;
    for(int i = 0; i <= logkw + 1; i ++)
        ans = min(ans, dis[id[i][t]]);
    printf("%lld", ans);
}
}
int main() {
    // freopen("sum.in", "r", stdin);
    // freopen("sum.out", "w", stdout);
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}