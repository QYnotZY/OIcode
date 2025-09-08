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
inline int Pow_1(int b) {return b & 1 ? mod - 1 : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
int fac[N], ifac[N];
void Furina(int ub) {
    fac[0] = 1; for(int i = 1; i <= ub; i ++) fac[i] = Mult(fac[i - 1], i);
    ifac[ub] = Inv(fac[ub]); for(int i = ub - 1; ~i; i --) ifac[i] = Mult(ifac[i + 1], i + 1);
}
inline int C(int n, int m) {return n < m || m < 0 ? 0 : Mult(fac[n], Mult(ifac[n - m], ifac[m]));}
int n, m;
int f[N][N];
void Hutao() {
    for(int i = 0; i <= 10; i ++) f[0][i] = 1;
    for(int i = 1; i <= 10; i ++) {
        f[i][0] = 0; f[i][1] = 0;
        for(int j = 2; j <= 10; j ++) {
            for(int k = 0; k <= j - 2; k ++) {
                f[i][j] = Add(f[i][j], f[i - 1][k]);
            }
        }
    }
    for(int i = 0; i <= 10; i ++) {
        for(int j = 0; j <= 10; j ++) {
            printf("%d ", f[i][j]);
        }
        printf("\n");
    }
}
}
int main() {
    work::Furina(1000);
    int t = read();
    while(t --) work::Hutao();
    return 0;
}