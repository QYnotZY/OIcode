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

const int N = 5e5 + 10, M = 5e5 + 10;
struct VE{
    int w;
    int u, v;
    bool operator < (VE obj){
        return w < obj.w;
    }
}ve[N + M];
namespace dsu{
    int fa[N];
    void init(int n){
        for(int i = 1; i <= n; i ++)
            fa[i] = i;
    }
    int find(int x){
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    bool same(int u, int v){
        return find(u) == find(v);
    }
    void merge(int u, int v){
        fa[find(v)] = find(u);
    }
}
int n, m;
int cnt;
ll ans;
vector<int> spe[N];
int main(){
    #ifndef Local_Judge
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
    #endif
    n = read(), m = read();
    for(int i = 1; i <= n; i ++){
        ve[i].u = i; ve[i].v = 0;
        ve[i].w = read();
    }
    for(int i = 1; i <= n; i ++)
        spe[i].emplace_back(0);
    for(int i = n + 1; i <= n + m; i ++){
        ve[i].u = read(), ve[i].v = read(), ve[i].w = read();
        spe[ve[i].u].emplace_back(ve[i].v);
        spe[ve[i].v].emplace_back(ve[i].u);
    }
    for(int i = 1; i <= n; i ++)
        spe[i].emplace_back(n + 1);
    sort(ve + 1, ve + n + m + 1);
    dsu::init(n);
    for(int i = 1, len, tmpl, tmpr; i <= n + m; i ++){
        if(ve[i].v){
            if(!dsu::same(ve[i].u, ve[i].v)){
                dsu::merge(ve[i].u, ve[i].v);
                cnt ++; ans += 1ll * ve[i].w;
                if(cnt == n - 1) goto printing;
            }
        } else{
            sort(spe[ve[i].u].begin(), spe[ve[i].u].end());
            len = spe[ve[i].u].size();
            for(int j = 1; j < len; j ++){
                tmpl = spe[ve[i].u][j - 1], tmpr = spe[ve[i].u][j];
                for(int k = tmpl + 1; k < tmpr; k ++){
                    if(!dsu::same(ve[i].u, k)){
                        dsu::merge(ve[i].u, k);
                        cnt ++; ans += 1ll * ve[i].w;
                        if(cnt == n - 1) goto printing;
                    }
                }
            }
        }
    }
    printing:
    printf("%lld", ans);
    return 0;
}