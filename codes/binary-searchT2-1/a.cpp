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
int n, m;
ll a[N], b[N], sumb[N], l, r;
int k;
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read<ll>();
    sort(a + 1, a + n + 1);
    for(int i = 1; i < n; i ++)
        b[i] = a[i + 1] - a[i];
    sort(b + 1, b + n);
    for(int i = 1; i < n; i ++)
        sumb[i] = sumb[i - 1] + b[i];
    m = read();
    while(m --) {
        l = read<ll>(), r = read<ll>();
        k = lower_bound(b + 1, b + n, r - l + 1) - b - 1;
        printf("%lld ", sumb[k] + (n - k) * (r - l + 1));
    }
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}