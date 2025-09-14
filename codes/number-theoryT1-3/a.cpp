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
const int N = 1e5 + 10;
ll x, y, z, h;
ll dis[N];
bitset<N> vis;
void dij() {
    memset(dis, 0x7f, z << 3); dis[1] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    q.push(make_pair(0, 1));
    while(q.size()) {
        int u = q.top().second; q.pop();
        if(vis[u]) continue; vis[u] = 1;
        if(!vis[(u + x) % z]) {
            ll w = (u + x) / z;
            if(dis[(u + x) % z] > dis[u] + w) {
                dis[(u + x) % z] = dis[u] + w;
                q.push(make_pair(dis[(u + x) % z], (u + x) % z));
            }
        }
        if(!vis[(u + y) % z]) {
            ll w = (u + y) / z;
            if(dis[(u + y) % z] > dis[u] + w) {
                dis[(u + y) % z] = dis[u] + w;
                q.push(make_pair(dis[(u + y) % z], (u + y) % z));
            }
        }
    }
    dis[z] = dis[0] - 1;
}
ll ans = 0;
void Hutao() {
    h = read<ll>();
    x = read<ll>(), y = read<ll>(), z = read<ll>();
    dij();
    for(int i = 1; i <= z; i ++) {
        if(dis[i] <= h / z && i <= h % z) ++ ans;
        ans += max(h / z - dis[i], 0ll);
        #ifdef db
        printf("%lld ", max(0ll, h / z - dis[i]));
        #endif
    }
    printf("%lld\n", ans);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}