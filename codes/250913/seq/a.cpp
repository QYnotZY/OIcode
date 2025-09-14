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
ll n, m, a[N], sum[N];
ll calc1(ll mid) {
    int k = lower_bound(a + 1, a + m + 1, n - mid) - a;
    return sum[m] - sum[k - 1] - (m - k + 1) * (n - mid);
}
ll solve1(ll cur) {
    ll le = 0, ri = n + 1;
    while(le + 1 < ri) (calc1(le + ri >> 1) <= cur * (le + ri >> 1) ? le : ri) = le + ri >> 1;
    return le;
}
ll calc2(ll mid) {
    int k = lower_bound(a + 1, a + m + 1, mid) - a;
    return sum[k - 1] + (m - k + 1) * mid;
}
ll solve2(ll cur) {
    ll le = 0, ri = n + 1;
    while(le + 1 < ri) (calc2(le + ri >> 1) >= cur * (le + ri >> 1) ? le : ri) = le + ri >> 1;
    return le;
}
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= m; i ++) a[i] = read();
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= m; i ++) sum[i] = sum[i - 1] + a[i];
    ll bound = sum[m] / n;
    for(int i = 1; i <= bound; i ++) {
        printf("%lld ", solve1(i));
    }
    for(int i = bound + 1; i <= m; i ++) {
        printf("%lld ", solve2(i));
    }
}
}
int main() {
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}