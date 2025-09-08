#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N=3010;
const ll mod=998244353;
int n;
vector<int> e[N];
int sz[N];
ll dp[N][N][2],pre1[N][N],suf0[N][N],tmp[N][2];
ll fac[N<<1],invfac[N<<1];
void getfac(int n){
    fac[0]=1ll;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    ll bas=fac[n],idx=mod-2;invfac[n]=1;
    for(;idx;idx>>=1,bas=bas*bas%mod) if(idx&1ll) (invfac[n]*=bas)%=mod;
    for(int i=n-1;i>=0;i--) invfac[i]=invfac[i+1]*(i+1)%mod;
}
ll C(int n,int m){
    return fac[n]*invfac[m]%mod*invfac[n-m]%mod;
}
void solve(int fa,int u){
    sz[u]=1;
    dp[u][1][0]=dp[u][1][1]=1ll;
    for(auto v:e[u]){
        if(fa==v) continue;
        solve(u,v);
        for(int i=1;i<=sz[u];i++)
            for(int j=0;j<=sz[v];j++)
                (tmp[i+j][0] += dp[u][i][0] * suf0[v][j] % mod * C(i-1+j,j) % mod * C(sz[u]-i+sz[v]-j,sz[v]-j) % mod)%=mod,
                (tmp[i+j][1] += dp[u][i][1] * pre1[v][j] % mod * C(i-1+j,j) % mod * C(sz[u]-i+sz[v]-j,sz[v]-j) % mod)%=mod;
        sz[u]+=sz[v];
        for(int i=0;i<=sz[u];i++){
            dp[u][i][0]=tmp[i][0];
            dp[u][i][1]=tmp[i][1];
            tmp[i][0]=tmp[i][1]=0;
        }
    }
    pre1[u][0]=suf0[u][n]=0;
    for(int i=1;i<=sz[u];i++)
        pre1[u][i]=(pre1[u][i-1]+dp[u][i][0])%mod;
    for(int i=sz[u];i>=1;i--)
        suf0[u][i-1]=(suf0[u][i]+dp[u][i][1])%mod;
    #ifdef db
    int &x=u;
    for(int i=1;i<=sz[x];i++) printf("dp[%d][%d] [0]=%d [1]=%d %lld %lld\n",x,i,dp[x][i][0],dp[x][i][1],pre1[u][1],suf0[u][0]);
    #endif
}
int main(){
    scanf("%d",&n);
    getfac(n<<1);
    for(int i=1,u,v;i<n;i++){
        scanf("%d%d",&u,&v);
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    solve(0,1);
    ll ans=0;
    for(int i=1;i<=n;i++)
        (ans+=dp[1][i][0]+dp[1][i][1])%=mod;
    printf("%lld",ans);
    return 0;
}