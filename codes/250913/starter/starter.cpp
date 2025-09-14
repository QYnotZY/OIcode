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
const int N = 2e5 + 10;
const ll inf = 1e15;
int n; ll a[N];
int pre[N], nxt[N];
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++) a[i] = read(), pre[i] = i - 1, nxt[i] = i + 1;
    pre[0] = 0, nxt[n + 1] = n + 1, a[0] = -inf, a[n + 1] = -inf;
    set<pair<ll, int>> s;
    for(int i = 1; i <= n; i ++) s.insert(make_pair(a[i], i));
    ll ans = 0;
    for(int k = 1; k <= n + 1 >> 1; k ++) {
        int u = s.rbegin()->second;
        ans += a[u];
        s.erase(make_pair(a[u], u));
        s.erase(make_pair(a[pre[u]], pre[u]));
        s.erase(make_pair(a[nxt[u]], nxt[u]));
        s.insert(make_pair(a[u] = a[pre[u]] + a[nxt[u]] - a[u], u));
        nxt[pre[pre[u]]] = u, pre[nxt[nxt[u]]] = u;
        pre[u] = pre[pre[u]], nxt[u] = nxt[nxt[u]];
        printf("%lld\n", ans);
    }
}
}
int main() {
    freopen("starter.in", "r", stdin);
    freopen("starter.out", "w", stdout);
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}