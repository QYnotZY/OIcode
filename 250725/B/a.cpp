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
const int N = 1e3 + 10;
const int mod = 998244353;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Pow_1(int a) {return a & 1 ? mod - 1 : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
struct Poly {
    int n, a[N];
    Poly() {n = 0; memset(a, 0, sizeof a);}
    void init(int C) {n = 0, a[0] = C;}
    void init(int a1, int C) {n = 1, a[1] = a1, a[0] = C;}
    Poly operator + (Poly obj) {
        Poly res;
        res.n = max(n, obj.n);
        for(int i = 0; i <= res.n; i ++)
            res.a[i] = Add(a[i], obj.a[i]);
        return res;
    }
    Poly operator *  (Poly obj) {
        Poly res;
        res.n = n + obj.n;
        for(int i = 0; i <= res.n; i ++)
            for(int j = max(i - obj.n, 0); j <= min(n, i); j ++) 
                res.a[i] = Add(res.a[i], Mult(a[j], obj.a[i - j]));
        return res;
    }
    Poly friend operator * (int a, Poly b) {
        Poly a1; a1.init(a);
        return a1 * b;
    }
    Poly operator / (Poly obj) {
        Poly sub = *this, res;
        res.n = sub.n - obj.n;
        for(int i = res.n; ~i; -- i) {
            res.a[i] = sub.a[i + obj.n];
            for(int j = obj.n; ~j; -- j) {
                sub.a[i + j] = Minus(sub.a[i + j], Mult(res.a[i], obj.a[j]));
            }
        }
        return res;
    }
    void print() {
        for(int i = 0; i <= n; i ++)
            printf("%d ", a[i]);
        printf("\n");
    }
    int f(int x) {
        int res = 0;
        for(int i = n; i; -- i) {
            res = Add(res, a[i]);
            res = Mult(res, x);
        }
        res = Add(res, a[0]);
        return res;
    }
} ;
int x[N], y[N];
Poly Lagrange(int n, int *x, int *y) {
    Poly res;
    Poly F; F.init(1);
    Poly tmp;
    for(int i = 0; i <= n; i ++) {
        tmp.init(1, mod - x[i]);
        F = F * tmp;
    }
    for(int i = 0; i <= n; i ++) {
        tmp.init(1, mod - x[i]); tmp = F / tmp;
        res = res + (Mult(y[i], Inv(tmp.f(x[i]))) * tmp);
    }
    return res;
}
ll n, m, a[N];
int f[N][N];
Poly tmp;
void Hutao() {
    n = read<ll>(), m = read<ll>();
    for(int i = 1; i <= n; i ++) a[i] = read<ll>(), x[i] = i;
    a[++ n] = 1; x[n] = n;
    f[n + 1][0] = 1;
    for(int i = n; i; i --) {
        if(a[i] == 1) {
            f[i][0] = f[i + 1][0];
            for(int j = 1; j <= n; j ++) f[i][j] = Add(f[i][j - 1], f[i + 1][j]);
        } else {
            y[0] = f[i + 1][0];
            for(int j = 1; j <= n; j ++) y[j] = Add(y[j - 1], f[i + 1][j]);
            tmp = Lagrange(n, x, y);
            ll m0 = m / a[i];
            for(int j = 0; j <= n; j ++)
                f[i][j] = tmp.f((m - m0 * a[i] + j * a[i]) % mod);
            m = m0;
        }
    }
    y[0] = f[1][0];
    for(int j = 1; j <= n; j ++) y[j] = Add(y[j - 1], f[1][j]);
    tmp = Lagrange(n, x, y);
    printf("%lld", tmp.f((m - 1) % mod));
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}