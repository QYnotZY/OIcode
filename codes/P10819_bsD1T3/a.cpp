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
const int N = 5010;
const int inf = 0x1f1f1f1f;
int n, m, k, s1, s2, t1, t2;
vector<int> to[N];
bool vis[N]; int dis[N][N];
void bfs(int s) {
    memset(vis, 0, n + 1);
    for(int i = 1; i <= n; i ++) dis[s][i] = inf;
    dis[s][s] = 0;
    queue<int> q;
    q.push(s), vis[s] = 1;
    while(q.size()) {
        int u = q.front(); q.pop();
        for(auto v : to[u])
            if(!vis[v]) dis[s][v] = dis[s][u] + 1, q.push(v), vis[v] = 1;
    }
}
int rdis[N];
double ans;
inline double calc(int kx, int x) {
    return x ? 1.0 * (kx % x) / (2 + kx / x) + 1.0 * (x - kx % x) / (1 + kx / x) : 0;
}
double solve(int x, int y) {
    int l = -1, r = k, mid;
    while(l + 1 < r) {
        mid = l + r >> 1;
        if(calc(mid, x) * 2.0 + calc(k - mid, y) >= calc(mid + 1, x) * 2.0 + calc(k - mid - 1, y))
            l = mid;
        else r = mid;
    }
    return calc(r, x) * 2.0 + calc(k - r, y);
}
void Hutao() {
    n = read(), m = read(), k = read();
    for(int i = 1, u, v; i <= m; i ++) {
        u = read(), v = read();
        to[u].push_back(v), to[v].push_back(u);
    }
    s1 = read(), t1 = read(), s2 = read(), t2 = read();
    for(int i = 1; i <= n; i ++) bfs(i), rdis[i - 1] = inf;
    rdis[0] = dis[s1][t1] + dis[s2][t2];
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            if(dis[i][j] < n) rdis[dis[i][j]] = min(rdis[dis[i][j]], dis[s1][i] + dis[j][t1] + min(dis[s2][i] + dis[j][t2], dis[s2][j] + dis[i][t2]));
    ans = rdis[0];
    for(int i = 0; i < n; i ++) {
        if(rdis[i] > 4 * n) break;
        ans = min(ans, solve(i, rdis[i]));
    }
    printf("%.9lf", ans);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}