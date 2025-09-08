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

const int N = 2e6;
int n, m, a[N];
namespace bit{
inline int lowbit(int x) {return x & -x;}
ll tr[3][N + 10];
void add(int op, int x, int v){
    if(x == 0) return;
    while(x <= N){
        tr[op][x] += v;
        x += lowbit(x);
    }
}
ll query(int op, int x){
    if(x == 0) return 0;
    ll res = 0;
    while(x > 0){
        res += tr[op][x];
        x -= lowbit(x);
    }
    return res;
}
void upd(int l, int r, ll val){
    add(1, l, val);
    add(2, l, l * val);
    add(1, r + 1, -val);
    add(2, r + 1, -val * (r + 1));
}
ll sum(int l, int r){
    return query(1, r) * (r + 1) - query(2, r) - query(1, l - 1) * l + query(2, l - 1);
}
}
ll ans;
int main(){
    #ifndef db
    freopen("maopao.in", "r", stdin);
    freopen("maopao.out", "w", stdout);
    #endif
    n = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    for(int i = n; i >= 1; i --){
        bit::upd(1, bit::query(0, a[i] - 1), 1);
        bit::add(0, a[i], 1);
    }
    m = read();
    char op; int k;
    for(; m --;){
        op = getchar(); while(op < 33 || op > 126) op = getchar();
        k = read();
        if(op == 'A'){
            bit::upd(1, bit::query(0, k - 1), 1);
            bit::add(0, k, 1);
        }
        if(op == 'Q'){
            if(k >= 1) ans ^= bit::sum(1, k);
        }
    }
    printf("%lld", ans);
    return 0;
}