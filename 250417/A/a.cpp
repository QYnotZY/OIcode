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

const int mod = 998244353;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
const int N = 1e7 + 10;
int n, m, typ, q;
namespace comb{
    int fac[N], ifac[N];
    int power(int a, int b){
        int res = 1;
        for(; b; a = Mult(a, a), b >>= 1)
            if(b & 1) res = Mult(res, a);
        return res;
    }
    void init(){
        fac[0] = 1;
        for(int i = 1; i <= n; i ++)
            fac[i] = Mult(fac[i - 1], i);
        ifac[n] = power(fac[n], mod - 2);
        for(int i = n; i >= 1; i --)
            ifac[i - 1] = Mult(fac[i], i);
    }
    int C(int n, int m){
        if(n < m) return 0;
        return Mult(fac[n], Mult(ifac[m], ifac[n - m]));
    }
    int iC(int n, int m){
        return Mult(Mult(fac[m], fac[n - m]), ifac[n]);
    }
} using namespace comb;
struct Poly{
    int a, b, c;
    int f(int x) {return Add(Mult(a, Mult(x, x)), Add(Mult(b, x), c));}
    #ifdef db
    void print(){
        printf("%d x^2 + %d x + %d\n", a, b, c);
    }
    #endif
} p;
inline Poly Add(Poly a, Poly b) {return Poly{Add(a.a, b.a), Add(a.b, b.b), Add(a.c, b.c)};}
inline Poly Mult(int a, Poly b) {return Poly{Mult(a, b.a), Mult(a, b.b), Mult(a, b.c)};}
void solve(int A, int B){
    int n = A + B;
    Poly pa0 = Poly{0, 0, C(n - 1, A - 1)}, pa1 = Mult(C(n - 2, A - 2), Poly{0, 1, mod - 1}), pa2 = Mult(C(n - 3, A - 3), Poly{1, mod - 3, 2});
    Poly pb0 = Poly{0, 0, C(n - 1, B - 1)}, pb1 = Mult(C(n - 2, B - 2), Poly{0, 1, mod - 1}), pb2 = Mult(C(n - 3, B - 3), Poly{1, mod - 3, 2});
    int ca0 = Add(Add(p.b, p.c), 1), ca1 = Add(p.b, 3), ca2 = p.a;
    int cb0 = Add(Add(Mult(2, Mult(p.a, A)), p.b), Add(1, p.f(A))), cb1 = Add(Add(Mult(2, Mult(p.a, A)), p.b), 3), cb2 = p.a;
    p = Mult(iC(n, A), Add(Mult(ca0, pa0), Add(Mult(ca1, pa1), Add(Mult(ca2, pa2), Add(Mult(cb0, pb0), Add(Mult(cb1, pb1), Mult(cb2, pb2)))))));
    #ifdef db
    printf("%d", iC(n, A));
    #endif
}
int main(){
    n = read(), m = read(), typ = read();
    init();
    if(typ == 1) p = Poly{0, 1, 0};
    else p = Poly{1, 0, 0};
    for(int i = 1; i <= m; i ++){
        int x = read();
        solve(x, n - x);
    }
    int q = read();
    for(int i = 1; i <= q; i ++){
        int x = read();
        printf("%d\n", p.f(x));
    }
    return 0;
}