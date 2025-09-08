#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
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
const int K = 1e6 + 10, mod = 998244353;
inline int Mod(int a) {return (a % mod + mod) % mod;}
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
int inv2;
int n, k;
vector<int> pri; bitset<K> isnp;
int mu[K], summu[K], i_n[K];
inline void Euler(int ub) {
    inv2 = Inv(2);
    i_n[0] = 0;
    mu[1] = 1, i_n[1] = 1;
    for(int i = 2; i <= ub; i ++) {
        if(!isnp[i]) {
            pri.push_back(i);
            mu[i] = mod - 1;
            i_n[i] = Pow(i, n);
        }
        for(auto j : pri) {
            if(i * j > ub) break;
            isnp[i * j] = 1;
            i_n[i * j] = Mult(i_n[i], i_n[j]);
            if(i % j == 0) {
                mu[i * j] = 0;
                break;
            }
            mu[i * j] = Minus(0, mu[i]);
        }
    }
    for(int i = 1; i <= ub; i ++)
        summu[i] = Add(summu[i - 1], mu[i]);
}
inline int Sum(int i, int j) {return Mult(Mult(Add(i, j), Minus(j, i - 1)), inv2);}
inline int F(int x) {
    int res = 0;
    for(int l = 1, r; l <= x; l = r + 1) {
        r = x / (x / l);
        res = Add(res, Mult(i_n[x / l], Minus(summu[r], summu[l - 1])));
    }
    return res;
}
void Hutao() {
    n = read(), k = read();
    work::Euler(1000001);
    int ans = 0;
    for(int l = 1, r; l <= k; l = r + 1) {
        r = k / (k / l);
        ans = Add(ans, Mult(Sum(l, r), F(k / l)));
    }
    ans = Mult(Inv(i_n[k]), ans);
    printf("%d\n", ans);
}
}
int main() {
    #ifndef db
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);
    #endif
    int t = read();
    while(t --) work::Hutao();
    return 0;
}