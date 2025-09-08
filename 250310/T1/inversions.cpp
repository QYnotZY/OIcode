#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T=int>
T read(){
    T res=0; bool f=0;
    char ch=getchar();
    for(;!('0'<=ch&&ch<='9');ch=getchar())
        if(ch=='-') f=!f;
    for(;'0'<=ch&&ch<='9';ch=getchar())
        res=(res<<3)+(res<<1)+(ch^48);
    return f?~res+1:res;
}
const int N=210,mod=1000000007;
int t,n,m,a[N],vis[N];
int tp1,tp2,dp[N][N];
int ans;
int main(){
    freopen("inversions.in","r",stdin);
    freopen("inversions.out","w",stdout);
    t=read();
    while(t--){
        tp1=0,tp2=0;
        n=read(),m=read();
        bool f=0;
        for(int i=1;i<=n;i++)
            vis[i]=0;
        for(int i=1;i<=m;i++){
            a[i]=read();
            vis[a[i]]=1;
            if(tp1<a[i]) tp1=a[i];
            else if(tp2<a[i]) tp2=a[i];
            else f=1;
        }
        if(tp1<tp2) swap(tp1,tp2);
        int cnt=0;
        for(int i=1;i<tp2;i++){
            if(vis[i]==0)
                f=1;
        }
        if(f){
            printf("0\n");
            continue;
        }
        for(int i=m;i<=n;i++)
            dp[m][i]=0;
        dp[m][tp1]=1;
        for(int i=m+1;i<=n;i++){
            for(int j=i;j<=n;j++){
                dp[i][j]=0;
                for(int k=i-1;k<=j;k++){
                    (dp[i][j]+=dp[i-1][k])%=mod;
                }
            }
        }
        printf("%d\n",dp[n][n]);
    }
    return 0;
}