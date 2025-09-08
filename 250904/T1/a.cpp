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
const int mod = 1e9 + 7;
int n, a[N], negcnt, negmaxid, non0, non0id;
ll ans;
void Hutao() {
    a[0] = -mod;
    n = read();
    negcnt = negmaxid = non0 = non0id = 0;
    for(int i = 1; i <= n; i ++) {
        a[i] = read();
        if(a[i]) ++ non0, non0id = i;
        if(a[i] < 0) {
            ++ negcnt;
            if(a[i] > a[negmaxid]) negmaxid = i;
        }
    }
    if(n == 1) return void(printf("%d\n", a[1]));
    if(non0 == 0) return void(printf("0\n"));
    if(non0 == 1) return void(printf("%d\n", max(0, a[non0id])));
    ans = 1;
    for(int i = 1; i <= n; i ++) {
        if((i == negmaxid && (negcnt & 1)) || a[i] == 0) continue;
        (ans *= a[i]) %= mod;
    }
    printf("%lld\n", ans);
}
}
int main() {
    int t = read(); while(t --) Qiuyu3600::Hutao();
    return 0;
}