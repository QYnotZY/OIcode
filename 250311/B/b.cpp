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
int read01(){
    char ch=getchar();
    while(ch!='0'&&ch!='1')
        ch=getchar();
    return ch^48;
}
template<typename T=int> T read(int f=0) {return f?read01():readnum<T>();}

const int N = 500'010;
int n, spos[N], tpos[N], ans;
int main(){
    n = read();
    for(int i = 1; i <= n; i ++)
        if(read(1) == 0)
            spos[++ spos[0]] = i;
    for(int i = 1; i <= n; i ++)
        if(read(1) == 0)
            tpos[++ tpos[0]] = i;
    if(spos[0] != tpos[0]){
        printf("-1");
        return 0;
    }
    for(int i = 1; i <= spos[0]; i ++)
        if(spos[i] != tpos[i])
            ans ++;
    printf("%d", ans);
    return 0;
}