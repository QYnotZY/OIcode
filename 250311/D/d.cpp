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

const int N = 4e5 + 10;
int n, a[N], p[N], rk[N];
bool stk[N]; int top;
bool cmp(int x, int y){
    return a[x] < a[y];
}
int main(){
    n = read();
    for(int i = 1; i <= n << 1; i ++)
        a[i] = read(), p[i] = i;
    sort(p + 1, p + (n << 1) + 1, cmp);
    for(int i = 1; i <= n << 1; i ++)
        rk[p[i]] = i;
    for(int i = 1; i <= n << 1; i ++){
        if(!top) stk[++top] = (rk[i] >= n + 1), printf("(");
        else{
            if(stk[top] != (rk[i] >= n + 1))
                top--, printf(")");
            else stk[++top] = (rk[i] >= n + 1), printf("(");
        }
    }
    return 0;
}