#include "bits/stdc++.h"
#define code using
#define by namespace
#define xjp std
code by xjp;
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

const int N = 4e6 + 10;
int n, m, q, rest;
namespace llfs{
    int tot, head[N];
    struct node{
        int to; int nxt;
        bool key;
    } e[N << 1];
    void init(int n){
        tot = 1;
        for(int i = 1; i <= n; i ++)
            head[i] = -1;
    }
    void dbadd(int u, int v){
        e[++ tot] = {v, head[u], 0};
        head[u] = tot;
        e[++ tot] = {u, head[v], 0};
        head[v] = tot;
    }
}
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
        if(!same(u, v))
            fa[find(v)] = find(u);
    }
}
namespace lt{
    int tot;
    struct node{
        int val, nxt;
    } l[N];
    int mp[N];
}
bool vis[N], key[N];
bool dfs_path(int u){
    vis[u] = key[u] = 1;
    lt::l[++ lt::tot] = {u, 0};
    lt::l[lt::tot - 1].nxt = lt::tot;
    lt::mp[u] = lt::tot;
    if(u == n) return true;
    for(int ii = llfs::head[u]; ~ii; ii = llfs::e[ii].nxt){
        int &v = llfs::e[ii].to;
        if(vis[v]) continue;
        llfs::e[ii].key = llfs::e[ii ^ 1].key = 1;
        if(dfs_path(v)) return true;
        llfs::e[ii].key = llfs::e[ii ^ 1].key = 0;
    }
    return key[u] = vis[u] = 0, -- lt::tot, false;
}
void update(int u, int v){
    if(dsu::same(u, v)) return;
    if(!key[dsu::find(u)] && !key[dsu::find(v)])
        return dsu::merge(u, v), void();
    if(!key[dsu::find(u)])
        return dsu::merge(v, u), void();
    if(!key[dsu::find(v)])
        return dsu::merge(u, v), void();
    if(lt::mp[dsu::find(u)] > lt::mp[dsu::find(v)]) swap(u, v);
    int st = dsu::find(u), en = dsu::find(v);
    int lst, cur = st;
    while(cur != en){
        lst = cur;
        cur = lt::l[lt::l[lt::mp[lst]].nxt].val;
        dsu::merge(st, cur);
        -- rest;
        #ifdef db
        printf("del %d\n", cur);
        #endif
    }
    lt::l[lt::mp[st]].nxt = lt::l[lt::mp[en]].nxt;
}
void solve(){
    dsu::init(n);
    dfs_path(1);
    rest = lt::tot - 1;
    for(int i = 1; i <= m; i ++){
        if(llfs::e[i << 1].key) continue;
        int u = llfs::e[i << 1 | 1].to, v = llfs::e[i << 1].to;
        update(u, v);
    }
}
int main(){
    // freopen("graph.in", "r", stdin);
    // freopen("graph.out", "w", stdout);
    n = read(), m = read(), q = read();
    llfs::init(n);
    dsu::init(n);
    for(int i = 1; i <= m; i ++){
        int u = read(), v = read();
        llfs::dbadd(u, v);
        dsu::merge(u, v);
    }
    bool st = dsu::same(1, n);
    if(st) solve(), printf("%d ", rest);
    else printf("-1 ");
    #ifdef db
    for(int i = 1; i <= lt::tot; i ++)
        printf("%d ", lt::l[i]);
    printf("\n");
    #endif
    for(int i = 1; i <= q; i ++){
        m ++;
        int u = read(), v = read();
        llfs::dbadd(u, v);
        if(st){
            update(u, v);
            printf("%d ", rest);
        } else{
            dsu::merge(u, v);
            st = dsu::same(1, n);
            if(st) solve(), printf("%d ", rest);
            else printf("-1 ");
        }
    }
    return 0;
}