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

const int N = 410;
ll mod;
ll f[N][N], g[2][N][N][2], F[N], ans;
int n, k, k0;
inline ll ADD(ll a, ll b) {return (a + b) % mod;}
inline ll MINUS(ll a, ll b) {return (a - b + mod) % mod;}
inline ll MULT(ll a, ll b) {return a * b % mod;}
namespace basic{
ll po[N][N], ipo[N][N], fac[N], ifac[N];
ll power(ll a, int b){
    ll res = 1;
    for(; b; a = MULT(a, a), b >>= 1)
        if(b & 1) res = MULT(res, a);
    return res;
}
ll inv(ll a){
    return power(a, (int)mod - 2);
}
void setting(){
    fac[0] = 1;
    for(int i = 1; i <= 400; i ++)
        fac[i] = MULT(fac[i - 1], i);
    ifac[400] = inv(fac[400]);
    for(int i = 399; i >= 0; i --)
        ifac[i] = MULT(ifac[i + 1], i + 1);
    for(int i = 1; i <= 400; i ++){
        po[i][0] = 1;
        for(int j = 1; j <= 400; j ++)
            po[i][j] = MULT(po[i][j - 1], i);
        ipo[i][400] = inv(po[i][400]);
        for(int j = 399; j >= 0; j --)
            ipo[i][j] = MULT(ipo[i][j + 1], i);
    }
}
ll C(int n, int m){
    if(n < m) return 0ll;
    if(n == m) return 1ll;
    return MULT(fac[n], MULT(ifac[m], ifac[n - m]));
}
}
using namespace basic;
namespace dp{
void solve(){
    for(int w = 1; w <= k; w ++)
        f[1][w] = w;
    for(int i = 2; i <= n; i ++){
        for(int w = 1; w <= k; w ++)
            for(int m = 1; m <= w; m ++)
                for(int d = 0; d <= 1; d ++)
                    g[i & 1][w][m][d] = ADD(g[~i & 1][w][m][d], MULT(ipo[m - d][i - 1], MINUS(f[i - 1][w - m + 1], f[i - 1][w - m])));
        for(int w = 1; w <= k; w ++){
            f[i][w] = po[w][i];
            for(int m = 1; m <= w; m ++)
                f[i][w] = MINUS(f[i][w], MINUS(MULT(po[m][i], g[i & 1][w][m][0]), MULT(po[m - 1][i], g[i & 1][w][m][1])));
        }
    }
    if(k == k0){
        ans = f[n][k];
        return;
    }
    for(int i = 1; i <= k; i ++){
        F[i] = f[n][i];
        for(int j = 1; j < i; j ++)
            F[i] = MINUS(F[i], MULT(C(i, j), F[j]));
    }
    #ifdef db
    for(int i = 1; i <= k; i ++)
        printf("%lld ", F[i]);
    #endif
    ll ak0i = k0;
    for(int i = 1; i <= k; i ++){
        ans = ADD(ans, MULT(MULT(ak0i, ifac[i]), F[i]));
        ak0i = MULT(ak0i, k0 - i);
    }
}
}
int main(){
    // freopen("counting.in","r",stdin);
    // freopen("counting.out","w",stdout);
    n = read(), k0 = read(), k = min(k0, n), mod = read<ll>();
    basic::setting();
    dp::solve();
    printf("%lld", ans);
    return 0;
}