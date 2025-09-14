#include "bits/stdc++.h"
using namespace std;
namespace FastIO {
    template<typename T = int> T read() {
        char ch = getchar(); bool neg = 0; T res = 0;
        for(; !('0' <= ch && ch <= '9'); ch = getchar()) if(ch == '-') neg = !neg;
        for(; ('0' <= ch && ch <= '9'); ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ 48);
        return neg ? ~res + 1 : res;
    }
    char readch(bool acsp = 0) {
        char ch = getchar(); for(; !(33 - acsp <= ch && ch < 127); ch = getchar()); return ch;
    }
} using namespace FastIO;
typedef long long ll;
namespace Qiuyu3600 {
const int N = 5e6 + 10;
const int mod = 998244353;
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
int fac[N], ifac[N];
void Furina(int inf) {
    fac[0] = 1; for(int i = 1; i <= inf; i ++) fac[i] = Mult(fac[i - 1], i);
    ifac[inf] = Inv(fac[inf]); for(int i = inf - 1; ~i; -- i) ifac[i] = Mult(ifac[i + 1], i + 1);
}
inline int C(int n, int m) {return Mult(Mult(fac[n], ifac[n - m]), ifac[m]);}
int t, inf, ans;
void Hutao() {
    cin >> t >> inf;
    Furina(inf);
    int a, b;
    while(t --) {
        cin >> a >> b;
        ans ^= C(a, b);
    }
    cout << ans;
}
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}