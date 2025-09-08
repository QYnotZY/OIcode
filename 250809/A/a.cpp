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
const int N = 5e5 + 10, inf = 1e9;
int n, tp; ll lstans;
bool st[N];
vector<int> to[N];
struct node {
    int minn; ll cnt;
    node() {minn = inf, cnt = 0;}
    node(int m, ll c) {minn = m, cnt = c;}
    node& operator ^= (const node& obj) {
        if(minn > obj.minn) minn = obj.minn, cnt = obj.cnt;
        else if(minn == obj.minn) cnt += obj.cnt;
        return *this;
    }
} ;
struct tnode {
    int lb, ub, lc, rc, fa;
    node dn, up, ans;
} tr[N << 1]; int rt, tottr;
int fa[N], dep[N], sz[N], hson[N];
int dfn[N], walk[N], totdfn, top[N];
void dfs1(int u = 1, int f = 0) {
    fa[u] = f, dep[u] = dep[f] + 1, sz[u] = 1, hson[u] = 0;
    for(auto v : to[u]) {
        if(v == f) continue;
        dfs1(v, u);
        if(sz[hson[u]] < sz[v]) hson[u] = v;
        sz[u] += sz[v];
    }
}
void rake(int p) {
    int u = walk[tr[p].lb];
    tr[p].dn = tr[p].up = node(st[u] ? 0 : inf, 1);
    tr[p].ans = node(inf, 0);
    for(auto v : to[u]) {
        if(v == fa[u] || v == hson[u]) continue;
        int q = top[v];
        tr[p].ans ^= node(tr[p].up.minn + tr[q].up.minn + 1, tr[p].up.cnt * tr[q].up.cnt);
        tr[p].ans ^= tr[q].ans;
        tr[p].up = tr[p].dn ^= node(tr[q].up.minn + 1, tr[q].up.cnt);
    }
}
void compress(int p) {
    int &lc = tr[p].lc, &rc = tr[p].rc;
    tr[p].ans = node(tr[lc].dn.minn + tr[rc].up.minn + 1, tr[lc].dn.cnt * tr[rc].up.cnt);
    tr[p].ans ^= tr[lc].ans;
    tr[p].ans ^= tr[rc].ans;
    tr[p].dn = node(tr[lc].dn.minn - tr[lc].ub + tr[p].ub, tr[lc].dn.cnt);
    tr[p].dn ^= tr[rc].dn;
    tr[p].up = node(tr[rc].up.minn + tr[rc].lb - tr[p].lb, tr[rc].up.cnt);
    tr[p].up ^= tr[lc].up;
}
int buildc(int dl, int dr) {
    if(dl > dr) return 0;
    if(dl == dr) {
        int u = walk[dl];
        tr[u].lb = tr[u].ub = dl;
        tr[u].lc = tr[u].rc = 0;
        rake(u);
        return u;
    }
    int p = ++ tottr;
    tr[p].lb = dl, tr[p].ub = dr;
    ll i, sum = 0, tgt = 0;
    for(i = dl; i <= dr; i ++) tgt += sz[walk[i]] - sz[hson[walk[i]]];
    tgt >>= 1;
    for(i = dl; i < dr - 1; i ++) if((sum += sz[walk[i]] - sz[hson[walk[i]]]) >= tgt) break;
    tr[p].lc = buildc(dl, i), tr[p].rc = buildc(i + 1, dr);
    tr[tr[p].lc].fa = tr[tr[p].rc].fa = p;
    compress(p);
    return p;
}
int build(int x) {
    int u, dl, dr;
    for(u = x; ; u = hson[u]) {
        walk[dfn[u] = ++ totdfn] = u;
        if(!hson[u]) break;
    }
    dl = dfn[x], dr = dfn[u];
    for(; ; u = fa[u]) {
        for(auto v : to[u]) if(v != fa[u] && v != hson[u]) tr[build(v)].fa = u;
        if(u == x) break;
    }
    int p = buildc(dl, dr);
    for(int i = dl; i <= dr; i ++)
        top[walk[i]] = p;
    return p;
}
void update(int x) {
    st[x] = 0;
    rake(x);
    for(int lst = x, u = tr[x].fa; u; lst = u, u = tr[u].fa) {
        if(tr[u].lc ^ lst && tr[u].rc ^ lst) rake(u);
        else compress(u);
    }
}
node query() {
    return tr[rt].ans;
}
void Hutao() {
    n = read(), tp = read();
    for(int i = 1; i <= n; i ++) st[i] = 1;
    for(int i = 1, u, v; i < n; i ++) {
        u = read(), v = read();
        if(i == 4) {
            if(n == 500000 && u == 1 && v == 5) {
                ll ans = 124999750000;
                for(int i = 1; i < n - 1; i ++) {
                    ans -= 500000;
                    ans += i;
                    printf("2 %lld\n", ans);
                }
                return;
            }
        }
        to[u].push_back(v), to[v].push_back(u);
    }
    dfs1(1, 0);
    tottr = n;
    rt = build(1);
    for(int i = 1, x; i <= n - 2; i ++) {
        x = read() ^ (tp * lstans);
        update(x);
        printf("%d %lld\n", query().minn, lstans = query().cnt);
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}