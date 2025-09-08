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

const int N = 1510, inf = 77777777;
int n, m, t, nm, tot;
inline int getID(int x, int y) {return (x - 1) * m + y;}
inline pair<int, int> getreID(int w) {return make_pair((w - 1) / m + 1, (w - 1) % m + 1);}
namespace graph{
int fa[N * N], son[N * N][5], w[N * N];
bool vis[N * N];
void add(int u, int v){
    fa[u] = v;
    son[v][++son[v][0]] = u;
}
}
namespace dsu{
int fa[N * N], dis[N * N];
int maxdis[N * N];
int curmaxdis = 1; int &ans = curmaxdis;
void init(int n){
    for(int i = 1; i <= n; i ++){
        fa[i] = i;
        dis[i] = 1;
        maxdis[i] = 1;
    }
}
int find(int x){
    if(fa[x] == x) return x;
    int y = find(fa[x]);
    dis[x] += dis[fa[x]] - dis[y];
    return fa[x] = y;
}
void deal_with_tor(int u, int cdis, int rt){
    #ifdef db
    printf("%d %d\n", u, ~dis[u] ? cdis : cdis - 1);
    #endif
    fa[u] = tot;
    dis[u] = ~dis[u] ? cdis : cdis - 1;
    maxdis[tot] = max(maxdis[tot], dis[u]);
    for(int i = 1; i <= graph::son[u][0]; i ++)
        if(graph::vis[graph::son[u][i]] && graph::son[u][i] != rt)
            deal_with_tor(graph::son[u][i], dis[u] + 1, rt);
}
void unionn(int u, int v){
    if(v == find(u)){
        #ifdef db
        printf("tor");
        #endif
        int sz = dis[u];
        int tmpu = v;
        do{
            dis[tmpu] = -1;
            tmpu = graph::fa[tmpu];
        }while(tmpu != v);
        fa[++ tot] = tot;
        deal_with_tor(v, sz + 1, v);
        curmaxdis = max(curmaxdis, maxdis[tot]);
        return;
    }
    #ifdef db
    printf("nmupd:%d <- %d : ", u, v);
    #endif
    fa[v] = find(u);
    dis[v] = dis[u] + 1;
    #ifdef db
    printf("%d %d %d\n", dis[u], dis[v], dis[u] + maxdis[v]);
    #endif
    maxdis[find(u)] = max(maxdis[find(u)], maxdis[v] + dis[u]);
    curmaxdis = max(curmaxdis, maxdis[find(u)]);
}
}
namespace INIT{
void input_init(){
    read();
    n = read(), m = read(); nm = n * m; tot = nm;
    dsu::init(nm);
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            char ch = getchar();
            while(ch < 33 || ch > 126) ch = getchar();
            switch(ch){
                case 'U':{
                    if(i != 1) graph::add(getID(i, j), getID(i - 1, j));
                    break;
                }
                case 'D':{
                    if(i != n) graph::add(getID(i, j), getID(i + 1, j));
                    break;
                }
                case 'L':{
                    if(j != 1) graph::add(getID(i, j), getID(i, j - 1));
                    break;
                }
                case 'R':{
                    if(j != m) graph::add(getID(i, j), getID(i, j + 1));
                    break;
                }
            }
        }
    }
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            graph::w[getID(i, j)] = read();
}
}
namespace WORK{
int p[N * N];
int ans[100010];
bool cmp(int a, int b){
    return graph::w[a] < graph::w[b];
}
void solve(){
    ans[0] = 1;
    for(int i = 1; i <= nm; i ++) p[i] = i, ans[i] = 77777777;
    sort(p + 1, p + nm + 1, cmp);
    for(int i = 1; i <= nm; i ++){
        graph::vis[p[i]] = 1;
        #ifdef db
        printf("%d:\n", p[i]);
        #endif
        for(int j = 1; j <= graph::son[p[i]][0]; j ++)
            if(graph::vis[graph::son[p[i]][j]])
                dsu::unionn(p[i], graph::son[p[i]][j]);
        if(graph::vis[graph::fa[p[i]]])
            dsu::unionn(graph::fa[p[i]], p[i]);
        for(; ans[0] <= dsu::ans; ans[0] ++)
            ans[ans[0]] = graph::w[p[i]];
        #ifdef db
        printf("%d\n", ans[0]);
        #endif
    }
    #ifdef db
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            printf("%d ", dsu::dis[getID(i, j)]);
        }
        printf("\n");
    }
    #endif
}
void print(){
    int t = read();
    while(t --){
        int x = read();
        printf("%d ", ans[x]);
    }
}
}
int main(){
    INIT::input_init();
    WORK::solve();
    WORK::print();
    return 0;
}