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
const int N = 500 + 5, mod = 998244353;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a - b < 0 ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
int fac[N], ifac[N];
void Init() {
    fac[0] = 1;
    for(int i = 1; i <= 500; i ++)
        fac[i] = Mult(fac[i - 1], i);
    ifac[500] = Inv(fac[500]);
    for(int i = 499; i >= 0; i --)
        ifac[i] = Mult(ifac[i + 1], i + 1);
}
inline int C(int n, int m) {return n < m ? 0 : Mult(fac[n], Mult(ifac[m], ifac[n - m]));}
int n, m;
int f[N][N], ans;
void Hutao() {
    n = read(), m = read();
    f[0][0] = 1;
    for(int i = 1; i < n; i ++)
        for(int j = 0; j <= m; j += 2)
            for(int k = 0; k <= j; k += 2)
                f[i][j] = Add(f[i][j], Mult(f[i - 1][j - k], Minus(C(m, m + k >> 1), C(m, (m + k >> 1) + 1))));
    for(int i = 0; i <= m; i += 2)
        ans = Add(ans, Mult(f[n - 1][i], Minus(C(m, m + i >> 1), C(m, (m + i >> 1) + 1))));
    write(ans);
}
}
int main() {
    work::Init();
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}