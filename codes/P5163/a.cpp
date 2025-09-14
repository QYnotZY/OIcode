#include "bits/stdc++.h"
using namespace std;
namespace FastIO {
    template<typename T = int> T read() {
        char ch = getchar(); bool neg = 0; T res = 0;
        for(; !('0' <= ch && ch <= '9'); ch = getchar()) if(ch == '-') neg = !neg;
        for(; ('0' <= ch && ch <= '9'); ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ 48);
        return neg ? ~res + 1 : res;
    }
    char readch(bool acsp = 0) {
        char ch = getchar(); for(; !(33 - acsp <= ch && ch < 127); ch = getchar()); return ch;
    }
} using namespace FastIO;
typedef long long ll;
namespace Qiuyu3600 {
const int N = 1e5 + 10, M = 2e5 + 10, inf = 1e9;
int n, m, q;
int a[N];
struct edge {int u, v, delt;} ed[M];
map<pair<int, int>, int> code;
struct opt {int op, a, b;} op[M];
namespace dsu {
    int fa[N], sz[N];
    pair<int, int> stk[N]; int top;
    void init(int n) {
        for(int i = 1; i <= n; i ++)
            fa[i] = i, sz[i] = 1;
    }
    int find(int x) {return fa[x] == x ? x : find(fa[x]);}
    bool merge(int x, int y) {
        int res = false;
        x = find(x), y = find(y);
        if(x == y) return res;
        if(sz[x] < sz[y]) swap(x, y), res = true;
        stk[++ top] = make_pair(x, y);
        fa[y] = x, sz[x] += sz[y];
        return res;
    }
    int record() {return top;}
    void undo(int t) {
        for(int x, y; top > t; -- top) {
            x = stk[top].first, y = stk[top].second;
            fa[y] = y, sz[x] -= sz[y];
        }
    }
}
namespace scc {
    bool inpts[N];
    vector<int> pts, to[N];
    int dfn[N], tot, low[N];
    int stk[N], top; bool instk[N];
    void add(int u) {
        if(!inpts[u]) inpts[u] = 1, pts.push_back(u);
    }
    void add(int u, int v) {
        to[u].push_back(v);
    }
    void Tarjan(int u) {
        low[u] = dfn[u] = ++ tot; stk[++ top] = u, instk[u] = 1;
        for(auto v : to[u])
            if(!dfn[v]) {
                Tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if(instk[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        if(dfn[u] == low[u]) {
            while(stk[top] ^ u) {
                dsu::merge(u, stk[top]);
                instk[stk[top --]] = 0;
            }
            instk[stk[top --]] = 0;
        }
    }
    void work() {
        for(auto u : pts) if(!dfn[u]) Tarjan(u);
        tot = top = 0;
        for(auto u : pts) inpts[u] = 0, to[u].clear(), dfn[u] = low[u] = 0;
        pts.clear();
    }
}
vector<int> ans[M]; int p[M], tmp[M];
void solve(int l, int r, int ql, int qr) {
    if(l == r) {
        for(int i = ql; i <= qr; i ++)
            ans[l].push_back(p[i]);
        return;
    }
    int mid = l + r >> 1, dsurec = dsu::record();
    for(int i = ql, x, y; i <= qr; i ++)
        if(ed[p[i]].delt > mid) {
            x = dsu::find(ed[p[i]].u), y = dsu::find(ed[p[i]].v);
            scc::add(x); scc::add(y); scc::add(x, y);
        }
    scc::work();
    int pl = ql - 1, pr = qr + 1;
    for(int i = ql; i <= qr; i ++) {
        if(ed[p[i]].delt > mid && dsu::find(ed[p[i]].u) == dsu::find(ed[p[i]].v)) {
            tmp[-- pr] = p[i];
        } else tmp[++ pl] = p[i];
    }
    for(int i = ql; i <= qr; i ++) p[i] = tmp[i];
    solve(l, mid, ql, pl);
    dsu::undo(dsurec);
    solve(mid + 1, r, pr, qr);
}
namespace smt {
    struct node {
        int lc, rc; int sz; ll sum;
    } tr[N * 96];
    int rt[N], tot;
    void pushup(int p) {
        int &lc = tr[p].lc, &rc = tr[p].rc;
        tr[p].sz = tr[lc].sz + tr[rc].sz;
        tr[p].sum = tr[lc].sum + tr[rc].sum;
    }
    void update_(int x, int v, int p, int l = 0, int r = inf) {
        if(l == r) return tr[p].sz += v, tr[p].sum += v * l, void();
        int mid = l + r >> 1;
        if(x <= mid) {if(!tr[p].lc) tr[p].lc = ++ tot; update_(x, v, tr[p].lc, l, mid);}
        else {if(!tr[p].rc) tr[p].rc = ++ tot; update_(x, v, tr[p].rc, mid + 1, r);}
        pushup(p);
    }
    void insert(int pos, int val) {
        if(!rt[pos]) rt[pos] = ++ tot; update_(val, 1, rt[pos]);
    }
    void change(int pos, int v0, int v1) {
        update_(v0, -1, rt[pos]); update_(v1, 1, rt[pos]);
    }
    int merge_(int p, int q, int l = 0, int r = inf) {
        if(!p || !q) return p | q;
        if(l == r) {
            tr[p].sz += tr[q].sz;
            tr[p].sum += tr[q].sum;
            return p;
        }
        int mid = l + r >> 1;
        tr[p].lc = merge_(tr[p].lc, tr[q].lc, l, mid);
        tr[p].rc = merge_(tr[p].rc, tr[q].rc, mid + 1, r);
        return pushup(p), p;
    }
    void merge(int u, int v) {
        if(u == v) return;
        rt[u] = merge_(rt[u], rt[v]);
    }
    ll query_(int k, int p, int l = 0, int r = inf) {
        if(l == r) return 1ll * l * k;
        int mid = l + r >> 1, rsz = tr[tr[p].rc].sz;
        if(rsz >= k) return query_(k, tr[p].rc, mid + 1, r);
        else return query_(k - rsz, tr[p].lc, l, mid) + tr[tr[p].rc].sum;
    }
    ll query(int pos, int k) {
        return query_(k, rt[pos]);
    }
}
void Merge(int u, int v) {
    u = dsu::find(u), v = dsu::find(v);
    dsu::merge(u, v) ? smt::merge(v, u) : smt::merge(u, v);
}
ll ANS[M];
void Hutao() {
    n = read(), m = read(), q = read();
    for(int i = 1; i <= n; i ++) a[i] = read();
    for(int i = 1; i <= m; i ++) {
        ed[i] = {read(), read(), q + 1};
        code[make_pair(ed[i].u, ed[i].v)] = i;
    }
    for(int i = 1; i <= q; i ++) {
        op[i] = {read(), read(), read()};
        if(op[i].op == 1) ed[code[make_pair(op[i].a, op[i].b)]].delt = i;
        if(op[i].op == 2) a[op[i].a] += op[i].b;
    }
    for(int i = 1; i <= m; i ++) p[i] = i; dsu::init(n);
    solve(0, q + 1, 1, m);
    dsu::init(n);
    for(int i = 1; i <= n; i ++) smt::insert(i, a[i]);
    for(auto ele : ans[q + 1]) Merge(ed[ele].u, ed[ele].v);
    for(int i = q; i; -- i)
        if(op[i].op == 1) {
            ANS[i] = -1;
            for(auto ele : ans[i]) Merge(ed[ele].u, ed[ele].v);
        } else if(op[i].op == 2) {
            ANS[i] = -1;
            smt::change(dsu::find(op[i].a), a[op[i].a], a[op[i].a] - op[i].b);
            a[op[i].a] -= op[i].b;
        } else {
            ANS[i] = smt::query(dsu::find(op[i].a), op[i].b);
        }
    for(int i = 1; i <= q; i ++)
        if(~ANS[i]) printf("%lld\n", ANS[i]);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}