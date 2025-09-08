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
const int N = 2e5 + 10;
const int mod = 998244353;
namespace work {
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {
    return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;
}
int n, y[N];
struct SMT {
    int sum[N << 2], tag[N << 2];
    void pushup(int p) {
        sum[p] = Add(sum[p << 1], sum[p << 1 | 1]);
    }
    void u1(int p, int val) {
        sum[p] = Mult(sum[p], val);
        tag[p] = Mult(tag[p], val);
    }
    void pushdown(int p) {
        u1(p << 1, tag[p]);
        u1(p << 1 | 1, tag[p]);
        tag[p] = 1;
    }
    void create(int p = 1, int l = 1, int r = n - 1) {
        sum[p] = 1, tag[p] = 1;
        if(l == r) return;
        int mid = l + r >> 1;
        create(p << 1, l, mid);
        create(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int ql, int qr, int p = 1, int l = 1, int r = n - 1) {
        if(ql > qr) return;
        if(ql <= l && r <= qr)
            return u1(p, 2);
        int mid = l + r >> 1;
        pushdown(p);
        if(ql <= mid) update(ql, qr, p << 1, l, mid);
        if(qr > mid) update(ql, qr, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    int query() {
        return sum[1];
    }
} smt;
int ans, c1_4, c5_8;
int Main() {
    n = read();
    for(int i = 1; i <= n; i ++)
        y[i] = read();
    smt.create();
    for(int i = 1; i <= n - 1; i ++) {
        smt.update(y[i], n - 1);
        c5_8 = Add(c5_8, smt.query());
    }
    smt.create();
    for(int i = 1; i <= n - 1; i ++) {
        smt.update(1, y[i] - 1);
        c5_8 = Add(c5_8, smt.query());
    }
    smt.create();
    for(int i = n; i >= 2; i --) {
        smt.update(y[i], n - 1);
        c5_8 = Add(c5_8, smt.query());
    }
    smt.create();
    for(int i = n; i >= 2; i --) {
        smt.update(1, y[i] - 1);
        c5_8 = Add(c5_8, smt.query());
    }
    c1_4 = Mult(Mult(4, n - 1), Minus(Pow(2, n), 2));
    ans = Mult(Mult(n - 1, n - 1), Minus(Pow(2, n), 1));
    ans = Add(Minus(ans, c1_4), c5_8);
    write(ans);
    return 0;
}
}
int main() {
    return work::Main();
}