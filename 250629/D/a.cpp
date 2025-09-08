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
const int N = 1e6 + 10;
namespace work {
int n, a[N], b[N];
ll lim[N], cnt[N];
ll ans;
int Main() {
    int t = read();
    while(t --) {
        n = read();
        for(int i = 1; i <= n; i ++)
            b[i] = 0, lim[i] = 1, cnt[i] = 0;
        for(int i = 1; i <= n; i ++)
            b[a[i] = read()] ++;
        for(int i = n; i >= 1; i --) {
            for(int j = i; j <= n; j += i) {
                if(b[i]) lim[j] = 0;
                cnt[i] += b[j];
            }
            cnt[i] = cnt[i] * (cnt[i] - 1) / 2;
            for(int j = i * 2; j <= n; j += i)
                cnt[i] -= cnt[j];
        }
        ans = 0;
        for(int i = 1; i <= n; i ++)
            ans += lim[i] * cnt[i];
        write<ll>(ans);
    }
    return 0;
}
}
int main() {
    return work::Main();
}