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
int n, m, a[N];
ll ans[N];
int rt[N], curseg;
struct segnode{
    int lc, rc;
    int cnt; ll ans;
}tr[N << 5];
void pushup(segnode &pa, segnode lc, segnode rc){
    if(lc.cnt > rc.cnt){
        pa.cnt = lc.cnt;
        pa.ans = lc.ans;
    } else if(lc.cnt < rc.cnt){
        pa.cnt = rc.cnt;
        pa.ans = rc.ans;
    } else{
        pa.cnt = lc.cnt;
        pa.ans = lc.ans + rc.ans;
    }
}
void Create(int x, int p, int l = 1, int r = n){
    if(l == r){
        tr[p].cnt = 1;
        tr[p].ans = x;
        return;
    }
    int mid = l + (r - l >> 1);
    if(x <= mid){
        tr[p].lc = ++ curseg;
        Create(x, tr[p].lc, l, mid);
    } else{
        tr[p].rc = ++ curseg;
        Create(x, tr[p].rc, mid + 1, r);
    }
    pushup(tr[p], tr[tr[p].lc], tr[tr[p].rc]);
}
int Merge(int p1, int p2, int l = 1, int r = n){
    if(!p1) return p2;
    if(!p2) return p1;
    if(l == r){
        tr[p1].cnt += tr[p2].cnt;
        return p1;
    }
    int mid = l + (r - l >> 1);
    tr[p1].lc = Merge(tr[p1].lc, tr[p2].lc, l, mid);
    tr[p1].rc = Merge(tr[p1].rc, tr[p2].rc, mid + 1, r);
    pushup(tr[p1], tr[tr[p1].lc], tr[tr[p1].rc]);
    return p1;
}
vector<int> e[N];
void dfs(int f, int u){
    rt[u] = ++ curseg;
    Create(a[u], rt[u]);
    for(auto v : e[u]){
        if(v == f) continue;
        dfs(u, v);
        rt[u] = Merge(rt[u], rt[v]);
    }
    ans[u] = tr[rt[u]].ans;
}
int main(){
    n = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    for(int i = 1, u, v; i < n; i ++){
        u = read(), v = read();
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    dfs(0, 1);
    for(int i = 1; i <= n; i ++){
        printf("%lld ", ans[i]);
    }
    return 0;
}