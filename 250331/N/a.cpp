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

const int N = 2e5 + 10;
int n;
ll a[N], b[N], rk[N];
ll cur, minn, pos, ans;
bool cmp(int x, int y){
    return a[x] > a[y];
}
int main(){
    n = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read(), b[i] = i;
    sort(b + 1, b + n + 1, cmp);
    for(int i = 1; i <= n; i ++)
        rk[b[i]] = i;
    for(int i = 1; i <= n; i ++){
        if(rk[i] > n / 2){
            cur ++;
        } else{
            cur --;
            ans += a[i];
            if(cur < minn){
                minn = cur;
                pos = i - 1;
            }
        }
    }
    printf("%lld %lld", pos, ans);
    return 0;
}
/*
https://v.douyin.com/F590nXBE_No/
*/