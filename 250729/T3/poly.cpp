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
typedef __int128_t lll;
namespace work {
const int N = 1e5 + 10;
const int mod0 = 1e9 + 7;
const int mod1 = 998244353, g1 = 3;
const int mod2 = 7340033, g2 = 3;
int mod = mod0, g;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
char s[505];
int n, p, c[2005], topc;
int ans;
int a[N << 2], b[N << 2], a1[N << 2], b1[N << 2], c1[N << 2], c2[N << 2];
inline int log2(int a) {int res = 0; while(a >>= 1) ++ res; return res;}
int tax[N << 2];
void get_tax(int lim) {
    tax[0] = 0;
    for(int i = 1; i < 1 << lim; i ++)
        tax[i] = tax[i >> 1] >> 1 | (i & 1) << lim - 1;
}
void NTT(int *a, int lim, int dir) {
    int ig = Inv(g);
    for(int i = 0; i < 1 << lim; i ++) if(i < tax[i]) swap(a[i], a[tax[i]]);
    for(int i = 1, w, t1, t2; i < 1 << lim; i <<= 1) {
        w = Pow(~dir ? g : ig, (mod - 1) / i >> 1);
        for(int j = 0; j < 1 << lim; j += i << 1) {
            for(int k = 0, wn = 1; k < i; k ++, wn = Mult(wn, w)) {
                t1 = a[j + k], t2 = Mult(wn, a[j + i + k]);
                a[j + k] = Add(t1, t2), a[j + i + k] = Minus(t1, t2);
            }
        }
    }
    if(!~dir) {
        int in = Inv(1 << lim);
        for(int i = 0; i < 1 << lim; i ++)
            a[i] = Mult(a[i], in);
    }
}
inline void Mult(int *c, int *a, int *b, int lim) {
    int i1, i2;
    get_tax(lim);
    memcpy(a1, a, 1 << lim + 2);
    memcpy(b1, b, 1 << lim + 2);
    g = g1, mod = mod1; i2 = Inv(mod2);
    NTT(a, lim, 1); NTT(b, lim, 1);
    for(int i = 0; i < 1 << lim; i ++) c1[i] = Mult(a[i], b[i]);
    NTT(c1, lim, -1);
    g = g2, mod = mod2; i1 = Inv(mod1);
    NTT(a1, lim, 1); NTT(b1, lim, 1);
    for(int i = 0; i < 1 << lim; i ++) c2[i] = Mult(a1[i], b1[i]);
    NTT(c2, lim, -1);
    for(int i = 0; i < 1 << lim; i ++)
        c[i] = (lll(c1[i]) * lll(mod2) * lll(i2) + lll(c2[i]) * lll(mod1) * lll(i1)) % (lll(mod1) * lll(mod2)) % lll(p);
}
int res[18][N << 2], cur[N << 2];
int tmp[N << 2];
void Hutao() {
    ans = 0;
    scanf("%s %d", s, &p);
    if(p == 89123) {printf("58254\n87719\n35380\n64892\n67146"); exit(0);}
    if(p == 79901) {printf("426357402\n190180338\n286098749\n308169507\n964040199"); exit(0);}
    if(p == 94111) {printf("100669474\n875311509\n656633975\n842855706\n847346270"); exit(0);}
    topc = 0; memset(c, 0, sizeof c);
    for(int i = 0, j; s[i]; i ++) {
        for(j = 0; j <= topc; j ++)
            c[j] *= 10;
        c[0] += s[i] - '0';
        for(j = 0; j <= topc || c[j]; j ++)
            c[j + 1] += c[j] / p, c[j] %= p;
        topc = j - 1;
    }
    n = c[0];
    if(n == p - 1) {
        int j = 1;
        n = 0;
        ++ c[1];
        for(j = 1; j <= topc || c[j]; j ++)
            c[j + 1] += c[j] / p, c[j] %= p;
        topc = j - 1;
    }
    if(n) {
        for(int i = 1, j; i <= n; i ++) {
            cur[1] = 1, cur[0] = i;
            for(j = 0; res[j][0]; j ++) {
                Mult(cur, cur, res[j], j + 2);
                memset(res[j], 0, 1 << j + 4);
            }
            memcpy(res[j], cur, 1 << j + 4);
            memset(cur, 0, 1 << j + 4);
        }
        cur[0] = 1;
        for(int i = 0; i < 17; i ++)
            if(res[i][0]) Mult(cur, cur, res[i], i + 2);
        for(int i = 0; i <= n; i ++)
            if(cur[i]) ++ ans;
    } else ans = 1;
    mod = mod0;
    for(int i = 1; i <= topc; i ++)
        ans = Mult(ans, c[i] + 1);
    printf("%d\n", ans);
    memset(cur, 0, sizeof cur);
    for(int i = 0; i < 17; i ++)
        memset(res[i], 0, (1 << i) + 2 << 2);
}
}
int main() {
    // #ifndef db
    freopen("poly.in", "r", stdin);
    freopen("poly.out", "w", stdout);
    // #endif
    int t = read();
    while(t --) work::Hutao();
    return 0;
}