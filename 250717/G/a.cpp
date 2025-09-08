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
const int N = 1.5e5 + 10, mod = 1e9 + 9;
int fac[N], ifac[N];
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
inline int C(int n, int m) {return Mult(fac[n], Mult(ifac[m], ifac[n - m]));}
inline int cb(int n, int m) {return C(n + m - 1, m - 1);}
int n0, m0, n, m;
void Skirk() {
    fac[0] = 1;
    for(int i = 1; i <= 150000; i ++)
        fac[i] = Mult(fac[i - 1], i);
    ifac[150000] = Inv(fac[150000]);
    for(int i = 149999; ~i; i --)
        ifac[i] = Mult(ifac[i + 1], i + 1);
}
int f[20][N], ans;
void Hutao() {
    n0 = read(), m0 = read();
    n = n0 - m0, m = (m0 + 1) / 2;
    int ln = log2(n);
    for(int i = 0; i <= ln; i ++) {
        for(int j = 0; j <= n; j ++) {
            for(int k = 0; k <= m && k << i <= j; k += 2) {
                f[i][j] = Add(f[i][j], Mult(i ? f[i - 1][j - (k << i)] : (j == k << i), C(m, k)));
            }
            #ifdef db
            printf("%d ", f[i][j]);
            #endif
        }
        #ifdef db
        printf("\n");
        #endif
    }
    for(int j = 0; j <= n; j ++) ans = Add(ans, Mult(f[ln][j], cb(n - j, m0 + 1 - m)));
    printf("%d\n", Minus(C(n0, m0), ans));
}
}
int main() {
    work::Skirk();
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}