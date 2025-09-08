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
const int N = 2e5 + 10, inf = 1e6;
namespace work {
int n, a[N], minn[N], maxx[N];
int Main() {
    int t = read();
    while(t --) {
        n = read();
        for(int i = 1; i <= n; i ++) {
            a[i] = read();
        }
        minn[0] = inf;
        for(int i = 1; i <= n; i ++)
            minn[i] = min(minn[i - 1], a[i]);
        maxx[n + 1] = 0;
        for(int i = n; i; i --)
            maxx[i] = max(maxx[i + 1], a[i]);
        for(int i = 1; i <= n; i ++) {
            printf(minn[i - 1] < a[i] && a[i] < maxx[i + 1] ? "0" : "1");
        }
        printf("\n");
    }
    return 0;
}
}
int main() {
    return work::Main();
}