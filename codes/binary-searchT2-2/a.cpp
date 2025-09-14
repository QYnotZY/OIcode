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
const int N = 2e5 + 10, inf = 1e9;
int n, m; ll k, b;
ll a[N], minn;
struct MDF {
    int l, r;
    bool operator<(const MDF &obj) const {
        return l < obj.l;
    }
} mdf[N];
ll tmp[N];
bool check(ll mid) {
    int res = 0;
    ll sum = 0, delta; for(int i = 1; i <= n; i ++) tmp[i] = 0;
    priority_queue<int> q;
    for(int i = 1, mi = 1; i <= n; i ++) {
        for(; mi <= m && mdf[mi].l <= i; mi ++) {
            q.push(mdf[mi].r);
        }
        delta = mid - a[i] - sum;
        while(q.size() && delta > 0) {
            int x = q.top(); q.pop();
            if(x < i) continue;
            delta -= b; ++ res; sum += b; tmp[x] -= b;
        }
        if(delta > 0) return false;
        sum += tmp[i];
    }
    return res <= k;
}
void Hutao() {
    n = read(), m = read(), k = read<ll>(), b = read<ll>();
    minn = inf;
    for(int i = 1; i <= n; i ++)
        minn = min(minn, a[i] = read<ll>());
    for(int i = 1; i <= m; i ++)
        mdf[i] = {read(), read()};
    sort(mdf + 1, mdf + m + 1);
    ll l = minn - 1, r = minn + k * b + 1;
    while(l + 1 < r) (check(l + r >> 1) ? l : r) = l + r >> 1;
    printf("%lld\n", l);
}
}
int main() {
    int t = read(); while(t --) Qiuyu3600::Hutao();
    return 0;
}