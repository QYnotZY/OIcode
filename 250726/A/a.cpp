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
const int N = 2e5 + 10;
const int mod = 998244353, gen = 3, invgen = 332748118;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
inline int log2(int x) {int res = 0; while(x >>= 1) ++ res; return res;}
int tax[N << 1];
void get_tax(int lim) {
    tax[0] = 0;
    for(int i = 0; i < 1 << lim; i ++)
        tax[i] = tax[i >> 1] >> 1 | (i & 1) << lim - 1;
}
struct Poly {
    int deg, a[N << 1];
    Poly() {deg = 0; memset(a, 0, sizeof a);}
    Poly(int n) {deg = n; memset(a, 0, n + 1 << 2);}
    void print() {
        for(int i = 0; i <= deg; i ++)
            printf("%d ", a[i]);
    }
    void NTT(int dir, int n) { //need get_tax
        int lim = log2(n) + 1;
        for(int i = 0; i < 1 << lim; i ++) if(i < tax[i]) swap(a[i], a[tax[i]]);
        for(int i = 2, w, t1, t2; i <= 1 << lim; i <<= 1) {
            w = Pow(~dir ? gen : invgen, (mod - 1) / i);
            for(int j = 0; j < 1 << lim; j += i) {
                for(int k = 0, wn = 1; k < i >> 1; k ++, wn = Mult(wn, w)) {
                    t1 = a[j + k], t2 = Mult(wn, a[j + (i >> 1) + k]);
                    a[j + k] = Add(t1, t2); a[j + (i >> 1) + k] = Minus(t1, t2);
                }
            }
        }
        if(!~dir) {
            int invn = Inv(1 << lim);
            for(int i = 0; i < 1 << lim; i ++)
                a[i] = Mult(a[i], invn);
        }
    }
    void NTT(int dir) {NTT(dir, deg + 1);}
    friend Poly operator * (Poly sub, Poly obj) {
        Poly res(sub.deg + obj.deg);
        int lim = log2(res.deg + 1) + 1;
        get_tax(lim);
        sub.NTT(1, res.deg + 1), obj.NTT(1, res.deg + 1);
        for(int i = 0; i < 1 << lim; i ++)
            res.a[i] = Mult(sub.a[i], obj.a[i]);
        res.NTT(-1);
        return res;
    }
} ;
int n;
Poly f, g;
Poly a, b, c;
void DFFT(int l = 0, int r = (1 << log2(n) + 1) - 1) {
    if(l == r) return;
    int mid = l + r >> 1;
    DFFT(l, mid);
    a.deg = mid - l, b.deg = r - l;
    for(int i = l; i <= mid; i ++) a.a[i - l] = f.a[i], b.a[i - l] = g.a[i - l];
    for(int i = mid + 1; i <= r; i ++) a.a[i - l] = 0, b.a[i - l] = g.a[i - l];
    c = a * b;
    for(int i = mid + 1; i <= r; i ++)
        f.a[i] = Add(f.a[i], c.a[i - l]);
    DFFT(mid + 1, r);
}
void Hutao() {
    n = read();
    f = Poly(n - 1), g = Poly(n - 1);
    f.a[0] = 1; g.a[0] = 0;
    for(int i = 1; i < n; i ++) g.a[i] = read();
    DFFT();
    f.print();
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}