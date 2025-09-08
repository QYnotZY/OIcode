#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// inline char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
inline char gc() {return getchar();}
template<typename T = int>
inline T read(){
    T res = 0; bool f = 0;
    char ch = gc();
    for(; !('0' <= ch && ch <= '9'); ch = gc())
        if(ch == '-') f = !f;
    for(; '0' <= ch && ch <= '9'; ch = gc())
        res = (res << 3) + (res << 1) + (ch ^ 48);
    return f ? ~res + 1 : res;
}
inline char readch(bool sp = 0){
    char ch = gc();
    for(; !(33 - sp <= ch && ch < 127); ch = gc()) ;
    return ch;
}
}
using FastIO::read;
using FastIO::readch;
typedef long long ll;
typedef __int128_t lll;
namespace work {
const int N = 5e5 + 10;
const ll mod = 1000000000000000003ll;
int n, a[N];
inline ll Mod(ll a) {return (a % mod + mod) % mod;}
inline ll Mult(ll a, ll b) {return lll(a) * lll(b) % lll(mod);}
inline ll Pow(ll a, ll b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
int cnt[N], cnt1[N];
ll sum[N];
map<ll, ll> buc;
ll ans;
void Hutao() {
    n = read();
    buc[0] = 1;
    for(int i = 1, l = 0; i <= n; i ++) {
        a[i] = read(); ++ cnt[a[i]];
        sum[i] = Mod(sum[i - 1] - Mult((cnt[a[i]] - 1) % 3, Pow(3, a[i])) + Mult(cnt[a[i]] % 3, Pow(3, a[i])));
        ans += buc[sum[i]];
        ++ cnt1[a[i]]; ++ buc[sum[i]];
        while(cnt1[a[i]] >= 5) {-- cnt1[a[l]]; -- buc[sum[l]]; ++ l;}
    }
    printf("%lld\n", ans);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}