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
const int N = 4e4 + 10, BSZ = 410, BSZ2 = BSZ * BSZ / 2;
int B = 200;
int n, m, a[N];
vector<int> to[N];
int fa[N], dep[N];
int fa_[N], ne_[N], up_[N], dn_[N]; vector<int> son_[N];
int idtot, id_[N]; vector<int> clu_[BSZ], bn_;
bitset<N> bsum[BSZ], btot[BSZ2]; int dcd[BSZ][BSZ];
namespace tdcp {
    int stk[N], top, rec[N], rsz[N], bn[N];
    void add(int u, int v, int l, int r) {
        if(l > r) return;
        v || (v = stk[r], bn_.push_back(v), id_[v] = ++ idtot);
        fa_[v] = u; son_[u].push_back(v);
        ne_[u] = u; for(int x = v; x ^ u; x = fa[x]) ne_[x] = x;
        for(int i = l, p; i <= r; i ++) {
            clu_[id_[v]].push_back(p = stk[i]), up_[p] = u, dn_[p] = v;
            ne_[p] || (ne_[p] = ne_[fa[p]]);
        }
        assert(fa_[v] == up_[v]);
    }
    void dfs(int u, int f) {
        fa[u] = f, dep[u] = dep[f] + 1, rec[u] = top, rsz[u] = 1, bn[u] = 0;
        int bncnt = 0;
        for(auto v : to[u]) {
            if(v == f) continue;
            stk[++ top] = v; dfs(v, u);
            rsz[u] += rsz[v]; bn[v] && (bn[u] = bn[v], ++ bncnt);
        }
        if(!f || bncnt > 1 || rsz[u] >= B) {
            rsz[u] = 1, bn[u] = u, id_[u] = ++ idtot; bn_.push_back(u);
            int curbn = 0, cursz = 0, currec = rec[u] + 1;
            for(auto v : to[u]) {
                if(v == f) continue;
                if(curbn && bn[v] || cursz + rsz[v] > B) {
                    add(u, curbn, currec, rec[v] - 1);
                    currec = rec[v], curbn = cursz = 0;
                }
                bn[v] && (curbn = bn[v]), cursz += rsz[v];
            }
            add(u, curbn, currec, top);
            top = rec[u];
        }
    }
}
void dfs_(int u) {
    for(int x = u; x ^ up_[u]; x = fa[x]) bsum[id_[u]].set(a[x]);
    for(int x = fa_[u]; x; x = fa_[x]) {
        dcd[id_[x]][id_[u]] = ++ idtot;
        btot[idtot] = bsum[id_[u]] | btot[dcd[id_[x]][id_[fa_[u]]]];
    }
    for(auto v : son_[u]) dfs_(v);
}
int query(int u, int v) {
    bitset<N> res(0);
    int tagu = id_[u] ? u : -1, tagv = id_[v] ? v : -1;
    while(up_[u] ^ up_[v]) {
        if(dep[up_[u]] > dep[up_[v]]) {
            if(tagu == -1) {
                tagu = up_[u];
                for(; u ^ tagu; u = fa[u])
                    res.set(a[u]);
            } else
                u = fa_[u];
        } else {
            if(tagv == -1) {
                tagv = up_[v];
                for(; v ^ tagv; v = fa[v])
                    res.set(a[v]);
            } else
                v = fa_[v];
        }
    }
    if(~tagu) res |= btot[dcd[id_[u]][id_[tagu]]];
    if(~tagv) res |= btot[dcd[id_[v]][id_[tagv]]];
    while(u ^ v) {
        if(dep[u] > dep[v]) res.set(a[u]), u = fa[u];
        else res.set(a[v]), v = fa[v];
    }
    res.set(a[u]);
    return res.count();
}
map<int, int> mp;
int lstans;
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= n; i ++) {
        a[i] = read();
        if(!mp[a[i]]) mp[a[i]] = ++ idtot;
        a[i] = mp[a[i]];
    }
    for(int i = 1, u, v; i < n; i ++) {
        u = read(), v = read();
        to[u].push_back(v), to[v].push_back(u);
    }
    idtot = 0; tdcp::dfs(1, 0);
    idtot = 0; dfs_(1);
    for(int i = 1, u, v; i <= m; i ++) {
        u = read() ^ lstans, v = read();
        printf("%d\n", lstans = query(u, v));
    }
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}