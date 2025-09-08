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
const int N = 2e5+10;
int n, a;
ll sum[N], maxx[N];
ll curans = 0;
int main(){
    n = read();
    for(int i = 1; i <= n; i ++){
        a = read();
        maxx[i] = max(maxx[i - 1], (ll)a);
        sum[i] = sum[i - 1] + a;
    }
    for(int i = 1; i <= n; i ++){
        curans += sum[i];
        printf("%lld\n", curans + i * maxx[i]);
    }
    return 0;
}