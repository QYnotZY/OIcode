#include"bits/stdc++.h"
// #define debug
using namespace std;
typedef long long ll;
int cnt[2][10],tmpc[2][10];
struct pip{
    int a;
    string b;
    string c;
    void min(pip obj){
        if(a<=obj.a) swap(*this,obj);
    }
}sum,ans;
void solve(){
    for(int i=1;i<=9;i++) tmpc[0][i]=cnt[0][i],tmpc[1][i]=cnt[1][i];
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            if(i+j>=9&&tmpc[0][i]&&tmpc[1][j]){
                int c=min(tmpc[0][i],tmpc[1][j]);
                tmpc[0][i]-=c,tmpc[1][j]-=c;sum.a+=c;
                sum.b+=string(c,i^'0'),sum.c+=string(c,j^'0');
            }
        }
    }
    sum.a+=max(tmpc[0][9],tmpc[1][9]);
    for(int i=9;i>=1;i--){
        sum.b+=string(tmpc[0][i],i^'0');
        sum.c+=string(tmpc[1][i],i^'0');
    }
    reverse(sum.b.begin(),sum.b.end());
    reverse(sum.c.begin(),sum.c.end());
}
int main(){
    string s,t;
    cin>>s>>t;
    for(auto ele:s) cnt[0][ele^48]++;
    for(auto ele:t) cnt[1][ele^48]++;
    ans={0,s,t};
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            if(i+j>=10&&cnt[0][i]&&cnt[1][j]){
                cnt[0][i]--;cnt[1][j]--;
                sum={1,string(1,i^'0'),string(1,j^'0')};
    #ifdef debug
    for(int i=0;i<=1;i++){
        for(int j=1;j<=9;j++)
            printf("%d ",cnt[i][j]);
        printf("\n");
    }
    #endif
                solve();
                ans.min(sum);
                cnt[0][i]++;cnt[1][j]++;
            }
        }
    }
    cout<<ans.b<<endl<<ans.c;
    return 0;
}