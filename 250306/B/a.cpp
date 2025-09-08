#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
const int szC=3e5+10,szQ=3e5+10;
int n,m,cntc,q;
int t[szQ],a[szQ],c[szQ];
ll sum[2];
set<int> pnt[2];
ll ans[szC];
int main(){
    scanf("%d%d%d%d",&n,&m,&cntc,&q);
    sum[0]=m,sum[1]=n;
    for(int i=1;i<=q;i++)
        scanf("%d%d%d",t+i,a+i,c+i);
    for(int i=q;i>=1;i--){
        t[i]--;
        if(pnt[t[i]].find(a[i])==pnt[t[i]].end()){
            pnt[t[i]].emplace(a[i]);
            ans[c[i]]+=sum[t[i]];
            sum[1-t[i]]--;
        }
    }
    for(int i=1;i<=cntc;i++)
        printf("%lld ",ans[i]);
    return 0;
}