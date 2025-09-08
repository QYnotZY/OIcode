#include "bits/stdc++.h"
#define int long long
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
const int N = 2e5 + 10, mod = 998244353;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a - b < 0 ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
int fac[N], ifac[N], inv2;
void Init() {
    inv2 = Inv(2);
    fac[0] = 1;
    for(int i = 1; i <= 200000; i ++)
        fac[i] = Mult(fac[i - 1], i);
    ifac[200000] = Inv(fac[200000]);
    for(int i = 199999; i >= 0; i --)
        ifac[i] = Mult(ifac[i + 1], i + 1);
}
inline int C(int n, int m) {return n < m ? 0 : Mult(fac[n], Mult(ifac[m], ifac[n - m]));}
int n;
int cnt[N], sum[N];
int f[2][N], g[N], h[N], h1[N], X, ans;
void Hutao() {
    n = read();
    for(int i = 0; i <= n + 1; i ++) cnt[i] = 0, sum[i] = 0, f[0][i] = f[1][i] = 0;
    for(int i = 1, x; i <= n; i ++) {
        x = read();
        cnt[x] ++;
    }
    for(int i = n - 1; ~i; i --)
        sum[i] = sum[i + 1] + cnt[i];
    for(int i = n - 1, i0 = i & 1; ~i; i --, i0 ^= 1) {
        g[0] = f[i0 ^ 1][0], h[0] = 1, h1[0] = 0;
        for(int j = 1; j <= cnt[i + 1]; j ++) {
            g[j] = Add(g[j - 1], Mult(C(cnt[i + 1], j), f[i0 ^ 1][j]));
            h[j] = Add(h[j - 1], C(cnt[i + 1], j));
            h1[j] = Add(h1[j - 1], C(cnt[i + 1] - 1, j - 1));
        }
        X = Mult(Pow(2, sum[i + 2]), i + 1);
        for(int j = 0; j <= cnt[i]; j ++) {
            if(j >= cnt[i + 1]) f[i0][j] = g[cnt[i + 1]];
            else f[i0][j] = Add(g[j], Mult(Minus(h[cnt[i + 1]], h[j]), f[i0 ^ 1][j]));
            f[i0][j] = Add(f[i0][j], Mult(X, Minus(Mult(j, h[min(j, cnt[i + 1])]), Mult(cnt[i + 1], h1[min(j, cnt[i + 1])]))));
        }
    }
    ans = 0;
    for(int i = 0; i <= cnt[0]; i ++)
        ans = Add(ans, Mult(C(cnt[0], i), f[0][i]));
    write(ans);
}
}
signed main() {
    work::Init();
    int t = read();
    while(t --) work::Hutao();
    return 0;
}