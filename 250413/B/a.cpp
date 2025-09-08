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

const int N = 1e4 + 10, inf = 1e7 + 10;
int n, m, ask[105];
bool ans[105];
namespace solve{
namespace llfs{
    int head[N], tot;
    struct edge{
        int to; int dis;
        int nxt;
    } e[N << 1];
    inline void init(){
        tot = 0;
        for(int i = 1; i <= n; i ++)
            head[i] = -1;
    }
    inline void add(int u, int v, int w){
        e[++ tot] = {v, w, head[u]};
        head[u] = tot;
    }
}
#define iter(u, v, w) for(int ii = llfs::head[u], v = llfs::e[ii].to, w = llfs::e[ii].dis; ~ii; ii = llfs::e[ii].nxt, v = llfs::e[ii].to, w = llfs::e[ii].dis)
bool del[N];
namespace findrootns{
    int totsz, sz[N]; pair<int, int> res;
    void dfs_findroot(int u, int f){
        sz[u] = 1;
        int maxv = 0;
        iter(u, v, w){
            if(v == f || del[v]) continue;
            dfs_findroot(v, u);
            maxv = max(maxv, sz[v]);
            sz[u] += sz[v];
        }
        maxv = max(maxv, totsz - sz[u]);
        if(maxv < res.second) res.first = u, res.second = maxv;
    }
    int findroot(int u){
        res = make_pair(0, n);
        totsz = sz[u] ? sz[u] : n;
        dfs_findroot(u, 0);
        return res.first;
    }
} using findrootns::findroot;
namespace calcns{
int curdis[N], cnt;
int dis[N];
bool ex[inf];
void getdis(int u, int f){
    curdis[++ cnt] = dis[u];
    iter(u, v, w){
        if(v == f || del[v]) continue;
        dis[v] = dis[u] + w;
        if(dis[v] < inf) getdis(v, u);
    }
}
int stkcl[N], top;
void calc(int u){
    dis[u] = 0;
    del[u] = ex[0] = 1;
    iter(u, v, w){
        if(del[v]) continue;
        dis[v] = w, cnt = 0;
        getdis(v, u);
        for(int i = 1; i <= cnt; i ++){
            for(int j = 1; j <= m; j ++){
                if(ask[j] >= curdis[i]) ans[j] |= ex[ask[j] - curdis[i]];
            }
        }
        for(int i = 1; i <= cnt; i ++){
            ex[curdis[i]] = 1;
            stkcl[++ top] = curdis[i];
        }
    }
    while(top) ex[stkcl[top --]] = 0;
}
} using calcns::calc;
void getans(int u){
    #ifdef db
    printf("c %d\n", u);
    #endif
    calc(u);
    iter(u, v, w){
        if(del[v]) continue;
        getans(findroot(v));
    }
}
#undef iter
} using solve::llfs::add;
int main(){
    n = read(), m = read();
    solve::llfs::init();
    for(int i = 1; i < n; i ++){
        int u = read(), v = read(), w = read();
        add(u, v, w), add(v, u, w);
    }
    for(int i = 1; i <= m; i ++)
        ask[i] = read();
    solve::getans(solve::findroot(1));
    for(int i = 1; i <= m; i ++){
        if(ans[i]){
            putchar('A'), putchar('Y'), putchar('E');
        } else{
            putchar('N'), putchar('A'), putchar('Y');
        }
        putchar('\n');
    }
    return 0;
}