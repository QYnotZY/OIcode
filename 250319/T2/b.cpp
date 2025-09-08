#include"bits/stdc++.h"
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)
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

const int N = 2010, inf = 77777777;
int n, m, t, nm, tot;
inline int getID(int x, int y) {return (x - 1) * m + y;}
inline pair<int, int> getreID(int w) {return make_pair((w - 1) / m + 1, (w - 1) % m + 1);}
namespace graph{
int fa[N * N],w[N * N];
vector<int>son[N*N];
bool vis[N * N];
void add(int u, int v){
    fa[u] = v;
    son[v].push_back(u);
}
}
namespace dsu{
int fa[N * N], dis[N * N];
int maxdis[N * N];
int curmaxdis = 0; int &ans = curmaxdis;
void init(int n){
    for(int i = 1; i <= n; i ++){
        fa[i] = i;
    }
}
int find(int x){
    if(fa[x] == x) return x;
    int y = find(fa[x]);
    dis[x] += dis[fa[x]];
    return fa[x] = y;
}
void deal_with_tor(int u, int cdis, int rt){
    #ifdef db
    printf("%d %d\n", u, ~dis[u] ? cdis : cdis - 1);
    #endif
    fa[u] = tot;
    dis[u] = !dis[u] ? cdis-1 : cdis ;
    maxdis[tot] = max(maxdis[tot], dis[u]);
    for(int i = 0; i <graph::son[u].size(); i ++)
        if(graph::vis[graph::son[u][i]] && graph::son[u][i] != rt)
            deal_with_tor(graph::son[u][i], dis[u] + 1, rt);
}
void unionn(int u, int v){
    if(v == find(u)){
        #ifdef db
        printf("tor");
        #endif
        int sz = dis[u]+1;
        int tmpu = v;
        do{
            dis[tmpu] = 0;
            tmpu = graph::fa[tmpu];
        }while(tmpu != v);
        fa[++tot] = tot;
        deal_with_tor(v, sz, v);
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
    maxdis[find(u)] = max(maxdis[find(u)], maxdis[v] + dis[v]);
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
struct qry{
	int a,id;
	bool friend operator<(qry a,qry b){
		return a.a<b.a;
	}
}ans[500005];
int anss[500005];
bool cmp(int a, int b){
    return graph::w[a] < graph::w[b];
}
void solve(){
	int T;
	scanf("%d",&T);
	for(int i=1;i<=T;i++)scanf("%d",&ans[i].a),ans[i].id=i;
	sort(ans+1,ans+T+1);
    for(int i = 1; i <= nm; i ++) p[i] = i;
    sort(p + 1, p + nm + 1, cmp);
    int now=1;
    for(int i = 1; i <= nm; i ++){
        if(i % 10000 == 0) printf("1");
        graph::vis[p[i]] = 1;
        for(int j = 0; j < graph::son[p[i]].size(); j ++)
            if(graph::vis[graph::son[p[i]][j]])
                dsu::unionn(p[i], graph::son[p[i]][j]);
        if(graph::vis[graph::fa[p[i]]])
            dsu::unionn(graph::fa[p[i]], p[i]);
        for(; ans[now].a <= dsu::ans+1&&now<=T; now ++)
            anss[ans[now].id] = graph::w[p[i]];
    }
    for(int i=1;i<=T;i++)printf("%d ",anss[i]?anss[i]:77777777);
}
}
int main(){
    freopen("uoj9.in", "r", stdin);
    freopen("uoj9.out", "w", stdout);
    INIT::input_init();
    WORK::solve();
    return 0;
}
/*
1
5 5
LURUR
RDLUR
UDRLD
UURDL
LRLUL
763327 149454 699974 896079 792776 
460754 966226 733545 244842 254688 
10016 859123 907877 771133 431136 
672628 690879 967828 627211 964441 
14400 157297 280155 600753 753076 
5
5 4 7 3 1 

966226 964441 77777777 672628 10016 */