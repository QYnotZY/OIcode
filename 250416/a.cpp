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

const ll mod = 998244353;
inline ll Add(ll a, ll b) {return a + b < mod ? a + b : a + b - mod;}
inline ll Mult(ll a, ll b) {return a * b % mod;}
const int N = 5010;
int n, m, q;
namespace llfs{
    int tot, head[N];
    struct edge{
        int v;
        int nxt;
    } e[N << 1];
    void init(){
        tot = 1;
        for(int i = 1; i <= n; i ++)
            head[i] = -1;
    }
    void add(int u, int v){
        e[++ tot] = {v, head[u]};
        head[u] = tot;
        e[++ tot] = {u, head[v]};
        head[v] = tot;
    }
}
using namespace llfs;
int vis[N], ban;
bool dfs(int u){
    vis[u] = true;
    if(u == n) return true;
    for(int ii = head[u]; ~ii; ii = e[ii].nxt){
        if(ii == ban * 2 || ii == ban * 2 + 1) continue;
        int &v = e[ii].v;
        if(vis[v]) continue;
        if(dfs(v)) return true;
    }
    vis[u] = false;
    return false;
}
void solve(){
    for(int i = 1; i <= n; i ++)
        vis[i] = false;
    if(!dfs(1)) return printf("-1\n"), void();
    int res = 0;
    for(int i = 1; i <= m; i ++){
        ban = i;
        for(int i = 1; i <= n; i ++)
            vis[i] = false;
        res += !dfs(1);
    }
    printf("%d ", res);
}
namespace dsu{
    int tot, fa[N];
    void init(){
        tot = n;
        for(int i = 1; i <= n; i ++)
            fa[i] = i;
    }
    int find(int x){
        return fa[x] == x ? x : (fa[x] = find(fa[x]));
    }
    void merge(int u, int v){
        if(find(v) != find(u))
            -- tot, fa[find(v)] = find(u);
    }
}
int main(){
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
    n = read(), m = read(), q = read();
    init();
    for(int i = 1; i <= m; i ++){
        int u = read(), v = read();
        add(u, v);
    }
    solve();
    for(; q --;){
        int u = read(), v = read();
        add(u, v); ++ m;
        solve();
    }
    return 0;
}