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
const int N = 2e5 + 10;
int n, k;
ll a[N], sum;
bool Skirk(ll mid) {
    ll res = 0;
    for(int i = 1; i <= n; i ++) res += min(a[i], mid);
    return res >= k * mid;
}
void Hutao() {
    n = read(), k = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read(), sum += a[i];
    ll l = -1, r = sum / k + 1;
    while(l + 1 < r) (Skirk(l + r >> 1) ? l : r) = l + r >> 1;
    printf("%lld\n", l);
}
}
int main() {
    int t = read(); while(t --) Qiuyu3600::Hutao();
    return 0;
}