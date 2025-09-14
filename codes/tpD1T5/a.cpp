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
int n, k; ll s;
ll a[30], fac[30]; int facsz;
ll sum;
map<ll, int> mp[30];
ll ans, cur;
void dfs1(int d) {
    if(sum > s || cur > k) return;
    if(d > n >> 1) {
        for(int i = 0; i <= k - cur; i ++)
            ++ mp[i][sum];
        return;
    }
    dfs1(d + 1);
    sum += a[d]; dfs1(d + 1); sum -= a[d];
    if(a[d] <= facsz) {sum += fac[a[d]]; cur ++; dfs1(d + 1); sum -= fac[a[d]]; cur --;}
}
void dfs2(int d) {
    if(sum > s || cur > k) return;
    if(d == n >> 1) {
        ans += mp[cur][s - sum];
        return;
    }
    dfs2(d - 1);
    sum += a[d]; dfs2(d - 1); sum -= a[d];
    if(a[d] <= facsz) {sum += fac[a[d]]; cur ++; dfs2(d - 1); sum -= fac[a[d]]; cur --;}
}
void getfac() {
    fac[facsz = 0] = 1;
    while(fac[facsz] <= s / (facsz + 1)) fac[facsz + 1] = fac[facsz] * (facsz + 1), ++ facsz;
}
void Hutao() {
    n = read(), k = read(), s = read<ll>();
    getfac();
    for(int i = 1; i <= n; i ++) a[i] = read();
    dfs1(1), dfs2(n);
    printf("%lld", ans);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}