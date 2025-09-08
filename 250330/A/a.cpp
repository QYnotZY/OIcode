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

const int N = 610;
ll mod;
inline ll Add(ll a, ll b) {return (a + b) % mod;}
inline ll Minus(ll a, ll b) {return (a - b + mod) % mod;}
inline ll Mult(ll a, ll b) {return (a * b) % mod;}
inline ll Mod(ll a, ll b = mod) {return (a % b + b) % b;}
int n;
ll a[N][N];
ll ans;
void Gauss(){
    int c = 0;
    ans = 1ll;
    for(int i = 1; i <= n; i ++){
        for(int j = i + 1; j <= n; j ++){
            if (a[j][i] > a[i][i]){
                swap(a[j], a[i]);
                ans = Mult(ans, mod - 1);
            }
            while(a[j][i]){
				ll div = a[i][i] / a[j][i];
				for(int k = i; k <= n; k ++)
                    a[i][k] = Minus(a[i][k], Mult(div, a[j][k]));
				swap(a[j], a[i]);
                ans = Mult(ans, mod - 1);
			}
        }
    }
    for(int i = 1; i <= n; i ++)
        ans = Mult(ans, a[i][i]);
    return;
}
int main(){
    n = read(), mod = read<ll>();
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            a[i][j] = Mod(read<ll>());
    Gauss();
    printf("%lld", ans);
    return 0;
}