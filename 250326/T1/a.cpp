#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
template<typename T=int> 
T readnum(){
    T res=0; bool f=0;
    char ch=getchar();
    while(!('0'<=ch&&ch<='9')){
        if(ch=='-') f=!f;
        ch=getchar();
    }
    while('0'<=ch&&ch<='9'){
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    return f?~res+1:res;
}
template<typename T=int>
T read() {return readnum<T>();}

const int N = 3e5 + 10;
int n, m;
namespace work{
ll w[N];
vector<int> to[N];
ll msiz[N], siz[N], sumsiz, ans0;
void input(){
    n = read(), m = read();
    for(int i = 1; i <= n; i ++){
        w[i] = read<ll>();
        sumsiz += w[i];
    }
    for(int i = 1, u, v; i < n; i ++){
        u = read(), v = read();
        to[u].emplace_back(v);
        to[v].emplace_back(u);
    }
}
void dfs_cg(int u, int fat){
    siz[u] = w[u];
    msiz[u] = 0;
    for(auto v : to[u]){
        if(v == fat) continue;
        dfs_cg(v, u);
        msiz[u] = max(msiz[u], siz[v]);
        siz[u] += siz[v];
    }
    msiz[u] = max(msiz[u], sumsiz - siz[u]);
}
int get_cg(){
    int res = 1;
    dfs_cg(1, 0);
    for(int i = 1; i <= n; i ++){
        if(msiz[res] > msiz[i]) res = i;
    }
    return res;
}
ll presiz[N];
int sz[N];
int fa[20][N], dep[N], dfn[N], curdfn;
void dfs_init(int u, int fat){
    fa[0][u] = fat;
    siz[u] = w[u]; sz[u] = 1;
    dep[u] = dep[fat] + 1;
    dfn[u] = ++ curdfn;
    for(auto v : to[u]){
        if(v == fat) continue;
        dfs_init(v, u);
        siz[u] += siz[v]; sz[u] += sz[v];
    }
    if(fat != 0) ans0 += siz[u];
}
void dfs_pre(int u, int fat){
    presiz[u] = presiz[fat] + siz[u];
    for(auto v : to[u]){
        if(v == fat) continue;
        dfs_pre(v, u);
    }
}
namespace LCA{
void init(){
    for(int i = 1; i < 20; i ++)
        for(int j = 1; j <= n; j ++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
}
int lca(int u, int v){
    if(dep[u] > dep[v]) swap(u, v);
    for(int i = 19; i >= 0; i --)
        if(dep[fa[i][v]] >= dep[u])
            v = fa[i][v];
    if(u == v) return u;
    for(int i = 19; i >= 0; i --)
        if(fa[i][u] != fa[i][v])
            u = fa[i][u], v = fa[i][v];
    return fa[0][u];
}
} using LCA::lca;
bool isa(int u, int v){
    return dfn[u] <= dfn[v] && dfn[v] < dfn[u] + sz[u];
}
int find(int y, int z, ll sizv){
    for(int i = 19; i >= 0; i --)
        if(isa(z, fa[i][y]) && z != fa[i][y])
            if(siz[fa[i][y]] + sizv <= sumsiz - siz[fa[i][y]] - sizv)
                y = fa[i][y];
    if(isa(z, y) && z != y)
        if(siz[y] + sizv <= sumsiz - siz[y] - sizv)
            y = fa[0][y];
    return y;
}
ll query(int u, int v, int x, int y){
    if(fa[0][u] == v) swap(u, v);
    if(fa[0][v] != u) return 0ll;
    if(isa(v, x)) swap(x, y);
    if(isa(v, x) || !isa(v, y)) return 0ll;
    int z = lca(u, x);
    ll d1 = -(dep[v] - dep[z]) * siz[v];
    int bound = find(x, z, siz[v]);
    ll d2 = (dep[x] + 1 - dep[bound]) * siz[v];
    d2 += (dep[bound] - dep[z]) * (sumsiz - siz[v]) - (presiz[bound] - presiz[z] << 1);
    ll d3 = (dep[y] - dep[v]) * siz[v] - (presiz[y] - presiz[v] << 1);
    return ans0 + d1 + d2 + d3;
}
}
ll ans;
int main(){
    work::input();
    int rt = work::get_cg();
    work::dfs_init(rt, 0);
    work::dfs_pre(rt, 0);
    work::LCA::init();
    for(int u, v, x, y; m --;){
        u = read(), v = read(), x = read(), y = read();
        ans ^= work::query(u, v, x, y) << 1;
    }
    printf("%lld", ans);
    return 0;
}