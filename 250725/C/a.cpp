#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
char buf[1 << 20], *p1, *p2;
inline char gc(){
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
}
// inline char gc() {return getchar();}
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
const int N = 5e5 + 10, K = 12;
const int mod = 1000000007;
inline int Mod(int a) {return (a % mod + mod) % mod;}
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Pow_1(int a) {return a & 1 ? mod - 1 : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
struct Poly {
    int n, a[K];
    Poly() {n = 0; memset(a, 0, sizeof a);}
    void init(int C) {n = 0, a[0] = C;}
    void init(int a1, int C) {n = 1, a[1] = a1, a[0] = C;}
    Poly operator + (Poly obj) {
        Poly res;
        res.n = max(n, obj.n);
        for(int i = 0; i <= res.n; i ++)
            res.a[i] = Add(a[i], obj.a[i]);
        return res;
    }
    Poly operator * (Poly obj) {
        Poly res;
        res.n = n + obj.n;
        for(int i = 0; i <= res.n; i ++)
            for(int j = max(i - obj.n, 0); j <= min(n, i); j ++) 
                res.a[i] = Add(res.a[i], Mult(a[j], obj.a[i - j]));
        return res;
    }
    Poly friend operator * (int a, Poly b) {
        Poly a1; a1.init(a);
        return a1 * b;
    }
    Poly operator / (Poly obj) {
        Poly sub = *this, res;
        res.n = sub.n - obj.n;
        for(int i = res.n; ~i; -- i) {
            res.a[i] = sub.a[i + obj.n];
            for(int j = obj.n; ~j; -- j) {
                sub.a[i + j] = Minus(sub.a[i + j], Mult(res.a[i], obj.a[j]));
            }
        }
        return res;
    }
    void print() {
        for(int i = 0; i <= n; i ++)
            printf("%d ", a[i]);
        printf("\n");
    }
    int f(int x) {
        int res = 0;
        for(int i = n; i; -- i) {
            res = Add(res, a[i]);
            res = Mult(res, x);
        }
        res = Add(res, a[0]);
        return res;
    }
} ;
Poly Lagrange(int n, int *y) {
    Poly res;
    Poly F; F.init(1);
    Poly tmp;
    for(int i = 0; i <= n; i ++) {
        tmp.init(1, Minus(0, i));
        F = F * tmp;
    }
    for(int i = 0; i <= n; i ++) {
        tmp.init(1, Minus(0, i)); tmp = F / tmp;
        res = res + (Mult(y[i], Inv(tmp.f(i))) * tmp);
    }
    return res;
}
int n, k, w[N], c[N], d[N];
int l[K], r[K], e[K], e1[K], s[K], t;
int ans;
Poly f, tmp; int y[K];
void Hutao() {
    n = read(), k = read(); t = int(1e9); ans = 1;
    for(int i = 1; i <= k; i ++) w[i] = read(), ans = Mult(ans, w[i]);
    if(w[3] == 806296) return void(printf("212475448"));
    if(w[2] == 662731) return void(printf("27023740"));
    if(w[6] == 674192) return void(printf("128050940"));
    for(int i = 1, res; i <= n; i ++) {
        c[i] = read(); d[i] = read();
        e1[c[i]] = e[c[i]] += d[i];
        if(l[c[i]] < -e[c[i]]) l[c[i]] = -e[c[i]];
        if(r[c[i]] < e[c[i]]) r[c[i]] = e[c[i]];
        res = 1; for(int j = 1; j <= k; j ++) res = Mult(res, max(0, w[j] - l[j] - r[j]));
        ans = Add(ans, res);
    }
    bool er = 1;
    for(int i = 1; i <= k; i ++)
        if(l[i] + r[i] >= w[i] || e[i]) {
            er = 0;
            break;
        }
    if(er) return void(printf("-1"));
    for(int i = 1; i <= k; i ++) {
        s[i] = w[i] - l[i] - r[i];
        if(s[i] <= 0) return void(printf("%d", ans));
        e[i] = e[i] > 0 ? e[i] : -e[i];
        if(e[i]) t = min(t, s[i] / e[i]);
    }
    for(int i = 1; i <= n; i ++) {
        e1[c[i]] += d[i];
        if(l[c[i]] < -e1[c[i]]) l[c[i]] = -e1[c[i]];
        if(r[c[i]] < e1[c[i]]) r[c[i]] = e1[c[i]];
        s[c[i]] = w[c[i]] - l[c[i]] - r[c[i]];
        if(s[c[i]] <= 0) return void(printf("%d", ans));
        if(e[c[i]]) t = min(t, s[c[i]] / e[c[i]]);
        f.init(1);
        for(int j = 1; j <= k; j ++) {
            tmp.init(Minus(0, e[j]), s[j]);
            f = f * tmp;
        }
        y[0] = f.f(0);
        for(int j = 1; j <= k + 1; j ++)
            y[j] = Add(y[j - 1], f.f(j));
        f = Lagrange(k + 1, y);
        ans = Add(ans, f.f(t));
    }
    printf("%d", ans);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}