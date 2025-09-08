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
const int N = 2e5 + 10;
const int B = 640;
typedef unsigned int uint;
int n, q; uint a[N];
vector<pair<int, uint> > to[N];
int fa[N], dep[N];
int ne_[N], up_[N], dn_[N], fa_[N];
vector<int> son_[N], clu_[N], bn_;
namespace tdcp {
    int stk[N], top, rec[N], rsz[N], lsbn[N];
    void add(int u, int v, int l, int r) {
        if(l > r) return;
        v || (v = stk[r]);
        bn_.push_back(v);
        fa_[v] = u; son_[u].push_back(v);
        ne_[u] = u; for(int x = v; x ^ u; x = fa[x]) ne_[x] = x;
        for(int i = l, x; i <= r; i ++) {
            clu_[v].push_back(x = stk[i]), up_[x] = u, dn_[x] = v;
            ne_[x] || (ne_[x] = ne_[fa[x]]);
        }
    }
    void dfs(int u = 1, int f = 0) {
        fa[u] = f, dep[u] = dep[f] + 1; rec[u] = top, rsz[u] = 1, lsbn[u] = 0;
        int bncnt = 0;
        for(auto ele : to[u]) {
            int &v = ele.first; uint &w = ele.second;
            if(v == f) continue;
            stk[++ top] = v; a[v] = a[u] + w;
            dfs(v, u);
            rsz[u] += rsz[v]; lsbn[v] && (lsbn[u] = lsbn[v], ++ bncnt);
        }
        if(!f || bncnt > 1 || rsz[u] >= B) {
            rsz[u] = 1, lsbn[u] = u;
            int currec = rec[u] + 1, cursz = 0, curbn = 0;
            for(auto ele : to[u]) {
                int &v = ele.first;
                if(v == f) continue;
                if(curbn && lsbn[v] || cursz + rsz[v] > B) {
                    add(u, curbn, currec, rec[v] - 1);
                    currec = rec[v], cursz = curbn = 0;
                }
                curbn |= lsbn[v], cursz += rsz[v];
            }
            add(u, curbn, currec, top);
            top = rec[u];
        }
        if(!f) dn_[u] = ne_[u] = u, clu_[u].push_back(u), bn_.push_back(u), reverse(bn_.begin(), bn_.end());
    }
}
uint isum_[N], osum_[N], tag_[N], tmp[N];
void init() {
    for(int i = 1; i <= n; i ++) isum_[i] = 0;
    for(auto i : bn_) osum_[i] = tag_[i] = 0;
}
void update(int u) {
    int t = dn_[u];
    for(int x = u; x ^ fa_[t]; x = fa[x]) tmp[x] = a[x] - a[fa[x]];
    for(auto x : clu_[t]) tmp[x] += tmp[fa[x]], isum_[x] += tmp[x];
    for(int x = fa_[t]; x; x = fa_[x]) tmp[x] = a[x] - a[fa_[x]], ++ tag_[x];
    for(auto x : bn_) tmp[x] += tmp[fa_[x]], osum_[x] += tmp[x];
    for(auto x : clu_[t]) tmp[x] = 0;
    for(auto x : bn_) tmp[x] = 0;
}
int query(int u) {
    int res = 0;
    if(u ^ dn_[u])
        res = isum_[u] + tag_[dn_[u]] * (a[ne_[u]] - a[up_[u]]), u = up_[u];
    res += osum_[u];
    return res;
}
struct QRY {
    int l, r, id;
    bool operator < (const QRY& obj) const {
        if(l / B == obj.l / B) return l / B & 1 ? r > obj.r : r < obj.r;
        return l / B < obj.l / B;
    }
} qry[N];
struct QRY2 {
    int x, yl, yr, sgn, id;
    bool operator < (const QRY2& obj) const {
        return x < obj.x;
    }
} qry2[N << 1];
uint ans[N], ans2[N];
int qtot;
void addq(int x, int yl, int yr, int sgn, int id) {
    qry2[++ qtot] = {x, yl, yr, sgn, id};
}
void Furina() {
    sort(qry2 + 1, qry2 + qtot + 1);
    for(int x = 0, qi = 1; x <= n; x ++) {
        if(x) update(x);
        for(; qi <= qtot && qry2[qi].x == x; qi ++)
            for(int y = qry2[qi].yl; y <= qry2[qi].yr; y ++)
                ans2[qry2[qi].id] += qry2[qi].sgn * query(y);
    }
}
uint D[N], P[N], S[N];
void Skirk() {
    for(int x = 1; x <= n; x ++) P[x] = query(x), update(x), S[x] = query(x);
    for(int x = 1; x <= n; x ++) P[x] += P[x - 1], S[x] += S[x - 1];
    sort(qry + 1, qry + q + 1); init();
    int l = 1, r = 1;
    for(int i = 1; i <= q; i ++) {
        ans2[i] = P[qry[i].r] - P[r] + S[qry[i].l - 1] - S[l - 1];
        if(qry[i].l < l) addq(r, qry[i].l, l - 1, 1, i), l = qry[i].l;
        if(r < qry[i].r) addq(l - 1, r + 1, qry[i].r, -1, i), r = qry[i].r;
        if(l < qry[i].l) addq(r, l, qry[i].l - 1, -1, i), l = qry[i].l;
        if(qry[i].r < r) addq(l - 1, qry[i].r + 1, r, 1, i), r = qry[i].r;
    }
    Furina();
    for(int i = 1; i <= q; i ++) ans2[i] += ans2[i - 1];
    for(int i = 1; i <= q; i ++) ans[qry[i].id] -= ans2[i] << 1;
}
void Hutao() {
    n = read(), q = read();
    for(uint i = 1, u, v, w; i < n; i ++) {
        u = read(), v = read(), w = read<uint>();
        to[u].push_back(make_pair(v, w)), to[v].push_back(make_pair(u, w));
    }
    tdcp::dfs();
    for(int i = 1; i <= n; i ++) D[i] = D[i - 1] + a[i];
    for(int i = 1; i <= q; i ++) {
        qry[i].l = read(), qry[i].r = read(), qry[i].id = i;
        ans[i] = uint(qry[i].r - qry[i].l) * (D[qry[i].r] - D[qry[i].l - 1]);
    }
    Skirk();
    for(int i = 1; i <= q; i ++) printf("%u\n", ans[i]);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}