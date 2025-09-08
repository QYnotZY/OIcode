#include "bits/stdc++.h"
using namespace std;
#include <atcoder/mincostflow>
using namespace atcoder;
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
namespace work{
const int N = 2e3 + 10;
mcf_graph<ll, ll> mcf(N);
int n, m, d, sum;
void Hutao() {
    n = read(), m = read(), d = read();
    int S = 1, T = n + 2;
    for(int i = 1; i <= n; i ++) {
        int a = read();
        mcf.add_edge(i, i + 1, m - a, 0);
        mcf.add_edge(i, i + 1, a, d);
        sum += a;
    }
    mcf.add_edge(n + 1, T, m, 0);
    for(int i = 1; i <= m; i ++) {
        int l = read(), r = read(), c = read();
        mcf.add_edge(l, r + 1, 1, c);
    }
    write(1ll * sum * d - mcf.flow(S, T, 1e15).second);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}