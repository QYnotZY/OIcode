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
ll a[N], b[N], f[N], g[N], ans[N];
bool Skirk(int i, int k) {return f[i] + g[k - i] <= f[i + 1] + g[k - i - 1];}
ll Layla(int lb, int ub, int k) {
    if(lb > ub) return -1;
    int l = lb - 1, r = ub, mid;
    #ifdef db
    printf("%d %d\n", l, r);
    #endif
    while(l + 1 < r) {
        mid = l + r >> 1;
        if(Skirk(mid, k)) l = mid;
        else r = mid;
        #ifdef db
        printf("%d %d\n", l, r);
        #endif
    }
    return f[r] + g[k - r];
}
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read<ll>();
    for(int i = 1; i <= m; i ++)
        b[i] = read<ll>();
    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1);
    for(int i = 1; i <= n >> 1; i ++)
        f[i] = f[i - 1] - a[i] + a[n - i + 1];
    for(int i = 1; i <= m >> 1; i ++)
        g[i] = g[i - 1] - b[i] + b[m - i + 1];
    for(int k = 1; k <= (n + m) / 3 + 1; k ++) {
        if(k > (n + m) / 3) ans[k] = -1;
        else ans[k] = Layla(max(0, 2 * k - m), min(k, n - k), k);
        if(ans[k] == -1) {
            write(k - 1);
            for(int i = 1; i < k; i ++)
                write<ll>(ans[i], ' ');
            if(k - 1) putchar('\n');
            break;
        }
    }
}
}
int main() {
    int t = read();
    while(t --) work::Hutao();
    return 0;
}