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
const int mod = 998244353; const int ub = 1e7;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
int n, m, k, p;
int inv[ub + 10];
bool isnp[ub + 10]; vector<int> pri;
int i_k[ub + 10], p_i[ub + 10], p1_i[ub + 10];
inline int _1_i(int i) {return i & 1 ? mod - 1 : 1;}
int f[ub + 10];
inline void Citlali() {
    inv[1] = 1;
    i_k[0] = 0, p_i[0] = 1, p1_i[0] = 1;
    i_k[1] = 1, p_i[1] = p, p1_i[1] = Minus(1, p);
    for(int i = 2; i <= k + 5; i ++) {
        p_i[i] = Mult(p_i[i - 1], p), p1_i[i] = Mult(p1_i[i - 1], Minus(1, p));
        inv[i] = Minus(0, Mult(mod / i, inv[mod % i]));
        if(!isnp[i]) {
            pri.push_back(i);
            i_k[i] = Pow(i, k);
        }
        for(auto j : pri) {
            if(i * j > k + 5) break;
            isnp[i * j] = 1;
            i_k[i * j] = Mult(i_k[i], i_k[j]);
            if(i % j == 0) break;
        }
    }
    f[k] = 1;
    int cni = n - k;
    for(int i = k - 1; ~i; i --)
        f[i] = Add(Mult(Minus(1, p), f[i + 1]), Mult(cni, Mult(_1_i(k - i), p_i[k - i]))), cni = Mult(cni, Mult(inv[k - i + 1], n - i));
}
int ans = 0;
void Hutao() {
    n = read(), m = read(), k = read(), p = Inv(m);
    Citlali();
    if(n < k) {
        int cni = 1;
        for(int i = 0; i <= n; i ++)
            ans = Add(ans, Mult(Mult(i_k[i], cni), Mult(p_i[i], p1_i[n - i]))), cni = Mult(cni, Mult(inv[i + 1], n - i));
        printf("%d", ans);
        return;
    }
    int cni = 1;
    for(int i = 0; i <= k; i ++)
        ans = Add(ans, Mult(Mult(i_k[i], cni), Mult(p_i[i], f[i]))), cni = Mult(cni, Mult(inv[i + 1], n - i));
    printf("%d", ans);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}