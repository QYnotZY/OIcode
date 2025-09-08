#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
char gc() {return getchar();}
template<typename T = int>
inline T readnum(){
    T res = 0; bool f = 0;
    char ch = gc();
    for(; !('0' <= ch && ch <= '9'); ch = gc())
        if(ch == '-') f = !f;
    for(; '0' <= ch && ch <= '9'; ch = gc())
        res = (res << 3) + (res << 1) + (ch ^ 48);
    return f ? ~res + 1 : res;
}
inline char readch(bool sp = 0){
    char ch = gc();
    for(; !(33 - sp <= ch && ch < 127); ch = gc()) ;
    return ch;
}
template<typename T = int>
T read() {return readnum<T>();}
}
using FastIO::read;
typedef long long ll;

const int N = 1e6 + 10;
int n;
vector<int> to[N];
int dep[N], maxdep[N], fa[N], hson[N];
int mpool[N], curpl, *f[N];
int ans[N];
void dfs1(int u, int f){
    maxdep[u] = dep[u] = dep[f] + 1;
    fa[u] = f;
    for(auto v : to[u]){
        if(v == fa[u]) continue;
        dfs1(v, u);
        if(maxdep[v] > maxdep[u])
            hson[u] = v, maxdep[u] = maxdep[v];
    }
}
int *makenew(int size){
    int *res = mpool + curpl;
    curpl += size;
    return res;
}
void dfs2(int u, int t){
    if(u == t) f[u] = makenew(maxdep[u] - dep[u] + 1);
    else f[u] = f[fa[u]] + 1;
    f[u][0] = 1; ans[u] = 0;
    if(hson[u]){
        dfs2(hson[u], t);
        if(f[u][ans[hson[u]] + 1] > f[u][0])
            ans[u] = ans[hson[u]] + 1;
    }
    for(auto v : to[u]){
        if(v == fa[u] || v == hson[u]) continue;
        dfs2(v, v);
        for(int i = 0; i <= maxdep[v] - dep[v]; i ++){
            f[u][i + 1] += f[v][i];
            if(f[u][i + 1] > f[u][ans[u]] || f[u][i + 1] == f[u][ans[u]] && i + 1 < ans[u])
                ans[u] = i + 1;
        }
    }
}
int main(){
    n = read();
    for(int i = 1; i < n; i ++){
        int u = read(), v = read();
        to[u].emplace_back(v);
        to[v].emplace_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for(int i = 1; i <= n; i ++)
        printf("%d\n", ans[i]);
    return 0;
}