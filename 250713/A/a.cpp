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
const int N = 1e5 + 10;
map<int, int> furina; int tot;
int head[N], nxt[N], sz[N];
int a[N], cnt;
int n, m;
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= n; i ++) {
        a[i] = read();
        if(!furina[a[i]]) furina[a[i]] = ++ tot;
        a[i] = furina[a[i]];
        nxt[i] = head[a[i]];
        head[a[i]] = i;
        sz[a[i]] ++;
        if(a[i] != a[i - 1]) cnt ++;
    }
    for(int i = 1; i <= m; i ++) {
        int op = read();
        if(op == 2) printf("%d\n", cnt);
        else {
            int x = read(), y = read(), fr = furina[x], to = furina[y], ep = 0;
            if(x == y) continue;
            if(!to) {furina[x] = 0, furina[y] = fr; continue;}
            if(sz[fr] > sz[to]) swap(fr, to);
            furina[y] = to, furina[x] = 0;
            for(int i = head[fr]; i; i = nxt[i])
                cnt -= (a[i - 1] != a[i]) + (a[i] != a[i + 1]);
            for(int i = head[fr]; i; i = nxt[i])
                a[i] = to;
            for(int i = head[fr]; i; i = nxt[i]) {
                cnt += (a[i - 1] != a[i]) + (a[i] != a[i + 1]);
                if(!nxt[i]) ep = i;
            }
            sz[to] += sz[fr];
            nxt[ep] = head[to];
            head[to] = head[fr];
            head[fr] = 0;
        }
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}