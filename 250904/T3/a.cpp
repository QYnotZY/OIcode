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
int k;
int buc[50001000];
int *tmp = buc + 25000500;
int ans;
int a, b, c, d;
void Hutao() {
    a = read(), b = read(), c = read(), d = read();
    if(a > 0 && b > 0 && c > 0 && d > 0 || a < 0 && b < 0 && c < 0 && d < 0) return void(printf("0\n"));
    for(register int x1 = 1, ax1_2 = a; x1 <= k; x1 ++, ax1_2 = a * x1 * x1)
        for(register int x2 = 1; x2 <= k; x2 ++)
            ++ tmp[ax1_2 + b * x2 * x2];
    ans = 0;
    for(register int x3 = 1, cx3_2 = c; x3 <= k; x3 ++, cx3_2 = c * x3 * x3)
        for(register int x4 = 1; x4 <= k; x4 ++)
            ans += tmp[-(cx3_2 + d * x4 * x4)];
    printf("%d\n", ans << 4);
    for(register int x1 = 1, ax1_2 = a; x1 <= k; x1 ++, ax1_2 = a * x1 * x1)
        for(register int x2 = 1; x2 <= k; x2 ++)
            -- tmp[ax1_2 + b * x2 * x2];
}
}
int main() {
    int t = read(); Qiuyu3600::k = read(); while(t --) Qiuyu3600::Hutao();
    return 0;
}