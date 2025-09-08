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
namespace work {
const int N = 2e5 + 10;
int n, m;
ll a[N], b[N], c[N];
ll suma[N], sumb[N], sumc[N];
int p1[N], p2[N];
bool cmp1(int A, int B) {
    return a[A] < a[B];
}
bool cmp2(int A, int B) {
    return (__int128_t)c[A] * (__int128_t)b[B] > (__int128_t)c[B] * (__int128_t)b[A];
}
ll bsans(int lb, int ub, int x) {
    int l = lb - 1, r = ub + 1, mid;
    while(l + 1 < r) {
        mid = l + r >> 1;
        if(b[p2[mid]] * x - c[p2[mid]] <= 0) l = mid;
        else r = mid;
    }
    return ll((__int128_t)sumb[l] * (__int128_t)x - (__int128_t)sumc[l]);
}
ll ans;
const ll inf = 0x7f7f7f7f7f7f7f7f;
void Hutao() {
    ans = inf;
    n = read(), m = read();
    for(int i = 1; i <= n; i ++) {
        a[i] = read<ll>(), p1[i] = i;
    }
    for(int i = 1; i <= m; i ++) {
        b[i] = read<ll>(), p2[i] = i;
    }
    for(int i = 1; i <= m; i ++)
        c[i] = read<ll>();
    sort(p1 + 1, p1 + n + 1, cmp1);
    sort(p2 + 1, p2 + m + 1, cmp2);
    for(int i = 1; i <= n; i ++)
        suma[i] = suma[i - 1] + a[p1[i]];
    for(int i = 1; i <= m; i ++)
        sumb[i] = sumb[i - 1] + b[p2[i]], sumc[i] = sumc[i - 1] + c[p2[i]];
    for(int i = 0; i <= n; i ++)
        ans = min(ans, suma[i] + bsans(1, m, n - i) + sumc[m]);
    write(ans);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}