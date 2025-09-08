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
namespace work {
ll n, m; ll mod;
ll a[8], p[8], cnt;
inline ll Mult(ll a, ll b, ll mod) {return a * b % mod;}
inline ll Pow(ll a, ll b, ll mod) {return b ? Mult(Pow(Mult(a, a, mod), b >> 1, mod), b & 1 ? a : 1, mod) : 1;}
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if(b == 0) return x = 1, y = 0, a;
    ll g = exgcd(b, a % b, y, x);
    return y -= a / b * x, g;
}
inline ll Inv(ll a, ll mod) {ll x, y; exgcd(a, mod, x, y); return (x % mod + mod) % mod;}
ll pre[1000010];
ll f(ll n, ll p, ll mod) {
    if(!n) return 1;
    return Mult(Mult(Pow(pre[mod], n / mod, mod), pre[n % mod], mod), f(n / p, p, mod), mod);
}
ll Layla(ll p, ll ap) {
    ll x = 0, y = 0, z = 0;
    for(ll i = p; i <= n; i *= p) x += n / i;
    for(ll i = p; i <= m; i *= p) y += m / i;
    for(ll i = p; i <= n - m; i *= p) z += (n - m) / i;
    if(x - y - z >= ap) return 0;
    ll pn = Pow(p, ap, 1000000);
    pre[0] = 1; for(int i = 1; i <= pn; i ++) pre[i] = Mult(pre[i - 1], i % p ? i : 1, pn);
    ll xx = f(n, p, pn), yy = f(m, p, pn), zz = f(n - m, p, pn);
    return Mult(Mult(Pow(p, x - y - z, pn), xx, mod), Inv(Mult(yy, zz, pn), pn), pn);
}
void Hutao() {
    n = read<ll>(), m = read<ll>(), mod = read<ll>();
    ll mod0 = mod;
    for(ll i = 2, ap; i <= mod0; i ++) {
        if(mod0 % i) continue;
        p[++ cnt] = 1, ap = 0; while(!(mod0 % i)) p[cnt] *= i, ++ ap, mod0 /= i;
        a[cnt] = Layla(i, ap);
    }
    ll ans = 0;
    for(int i = 1; i <= cnt; i ++) (ans += Mult(a[i], Mult(mod / p[i], Inv(mod / p[i], p[i]), mod), mod)) %= mod;
    printf("%lld\n", ans);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}