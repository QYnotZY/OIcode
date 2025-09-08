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
const int N=3e5+10;
struct line{
    int a,b;
    bool operator<(line obj){
        return a<obj.a;
    }
};
int n,a[N];
ll sum,delta;
vector<line> l1,l2;
int main(){
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        if(i==1) continue;
        sum+=abs(a[i]-a[i-1]);
        if(a[i-1]<=a[i]) l1.emplace_back(line{a[i-1],a[i]});
        else l2.emplace_back(line{a[i],a[i-1]});
    }
    for(int i=2;i<n;i++)
        delta=min(delta,abs(1ll*a[1]-a[i+1])-abs(a[i]-a[i+1])),
        delta=min(delta,abs(1ll*a[n]-a[i-1])-abs(a[i]-a[i-1]));
    sort(l1.begin(),l1.end());
    int maxr;
    if(l1.size()) maxr=l1[0].b;
    for(int i=1;i<l1.size();i++){
        delta=min(delta,-2ll*(min(maxr,l1[i].b)-l1[i].a));
        maxr=max(maxr,l1[i].b);
    }
    sort(l2.begin(),l2.end());
    if(l2.size()) maxr=l2[0].b;
    for(int i=1;i<l2.size();i++){
        delta=min(delta,-2ll*(min(maxr,l2[i].b)-l2[i].a));
        maxr=max(maxr,l2[i].b);
    }
    printf("%lld",sum+delta);
    return 0;
}