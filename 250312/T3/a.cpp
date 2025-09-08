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
int n, m, fol;
vector<int> e[N];
int rt[2][N], tot[2];
ll w[N], v[N];
struct segnode{
    int lc, rc;
    ll taga1, tagk;
}tr[2][N << 5];
void Create(int tp, int p, int l = ~n + 1, int r = n << 1){
    tr[tp][p] = segnode{0, 0, 0, 0};
    if(l == r) return;
    int mid = l + (r - l >> 1);
    tr[tp][p].lc = ++ tot[tp];
    Create(tp, tot[tp], l, mid);
    tr[tp][p].rc = ++ tot[tp];
    Create(tp, tot[tp], mid + 1, r);
}
void Modify(int tp, int l0, int r0, ll k, ll b, int p, int p1, int l = ~n + 1, int r = n << 1){
    tr[tp][p1] = tr[tp][p];
    if(l0 <= l && r <= r0){
        tr[tp][p1].taga1 += k * l + b;
        tr[tp][p1].tagk += k;
        return;
    }
    int mid = l + (r - l >> 1);
    if(l0 <= mid){
        tr[tp][p1].lc = ++tot[tp];
        Modify(tp, l0, r0, k, b, tr[tp][p].lc, tot[tp], l, mid);
    }
    if(r0 >= mid + 1){
        tr[tp][p1].rc = ++tot[tp];
        Modify(tp, l0, r0, k, b, tr[tp][p].rc, tot[tp], mid + 1, r);
    }
}
ll Query(int tp, int x0, int p, int l = ~n + 1, int r = n << 1){
    if(l == x0 && x0 == r)
        return tr[tp][p].taga1;
    int mid = l + (r - l >> 1);
    ll res = tr[tp][p].taga1 + tr[tp][p].tagk * (x0 - l);
    if(x0 <= mid) return res + Query(tp, x0, tr[tp][p].lc, l, mid);
    else return res + Query(tp, x0, tr[tp][p].rc, mid + 1, r);
}
int fa[20][N], dep[N];
inline ll ceildiv(ll a, ll b){
    if(b < 0){
        a = -a;
        b = -b;
    }
    if(a < 0) return a / b;
    return (a + b - 1) / b;
}
inline ll floordiv(ll a, ll b){
    if(b < 0){
        a = -a;
        b = -b;
    }
    if(a >= 0) return a / b;
    return (a - b + 1) / b;
}
void dfs(int f, int u){
    fa[0][u] = f, dep[u] = dep[f] + 1;
    ll k = v[u], b = w[u], l0, r0;
    if(k > 0){
        l0 = max(~(ll)n + 1, ceildiv(dep[u] * k - b, k));
        r0 = n << 1;
        rt[0][u] = ++ tot[0];
        if(l0 <= r0) Modify(0, l0, r0, k, -dep[u] * k + b, rt[0][f], rt[0][u]);
        else Modify(0, ~n + 1, n << 1, 0, 0, rt[0][f], rt[0][u]);
        l0 = max(~(ll)n + 1, ceildiv(- dep[u] * k - b, k));
        r0 = n << 1;
        rt[1][u] = ++ tot[1];
        if(l0 <= r0) Modify(1, l0, r0, k, dep[u] * k + b, rt[1][f], rt[1][u]);
        else Modify(1, ~n + 1, n << 1, 0, 0, rt[1][f], rt[1][u]);
    }
    if(k == 0){
        if(b > 0) Modify(0, ~n + 1, n << 1, 0, b, rt[0][f], rt[0][u]=++tot[0]),
                  Modify(1, ~n + 1, n << 1, 0, b, rt[1][f], rt[1][u]=++tot[1]);
        else Modify(0, ~n + 1, n << 1, 0, 0, rt[0][f], rt[0][u]=++tot[0]),
             Modify(1, ~n + 1, n << 1, 0, 0, rt[1][f], rt[1][u]=++tot[1]);
    }
    if(k < 0){
        r0 = min((ll)n << 1, floordiv(dep[u] * k - b, k));
        l0 = ~n + 1;
        rt[0][u] = ++ tot[0];
        if(l0 <= r0) Modify(0, l0, r0, k, -dep[u] * k + b, rt[0][f], rt[0][u]);
        else Modify(0, ~n + 1, n << 1, 0, 0, rt[0][f], rt[0][u]);
        r0 = min((ll)n << 1, floordiv(- dep[u] * k - b, k));
        l0 = ~n + 1;
        rt[1][u] = ++ tot[1];
        if(l0 <= r0) Modify(1, l0, r0, k, dep[u] * k + b, rt[1][f], rt[1][u]);
        else Modify(1, ~n + 1, n << 1, 0, 0, rt[1][f], rt[1][u]);
    }
    #ifdef db
    printf("%d::\n", u);
    for(int i = ~n + 1; i <= n << 1; i ++)
        printf("%lld ", Query(1, i, rt[1][u]));
    printf("\n");
    for(int i = ~n + 1; i <= n << 1; i ++)
        printf("%lld ", Query(0, i, rt[0][u]));
    printf("\n");
    #endif
    for(auto v : e[u]){
        if(v == f) continue;
        dfs(u, v);
    }
}
void getfa(){
    for(int i = 1; i < 20; i ++)
        for(int j = 1; j <= n; j ++)
            fa[i][j] = fa[i-1][fa[i-1][j]];
}
int LCA(int u, int v){
    if(dep[u] > dep[v]) swap(u, v);
    for(int i = 19; i >= 0; i --)
        if(dep[v] - dep[u] >= 1 << i)
            v = fa[i][v];
    if(u == v) return u;
    for(int i = 19; i >= 0; i --)
        if(fa[i][u] != fa[i][v])
            u = fa[i][u], v = fa[i][v];
    return fa[0][u];
}
int main(){
    #ifndef nt
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    #endif
    read(), n = read(), m = read(), fol = read();
    rt[0][0] = ++ tot[0];
    Create(0, 1);
    rt[1][0] = ++ tot[1];
    Create(1, 1);
    for(int i = 1, u, v; i < n; i ++){
        u = read(), v = read();
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    for(int i = 1; i <= n; i ++)
        w[i] = read<ll>();
    for(int i = 1; i <= n; i ++)
        v[i] = read<ll>();
    dep[0] = -1;
    dfs(0, 1);
    getfa();
    ll res = 0;
    for(int i = 1, x, y, t, lca, falca; i <= m; i ++){
        x = (read() + res * fol - 1) % n + 1, y = (read() + res * fol - 1) % n + 1, t = (read() + res * fol - 1) % n + 1;
        lca = LCA(x, y), falca = fa[0][lca];
        res = Query(0, t + dep[x], rt[0][x]) - Query(0, t + dep[x], rt[0][falca]) + Query(1, t + dep[x] - 2 * dep[lca], rt[1][y]) - Query(1, t + dep[x] - 2 * dep[lca], rt[1][lca]);
        printf("%lld\n", res);
    }
    return 0;
}