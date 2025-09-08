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
const int mod = 1e9 + 7, inv2 = 5e8 + 4;
inline int Mod(ll a) {return (a % mod + mod) % mod;}
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
const int C[3][3] = {{1, 0, 0}, {1, 1, 0}, {1, 2, 1}};
int dp[64][3];
int tmp[3], res[3];
int shift(int k, int *a, int dist) {
    int res = 0;
    for(int i = 0; i <= k; i ++)
        res = Add(res, Mult(Mult(C[k][i], Pow(dist, k - i)), a[i]));
    return res;
}
void precalc() {
    dp[0][0] = 1, dp[0][1] = 0, dp[0][2] = 0;
    for(int i = 1; i < 63; i ++) {
        dp[i][0] = Add(dp[i - 1][0], Add(dp[i - 1][0], shift(0, dp[i - 1], Mod(1ll << i - 1))));
        dp[i][1] = Add(dp[i - 1][1], Add(dp[i - 1][1], shift(1, dp[i - 1], Mod(1ll << i - 1))));
        dp[i][2] = Add(dp[i - 1][2], Add(dp[i - 1][2], shift(2, dp[i - 1], Mod(1ll << i - 1))));
    }
}
int calc(ll n, int k) {
    if(n == 0) {res[0] = 1, res[1] = 0, res[2] = 0; return res[k];}
    int cnt = 0; for(; 1ll << cnt <= n; cnt ++) ; -- cnt;
    calc(n - (1ll << cnt), k);
    for(int i = 0; i <= k; i ++) tmp[i] = Add(res[i], shift(i, res, Mod(1ll << cnt)));
    for(int i = 0; i <= k; i ++) res[i] = Add(dp[cnt][i], tmp[i]);
    return res[k];
}
int n, k;
void Hutao() {
    precalc();
    n = read(), k = read();
    ll l, r;
    for(int i = 1; i <= n; i ++) {
        l = read<ll>(), r = read<ll>();
        printf("%d\n", Minus(calc(r, k), calc(l - 1, k)));
    }
}
}
int main() {
    freopen("dialog.in", "r", stdin);
    freopen("dialog.out", "w", stdout);
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}