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
inline int Neg(int a) {return a ? mod - a : 0;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
struct BIT {
    int n, pre[N];
    inline int lowbit(int x) {return x & -x;}
    void init(int n) {
        this -> n = n;
        for(int i = 1; i <= n; i ++) {
            pre[i] = 0;
        }
    }
    void add(int pos, int val) {
        int x = pos;
        while(x <= n) {
            pre[x] = Add(pre[x], val);
            x += lowbit(x);
        }
    }
    int query(int pos, int typ) { //pre 0  suf 1
        int x = pos - typ, res = 0;
        while(x) {
            res = Add(res, pre[x]);
            x -= lowbit(x);
        }
        return typ ? Minus(query(n, 0), res) : res;
    }
} bit[4];
char s[N];
int n, q, ans;
void solve() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    bit[0].init(n), bit[1].init(n), bit[2].init(n), bit[3].init(n);
    for(int i = 1; i <= n; i ++) {
        bit[s[i] - '0'].add(i, Pow(2, i - 1));
        bit[2 + s[i] - '0'].add(i, Pow(2, n - i));
    }
    ans = 0;
    for(int i = 1; i <= n; i ++) {
        ans = Add(ans, Mult(Add(bit['1' - s[i]].query(i - 1, 0), 1), Pow(2, n - i)));
    }
    q = read();
    for(; q --;) {
        int i = read();
        ans = Minus(ans, Mult(Add(bit['1' - s[i]].query(i - 1, 0), 1), Pow(2, n - i)));
        ans = Minus(ans, Mult(bit[2 + '1' - s[i]].query(i + 1, 1), Pow(2, i - 1)));
        bit[s[i] - '0'].add(i, Neg(Pow(2, i - 1)));
        bit[2 + s[i] - '0'].add(i, Neg(Pow(2, n - i)));
        s[i] = '1' - s[i] + '0';
        bit[s[i] - '0'].add(i, Pow(2, i - 1));
        bit[2 + s[i] - '0'].add(i, Pow(2, n - i));
        ans = Add(ans, Mult(Add(bit['1' - s[i]].query(i - 1, 0), 1), Pow(2, n - i)));
        ans = Add(ans, Mult(bit[2 + '1' - s[i]].query(i + 1, 1), Pow(2, i - 1)));
        write(ans, ' ');
    }
    printf("\n");
}
int Main() {
    int t = read();
    while(t --) solve();
    return 0;
}
}
int main() {
    return work::Main();
}