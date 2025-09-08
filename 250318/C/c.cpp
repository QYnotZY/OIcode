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

const ll N = 1e18;
ll n, m;
int s01;
ll calc(ll x){
    ll res = 0;
    for(int i = 7; i >= 0; i --){
        int tmp = s01 >> i & 1;
        if(res > N / x) return N + 1;
        res = res * x + tmp;
    }
    return res;
}
ll bsans(ll lb, ll ub){
    ll left = lb - 1, right = ub + 1;
    while(left + 1 < right){
        ll mid = left + (right - left >> 1);
        if(calc(mid) <= n) left = mid;
        else right = mid;
    }
    return left;
}
ll big(ll lb){
    ll ans = 0;
    for(s01 = 0; s01 < (1 << 8); s01 ++){
        ll tmp = bsans(lb, n);
        if(tmp == 1 || tmp < lb || tmp > n) continue;
        if(calc(tmp) == n) ans ++;
    }
    return ans;
}
ll small(ll ub){
    ll tmp = n, ans = 0;
    for(ll i = 2; i <= ub; i ++){
        for(tmp = n; tmp; tmp /= i)
            if(tmp % i > 1) goto ending;
        ans ++;
        ending:;
    }
    return ans;
}
int solve(){
    n = read<ll>();
    printf("%lld\n", small(min(n, 999ll)) + big(min(n+1, 1000ll)));
    return 0;
}
int main(){
    int t = read();
    while(t --){
        solve();
    }
    return 0;
}