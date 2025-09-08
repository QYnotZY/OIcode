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
const int N = 2e6 + 10, M = 5000 + 10;
int n, m, a;
int f[M], f1[M], g[M], cnt;
int ans;
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= n + 1; i ++) {
        a = i <= n ? read() : 0;
        if(abs(a) > cnt) continue;
        if(a > 0) {
            g[a] ++;
        } else if(a < 0) {
            a = -a;
            g[0] ++, g[cnt - a + 1] --;
        } else {
            f[0] += g[0];
            for(int i = 1; i <= cnt; i ++) {
                g[i] += g[i - 1];
                f[i] += g[i];
            }
            cnt ++;
            g[0] = 0;
            f1[0] = f[0];
            for(int i = 1; i <= cnt; i ++) {
                f1[i] = max(f[i], f[i - 1]);
                g[i] = 0;
            }
            for(int i = 0; i <= cnt; i ++) {
                f[i] = f1[i];
                f1[i] = 0;
            }
        }
        #ifdef db
        for(int i = 0; i <= cnt; i ++)
            printf("%d,%d ", f[i], g[i]);
        printf("\n");
        #endif
    }
    for(int i = 0; i <= m; i ++)
        ans = max(ans, f[i]);
    write(ans);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}