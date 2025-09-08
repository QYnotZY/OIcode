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

const int N = 5e5 + 10, M = 1e5 + 10, logV = 64;
struct LB{
    ll b[logV + 5];
    void insert(ll x){
        for(int d = logV - 1; d >= 0; d --){
            if(!(x >> d & 1ll)) continue;
            if(b[d])
                x ^= b[d];
            else{
                b[d] = x;
                return;
            }
        }
    }
    ll query(ll x){
        ll res = x;
        for(int d = logV - 1; d >= 0; d --){
            if(res >> d & 1ll) continue;
            if(!b[d]) continue;
            res ^= b[d];
        }
        return res;
    }
}lb;
int n, m;
struct edge{
    int to;
    ll dis;
};
vector<edge> e[N];
ll dis[N];
int dfn[N], curdfn;
bool vis[N];
void dfs(int u, int fat){
    // dfn[u] = ++ curdfn;
    vis[u] = 1;
    for(auto ed : e[u]){
        int v = ed.to; ll w = ed.dis;
        if(v == fat) continue;
        // if(dfn[v] < dfn[u])
        if(vis[v])
            lb.insert(dis[v] ^ dis[u] ^ w);
        else
            dis[v] = dis[u] ^ w, dfs(v, u);
    }
}
int main(){
    n = read(), m = read();
    for(int i = 1; i <= m; i ++){
        int u = read(), v = read();
        ll w = read<ll>();
        e[u].emplace_back(edge{v, w});
        e[v].emplace_back(edge{u, w});
    }
    dfs(1, 0);
    printf("%lld", lb.query(dis[n]));
    return 0;
}