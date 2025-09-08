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
namespace gen {
class MT_gen {
    const unsigned A = 2567483615u, B = 2636928640u, C = 4022730752u, F = 1812433253u;
    unsigned MT[624], tot;
    unsigned keep(unsigned index) { return index >= 624 ? index - 624 : index; }

    public:
    MT_gen(unsigned seed) {
        MT[0] = seed;
        tot = 0;
        for (int i = 1; i < 624; ++i) MT[i] = F * (MT[i - 1] ^ (MT[i - 1] >> 30)) + i;
    }
    void twist() {
        for (int i = 0; i < 624; ++i) {
        unsigned tmp = (MT[i] & 0x80000000) | (MT[keep(i + 1)] & 0x7fffffff);
        tmp = (tmp & 1) ? (tmp >> 1) ^ A : (tmp >> 1);
        MT[i] = MT[keep(i + 397)] ^ tmp;
        }
    }
    unsigned operator()() {
        if (tot == 0) twist();
        unsigned tmp = MT[tot];
        tmp ^= tmp >> 11;
        tmp ^= tmp << 7 & B;
        tmp ^= tmp << 15 & C;
        tmp ^= tmp >> 18;
        tot = keep(tot + 1);
        return tmp;
    }
};
char c[10000005];
void get(int n, unsigned seed) {
    MT_gen rnd(seed);
    for (int i = 1; i <= n / 2; ++i) c[i] = '(';
    for (int i = n / 2 + 1; i <= n; ++i) c[i] = ')';
    for (int i = n; i >= 1; --i) std::swap(c[i], c[rnd() % i + 1]);
}
} using gen::c;
typedef long long ll;
namespace work {
const int N = 1e7 + 10;
int n, q, mod; unsigned seed;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
int fac[N], ifac[N];
void prework(int ub) {
    fac[0] = 1; for(int i = 1; i <= ub; i ++) fac[i] = Mult(fac[i - 1], i);
    ifac[ub] = Inv(fac[ub]); for(int i = ub - 1; ~i; i --) ifac[i] = Mult(ifac[i + 1], i + 1);
}
inline int C(int n, int m) {return Mult(fac[n], Mult(ifac[n - m], ifac[m]));}
inline int Catalan(int n) {return Minus(C(n << 1, n), C(n << 1, n - 1));}
int rS, rT;
void precalc() {
    int res = 0;
    for(int i = 1; i <= n - 1; i ++)
        res = Add(res, Mult(Mult(2 * n - 1 - 2 * i, i), Mult(Catalan(i), Catalan(n - 1 - i))));
    rT = Minus(Mult(Catalan(n), C(n, 2)), res);
} 
int calc() {
    return Add(Mult(Mult(Catalan(n), C(n, 2)), Mult(fac[n], fac[n])), Mult(Mult(fac[n - 1], fac[n - 1]), Add(Mult(Mult(Catalan(n), Mult(n, n)), rS), Mult(Minus(Mult(n, n), Add(rS, rS)), rT))));
}
void Hutao() {
    n = read(), q = read(), mod = read();
    prework(10000000);
    seed = read<unsigned>();
    gen::get(n, seed);
    n >>= 1;
    for(int i = 1, cnt = 0; i <= n << 1; i ++) {
        if(c[i] == ')') ++ cnt;
        else rS = Add(rS, cnt);
    }
    precalc();
    printf("%d\n", calc());
    for(int i = 1, l, r; i <= q; i ++) {
        l = read(), r = read();
        if(l > r) swap(l, r);
        if(c[l] == '(' && c[r] == ')') rS = Add(rS, r - l);
        else if(c[l] == ')' && c[r] == '(') rS = Minus(rS, r - l);
        swap(c[l], c[r]);
        printf("%d\n", calc());
    }
}
}
int main() {
    freopen("bad.in", "r", stdin);
    freopen("bad.out", "w", stdout);
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}