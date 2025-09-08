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
typedef long double ll;
typedef pair<int, ll> pil;
typedef pair<int, int> pii;
const int N = 1e5 + 10;
const ll inf = 1e18;
namespace work {
int n, l, p;
char s[N][32];
ll sum[N];
ll power(ll a, int b) {
    ll res = 1;
    for(; b; b >>= 1, a *= a)
        if(b & 1) res *= a;
    return res;
}
ll calc(int i, int j) {return power(abs(sum[j] - sum[i] - 1 - l), p);}
pil f[N];
pii q[N]; int ql, qr;
bool check(int i1, int i2, int mid) {
    return f[i1].second + calc(i1, mid) < f[i2].second + calc(i2, mid);
}
int bs(int i1, int i2) {
    int l = i2, r = n + 1;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(check(i1, i2, mid)) l = mid;
        else r = mid;
    }
    return l;
}
void init() {
    n = read(), l = read(), p = read();
    for(int i = 1; i <= n; i ++) {
        memset(s[i], 0, sizeof s[i]);
        scanf("%s", s[i]);
        sum[i] = sum[i - 1] + 1 + strlen(s[i]);
    }
}
void solve() {
    ql = 1, qr = 0;
    q[++ qr] = make_pair(0, n + 1);
    for(int i = 1; i <= n; i ++) {
        while(q[ql].second < i) ql ++;
        f[i] = make_pair(q[ql].first, f[q[ql].first].second + calc(q[ql].first, i));
        while(ql != qr && q[qr - 1].second >= bs(q[qr].first, i)) qr --;
        q[qr].second = bs(q[qr].first, i), q[++ qr] = make_pair(i, n + 1); //一定要注意前半句话
    }
}
void dfs_print(int d) {
    if(!f[d].first) {
        for(int i = 1; i < d; i ++)
            printf("%s ", s[i]);
        printf("%s\n", s[d]);
        return;
    }
    dfs_print(f[d].first);
    for(int i = f[d].first + 1; i < d; i ++)
        printf("%s ", s[i]);
    printf("%s\n", s[d]);
}
void print() {
    if(f[n].second > inf) {
        printf("Too hard to arrange\n");
        goto end;
    }
    write<long long>((long long)(f[n].second));
    dfs_print(n);
    end:
    for(int i = 1; i <= 20; i ++)
        putchar('-');
    putchar('\n');
}
int Main() {
    int t;
    cin >> t;
    while(t --) {
        init();
        solve();
        print();
    }
    return 0;
}
}
int main() {
    return work::Main();
}