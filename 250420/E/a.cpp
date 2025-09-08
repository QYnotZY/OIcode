#include "bits/stdc++.h"
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

const int N = 1e5 + 10;
int n;
vector<int> e[N];
int dep[N], maxdep[N], fa[N], hson[N];
ll *f[N], ans[N]; ll mpool[N]; int curpl;
inline ll c2(ll x) {return x * (x - 1) / 2;}
inline ll c3(ll x) {return x * (x - 1) / 2 * (x - 2) / 3;}
void dfs1(int u, int f){
    maxdep[u] = dep[u] = dep[f] + 1;
    fa[u] = f;
    for(auto v : e[u]){
        if(v == f) continue;
        dfs1(v, u);
        if(maxdep[v] > maxdep[u])
            hson[u] = v, maxdep[u] = maxdep[v];
    }
}
ll *newarr(int size){
    ll *res = mpool + curpl;
    curpl += size;
    return res;
}
void dfs2(int u, int t){
    if(u == t) f[u] = newarr(maxdep[u] - dep[u] + 1);
    else f[u] = f[fa[u]] + 1;
    f[u][0] = 1, ans[u] = 0;
    if(hson[u]){
        dfs2(hson[u], t);
        ans[u] = ans[hson[u]];
        if(2 <= maxdep[u] - dep[u]) ans[u] -= c3(f[u][2]);
        if(dep[u] <= maxdep[u] - dep[u]) ans[u] -= c2(f[u][dep[u]]);
        if(dep[u] + 1 <= maxdep[u] - dep[u]) ans[u] -= c2(f[u][dep[u] + 1]);
    }
    for(auto v : e[u]){
        if(v == fa[u] || v == hson[u]) continue;
        dfs2(v, v);
        for(int i = 0; i <= maxdep[v] - dep[v]; i ++){
            ans[u] -= (i + 1 == 1) * c3(f[u][i + 1]) + (i + 1 <= dep[u] - 1) * c2(f[u][i + 1]);
            f[u][i + 1] += f[v][i];
            ans[u] += (i + 1 == 1) * c3(f[u][i + 1]) + (i + 1 <= dep[u] - 1) * c2(f[u][i + 1]);
        }
    }
}
int main(){
    n = read();
    for(int i = 1; i < n; i ++){
        int u = read(), v = read();
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for(int i = 1; i <= n; i ++)
        ans[0] += ans[i];
    printf("%lld", ans[0]);
    return 0;
}