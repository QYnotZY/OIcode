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
const int N = 5e5 + 10;
int n, q;
vector<int> to[N];
int fa[N][20], dep[N], ldep[N];
void dfs(int u, int f) {
    fa[u][0] = f, dep[u] = dep[f] + 1;
    for(int i = 1; i < 20; i ++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for(auto v : to[u]) {
        if(v == f) continue;
        dfs(v, u);
    }
}
int lca(int u, int v) {
    if(dep[u] > dep[v]) swap(u, v);
    for(int i = 19; ~i; -- i)
        if(dep[v] - dep[u] >= 1 << i) v = fa[v][i];
    if(u == v) return u;
    for(int i = 19; ~i; -- i)
        if(fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}
namespace st2 {
    int _[20][N];
    inline int log2(int x) {int res = 0; while(x >>= 1) ++ res; return res;}
    inline void build() {
        for(int i = 1; i <= n; i ++) _[0][i] = dep[i];
        for(int i = 1; i < 20; i ++)
            for(int j = 1; j + (1 << i) - 1 <= n; j ++)
                _[i][j] = max(_[i - 1][j], _[i - 1][j + (1 << i - 1)]);
    }
    inline int query(int x, int y) {
        int log2n = log2(y - x + 1);
        return max(_[log2n][x], _[log2n][y - (1 << log2n) + 1]);
    }
}
namespace st {
    struct node {
        int pos, minn;
        bool operator <(const node& obj) const {
            return minn < obj.minn;
        }
    } _[20][N];
    inline int log2(int x) {int res = 0; while(x >>= 1) ++ res; return res;}
    inline void build() {
        for(int i = 1; i < n; i ++) _[0][i] = {i, ldep[i]};
        for(int i = 1; i < 20; i ++)
            for(int j = 1; j + (1 << i) - 1 < n; j ++) 
                _[i][j] = min(_[i - 1][j], _[i - 1][j + (1 << i - 1)]);
    }
    inline int query(int x, int y) {
        int log2n = log2(y - x + 1);
        return min(_[log2n][x], _[log2n][y - (1 << log2n) + 1]).pos;
    }
}
struct MDF {
    int l, r, val;
    bool operator <(const MDF& obj) const {
        return r > obj.r;
    }
    bool operator >(const MDF& obj) const {
        return r - l > obj.r - obj.l;
    }
} mdf[N]; int msz;
void getmdf(int l, int r) {
    if(l > r) return;
    int mid = st::query(l, r);
    mdf[++ msz] = {l, r, ldep[mid]};
    getmdf(l, mid - 1), getmdf(mid + 1, r);
}
struct QRY {
    int l, r, k; int id;
    bool operator <(const QRY& obj) const {
        return r > obj.r;
    }
    bool operator >(const QRY& obj) const {
        return k > obj.k;
    }
} qry[N]; int qsz;
int ans[N];
namespace smt {
    int tr[N << 2];
    void pushup(int p) {
        tr[p] = max(tr[p << 1], tr[p << 1 | 1]);
    }
    void build(int p = 1, int l = 1, int r = n) {
        if(l == r) return void(tr[p] = 0);
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int x, int v, int p = 1, int l = 1, int r = n) {
        if(l == r) return void(tr[p] = v);
        int mid = l + r >> 1;
        if(x <= mid) update(x, v, p << 1, l, mid);
        else update(x, v, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    int query(int ql, int qr, int p = 1, int l = 1, int r = n) {
        if(ql <= l && r <= qr) return tr[p];
        int mid = l + r >> 1, res = 0;
        if(ql <= mid) res = max(res, query(ql, qr, p << 1, l, mid));
        if(qr > mid) res = max(res, query(ql, qr, p << 1 | 1, mid + 1, r));
        return res;
    }
}
void Hutao() {
    n = read();
    for(int i = 1, u, v; i < n; i ++) {
        u = read(), v = read();
        to[u].push_back(v), to[v].push_back(u);
    }
    dfs(1, 0);
    st2::build();
    for(int i = 1; i < n; i ++) ldep[i] = dep[lca(i, i + 1)];
    st::build(); getmdf(1, n - 1);
    q = read();
    for(int i = 1, l, r, k; i <= q; i ++) {
        l = read(), r = read(), k = read();
        if(k == 1) {ans[i] = st2::query(l, r);}
        else {qry[++ qsz] = {l, r - 1, k - 1, i};}
    }
    sort(mdf + 1, mdf + msz + 1), sort(qry + 1, qry + qsz + 1); smt::build();
    for(int r = n, mi = 1, qi = 1; r; -- r) {
        for(; mi <= msz && mdf[mi].r > r; mi ++)
            smt::update(mdf[mi].l, mdf[mi].val);
        for(; qi <= qsz && qry[qi].r == r; qi ++)
            ans[qry[qi].id] = max(ans[qry[qi].id], smt::query(1, r - qry[qi].k + 1));
    }
    sort(mdf + 1, mdf + msz + 1, greater<MDF>()), sort(qry + 1, qry + qsz + 1, greater<QRY>()); smt::build();
    for(int k = n, mi = 1, qi = 1; k; -- k) {
        for(; mi <= msz && mdf[mi].r - mdf[mi].l + 1 >= k; mi ++)
            smt::update(mdf[mi].r, mdf[mi].val);
        for(; qi <= qsz && qry[qi].k == k; qi ++)
            ans[qry[qi].id] = max(ans[qry[qi].id], smt::query(qry[qi].l + k - 1, qry[qi].r));
    }
    for(int i = 1; i <= q; i ++)
        printf("%d\n", ans[i]);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}