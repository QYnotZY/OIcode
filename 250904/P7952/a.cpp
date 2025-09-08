#include "bits/stdc++.h"
using namespace std;
namespace FastIO {
    template <typename T = int> T read() {
        char ch = '\0'; bool f = 0; T res = 0;
        for(; !('0' <= ch && ch <= '9'); ch = getchar()) if(ch == '-') f = !f;
        for(; '0' <= ch && ch <= '9'; ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ '0');
        return f ? ~res + 1 : res;
    }
    char readch(const int acsp = 0) {
        char ch = '\0';
        for(; !(33 - acsp <= ch && ch < 127); ch = getchar()) ;
        return ch;
    }
} using FastIO::read; using FastIO::readch;
typedef long long ll;
namespace Qiuyu3600 {
const int N = 1e6 + 10;
mt19937_64 fate(time(0) << 1 | 1);
int n, q, a[N];
vector<int> to[N];
namespace fhqt {
    int rt[N], tot, rcyc[N];
    struct node {
        int key, sz, fa, lc, rc;
        ll val, maxx;
    } tr[N << 1];
    int newnode(ll val) {
        int p = rcyc[0] ? rcyc[rcyc[0] --] : ++ tot;
        tr[p].key = fate(); tr[p].sz = 1;
        tr[p].fa = tr[p].lc = tr[p].rc = 0;
        tr[p].val = tr[p].maxx = val;
        return p;
    }
    void delnode(int p) {
        if(p) rcyc[++ rcyc[0]] = p;
    }
    void pushup(int p) {
        int &lc = tr[p].lc, &rc = tr[p].rc;
        tr[p].sz = tr[lc].sz + tr[rc].sz + 1;
        tr[p].maxx = max(max(tr[lc].maxx, tr[rc].maxx), tr[p].val);
    }
    void split(int p, int k, int& x, int& y) {
        if(!p) return void(x = y = 0);
        int &lc = tr[p].lc, &rc = tr[p].rc;
        if(tr[lc].sz < k) {
            x = p;
            split(rc, k - tr[lc].sz - 1, rc, y);
        } else {
            y = p;
            split(lc, k, x, lc);
        }
        pushup(p);
    }
    int merge(int x, int y) {
        if(!x || !y) return x | y;
        int p;
        if(tr[x].key > tr[y].key) {
            p = x;
            tr[p].rc = merge(tr[p].rc, y);
        } else {
            p = y;
            tr[p].lc = merge(x, tr[p].lc);
        }
        return pushup(p), p;
    }
    void add(int u, ll val) {
        rt[u] = merge(newnode(val), rt[u]);
    }
    void update(int u, int num, ll val) {
        int A, B, C;
        num = ~num ? tr[rt[u]].sz - num : 0;
        split(rt[u], num, A, rt[u]);
        split(rt[u], 1, B, C);
        delnode(B);
        B = newnode(val);
        rt[u] = merge(A, merge(C, B));
    }
    ll query(int u, int num) {
        int A, B; ll res;
        if(!~num) return tr[rt[u]].maxx;
        if(!num) {
            split(rt[u], 1, A, B);
            res = tr[A].maxx;
            rt[u] = merge(A, B);
            return res;
        }
        num = tr[rt[u]].sz - num;
        split(rt[u], num, A, B);
        res = tr[B].maxx;
        rt[u] = merge(A, B);
        return res;
    }
    void mergec(int u, int v) {
        rt[v] = merge(rt[u], rt[v]); rt[u] = 0;
    }
}
namespace smt {
    ll tr[N << 2];
    void pushup(int p) {
        tr[p] = max(tr[p << 1], tr[p << 1 | 1]);
    }
    void update(int x, ll val, int p = 1, int l = 1, int r = n) {
        if(l == r) return void(tr[p] = val);
        int mid = l + r >> 1;
        if(x <= mid) update(x, val, p << 1, l, mid);
        else update(x, val, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    ll query(int ql, int qr, int p = 1, int l = 1, int r = n) {
        if(ql > qr) return 0;
        if(ql <= l && r <= qr) return tr[p];
        int mid = l + r >> 1; ll res = 0;
        if(ql <= mid) res = max(res, query(ql, qr, p << 1, l, mid));
        if(qr > mid) res = max(res, query(ql, qr, p << 1 | 1, mid + 1, r));
        return res;
    }
}
int dep[N], key[N];
int dn_[N], fa_[N], dfn_[N], sz_[N]; int totdfn_;
int find_(int u) {
    return dn_[u] == u ? u : dn_[u] = find_(dn_[u]);
}
vector<int> son_[N]; int curs_[N];
void dfs(int u, int f) {
    dep[u] = dep[f] + 1;
    if((f == 0) + to[u].size() != 2) {
        key[u] = 1;
        dn_[u] = u;
        dfn_[u] = ++ totdfn_;
        sz_[u] = 1;
        fhqt::add(u, a[u]), smt::update(dfn_[u], fhqt::query(u, -1));
        for(auto v : to[u]) {
            if(v == f) continue;
            dfs(v, u);
            fa_[dn_[v]] = u;
            son_[u].push_back(dn_[v]);
            ++ curs_[u];
            sz_[u] += sz_[dn_[v]];
        }
    } else {
        for(auto v : to[u]) {
            if(v == f) continue;
            dfs(v, u);
            dn_[u] = dn_[v];
            fhqt::add(dn_[u], a[u]); smt::update(dfn_[dn_[u]], fhqt::query(dn_[u], -1));
        }
    }
}
void update(int u, bool all = 0) {
    if(find_(u) == 0) return;
    ll res = 0; int tmp = 0;
    for(auto& v : son_[find_(u)])
        if(key[v = find_(v)]) res += fhqt::query(v, 0);
    fhqt::update(find_(u), all ? -1 : dep[find_(u)] - dep[u] + 1, res);
    smt::update(dfn_[find_(u)], fhqt::query(find_(u), -1));
    u = find_(u);
    for(auto& v : son_[u]) {
        if(!key[v = find_(v)]) continue;
        update(v, 1);
        if(!find_(v)) -- curs_[u];
        else tmp = v = find_(v);
    }
    if(!curs_[u] && !fhqt::query(u, -1)) {
        key[u] = dn_[u] = 0;
        if(all == 0) {
            -- curs_[fa_[u]];
        }
    }
    if(curs_[u] == 1) {
        key[u] = 0;
        fhqt::mergec(u, tmp);
        smt::update(dfn_[tmp], fhqt::query(tmp, -1));
        smt::update(dfn_[u], 0);
        dn_[u] = tmp;
        fa_[tmp] = fa_[u];
    }
}
ll query(int u) {
    ll res = fhqt::query(find_(u), dep[find_(u)] - dep[u] + 1);
    res = max(res, smt::query(dfn_[find_(u)] + 1, dfn_[find_(u)] + sz_[find_(u)] - 1));
    return res;
}
void Hutao() {
    n = read(), q = read();
    for(int i = 1; i <= n; i ++) a[i] = read();
    for(int i = 2, f; i <= n; i ++) {
        f = read();
        to[f].push_back(i), to[i].push_back(f);
    }
    dfs(1, 0);
    for(int i = 1, op, x; i <= q; i ++) {
        op = read(), x = read();
        if(op == 1) printf("%lld\n", query(x));
        else update(x);
    }
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}