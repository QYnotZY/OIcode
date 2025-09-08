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
int n, m;
vector<int> e[N];
int sz[N], fa[N], hs[20][N], hs2[N], hs3[N];
int dfn[N], curdfn;
void dfs(int f, int u){
    sz[u] = 1; fa[u] = f;
    dfn[u] = ++ curdfn;
    for(auto v : e[u]){
        if(f == v) continue;
        dfs(u, v);
        sz[u] += sz[v];
        if(sz[v] > sz[hs[0][u]]){
            hs3[u] = hs2[u];
            hs2[u] = hs[0][u];
            hs[0][u] = v;
        } else if(sz[v] > sz[hs2[u]]){
            hs3[u] = hs2[u];
            hs2[u] = v;
        } else if(sz[v] > sz[hs3[u]]){
            hs3[u] = v;
        }
    }
}
void geths(){
    for(int i = 1; i < 20; i ++){
        for(int j = 1; j <= n; j ++){
            hs[i][j] = hs[i-1][hs[i-1][j]];
        }
    }
}
int sz1, ban1, ban2;
bool isa(int p, int u){
    return dfn[p] <= dfn[u] && dfn[u] < dfn[p] + sz[p];
}
int down(int p){
    int szp = sz[p];
    if(isa(p, ban1)) szp -= sz[ban1];
    if(isa(p, ban2)) szp -= sz[ban2];
    if(sz1 - szp > szp) return 0;
    for(int i = 19, tgtson, tgtsz; i >= 0; i --){
        tgtson = hs[i][p], tgtsz = sz[tgtson];
        if(tgtson == 0 || isa(ban1, tgtson) || isa(ban2, tgtson)) continue; //! 被删掉的节点要单独特判
        if(isa(tgtson, ban1)) tgtsz -= sz[ban1];
        if(isa(tgtson, ban2)) tgtsz -= sz[ban2];
        if(sz1 - tgtsz <= tgtsz) p = tgtson;
    }
    return p;
}
pair<int, int> solve(int p){
    #ifdef db
    printf("%d ", p);
    #endif
    int tmp;
    tmp = down(hs[0][p]);
    if(tmp) return solve(tmp);
    tmp = down(hs2[p]);
    if(tmp) return solve(tmp);
    tmp = down(hs3[p]);
    if(tmp) return solve(tmp);
    int szp = sz[p];
    if(isa(p, ban1)) szp -= sz[ban1];
    if(isa(p, ban2)) szp -= sz[ban2]; 
    if(szp <= sz1 >> 1) return make_pair(fa[p], p); //! 判断是否为重心
    return make_pair(p, 0);
}
int main(){
    n = read(), m = read();
    for(int i = 1, u, v; i < n; i ++){
        u = read(), v = read();
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    sz[0] = 0;
    dfs(0, 1);
    geths();
    for(int i = 1; i <= m; i ++){
        ban1 = read(), ban2 = read();
        if(isa(ban1, ban2)) ban2 = 0;
        if(isa(ban2, ban1)) ban1 = 0;
        sz1 = n - sz[ban1] - sz[ban2];
        #ifdef db
        printf("%d ", sz1);
        #endif
        if(sz1 == 0){
            printf("0\n");
            continue;
        }
        pair<int, int> ans = solve(down(1));
        if(!ans.second) printf("%d\n", ans.first);
        else{
            if(ans.first > ans.second) swap(ans.first, ans.second);
            printf("%d %d\n", ans.first, ans.second);
        }
    }
    return 0;
}