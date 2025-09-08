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
typedef __int128_t lll;
typedef unordered_map<int, int> umapii;
namespace work {
ll phi(ll n) {
    ll res = n;
    for(ll i = 2; i * i <= n; i ++) {
        if(n % i == 0) (res /= i) *= i - 1;
        while(n % i == 0) n /= i;
    }
    if(n != 1) (res /= n) *= n - 1;
    return res;
}
ll ord(ll n, ll k, ll phin) {
    ll res = phin;
    for(ll i = 1, tmp, bas, idx; i * i <= phin; i ++) {
        if(!(phin % i)) {
            tmp = 1, bas = k, idx = i;
            for(; idx; idx >>= 1, bas = lll(bas) * bas % n)
                if(idx & 1) tmp = lll(tmp) * bas % n;
            if(tmp == 1) return i;
            tmp = 1, bas = k, idx = phin / i;
            for(; idx; idx >>= 1, bas = lll(bas) * bas % n)
                if(idx & 1) tmp = lll(tmp) * bas % n;
            if(tmp == 1) res = phin / i;
        }
    }
    return res;
}
ll m, k, ans;
ll calc(ll n) {
    if(n == 1) return 1;
    ll phin = phi(n);
    return phin / ord(n, k % n, phin);
}
int Main() {
    m = read<ll>(), k = read<ll>();
    ll sqrtm = pow(m, 0.5);
    for(ll i = 1; i <= sqrtm; i ++)
        if(!(m % i)) {
            ans += calc(i);
            if(i != m / i) ans += calc(m / i);
        }
    write<ll>(ans);
    return 0;
}
}
int main() {
    #ifndef db
    freopen("guess.in", "r", stdin);
    freopen("guess.out", "w", stdout);
    #endif
    return work::Main();
}