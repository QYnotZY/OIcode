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
const int N = 1e6 + 10;
const int mod = 998244353;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
bool isnp[N];
int pri[N], prisz;
int mu[N], phi[N], ad[N], sig0[N];
void Euler(int ub) {
    mu[1] = 1, phi[1] = 1, sig0[1] = 1;
    for(int i = 2; i <= ub; i ++) {
        if(!isnp[i]) {
            pri[++ prisz] = i;
            mu[i] = mod - 1;
            phi[i] = i - 1;
            ad[i] = 1;
            sig0[i] = 2;
        }
        for(int j = 1; j <= prisz && i * pri[j] <= ub; j ++) {
            isnp[i * pri[j]] = 1;
            if(!(i % pri[j])) {
                mu[i * pri[j]] = 0;
                phi[i * pri[j]] = phi[i] * pri[j];
                ad[i * pri[j]] = ad[i] + 1;
                sig0[i * pri[j]] = Mult(sig0[i], Mult(ad[i * pri[j]] + 1, Inv(ad[i * pri[j]])));
                break;
            }
            mu[i * pri[j]] = Minus(0, mu[i]);
            phi[i * pri[j]] = phi[i] * (pri[j] - 1);
            ad[i * pri[j]] = 1;
            sig0[i * pri[j]] = Mult(sig0[i], 2);
        }
    }
}
int n, ans;
void Hutao() {
    Euler(1000000);
    printf("{0");
    for(int tmpn = 1; tmpn <= 1000; tmpn ++) {
        if(tmpn % 50 == 0) cerr << "d";
        n = tmpn;
        ans = 0; int tmp;
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= n; j ++) {
                tmp = phi[i * j];
                for(int k = 1; k <= n; k ++)
                    ans = Add(ans, Mult(tmp, Mult(mu[i * k], sig0[j * k])));
            }
        printf(",%d", ans);
    }
    printf("}");
}
}
int main() {
    freopen("sumsumsum.in", "r", stdin);
    freopen("sumsumsum.out", "w", stdout);
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}