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
int n, m, rt, p, a[N];
vector<int> to[N];
int fa[N], dep[N], sz[N], hson[N];
int dfn[N], redfn[N], tot;
void dfs(int u = rt, int f = 0) {
    fa[u] = f, dep[u] = dep[f] + 1, sz[u] = 1, hson[u] = 0;
    dfn[u] = ++ tot, redfn[tot] = u;
    for(auto v : to[u]) {
        if(v == fa[u]) continue;
        dfs(v, u);
        if(sz[v] > sz[hson[u]]) hson[u] = v;
        sz[u] += sz[v];
    }
}
int fa1[N], lc1[N], rc1[N], dep1[N];
int val1[N], sum1[N], tag1[N];
int buildc(int l, int r, int d) {
    if(l > r) return 0;
    int sum = 0, cur = 0, mid;
    for(int i = l; i <= r; i ++) sum += sz[redfn[i]] - sz[hson[redfn[i]]];
    for(mid = l; mid <= r; mid ++) {
        cur += sz[redfn[mid]] - sz[hson[redfn[mid]]];
        if(cur << 1 >= sum) break;
    }
    int lrt = buildc(l, mid - 1, d + 1), rrt = buildc(mid + 1, r, d + 1), rt = redfn[mid];
    fa1[lrt] = fa1[rrt] = rt;
    lc1[rt] = lrt, rc1[rt] = rrt;
    dep1[rt] = d;
    val1[rt] = a[rt], sum1[rt] = (sum1[lrt] + a[rt] + sum1[rrt]) % p, tag1[rt] = 0;
    return rt;
}
int build(int p = rt) {
    int u = p;
    do {
        for(auto v : to[u]) {
            if(v == fa[u] || v == hson[u]) continue;
            fa1[build(v)] = u;
        }
        u = hson[u];
    } while(hson[u]);
    return buildc(dfn[p], dfn[u], 1);
}
void Hutao() {
    n = read(), m = read(), rt = read(), p = read();
    for(int i = 1; i <= n; i ++) (a[i] = read()) %= p;
    for(int i = 1; i < n; i ++) {
        int u = read(), v = read();
        to[u].push_back(v), to[v].push_back(u);
    }
    for(int i = 1; i <= m; i ++) {
        int op = read(), x, y, z;
        if(op == 1) {
            x = read(), y = read(), (z = read()) %= p;

        } else if(op == 2) {
            x = read(), y = read();

        } else if(op == 3) {
            x = read(), (z = read()) %= p;

        } else {
            x = read();

        }
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}