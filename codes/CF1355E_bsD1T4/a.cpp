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
int n, c1, c2, c3;
int a[N], minn, maxx;
ll calc(int x) {
    ll res0 = 0, res1 = 0;
    for(int i = 1; i <= n; i ++) {
        if(a[i] < x) res0 += x - a[i];
        if(x < a[i]) res1 += a[i] - x;
    }
    ll resm = min(res0, res1);
    res0 -= resm, res1 -= resm;
    return resm * min(c3, c1 + c2) + res0 * c1 + res1 * c2;
}
void Hutao() {
    n = read(), c1 = read(), c2 = read(), c3 = read();
    minn = 1e9, maxx = 0;
    for(int i = 1; i <= n; i ++) {
        a[i] = read();
        minn = min(minn, a[i]), maxx = max(maxx, a[i]);
    }
    int l = minn - 1, r = maxx, mid;
    while(l + 1 < r) {
        mid = l + r >> 1;
        if(calc(mid) >= calc(mid + 1)) l = mid;
        else r = mid;
    }
    printf("%lld", calc(r));
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}