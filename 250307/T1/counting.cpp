#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
template<typename T=int>
T readnum(){
    T res=0; bool f=0;
    char ch=getchar();
    for(;!('0'<=ch&&ch<='9');ch=getchar())
        if(ch=='-') f=!f;
    for(;'0'<=ch&&ch<='9';ch=getchar())
        res=(res<<3)+(res<<1)+(ch^48);
    return f?~res+1:res;
}
template<typename T=int>
T read() {return readnum();}
const int N=410;
ll mod;
ll fac[N],ifac[N];
ll power(ll a,ll idx){
    ll res=1ll;
    for(;idx;idx>>=1,(a*=a)%=mod)
        if(idx&1ll) (res*=a)%=mod;
    return res;
}
ll getinv(ll a){
    return power(a,mod-2ll);
}
void setfac(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=fac[i-1]*i%mod;
    ifac[n]=getinv(fac[n]);
    for(int i=n;i>=1;i--)
        ifac[i-1]=ifac[i]*i%mod;
}
ll C(int n,int m){
    return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
int n,k,w; ll ans;
ll dp[N][N],func[N][N][N][2];
int main(){
    #ifndef nt
    freopen("counting.in","r",stdin);
    freopen("counting.out","w",stdout);
    #endif
    n=read(),k=read(),w=min(n,k);
    mod=read<ll>();
    setfac(n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=w;j++){
            for(int ){
                dp[i][j] += 
            }
        }
    }
    return 0;
}