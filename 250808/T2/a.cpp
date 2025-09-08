#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// inline char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
inline char gc() {return getchar();}
template<typename T = int>
inline T read(){
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
}
using FastIO::read;
using FastIO::readch;
typedef long long ll;
namespace work {
const int N = 8e5 + 10, M = 1e6 + 10;
int n, m, q, tid;
struct DSU {
    int fa[N];
    void init(int n) {for(int i = 1; i <= n; i ++) fa[i] = i;}
    int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
    bool same(int x, int y) {return find(x) == find(y);}
    void merge(int x, int y) {x = find(x), y = find(y), fa[y] = x;}
} dsu;
struct edge {
    int u, v, delt;
    bool operator < (const edge& obj) const {
        return delt > obj.delt;
    }
} ed[M];
struct QRY {
    int u, v, t;
} qry[M]; int qsz;
namespace llfs {
    int tot, head[N];
    struct edge {
        int v, nxt;
    } e[N << 1];
    void adde(int u, int v) {
        e[++ tot] = edge{v, head[u]}, head[u] = tot;
        e[++ tot] = edge{u, head[v]}, head[v] = tot;
    }
} using llfs::head; using llfs::e;
int fa[N], dep[N];
void dfs(int u, int f) {
    fa[u] = f; dep[u] = dep[f] + 1;
    for(int i = head[u]; i; i = e[i].nxt) {
        int &v = e[i].v;
        if(v == f) continue;
        dfs(v, u);
    }
}
bool ans[M];
void Hutao() {
    n = read(), m = read(), q = read(), tid = read();
    for(int i = 1; i <= m; i ++)
        ed[i].u = read(), ed[i].v = read(), ed[i].delt = q + 1;
    for(int i = 1, op; i <= q; i ++) {
        op = read();
        if(op == 1) {
            int tmp = read();
            ed[tmp].delt = i;
        } else {
            qry[++ qsz].u = read(), qry[qsz].v = read(), qry[qsz].t = i;
        }
    }
    sort(ed + 1, ed + m + 1);
    dsu.init(n);
    for(int i = 1, cnt = 0; i <= m && cnt < n - 1; i ++)
        if(!dsu.same(ed[i].u, ed[i].v)) {
            dsu.merge(ed[i].u, ed[i].v);
            llfs::adde(ed[i].u, ed[i].v);
            ed[i].delt = 0;
            cnt ++;
        }
    for(int i = 1; i <= n; i ++)
        if(!dep[i]) dfs(i, 0);
    sort(ed + 1, ed + m + 1);
    dsu.init(n);
    for(int mi = 1, qi = qsz; qi; qi --) {
        for(; ed[mi].delt > qry[qi].t; mi ++)
            if(!dsu.same(ed[mi].u, ed[mi].v)) {
                int u = dsu.find(ed[mi].u), v = dsu.find(ed[mi].v);
                while(u != v) {
                    if(dep[v] > dep[u]) {
                        dsu.merge(fa[v], v);
                        v = dsu.find(v);
                    } else {
                        dsu.merge(fa[u], u);
                        u = dsu.find(u);
                    }
                }
            }
        ans[qi] = dsu.same(qry[qi].u, qry[qi].v);
    }
    for(int i = 1; i <= qsz; i ++) printf(ans[i] ? "YES\n" : "NO\n");
}
}
int main() {
    #ifndef db
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
    #endif
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}