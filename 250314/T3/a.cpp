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
template<typename T=int>
T read() {return readnum<T>();}

int t, n, p, ans;
int a[100010], b[100010];
int main(){
    t = read();
    while(t --){
    ans = 0;
    n = read(), p = read();
    if(n < p){
        printf("%d\n", n + 1);
        continue;
    }
    a[0] = 1;
    for(int i = 1; i <= n; i ++){
        a[i] = 0;
        for(int j = i; j >= 1; j --)
            (a[j] = a[j - 1] + i * a[j]) %= p;
        (a[0] *= i) %= p;
        #ifdef db
        for(int j = i; j >= 0; j --){
            printf("%d ", a[j]);
        }
        printf("\n");
        #endif
    }
    for(int i = 0; i <= n; i ++){
        if(a[i] != 0) ans++;
    }
    printf("%d\n", ans);
    }
    return 0;
}