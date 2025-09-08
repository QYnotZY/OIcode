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

const int N = 2e5 + 10, logN = 20;
const ll mod = 998244353;
inline ll ADD(ll a, ll b) {return a + b >= mod ? a + b - mod : a + b;}
inline ll MINUS(ll a, ll b) {return a >= b ? a - b : a + mod - b;}
int n, a[N];
namespace st{
int pos[logN][N], val[logN][N];
void create(){
    for(int i = 1; i <= n; i ++)
        pos[0][i] = i, val[0][i] = a[i];
    for(int i = 1; i < logN; i ++)
        for(int j = 1; j <= n - (1 << i) + 1; j ++)
            if(val[i - 1][j] <= val[i - 1][j + (1 << i - 1)])
                pos[i][j] = pos[i - 1][j], val[i][j] = val[i - 1][j];
            else
                pos[i][j] = pos[i - 1][j + (1 << i - 1)], val[i][j] = val[i - 1][j + (1 << i - 1)];
}
int qpos(int l, int r){
    int tlog = 0;
    while(1 << tlog < r - l + 1) tlog ++;
    tlog --;
    if(val[tlog][l] <= val[tlog][r - (1 << tlog) + 1])
        return pos[tlog][l];
    return pos[tlog][r - (1 << tlog) + 1];
}
}
map<int, ll> f[N];
ll ans(int l, int r){
    if(l >= r) return 1;
    if(f[l].find(r) != f[l].end()) return f[l][r];
    if(st::qpos(l, r) == l || st::qpos(l, r) == r)
        return f[l][r] = ADD(ans(l, r - 1), ans(l + 1, r));
    else
        return f[l][r] = MINUS(ADD(ans(l, st::qpos(l, r)), ans(st::qpos(l, r), r)), 1);
}
void solve(){
    n = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    st::create();
    for(int i = 1; i <= n; i ++) f[i].clear();
    printf("%lld\n", ans(1, n));
}
int main(){
    int t = read();
    while(t --){
        solve();
    }
    return 0;
}