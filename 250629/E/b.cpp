#include<bits/stdc++.h>
#include<ext/rope>
using namespace __gnu_cxx;
#define mp make_pair
#define pb push_back
#define dbg puts("-------------qaqaqaqaqaqaqaqaqaq------------")
#define pl (p<<1)
#define pr ((p<<1)|1)
#define pii pair<int,int>
#define int long long
#define mod 998244353
#define eps 1e-9
#define ent putchar('\n')
#define sp putchar(' ')
using namespace std;
inline int read(){
    char c=getchar(),f=0;int t=0;
    for(;c<'0'||c>'9';c=getchar()) if(!(c^45)) f=1;
    for(;c>='0'&&c<='9';c=getchar()) t=(t<<1)+(t<<3)+(c^48);
    return f?-t:t;
}
inline void write(int x){
    static int t[25];int tp=0;
    if(x==0) return(void)(putchar('0'));else if(x<0) putchar('-'),x=-x;
    while(x) t[tp++]=x%10,x/=10;
    while(tp--) putchar(t[tp]+48);
}
const int N=3e5+10;
int n,ans;
int a[N],b[N],tr[4*N],lz[4*N];
int lst[N],llst[N];
void push_up(int p){
    tr[p]=min(tr[pl],tr[pr]);
}
void push_down(int p){
    tr[pl]+=lz[p],tr[pr]+=lz[p];
    lz[pl]+=lz[p],lz[pr]+=lz[p];
    lz[p]=0;
}
void build(int l,int r,int p){
    if(l==r){
        tr[p]=lz[p]=0;
        return;
    }
    lz[p]=0;
    int mid=l+r>>1;
    build(l,mid,pl);
    build(mid+1,r,pr);
    push_up(p);
}
void modify(int l,int r,int li,int ri,int k,int p){
    
    if(li<=l&&r<=ri){
        tr[p]+=k,lz[p]+=k;
        
        return;
    }
    push_down(p);
    int mid=l+r>>1;
    if(li<=mid) modify(l,mid,li,ri,k,pl);
    if(ri>mid) modify(mid+1,r,li,ri,k,pr);
    push_up(p);
}
int query(int l,int r,int li,int ri,int p){
    
    if(li<=l&&r<=ri){
        #ifdef db
    printf("%d %d %d %d\n", p, l, r, tr[p]);
    #endif
        return tr[p];
    }
    push_down(p);
    int mid=l+r>>1;
    int ans=INT_MAX;
    if(li<=mid) ans=min(ans,query(l,mid,li,ri,pl));
    if(ri>mid) ans=min(ans,query(mid+1,r,li,ri,pr));
    #ifdef db
    printf("%d %d %d %d\n", p, l, r, ans);
    #endif
    return ans;
}
signed main(){
    int T=read();
    while(T--){
        n=read(),ans=0;
        for(int i=1;i<=n;i++){
            a[i]=read();
            llst[i]=lst[i]=b[i]=0;
        }
        for(int i=1;i<=n;i++){
            lst[i]=b[a[i]];
            llst[i]=lst[lst[i]];
            b[a[i]]=i;
        } 
        build(1,n,1);
        for(int i=1;i<=n;i++){
            write(lst[i]+1),sp,write(i),ent;
            modify(1,n,lst[i]+1,i,1,1);
            if(lst[i]){
                write(llst[i]+1),sp,write(lst[i]),dbg;
                modify(1,n,llst[i]+1,lst[i],-1,1);
            }
            write(query(1,n,1,i,1)),dbg;
            if(query(1,n,1,i,1)==0) modify(1,n,1,i,1,1),ans++;
        }
        write(ans),ent;
    }
    return 0;
}