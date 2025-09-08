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
using FastIO::readch;
using FastIO::write;
typedef long long ll;
namespace work {
const int N = 5e5 + 10;
int n, val[N];
vector<int> son[N];
int tot, dfn[N], redfn[N], sz[N], hson[N], dep[N], dis[N];
void Citlali(int u = 1, int f = 0) {
    dep[u] = dep[f] + 1, dfn[u] = ++ tot, redfn[tot] = u, sz[u] ++, hson[u] = 0;
    dis[u] = dis[f] ^ 1 << val[u];
    for(auto v : son[u]) {
        Citlali(v, u);
        if(sz[v] > sz[hson[u]]) hson[u] = v;
        sz[u] += sz[v];
    }
}
int buc[N * 20];
int check(int lca, int u, int tgt) {
    if(buc[tgt ^ dis[u]]) {
        return dep[u] + buc[tgt ^ dis[u]] - (dep[lca] << 1);
    }
    return 0;
}
int query(int lca, int u) {
    int res = check(lca, u, 0);
    for(int i = 1; i < 1 << 23; i <<= 1) {
        res = max(res, check(lca, u, i));
    }
    return res;
}
void add(int x) {
    if(dep[x] > buc[dis[x]]) buc[dis[x]] = dep[x];
}
int ans[N];
int Furina(int u = 1, int f = 0, bool clr = 0) {
    int res = 0;
    for(auto v : son[u]) if(v != hson[u]) res = max(res, Furina(v, u, 1));
    if(hson[u]) res = max(res, Furina(hson[u], u, 0));
    res = max(res, query(u, u)); add(u);
    for(auto v : son[u]) {
        if(v == hson[u]) continue;
        for(int i = dfn[v]; i < dfn[v] + sz[v]; i ++) res = max(res, query(u, redfn[i]));
        for(int i = dfn[v]; i < dfn[v] + sz[v]; i ++) add(redfn[i]);
    }
    if(clr) {
        for(int i = dfn[u]; i < dfn[u] + sz[u]; i ++)
            buc[dis[redfn[i]]] = 0;
    }
    return ans[u] = res;
}
void Hutao() {
    n = read();
    for(int i = 2; i <= n; i ++) {
        int x = read(); char ch = readch();
        val[i] = ch - 'a';
        son[x].emplace_back(i);
    }
    Citlali(); Furina();
    for(int i = 1; i <= n; i ++)
        printf("%d ", ans[i]);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}