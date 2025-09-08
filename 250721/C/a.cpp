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
int mod = 998244353;
const int N = 500 + 10;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Pow_1(int a) {return a & 1 ? mod - 1 : 1;}
inline int Sqrt(int a) {
    if(a < 2) return a;
    int l = 0, r = a + 1, mid;
    while(l + 1 < r) {
        mid = l + r >> 1;
        (mid <= a / mid) ? (l = mid) : (r = mid);
    }
    return l;
}
int n, liml[N], limr[N], p[N], ans;
int f[N][N];
int Furina(int k) {
    memset(f, 0, sizeof f); f[0][0] = 1;
    int c1 = 0, c2 = 0;
    for(int i = 1; i <= n << 1; i ++) {
        if(p[i] >= n) {
            for(int j = 0; j <= c2; j ++)
                f[i][j] = Add(f[i][j], Mult(f[i - 1][j], limr[p[i]] + 1 - j - c1));
            c1 ++;
        } else {
            for(int j = 1; j <= c2 + 1; j ++)
                f[i][j] = Add(f[i][j], Mult(f[i - 1][j - 1], liml[p[i]] + 2 - j - c1));
            for(int j = 0; j <= c2 + 1; j ++)
                f[i][j] = Add(f[i][j], Mult(f[i - 1][j], limr[p[i]] + 1 - n - k - c2 + j));
            c2 ++;
        }
    }
    return f[n << 1][k];
}
bool cmp(int x, int y) {
    return (x < n ? liml[x] : limr[x]) < (y < n ? liml[y] : limr[y]) || (x < n ? liml[x] : limr[x]) == (y < n ? liml[y] : limr[y]) && (x < n ? limr[x] : liml[x]) < (y < n ? limr[y] : liml[y]);
}
void Hutao() {
    n = read(), mod = read();
    for(int i = 0; i < n; i ++) {liml[i] = Sqrt(n * n - i * i); if(liml[i] * liml[i] + i * i == n * n) -- liml[i];}
    for(int i = 0; i < n << 1; i ++) limr[i] = min(Sqrt((n * n << 2) - i * i), (n << 1) - 1), p[i + 1] = i;
    sort(p + 1, p + (n << 1) + 1, cmp);
    for(int i = 0; i <= n; i ++) ans = Add(ans, Mult(Pow_1(i), Furina(i)));
    printf("%d", ans);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}