#include "bits/stdc++.h"
#define int unsigned int
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
char gc() {return getchar();}
template<typename T = int>
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
T read() {return readnum<T>();}
}
using FastIO::read;
typedef long long ll;

int s;
inline int get(int x){
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return s = x;
}

const int N = 5e5 + 10;
vector<int> son[N];
int fa[22][N];
int dep[N], maxdep[N];
int hson[N];
void dfs1(int u, int f){
    for(int i = 1; i < 22; i ++)
        fa[i][u] = fa[i - 1][fa[i - 1][u]];
    maxdep[u] = dep[u] = dep[f] + 1;
    for(auto v : son[u]){
        dfs1(v, u);
        if(maxdep[v] > maxdep[u]){
            maxdep[u] = maxdep[v];
            hson[u] = v;
        }
    }
}
int dfn[N], dcur;
int top[N];
vector<int> lis[N];
void dfs2(int u, int t){
    dfn[u] = ++ dcur;
    top[u] = t;
    if(hson[u])
        dfs2(hson[u], t);
    lis[t].emplace_back(u);
    if(u == t)
        for(int i = maxdep[u], cur = fa[0][u]; i >= dep[u]; -- i, cur = fa[0][cur])
            lis[t].emplace_back(cur);
    for(auto v : son[u]){
        if(v == hson[u]) continue;
        dfs2(v, v);
    }
}
int n, q;
int Log2[N];
void init(){
    n = read(), q = read(), s = read();
    for(int i = 1, f; i <= n; i ++){
        f = read();
        fa[0][i] = f;
        son[f].emplace_back(i);
    }
    Log2[1] = 0;
    for(int i = 2; i <= n; i ++)
        Log2[i] = Log2[i / 2] + 1;
    dfs1(son[0][0], 0);
    dfs2(son[0][0], son[0][0]);
}
int query(int d, int k){
    if(k == 0) return d;
    d = fa[Log2[k]][d];
    k -= 1 << Log2[k];
    int now = maxdep[d] - dep[d];
    return lis[top[d]][now + k];
}
int lstans = 0;
ll ans;
signed main(){
    init();
    for(int i = 1; i <= q; i ++){
        int x = (get(s) ^ lstans) % n + 1, k = (get(s) ^ lstans) % dep[x];
        ans ^= ll(lstans = query(x, k)) * i;
    }
    printf("%lld", ans);
    return 0;
}