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
const int N=5e4+10;
const ll inf=1e9;
template<typename T=int>
inline T mid(int l,int r){
    return l+(r-l>>1);
}
inline int lc(int p) {return p<<1;}
inline int rc(int p) {return p<<1|1;}
struct segnode{
    int l,r;
    ll sum,maxx,maxl,maxr,tag;
    int size() {return r-l+1;}
}tr[N<<2];
void pushup(int p){
    tr[p].sum = tr[lc(p)].sum + tr[rc(p)].sum;
    tr[p].maxx = max(max(tr[lc(p)].maxx, tr[rc(p)].maxx), tr[lc(p)].maxr + tr[rc(p)].maxl);
    tr[p].maxl = max(tr[lc(p)].maxl, tr[lc(p)].sum + tr[rc(p)].maxl);
    tr[p].maxr = max(tr[rc(p)].maxr, tr[rc(p)].sum + tr[lc(p)].maxr);
}
void pushup(segnode&sub,segnode obj1,segnode obj2){
    sub.sum = obj1.sum + obj2.sum;
    sub.maxx = max(max(obj1.maxx, obj2.maxx), obj1.maxr + obj2.maxl);
    sub.maxl = max(obj1.maxl, obj1.sum + obj2.maxl);
    sub.maxr = max(obj2.maxr, obj2.sum + obj1.maxr);
}
void upd1(int p,int val){
    tr[p].sum += val * tr[p].size();
    tr[p].maxx += val;
    tr[p].maxl += val;
    tr[p].maxr += val;
    tr[p].tag += val;
}
void pushdown(int p){
    upd1(lc(p), tr[p].tag);
    upd1(rc(p), tr[p].tag);
    tr[p].tag = 0;
}
void Modify(int l0,int r0,ll val,int p=1){
    if(l0 <= tr[p].l && tr[p].r <= r0){
        upd1(p, val);
        #ifdef db
        printf("%d %d:%lld\n",tr[p].l,tr[p].r,tr[p].maxx);
        #endif
        return;
    }
    pushdown(p);
    if(l0 <= tr[lc(p)].r) Modify(l0, r0, val, lc(p));
    if(r0 >= tr[rc(p)].l) Modify(l0, r0, val, rc(p));
    pushup(p);
}
segnode Query(int l0,int r0,int p=1){
    if(l0 <= tr[p].l && tr[p].r <= r0)
        return 
        #ifdef db
        printf("%d %d:%lld\n",tr[p].l,tr[p].r,tr[p].maxx),
        #endif
        tr[p];
    segnode res,q1=segnode{0,0,-inf,-inf,-inf,-inf,0},q2=segnode{0,0,-inf,-inf,-inf,-inf,0};
    if(l0 <= tr[lc(p)].r) q1 = Query(l0, r0, lc(p));
    if(r0 >= tr[rc(p)].l) q2 = Query(l0, r0, rc(p));
    pushup(res, q1, q2);
    return 
    #ifdef db
    printf("%d %d:%lld\n",tr[p].l,tr[p].r,res),
    #endif
    res;
}
int n,m;
ll a[N];
void Create(int p=1,int l=1,int r=n){
    tr[p] = {l, r, a[l], a[l], a[l], a[l], 0};
    if(l == r) return;
    Create(lc(p), l, mid(l, r));
    Create(rc(p), mid(l, r) + 1, r);
    pushup(p);
}
int main(){
    n=read();
    for(int i=1;i<=n;i++)
        a[i]=read<ll>();
    Create();
    m=read();
    for(int i=1,op;i<=m;i++){
        op=read();
        if(op==1){
            int x=read(),y=read();
            if(x>y) swap(x,y);
            printf("%lld\n",Query(x,y).maxx);
        }
        if(op==0){
            int x=read();ll y=read<ll>();
            Modify(x,x,y-Query(x,x).maxx);
        }
    }
    return 0;
}