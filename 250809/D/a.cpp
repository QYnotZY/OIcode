#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
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
const int N = 1e6 + 10;
mt19937 my_rand(1145141);
int n, m;
int a[N];
vector<int> to[N];
namespace bit {
    int tr[N], tmp, res;
    inline int lowbit(const int &x) {return x & -x;}
    inline void add(int x, const int v) {for(; x <= n; x += lowbit(x)) tr[x] += v;}
    inline int query(int x) {for(res = 0; x; x -= lowbit(x)) res += tr[x]; return res;}
}
namespace fhqt {
    int rt[N], tot;
    struct node {
        int key, lc, rc, sz; int val, cnt;
    } tr[N * 5];
    inline int newnode(const int &val) {
        int p = ++ tot;
        tr[p].key = my_rand(), tr[p].val = val;
        tr[p].lc = tr[p].rc = 0;
        tr[p].sz = tr[p].cnt = 1;
        return p;
    }
    inline void pushup(const int &p) {
        tr[p].sz = tr[tr[p].lc].sz + tr[p].cnt + tr[tr[p].rc].sz;
    }
    void split(int p, const int val, int &x, int &y) {
        if(!p) return void(x = y = 0);
        int &lc = tr[p].lc, &rc = tr[p].rc;
        if(tr[p].val <= val) {
            x = p;
            split(rc, val, rc, y);
        } else {
            y = p;
            split(lc, val, x, lc);
        }
        pushup(p);
    }
    int merge(const int &x, const int &y) {
        if(!x || !y) return x | y;
        int p;
        if(tr[x].key > tr[y].key) {
            p = x;
            tr[p].rc = merge(tr[x].rc, y);
        } else {
            p = y;
            tr[p].lc = merge(x, tr[y].lc);
        }
        pushup(p);
        return p;
    }
    inline void ins(const int &u, const int &val) {
        int A, B, C;
        split(rt[u], val - 1, A, B);
        split(B, val, B, C);
        if(B) tr[B].sz = ++ tr[B].cnt;
        else B = newnode(val);
        rt[u] = merge(A, merge(B, C));
    }
    inline void del(const int &u, const int &val) {
        int A, B, C;
        split(rt[u], val - 1, A, B);
        split(B, val, B, C);
        if(tr[B].cnt == 1) return rt[u] = merge(A, C), void();
        tr[B].sz = -- tr[B].cnt;
        rt[u] = merge(A, merge(B, C));
    }
    int sc(const int &p, const int &k) {
        int &lsz = tr[tr[p].lc].sz, &c = tr[p].cnt;
        return k - c <= lsz && lsz <= k - 1 ? tr[p].val : (lsz < k - c ? sc(tr[p].rc, k - lsz - c) : sc(tr[p].lc, k));
    }
    inline int topk(const int &u, const int &k) {
        if(tr[rt[u]].sz < k) return 0;
        return sc(rt[u], k);
    }
    void print(int p) {
        if(!p) return;
        print(tr[p].lc);
        printf("%d  %d %d  %d %d %d\n", p, tr[p].val, tr[p].cnt, tr[p].sz, tr[p].lc, tr[p].rc);
        print(tr[p].rc);
    }
}
namespace hld {
    int fa[N], dep[N], sz[N], hson[N];
    void dfs1(const int &u, const int &f) {
        fa[u] = f, dep[u] = dep[f] + 1, sz[u] = 1, hson[u] = 0;
        for(auto &v : to[u]) {
            if(v == f) continue;
            dfs1(v, u);
            if(sz[hson[u]] < sz[v]) hson[u] = v;
            sz[u] += sz[v];
        }
    }
    int dfn[N], walk[N], totdfn, top[N];
    void dfs2(const int &u, const int &t) {
        walk[dfn[u] = ++ totdfn] = u; top[u] = t;
        if(hson[u]) dfs2(hson[u], t);
        for(auto &v : to[u]) {
            if(v == fa[u] || v == hson[u]) continue;
            dfs2(v, v);
            fhqt::ins(u, a[v]);
        }
    }
    void init() {
        dfs1(1, 0);
        dfs2(1, 1);
        for(int i = 1; i <= n; i ++) bit::add(i, a[walk[i]] - a[walk[i - 1]]);
    }
    void update(int u, int v, const int &val) {
        while(top[u] != top[v]) {
            if(dep[top[u]] < dep[top[v]]) {
                fhqt::del(fa[top[v]], bit::query(dfn[top[v]]));
                bit::add(dfn[top[v]], val);
                bit::add(dfn[v] + 1, -val);
                fhqt::ins(fa[top[v]], bit::query(dfn[top[v]]));
                v = fa[top[v]];
            } else {
                fhqt::del(fa[top[u]], bit::query(dfn[top[u]]));
                bit::add(dfn[top[u]], val);
                bit::add(dfn[u] + 1, -val);
                fhqt::ins(fa[top[u]], bit::query(dfn[top[u]]));
                u = fa[top[u]];
            }
        }
        if(dep[u] > dep[v]) swap(u, v);
        if(u ^ 1 && u == top[u]) fhqt::del(fa[top[u]], bit::query(dfn[top[u]]));
        bit::add(dfn[u], val);
        bit::add(dfn[v] + 1, -val);
        if(u ^ 1 && u == top[u]) fhqt::ins(fa[top[u]], bit::query(dfn[top[u]]));
    }
    inline int query(const int &u, const int &k) {
        if(u ^ 1) fhqt::ins(u, bit::query(dfn[fa[u]]));
        if(hson[u]) fhqt::ins(u, bit::query(dfn[hson[u]]));
        fhqt::ins(u, bit::query(dfn[u]));
        int res = fhqt::topk(u, k);
        if(u ^ 1) fhqt::del(u, bit::query(dfn[fa[u]]));
        if(hson[u]) fhqt::del(u, bit::query(dfn[hson[u]]));
        fhqt::del(u, bit::query(dfn[u]));
        return res;
    }
}
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= n; i ++) a[i] = read();
    for(int i = 1, u, v; i < n; i ++) {
        u = read(), v = read();
        to[u].push_back(v), to[v].push_back(u);
    }
    hld::init();
    for(int i = 1, op, x, y, z; i <= m; i ++) {
        op = read(), x = read(), y = read();
        if(op == 1) {
            z = read();
            hld::update(x, y, z);
        } else {
            printf("%d\n", hld::query(x, y));
        }
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}