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

const int N = 1e5 + 10;
const ll inf = 1ll << 61;
int n, w;
ll a[N];
int d[N], tmpd[N];
ll sum, ans;
void solve(){
    n = read(), w = read();
    for(int i = 1; i <= n; i ++){
        a[i] = read<ll>();
        d[i] = 0;
    }
    ans = (1ll << w) - 1;
    for(int i = w - 1; i >= 0; i --){
        sum = 0;
        ans ^= 1ll << i;
        for(int j = 1; j <= n; j ++){
            tmpd[j] = d[j];
            while((a[j] >> tmpd[j] | ans)> ans) tmpd[j] ++;
            sum += 1ll << w - tmpd[j];
            if(sum > 1ll << w) sum = 1ll << w;
        }
        if(sum >= 1ll << w){
            for(int j = 1; j <= n; j ++)
                d[j] = tmpd[j];
        }
        else ans ^= 1ll << i;
    }
    printf("%lld\n", ans);
}
int main(){
    #ifndef db
    freopen("merge.in", "r", stdin);
    freopen("merge.out", "w", stdout);
    #endif
    int t = read();
    for(; t --;){
        solve();
    }
    return 0;
}