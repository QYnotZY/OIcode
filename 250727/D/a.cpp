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
ll a, b, c, x, y, dx, dy;
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if(b == 0) return x = 1, y = 0, a;
    int g = exgcd(b, a % b, y, x);
    return y -= a / b * x, g;
}
ll fdiv(ll a, ll b) {if(b < 0) a = -a, b = -b; return a > 0 ? a / b : (a - b + 1) / b;}
ll cdiv(ll a, ll b) {return fdiv(a + b - 1, b);}
ll rmod(ll a, ll b) {return (a - 1) - fdiv(a - 1, b) * b + 1;}
void Hutao() {
    a = read(), b = read(), c = read();
    ll g = exgcd(a, b, x, y);
    if(c % g) return printf("-1\n"), void();
    x *= c / g, y *= c / g, dx = b / g, dy = a / g;
    ll lb = fdiv(-x, dx) + 1, ub = cdiv(y, dy) - 1;
    if(lb > ub) return printf("%lld %lld\n", rmod(x, dx), rmod(y, dy)), void();
    printf("%lld %lld %lld %lld %lld\n", ub - lb + 1, x + lb * dx, y - ub * dy, x + ub * dx, y - lb * dy);
}
}
int main() {
    int t = read();
    while(t --) work::Hutao();
    return 0;
}