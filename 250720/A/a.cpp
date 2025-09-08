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
const int mod = 1e9 + 7; const int N = 1010, ub = 2000;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
int fac[ub + 10], ifac[ub + 10];
inline void fac_init() {
    fac[0] = 1; for(int i = 1; i <= ub; i ++) fac[i] = Mult(fac[i - 1], i);
    ifac[ub] = Inv(fac[ub]); for(int i = ub - 1; ~i; -- i) ifac[i] = Mult(ifac[i + 1], i + 1);
}
inline int C(int n, int m) {return n < m ? 0 : Mult(fac[n], Mult(ifac[m], ifac[n - m]));}
inline int exC(int n, int m, bool empty) {return empty ? C(n + m - 1, m - 1) : C(n - 1, m - 1);}
int n, m, a[N], ans;
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= m; i ++) a[i] = read();
    for(int i = 0, gi; i < n; i ++) {
        gi = 1;
        for(int j = 1; j <= m; j ++)
            gi = Mult(gi, exC(a[j], n - i, 1));
        ans = Add(ans, Mult(Mult(Pow(mod - 1, i), C(n, i)), gi));
    }
    printf("%d", ans);
}
}
int main() {
    work::fac_init();
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}