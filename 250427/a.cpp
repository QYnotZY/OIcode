#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
char gc() {return getchar();}
template<typename T = int>
inline T readnum(){
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
template<typename T = int>
T read() {return readnum<T>();}
}
using FastIO::read;
typedef long long ll;
typedef __int128_t lll;

const ll mod = 998244353, inv2 = 499122177, inv4 = 748683265, inv12 = 582309206;
int T;
ll n, m;
inline ll Mod(ll a) {return (a % mod + mod) % mod;}
inline ll Add(ll a, ll b) {return Mod(Mod(a) + Mod(b));}
inline ll Mult(ll a, ll b) {return Mod(Mod(a) * Mod(b));}
inline ll pS(ll a) {return Add(Mult(Mult(a, Add(a, 1)), Mult(Add(a, Add(a, 1)), inv12)), Add(Mult(mod - 1, Mult(Mult(a, Add(a, 1)), inv4)), a));}
inline ll sS(ll a) {return Add(Mult(Add(Add(n, 1), Mult(mod - 1, a)), Add(m, Mult(mod - 1, n))), Mult(Mult(Add(a, n), Add(Add(n, 1), Mult(mod - 1, a))), inv2));}
ll bsans(ll lb, ll ub){
    ll l = lb - 1, r = ub + 1;
    while(l + 1 < r){
        ll mid = l + (r - l >> 1);
        if((lll)mid * lll(mid - 1) / lll(2) + lll(1) > lll(m - n + mid)) r = mid;
        else l = mid;
    }
    if(l == n) return pS(n);
    return Add(pS(l), sS(r));
}
int main(){
    T = read();
    while(T --){
        n = read<ll>(), m = read<ll>(); n --;
        printf("%lld\n", bsans(1, n));
    }
    return 0;
}