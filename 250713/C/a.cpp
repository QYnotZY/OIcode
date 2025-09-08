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
int n, c[N];
vector<int> to[N];
int tot, dfn[N], redfn[N], sz[N], hson[N];
void Skirk(int u = 1, int f = 0) {
    dfn[u] = ++ tot, redfn[tot] = u, sz[u] = 1, hson[u] = 0;
    for(auto v : to[u]) {
        if(v == f) continue;
        Skirk(v, u);
        if(sz[v] > sz[hson[u]]) hson[u] = v;
        sz[u] += sz[v];
    }
}
int b[N], maxsz; ll curans;
void add(int col) {
    b[col] ++;
    if(b[col] > maxsz) curans = col, maxsz = b[col];
    else if(b[col] == maxsz) curans += col;
}
ll ans[N];
void Layla(int u = 1, int f = 0, bool clr = true) {
    for(auto v : to[u]) {
        if(v == f || v == hson[u]) continue;
        Layla(v, u, 1);
    }
    if(hson[u]) Layla(hson[u], u, 0);
    add(c[u]);
    for(auto v : to[u]) {
        if(v == f || v == hson[u]) continue;
        for(int i = dfn[v]; i < dfn[v] + sz[v]; i ++)
            add(c[redfn[i]]);
    }
    ans[u] = curans;
    if(clr) {
        for(int i = dfn[u]; i < dfn[u] + sz[u]; i ++)
            -- b[c[redfn[i]]];
        curans = maxsz = 0;
    }
}
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++) c[i] = read();
    for(int i = 1; i < n; i ++) {
        int u = read(), v = read();
        to[u].push_back(v);
        to[v].push_back(u);
    }
    Skirk();
    Layla();
    for(int i = 1; i <= n; i ++)
        printf("%lld ", ans[i]);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}