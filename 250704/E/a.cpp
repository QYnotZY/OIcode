#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// inline char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
inline char gc() {return getchar();}
template<typename T>
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
inline T read() {return readnum<T>();}
char wc[50]; int top;
template<typename T>
inline void writenum(T x, char sp){
    if(!x) return putchar('0'), void(putchar(sp));
    if(x < 0) putchar('-'), x = ~x + 1;
    top = 0;
    for(; x; x /= 10) wc[top ++] = x % 10 ^ 48;
    while(top --) putchar(wc[top]);
    putchar(sp);
}
template<typename T = int>
inline void write(T x, char sp = '\n'){
    writenum(x, sp);
}
}
using FastIO::read;
using FastIO::write;
typedef long long ll;
namespace work {
const ll B(4000), inf(1e18);
ll x, y, z, k;
ll ans;
inline ll get_b(ll r, ll a) {
    return (z - r * (r + 1) / 2 * k - 1) / (r * k + a) + 1;
}
inline ll get_a(ll r, ll b) {
    return (z - r * (r + 1) / 2 * k - 1) / b + 1 - r * k;
}
inline ll cost(ll r, ll a, ll b) {
    return k * r * x + r * y + a * x + b * y;
}
void Furina() {
    ll la = 1, ra, b;
    for(; la <= k && la <= z; la = ra + 1) {
        b = (z - 1) / la + 1;
        if(b == 0) return;
        if(b != 1) ra = (z - 1) / (b - 1);
        else ra = k;
        #ifdef db
        printf("%lld %lld %lld\n", la, ra, b);
        #endif
        ans = min(ans, cost(0, la, b));
    }
}
void Layla() {
    for(ll r = 1, limrr = 2 * z / k; r * (r + 1) <= limrr; r ++) {
        for(ll a = 0, b = get_b(r, a); a <= k && b >= 0; b = get_b(r, ++ a)) {
            ans = min(ans, cost(r, a, b));
        }
    }
}
void Citlali() {
    for(ll r = 1, limrr = 2 * z / k; r * (r + 1) <= limrr; r ++) {
        for(ll b = 1, a = get_a(r, b); a >= 0; a = get_a(r, ++ b)) {
            if(a <= k) ans = min(ans, cost(r, a, b));
        }
    }
}
void Hutao() {
    x = read<ll>(), y = read<ll>(), z = read<ll>(), k = read<ll>();
    ans = inf;
    Furina();
    #ifdef db
    printf("done");
    #endif
    if(k <= B) Layla();
    else Citlali();
    write(ans);
}
}
int main() {
    int t = read();
    while(t --) work::Hutao();
    return 0;
}