#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
const int inf=1e9;
int n,curl=1,curr=inf,ans=0;
int main(){
    scanf("%d",&n);
    for(int i=1,l,r,cnt=0;i<=n;i++,cnt=0){
        scanf("%d%d",&l,&r);
        l-=ans,r+=ans;
        if(curl<=l&&l<=curr) curl=l,curr=min(r,curr);
        else if(curl<=r&&r<=curr) curr=r,curl=max(curl,l);
        else if(l<=curl&&curr<=r) ;
        else if(curl>=l) cnt=curl-r+1>>1,curl-=cnt,curr=r+cnt;
        else cnt=l-curr+1>>1,curl=l-cnt,curr+=cnt;
        ans+=cnt;
        printf("%d\n",ans);
    }
    return 0;
}