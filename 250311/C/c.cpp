#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef vector<int> vi;
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

const int N = 2e5 + 10;

inline int mid(int l,int r){return l+(r-l>>1);}
inline int lc(int p){return p<<1;}
inline int rc(int p){return p<<1|1;}
struct segnode{
    int l,r;
    ll sum,tag;
    int size(){
        return r-l+1;
    }
}tr[N<<2];
void pushdown(int p){
    tr[lc(p)].sum+=tr[p].tag*(tr[lc(p)].size());
    tr[rc(p)].sum+=tr[p].tag*(tr[rc(p)].size());
    tr[lc(p)].tag+=tr[p].tag;
    tr[rc(p)].tag+=tr[p].tag;
    tr[p].tag=0;
}
void pushup(int p){
    tr[p].sum=tr[lc(p)].sum+tr[rc(p)].sum;
}
void upd1(int p,ll val){
    tr[p].sum+=val*tr[p].size();
    tr[p].tag+=val;
}
void Create(int p,int l,int r){
    tr[p]={l,r,0,0};
    if(l==r) return;
    Create(lc(p),l,mid(l,r));
    Create(rc(p),mid(l,r)+1,r);
    pushup(p);
}
void Modify(int l0,int r0,ll val,int p=1){
    if(l0<=tr[p].l&&tr[p].r<=r0){
        upd1(p,val);
        return;
    }
    pushdown(p);
    if(l0<=tr[lc(p)].r) Modify(l0,r0,val,lc(p));
    if(r0>=tr[rc(p)].l) Modify(l0,r0,val,rc(p));
    pushup(p);
}
ll Query(int l0,int r0,int p=1){
    if(l0<=tr[p].l&&tr[p].r<=r0){
        return tr[p].sum;
    }
    ll res=0ll;
    pushdown(p);
    if(l0<=tr[lc(p)].r) res+=Query(l0,r0,lc(p));
    if(r0>=tr[rc(p)].l) res+=Query(l0,r0,rc(p));
    return res;
}
int n, a[N], b[N];
map<int, int> mp; int cnt;
vi buc[N];
ll ans;
int main(){
    n = read();
    for(int i = 1; i <= n; i ++){
        a[i] = read();
        if(mp.find(a[i]+i) == mp.end())
            mp[a[i]+i] = ++ cnt, buc[cnt].emplace_back(0);
        buc[mp[a[i]+i]].emplace_back(i);
    }
    Create(1,1,n);
    #ifdef db
    for(auto [a,b]:mp){
        printf("%d %d\n",a,b);
    }
    #endif
    for(int i = 1; i <= n; i ++){
        b[i] = read();
        if(mp.find(b[i]+i) == mp.end()){
            printf("-1\n");
            return 0;
        }
        int &cur = buc[mp[b[i]+i]][0];
        if(cur >= buc[mp[b[i]+i]].size()-1){
            printf("-1\n");
            return 0;
        }
        int val = buc[mp[b[i]+i]][++cur];
        #ifdef db
        printf("0\n");
        #endif
        ans += val==n?0:Query(val + 1, n);
        #ifdef db
        printf("1\n");
        #endif
        Modify(val, val, 1);
        #ifdef db
        printf("%d %d %d\n",b[i]+i,i,buc[mp[b[i]+i]][cur]);
        #endif
    }
    printf("%lld\n", ans);
    return 0;
}