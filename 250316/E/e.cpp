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

const int N = 1e5 + 10;
int n, m;
int rt[N], curseg;
struct segnode{
    int lc, rc;
    int cnt, ans;
}tr[N << 6];
void pushup(segnode &pa, segnode lc, segnode rc){
    if(lc.cnt > rc.cnt){
        pa.cnt = lc.cnt;
        pa.ans = lc.ans;
    } else if(lc.cnt < rc.cnt){
        pa.cnt = rc.cnt;
        pa.ans = rc.ans;
    } else{
        pa.cnt = lc.cnt;
        pa.ans = min(lc.ans, rc.ans);
    }
}
void Insert(int x, int val, int p, int l = 1, int r = N){
    if(l == r){
        tr[p].cnt += val;
        if(tr[p].cnt > 0) tr[p].ans = x;
        return;
    }
    int mid = l + (r - l >> 1);
    if(x <= mid){
        if(!tr[p].lc) tr[p].lc = ++ curseg;
        Insert(x, val, tr[p].lc, l, mid);
    }else{
        if(!tr[p].rc) tr[p].rc = ++ curseg;
        Insert(x, val, tr[p].rc, mid + 1, r);
    }
    pushup(tr[p], tr[tr[p].lc], tr[tr[p].rc]);
}
int Merge(int p1, int p2, int l = 1, int r = N){
    if(!p1 || !p2) return p1 | p2;
    if(l == r){
        tr[p1].cnt += tr[p2].cnt;
        if(tr[p1].cnt > 0) tr[p1].ans = l;
        return p1;
    }
    int mid = l + (r - l >> 1);
    tr[p1].lc = Merge(tr[p1].lc, tr[p2].lc, l, mid);
    tr[p1].rc = Merge(tr[p1].rc, tr[p2].rc, mid + 1, r);
    pushup(tr[p1], tr[tr[p1].lc], tr[tr[p1].rc]);
    return p1;
}
vector<int> e[N];
int dep[N], fa[20][N];
void dfs(int f, int u){
    fa[0][u] = f; dep[u] = dep[f] + 1;
    for(auto v : e[u]){
        if(v == f) continue;
        dfs(u, v);
    }
}
void INIT(){
    dfs(0, 1);
    for(int i = 1; i <= 19; i ++)
        for(int j = 1; j <= n; j ++)
            fa[i][j] = fa[i-1][fa[i-1][j]];
    for(int i = 1; i <= n; i ++)
        rt[i] = ++ curseg;
}
int LCA(int u, int v){
    if(dep[u] > dep[v]) swap(u, v);
    for(int i = 19; i >= 0; i --)
        if(dep[v] - dep[u] >= (1 << i))
            v = fa[i][v];
    if(u == v) return u;
    for(int i = 19; i >= 0; i --)
        if(fa[i][u] != fa[i][v])
            u = fa[i][u], v = fa[i][v];
    return fa[0][u];
}
int ans[N];
void dfs(int u){
    for(auto v : e[u]){
        if(v == fa[0][u]) continue;
        dfs(v);
        rt[u] = Merge(rt[u], rt[v]);
    }
    ans[u] = tr[rt[u]].ans;
}
int main(){
    n = read(), m = read();
    for(int i = 1, u, v; i < n; i ++){
        u = read(), v = read();
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    INIT();
    for(int i = 1, x, y, z; i <= m; i ++){
        x = read(), y = read(), z = read();
        Insert(z, 1, rt[x]);
        Insert(z, 1, rt[y]);
        int lca = LCA(x, y);
        Insert(z, -1, rt[lca]);
        if(fa[0][lca]) Insert(z, -1, rt[fa[0][lca]]);
    }
    dfs(1);
    for(int i = 1; i <= n; i ++)
        printf("%d\n", ans[i]);
    #ifdef db
    printf("%d\n", tr[rt[1]].cnt);
    #endif
    return 0;
}