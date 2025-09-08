#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// inline char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
inline char gc() {return getchar();}
template<typename T>
inline T readnum(){
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
template<typename T = int>
inline T read() {return readnum<T>();}
char wc[50]; int top;
template<typename T>
inline void writenum(T x, char sp){
    if(!x) return putchar('0'), void(putchar(sp));
    if(x < 0) putchar('-'), x = ~x + 1;
    top = 0;
    for(; x; x /= 10) wc[top ++] = x % 10 ^ 48;
    while(top --) putchar(wc[top]);
    putchar(sp);
}
template<typename T = int>
inline void write(T x, char sp = '\n'){
    writenum(x, sp);
}
}
using FastIO::read;
using FastIO::write;
typedef long long ll;
const int sqN = 4e5 + 10;
const int mod = 998244353;
namespace work {
inline int Mod(ll a) {return (a % mod + mod) % mod;}
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
struct Poly {
    int deg, a[40];
    void init(int n, bool _1 = false) {
        deg = n;
        for(int i = 0; i <= deg; i ++)
            a[i] = 0;
        if(_1) a[0] = 1;
    }
    Poly operator + (Poly obj) {
        Poly res; res.init(max(deg, obj.deg));
        for(int i = 0; i <= res.deg; i ++) {
            if(deg < i) res.a[i] = obj.a[i];
            else if(obj.deg < i) res.a[i] = a[i];
            else res.a[i] = Add(a[i], obj.a[i]);
        }
        return res;
    }
    Poly operator + (int a) {
        Poly tmp; tmp.init(0);
        tmp.a[0] = a;
        return *this + tmp;
    }
    Poly operator * (Poly obj) {
        Poly res; res.init(deg + obj.deg);
        for(int i = 0; i <= deg; i ++)
            for(int j = 0; j <= obj.deg; j ++)
                res.a[i + j] = Add(res.a[i + j], Mult(a[i], obj.a[j]));
        return res;
    }
    Poly friend operator * (int a, Poly b) {
        Poly tmp; tmp.init(0);
        tmp.a[0] = a;
        return tmp * b;
    }
    Poly friend operator ^ (Poly sub, Poly obj) {
        Poly res; res.init(0);
        for(int i = obj.deg; i; i --) {
            
            res = res + obj.a[i];
            res = res * sub;
        }
        res = res + obj.a[0];
        return res;
    }
    int calc(int x) {
        int res = 0;
        for(int i = deg; i; i --) {
            res = Add(res, a[i]);
            res = Mult(res, x);
        }
        res = Add(res, a[0]);
        return res;
    }
} ;
Poly Lagrange(int n, int *y) {
    Poly res; res.init(n - 1);
    Poly tmp; tmp.init(1); tmp.a[1] = 1;
    Poly cur;
    for(int i = 1; i <= n; i ++) {
        cur.init(0); cur.a[0] = y[i];
        for(int j = 1; j <= n; j ++) {
            if(i == j) continue;
            tmp.a[0] = Minus(0, j);
            cur = cur * (Inv(Minus(i, j)) * tmp);
        }
        res = res + cur;
    }
    return res;
}
Poly h[40];
void init() {
    static int y[40];
    y[0] = 0;
    for(int i = 0; i < 36; i ++) {
        for(int j = 1; j <= i + 2; j ++)
            y[j] = Add(y[j - 1], Pow(j, i));
        h[i] = Lagrange(i + 2, y);
    }
}
int cur;
map<ll, int> pos;
set<ll> s;
Poly f[sqN];
void trans(ll m, int k) {
    int i1 = pos[m], i2 = pos[m / k];
    Poly tmp; tmp.init(1); tmp.a[1] = k; tmp.a[0] = Minus(Add(1, m % k), k);
    Poly g = tmp ^ f[i1];
    Poly cur; cur.init(0);
    for(int j = 0; j <= g.deg; j ++)
        cur = cur + (g.a[j] * h[j]);
    f[i2] = f[i2] + cur;
}
int ans;
int Main() {
    init();
    ll n = read<ll>(); int k = read();
    s.insert(n); pos[n] = ++ cur; f[cur].init(0, 1);
    while(s.size()) {
        ll i = *(s.rbegin());
        for(int j = 2; j <= k; j ++) {
            if(pos.find(i / j) == pos.end()) pos[i / j] = ++ cur, s.insert(i / j);
            trans(i, j);
        }
        ans = Add(ans, f[pos[i]].calc(Mod(i)));
        #ifdef db
        for(int j = 0; j <= f[pos[i]].deg; j ++)
            printf("%d ", f[pos[i]].a[j]);
        printf("\n");
        #endif
        s.erase(i);
    }
    write(ans);
    return 0;
}
}
int main() {
    #ifndef db
    freopen("coin.in", "r", stdin);
    freopen("coin.out", "w", stdout);
    #endif
    return work::Main();
}