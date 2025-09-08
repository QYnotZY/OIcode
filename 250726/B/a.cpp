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
const int N = 1e5 + 10;
const int mod = 998244353, gen = 3, invgen = 332748118;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
inline int log2(int n) {int res = 0; while(n >>= 1) ++ res; return res;}
int tax[N << 1];
void get_tax(int lim) {
    tax[0] = 0;
    for(int i = 1; i < 1 << lim; i ++)
        tax[i] = tax[i >> 1] >> 1 | (i & 1) << lim - 1;
}
void NTT(int *a, int lim, int dir) {
    for(int i = 1; i < 1 << lim; i ++) if(i < tax[i]) swap(a[i], a[tax[i]]);
    for(int i = 1, w, t1, t2; i < 1 << lim; i <<= 1) {
        w = Pow(~dir ? gen : invgen, (mod - 1) / i >> 1);
        for(int j = 0; j < 1 << lim; j += i << 1) {
            for(int k = 0, wn = 1; k < i; k ++, wn = Mult(wn, w)) {
                t1 = a[j + k], t2 = Mult(wn, a[j + i + k]);
                a[j + k] = Add(t1, t2), a[j + i + k] = Minus(t1, t2);
            }
        }
    }
    if(!~dir) {
        int invn = Inv(1 << lim);
        for(int i = 0; i < 1 << lim; i ++)
            a[i] = Mult(a[i], invn);
    }
}
void Mult(int *c, int *a, int *b, int lim) {
    get_tax(lim);
    NTT(a, lim, 1), NTT(b, lim, 1);
    for(int i = 0; i < 1 << lim; i ++)
        c[i] = Mult(a[i], b[i]);
    NTT(c, lim, -1);
}
int t, n;
int f[N << 1];
int a[N << 1], b[N << 1], c[N << 1];
void Skirk(int l, int r) {
    if(l > r) return;
    if(l == r) return void(f[l] = Add(f[l], Mult(l - 1, f[l - 1])));
    int mid = l + r >> 1;
    Skirk(l, mid);
    for(int i = l; i <= mid; i ++) a[i - l] = f[i], b[i - l] = Mult(Minus(i, 1), f[i]);
    for(int i = mid - l + 1; i < 1 << log2(mid - l << 1) + 1; i ++) a[i] = b[i] = 0;
    Mult(c, a, b, log2(mid - l << 1) + 1);
    for(int i = max(l << 1, mid + 1); i <= r; i ++)
        f[i] = Add(f[i], c[i - (l << 1)]);
    if(r - l >= 2) {
        a[0] = a[1] = 0;
        for(int i = 2; i <= min(r - l, l - 1); i ++) a[i] = f[i];
        for(int i = l; i <= mid; i ++) b[i - l] = f[i];
        for(int i = min(r - l, l - 1) + 1; i < 1 << log2(min(r - l, l - 1) + mid - l) + 1; i ++) a[i] = 0;
        for(int i = mid - l + 1; i < 1 << log2(min(r - l, l - 1) + mid - l) + 1; i ++) b[i] = 0;
        Mult(c, a, b, log2(min(r - l, l - 1) + mid - l) + 1);
        for(int i = max(l, mid + 1); i <= r && i - l < 1 << log2(min(r - l, l - 1) + mid - l) + 1; i ++)
            f[i] = Add(f[i], Mult(i - 2, c[i - l]));
    }
    Skirk(mid + 1, r);
}
int l[N];
int stk[N], top;
void Hutao() {
    t = read(), n = read();
    f[0] = 1, f[1] = 2;
    Skirk(2, n);
    for(int i = 0; i < t; i ++) {
        for(int i = 1; i <= n; i ++) l[i] = read();
        if(l[n] != n) {printf("0\n"); continue;}
        int ans = 1; top = 0;
        for(int i = 1, res = 0; i <= n; i ++, res = 0) {
            while(top) {
                if(i - l[i] + 1 <= stk[top]) {
                    if(i - l[i] + 1 > stk[top] - l[stk[top]] + 1) {
                        ans = 0;
                        break;
                    }
                    res ++; top --;
                } else break;
            }
            if(!ans) break;
            ans = Mult(ans, f[res]);
            stk[++ top] = i;
        }
        printf("%d\n", ans);
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}