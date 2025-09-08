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
const int N = 5e4 + 10;
const int B = 223;
const int mod = 998244353;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
int powk[N];
int n, q, k, a[N];
vector<pair<int, int> > to[N];
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
        if(!f) a[u] = 1; //
        fa[u] = f, dep[u] = dep[f] + 1; rec[u] = top, rsz[u] = 1, lsbn[u] = 0;
        int bncnt = 0;
        for(auto ele : to[u]) {
            int &v = ele.first, &w = ele.second;
            if(v == f) continue;
            stk[++ top] = v; a[v] = powk[dep[u] + 1]/*Add(a[u], w)*/;
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
int isum_[N], osum_[N], tag_[N], tmp[N];
void init() {
    for(int i = 1; i <= n; i ++) isum_[i] = 0;
    for(auto i : bn_) osum_[i] = tag_[i] = 0;
}
void update(int u) {
    int t = dn_[u];
    for(int x = u; x ^ fa_[t]; x = fa[x]) tmp[x] = Minus(a[x], a[fa[x]]);
    for(auto x : clu_[t]) tmp[x] = Add(tmp[x], tmp[fa[x]]), isum_[x] = Add(isum_[x], tmp[x]);
    for(int x = fa_[t]; x; x = fa_[x]) tmp[x] = Minus(a[x], a[fa_[x]]), ++ tag_[x];
    for(auto x : bn_) tmp[x] = Add(tmp[x], tmp[fa_[x]]), osum_[x] = Add(osum_[x], tmp[x]);
    for(auto x : clu_[t]) tmp[x] = 0;
    for(auto x : bn_) tmp[x] = 0;
}
int query(int u) {
    int res = 0;
    if(u ^ dn_[u])
        res = Add(isum_[u], Mult(tag_[dn_[u]], Minus(a[ne_[u]], a[up_[u]]))), u = up_[u];
    res = Add(res, osum_[u]);
    return res;
}
struct QRY {
    int x, y, id;
    bool operator < (const QRY& obj) const {
        return x < obj.x;
    }
} qry[N];
int ans[N];
void Hutao() {
    n = read(), q = read(), k = read();
    for(int i = 1; i <= n; i ++) powk[i] = Pow(i, k);
    for(int i = 2, u; i <= n; i ++) {
        u = read();
        to[i].push_back(make_pair(u, 0)), to[u].push_back(make_pair(i, 0));
    }
    tdcp::dfs();
    for(int i = 1; i <= q; i ++)
        qry[i].x = read(), qry[i].y = read(), qry[i].id = i;
    sort(qry + 1, qry + q + 1);
    for(int x = 1, qi = 1; x <= n; x ++) {
        update(x);
        for(; qry[qi].x == x; qi ++) ans[qry[qi].id] = query(qry[qi].y);
    }
    for(int i = 1; i <= q; i ++) printf("%d\n", ans[i]);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}