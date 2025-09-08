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
const int N = 1e5 + 10;
int n, m;
namespace llfs {
    int head[N], tot;
    struct edge {
        int to;
        int nxt;
    } e[N << 1];
    void init(int n) {tot = 0; memset(head, -1, sizeof head);}
    void adde(int u, int v) {
        e[++ tot] = {v, head[u]}; head[u] = tot;
        e[++ tot] = {u, head[v]}; head[v] = tot;
    }
} using llfs::head; using llfs::e;
struct node {
    int sz, coll, colr, ans;
    node() {ans = coll = colr = sz = 0;}
    node(int a, int b, int c, int d) {tie(sz, coll, colr, ans) = tie(a, b, c, d);}
    node operator + (const node &obj) {
        node res;
        res.sz = sz + obj.sz;
        res.coll = coll;
        res.colr = obj.colr;
        res.ans = ans + obj.ans;
        if(colr == obj.coll && colr) res.ans ++;
        return res;
    }
    void reverse() {
        swap(coll, colr);
    }
} ;
namespace smt {
    struct smtnode {
        node res; int tag;
    } tr[N << 2];
    void pushup(int p) {
        tr[p].res = tr[p << 1].res + tr[p << 1 | 1].res;
    }
    void upd1(int p, int v) {
        tr[p].res = node{tr[p].res.sz, v, v, tr[p].res.sz - 1};
        tr[p].tag = v;
    }
    void pushdown(int p) {
        if(!tr[p].tag) return;
        upd1(p << 1, tr[p].tag);
        upd1(p << 1 | 1, tr[p].tag);
        tr[p].tag = 0;
    }
    void build(int p = 1, int l = 1, int r = n) {
        tr[p].res = node(r - l + 1, 0, 0, 0); tr[p].tag = 0;
        if(l == r) return;
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int ql, int qr, int v, int p = 1, int l = 1, int r = n) {
        if(ql <= l && r <= qr) return upd1(p, v);
        int mid = l + r >> 1;
        pushdown(p);
        if(ql <= mid) update(ql, qr, v, p << 1, l, mid);
        if(qr > mid) update(ql, qr, v, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    node query(int ql, int qr, int p = 1, int l = 1, int r = n) {
        if(ql <= l && r <= qr) return tr[p].res;
        int mid = l + r >> 1;
        pushdown(p);
        if(qr <= mid) return query(ql, qr, p << 1, l, mid);
        else if(ql > mid) return query(ql, qr, p << 1 | 1, mid + 1, r);
        else return query(ql, qr, p << 1, l, mid) + query(ql, qr, p << 1 | 1, mid + 1, r);
    }
}
namespace hld {
    int fa[N], dep[N], sz[N], hson[N];
    void dfs1(int u, int f) {
        sz[u] = 1; fa[u] = f; dep[u] = dep[f] + 1; hson[u] = 0;
        for(int i = head[u]; ~i; i = e[i].nxt) {
            int &v = e[i].to;
            if(v == f) continue;
            dfs1(v, u);
            if(sz[hson[u]] < sz[v]) hson[u] = v;
            sz[u] += sz[v];
        }
    }
    int dfn[N], walk[N], totdfn;
    int top[N];
    void dfs2(int u, int t) {
        walk[dfn[u] = ++ totdfn] = u;
        top[u] = t;
        if(!hson[u]) return;
        dfs2(hson[u], t);
        for(int i = head[u]; ~i; i = e[i].nxt) {
            int &v = e[i].to;
            if(v == fa[u] || v == hson[u]) continue;
            dfs2(v, v);
        }
    }
    int curcol;
    void init() {
        totdfn = curcol = 0;
        dfs1(1, 0);
        dfs2(1, 1);
        smt::build();
    }
    void update(int u, int v) {
        ++ curcol;
        while(top[u] != top[v]) {
            if(dep[top[u]] > dep[top[v]]) {
                smt::update(dfn[top[u]], dfn[u], curcol);
                u = fa[top[u]];
            } else {
                smt::update(dfn[top[v]], dfn[v], curcol);
                v = fa[top[v]];
            }
        }
        if(dep[u] > dep[v]) smt::update(dfn[v], dfn[u], curcol);
        else smt::update(dfn[u], dfn[v], curcol);
    }
    int query(int u, int v) {
        node res1, res2; bool tag1 = 0, tag2 = 0;
        while(top[u] != top[v]) {
            if(dep[top[u]] > dep[top[v]]) {
                tag1 ? (res1 = smt::query(dfn[top[u]], dfn[u]) + res1) : (res1 = smt::query(dfn[top[u]], dfn[u]));
                tag1 = 1;
                u = fa[top[u]];
            } else {
                tag2 ? (res2 = smt::query(dfn[top[v]], dfn[v]) + res2) : (res2 = smt::query(dfn[top[v]], dfn[v]));
                tag2 = 1;
                v = fa[top[v]];
            }
        }
        if(dep[u] > dep[v]) (tag1 ? (res1 = smt::query(dfn[v], dfn[u]) + res1) : (res1 = smt::query(dfn[v], dfn[u]))), tag1 = 1;
        else (tag2 ? (res2 = smt::query(dfn[u], dfn[v]) + res2) : (res2 = smt::query(dfn[u], dfn[v]))), tag2 = 1;
        res1.reverse();
        if(!tag1) return res2.ans;
        if(!tag2) return res1.ans;
        return (res1 + res2).ans;
    }
}
void Hutao() {
    n = read(), m = read();
    llfs::init(n);
    for(int i = 1, u, v; i < n; i ++) {
        u = read(), v = read();
        llfs::adde(u, v);
    }
    hld::init();
    for(int i = 1, op, u, v; i <= m; i ++) {
        op = read(), u = read(), v = read();
        if(op == 1) hld::update(u, v);
        else printf("%d\n", hld::query(u, v));
    }
}
}
int main() {
    int t = read();
    while(t --) work::Hutao();
    return 0;
}