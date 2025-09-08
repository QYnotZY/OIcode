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
const int K = 8, N = 300 + 10, inf = 1e6 + 1;
namespace work {
int n, k;
int a[N], b[K];
inline int dcf(int l, int r, int S) {return S * (n + 1) * (n + 1) + l * (n + 1) + r;}
int f[N * N * (1 << K)], len[1 << K];
ll ans;
int Main() {
    n = read(), k = read();
    for(int i = 1; i <= n; i ++)
        ans += (a[i] = read()) << 1;
    b[0] = b[k + 1] = inf;
    len[0] = 0;
    for(int i = 1, id; i <= k; i ++) {
        id = read();
        b[i] = a[id];
        a[id] = inf;
        for(int j = 0; j < 1 << i - 1; j = j << 1 | 1) {
            len[1 << i - 1 | j] = id - i - len[1 << i - 2] + len[j];
        }
    }
    sort(a + 1, a + n + 1);

    return 0;
}
}
int main() {
    return work::Main();
}
/*

*/