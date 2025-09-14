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
typedef long double ldb;
const int N = 3010;
const double inf = 3e11;
int n, m;
ldb dis[N];
vector<pair<int, double>> to[N];
int cnt[N], vis[N];
bool check(double dw) {
    queue<int> q;
    for(int i = 1; i <= n; i ++)
        dis[i] = 0, q.push(i), vis[i] = 1, cnt[i] = 0;
    while(q.size()) {
        int u = q.front(); q.pop(), vis[u] = 0;
        if(++ cnt[u] > n) return true;
        for(auto ele : to[u]) {
            int &v = ele.first; double &w = ele.second;
            if(dis[v] > dis[u] + w - dw) {
                dis[v] = dis[u] + w - dw;
                if(!vis[v]) q.push(v), vis[v] = 1;
            }
        }
    }
    return false;
}
void Hutao() {
    scanf("%d%d", &n, &m);
    int u, v; double w;
    for(int i = 1; i <= m; i ++) {
        scanf("%d%d%lf", &u, &v, &w);
        to[u].push_back(make_pair(v, w));
    }
    double l = -1e7, r = 1e7;
    for(int id = 1; id <= 55; id ++)
        (check((l + r) / 2) ? r : l) = (l + r) / 2;
    printf("%.8lf", l);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}