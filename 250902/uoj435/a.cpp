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
const int N = 1e5 + 10;
const int B = 300, Basz = 1320, B2 = 1000, Vbuc = B2, B2asz = Vbuc + 5 << 1;
int n, m, T, a[N];
vector<int> to[N];
int fa[N], dep[N];
int fa_[N], ne_[N], up_[N], dn_[N]; vector<int> son_[N];
int id_[N]; vector<int> clu_[Basz];
int buc_c[Basz][B2asz], ans_c[Basz], ans_s[Basz], tag_c[Basz];
namespace tdcp {
    int idtot, stk[N], top, rec[N], rsz[N], bn[N];
    void add(int u, int v, int l, int r) {
        if(l > r) return;
        v || (v = stk[r], id_[v] = ++ idtot);
        fa_[v] = u; son_[u].push_back(v);
        ne_[u] = u; for(int x = v; x ^ u; x = fa[x]) ne_[x] = x;
        for(int i = l, x; i <= r; i ++) {
            clu_[id_[v]].push_back(x = stk[i]), up_[x] = u, dn_[x] = v;
            if(!ne_[x]) ne_[x] = ne_[fa[x]];
        }
    }
    void dfs(int u, int f) {
        fa[u] = f, dep[u] = dep[f] + 1, rec[u] = top, rsz[u] = 1, bn[u] = 0;
        int bncnt(0);
        for(auto v : to[u]) {
            if(v == f) continue;
            stk[++ top] = v; dfs(v, u);
            rsz[u] += rsz[v], bn[v] && (bn[u] = bn[v], ++ bncnt);
        }
        if(!f || bncnt > 1 || rsz[u] >= B) {
            id_[u] = ++ idtot; bn[u] = u, rsz[u] = 1;
            int currec = rec[u] + 1, cursz = 0, curbn = 0;
            for(auto v : to[u]) {
                if(v == f) continue;
                if(curbn && bn[v] || cursz + rsz[v] > B) {
                    add(u, curbn, currec, rec[v] - 1);
                    currec = rec[v], cursz = curbn = 0;
                }
                curbn |= bn[v], cursz += rsz[v];
            }
            add(u, curbn, currec, top);
            top = rec[u];
        }
        if(!f) {
            ne_[u] = u;
            dn_[u] = u;
            clu_[id_[u]].push_back(u);
        }
    }
}
void pushup(int u) {
    if(!u) return;
    int idu = id_[u];
    ans_s[idu] = 0;
    for(auto v : clu_[idu]) {
        if(ne_[v] == v) {
            if(abs(a[v]) < Vbuc) ++ buc_c[idu][Vbuc + a[v]];
            if(a[v] > 0) ++ ans_c[idu];
        } else {
            if(a[v] > 0) ++ ans_s[idu];
        }
    }
}
void pushdown(int u) {
    if(!u) return;
    int idu = id_[u];
    for(auto v : clu_[idu])
        if(ne_[v] == v)
            if(abs(a[v]) < Vbuc) buc_c[idu][Vbuc + a[v]] = 0;
    ans_c[idu] = ans_s[idu] = 0;
    for(auto v : clu_[idu])
        if(ne_[v] == v)
            a[v] += tag_c[idu];
    tag_c[idu] = 0;
}
void upd1addc(int u, int val) {
    if(!u) return;
    int idu = id_[u];
    if(val == 1) {
        ans_c[idu] += buc_c[idu][Vbuc - tag_c[idu]];
        ++ tag_c[idu];
    } else {
        -- tag_c[idu];
        ans_c[idu] -= buc_c[idu][Vbuc - tag_c[idu]];
    }
}
void build(bool down, int u = 1) {
    if(down) pushdown(u);
    pushup(u);
    for(auto v : son_[u]) build(down, v);
}
int pstk[4], ptop;
void updatep(int u, int v, int w) {
    int tagu = 0, tagv = 0;
    while(up_[u] ^ up_[v]) {
        if(dep[up_[u]] > dep[up_[v]]) {
            if(!tagu) {
                tagu = dn_[u];
                pushdown(tagu);
                for(; u ^ fa_[tagu]; u = fa[u]) a[u] += w;
                pushup(tagu);
            } else upd1addc(u, w), u = fa_[u];
        } else {
            if(!tagv) {
                tagv = dn_[v];
                pushdown(tagv);
                for(; v ^ fa_[tagv]; v = fa[v]) a[v] += w;
                pushup(tagv);
            } else upd1addc(v, w), v = fa_[v];
        }
    }
    tagu = dn_[u], tagv = dn_[v];
    pushdown(tagu); if(tagu ^ tagv) pushdown(tagv);
    while(u ^ v) {
        if(dep[u] > dep[v]) a[u] += w, u = fa[u];
        else a[v] += w, v = fa[v];
    }
    if(dn_[u] ^ tagu) pushdown(dn_[u]);
    a[u] += w;
    if(dn_[u] ^ tagu) pushup(dn_[u]);
    pushup(tagu); if(tagu ^ tagv) pushup(tagv);
}
int queryp(int u, int v) {
    int res = 0;
    int tagu = 0, tagv = 0;
    while(up_[u] ^ up_[v]) {
        if(dep[up_[u]] > dep[up_[v]]) {
            if(!tagu) {
                tagu = dn_[u];
                for(; u ^ fa_[tagu]; u = fa[u]) res += (a[u] > (ne_[u] == u ? -tag_c[id_[tagu]] : 0));
            } else res += ans_c[id_[u]], u = fa_[u];
        } else {
            if(!tagv) {
                tagv = dn_[v];
                for(; v ^ fa_[tagv]; v = fa[v]) res += (a[v] > (ne_[v] == v ? -tag_c[id_[tagv]] : 0));
            } else res += ans_c[id_[v]], v = fa_[v];
        }
    }
    while(u ^ v) {
        if(dep[u] > dep[v]) res += (a[u] > (ne_[u] == u ? -tag_c[id_[dn_[u]]] : 0)), u = fa[u];
        else res += (a[v] > (ne_[v] == v ? -tag_c[id_[dn_[v]]] : 0)), v = fa[v];
    }
    res += (a[u] > (ne_[u] == u ? -tag_c[id_[dn_[u]]] : 0));
    return res;
}
int qsdfs1(int u) {
    int res = (a[u] > (ne_[u] == u ? -tag_c[id_[dn_[u]]] : 0));
    for(auto v : to[u])
        if(v != fa[u] && dn_[v] == dn_[u]) res += qsdfs1(v);
    return res;
}
int qsdfs2(int u) {
    int res = ans_c[id_[u]] + ans_s[id_[u]];
    for(auto v : son_[u])
        res += qsdfs2(v);
    return res;
}
int querys(int u) {
    int res = qsdfs1(u);
    if(ne_[u] == u) for(auto v : son_[dn_[u]])
        res += qsdfs2(v);
    return res;
}
int lstans;
void Hutao() {
    n = read(), m = read(), T = read();
    for(int i = 1, u, v; i < n; i ++) {
        u = read(), v = read();
        to[u].push_back(v), to[v].push_back(u);
    }
    for(int i = 1; i <= n; i ++) a[i] = read();
    tdcp::idtot = 0, tdcp::dfs(1, 0);
    build(0);
    for(int i = 1, op, x, y, z, cnt = 0; i <= m; i ++) {
        op = read(), x = read() ^ T * lstans;
        if(op == 3) {
            printf("%d\n", lstans = querys(x));
        } else {
            y = read() ^ T * lstans;
            if(op == 2) {
                printf("%d\n", lstans = queryp(x, y));
            } else {
                z = read();
                updatep(x, y, z);
                ++ cnt;
                if(cnt >= B2) {
                    cnt = 0;
                    build(1);
                }
            }
        }
    }
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}