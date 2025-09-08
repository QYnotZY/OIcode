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
template<typename T=int> T read() {return readnum<T>();}
const int N=1e6+10;
int n,m,rt;
vector<int> e[N];
int a[N],a1[N];
int fa[N],sz[N],dfn[N],curdfn;
void dfs(int f,int u){
    fa[u]=f,sz[u]=1,dfn[u]=++curdfn;
    a1[curdfn]=a[u];
    for(auto v:e[u]){
        if(v==f) continue;
        dfs(u,v);
        sz[u]+=sz[v];
    }
}
inline int mid(int l,int r) {return l+(r-l>>1);}
inline int lc(int p) {return p<<1;}
inline int rc(int p) {return p<<1|1;}
struct segnode{
    int l,r;
    ll sum,tag;
    int size(){
        return r-l+1;
    }
}tr[N<<2];
void upd1(int p,ll add){
    tr[p].sum += add * tr[p].size();
    tr[p].tag += add;
}
void pushup(int p,int lcp,int rcp){
    tr[p].sum = tr[lcp].sum + tr[rcp].sum;
}
void pushdown(int p,int lcp,int rcp){
    upd1(lcp, tr[p].tag);
    upd1(rcp, tr[p].tag);
    tr[p].tag = 0;
}
void Modify(int l0,int r0,ll val,int p=1){
    if(l0 <= tr[p].l && tr[p].r <= r0){
        upd1(p, val);
        return;
    }
    pushdown(p, lc(p), rc(p));
    if(l0 <= tr[lc(p)].r) Modify(l0, r0, val, lc(p));
    if(r0 >= tr[rc(p)].l) Modify(l0, r0, val, rc(p));
    pushup(p, lc(p), rc(p));
}
ll Query(int l0,int r0,int p=1){
    if(l0 <= tr[p].l && tr[p].r <= r0)
        return tr[p].sum;
    pushdown(p, lc(p), rc(p));
    ll res = 0;
    if(l0 <= tr[lc(p)].r) res += Query(l0, r0, lc(p));
    if(r0 >= tr[rc(p)].l) res += Query(l0, r0, rc(p));
    return res;
}
void Create(int p=1,int l=1,int r=n){
    tr[p] = segnode{l, r, a1[l], 0};
    if(l == r) return;
    Create(lc(p), l, mid(l, r));
    Create(rc(p), mid(l, r) + 1, r);
    pushup(p, lc(p), rc(p));
}
int main(){
    n=read(),m=read(),rt=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1,u,v;i<n;i++){
        u=read(),v=read();
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    dfs(0, rt);
    Create();
    for(int i=1,op,p;i<=m;i++){
        op=read(),p=read();
        if(op==1){
            ll x=read<ll>();
            Modify(dfn[p],dfn[p]+sz[p]-1,x);
        }
        if(op==2){
            printf("%lld\n",Query(dfn[p],dfn[p]+sz[p]-1));
        }
    }
    return 0;
}