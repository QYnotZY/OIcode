#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
char buf[1 << 20], *p1, *p2;
inline char gc(){
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
}
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
const int N = 5e5 + 10, M = 1e6 + 10;
int n, m;
namespace scl {
    namespace smt {
        int tr[N];
        inline int lowbit(int x) {return x & -x;}
        void add(int x, int v) {
            for(; x <= n; x += lowbit(x)) tr[x] += v;
        }
        int query(int x) {
            int res = 0; for(; x; x -= lowbit(x)) res += tr[x]; return res;
        }
        void build() {
            memset(tr, 0, sizeof tr);
        }
        void update(int ql, int qr, int v) {
            add(ql, v), add(qr + 1, -v);
        }
    }
    struct MDF {
        int yl, yr, v;
    } ;
    vector<MDF> m[N];
    struct QRY {
        int y, id;
    } ;
    vector<QRY> q[N];
    int ans[M]; int asz;
    void mdf_insert(int x1, int x2, int y1, int y2) {
        if(x1 > x2 || y1 > y2) return;
        m[x1].push_back(MDF{y1, y2, 1});
        m[x2 + 1].push_back(MDF{y1, y2, -1});
    }
    void qry_insert(int x, int y) {
        q[x].push_back(QRY{y, ++ asz});
    }
    void work() {
        smt::build();
        for(int x = 1, mi = 1, qi = 1; x <= n; x ++) {
            for(auto &ele : m[x]) smt::update(ele.yl, ele.yr, ele.v);
            for(auto &ele : q[x]) ans[ele.id] = smt::query(ele.y);
        }
    }
}
int typ[N], a[N];
vector<int> to[N];
int fa[N][18], dep[N], sz[N];
int dfn[N], walk[N], totdfn;
void dfs(int u, int f) {
    fa[u][0] = f, dep[u] = dep[f] + 1, sz[u] = 1;
    for(int i = 1; i < 18; i ++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    dfn[u] = ++ totdfn, walk[totdfn] = u;
    for(auto v : to[u]) {
        if(v == f) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}
namespace st {
    int res[19][N], minn[19][N], log2[N];
    void init() {
        log2[1] = 0;
        for(int i = 2; i <= n; i ++) log2[i] = log2[i >> 1] + 1;
        for(int i = 1; i <= n; i ++) res[0][i] = walk[i], minn[0][i] = dep[walk[i]];
        for(int i = 1; i < 19; i ++)
            for(int j = 1; j <= n + 1 - (1 << i); j ++)
                if(minn[i - 1][j] <= minn[i - 1][j + (1 << i - 1)])
                    res[i][j] = res[i - 1][j], minn[i][j] = minn[i - 1][j];
                else
                    res[i][j] = res[i - 1][j + (1 << i - 1)], minn[i][j] = minn[i - 1][j + (1 << i - 1)];
    }
    int query(int l, int r) {
        int lg = log2[r - l + 1];
        return minn[lg][l] <= minn[lg][r + 1 - (1 << lg)] ? res[lg][l] : res[lg][r + 1 - (1 << lg)];
    }
}
int lca(int u, int v) {return u == v ? u : fa[dfn[u] < dfn[v] ? st::query(dfn[u] + 1, dfn[v]) : st::query(dfn[v] + 1, dfn[u])][0];}
int mp[N], rmp[N], totmp;
vector<int> col[N];
bool cmp(int x, int y) {
    return dfn[x] < dfn[y];
}
int va[N], szv;
namespace vt {
    int head[N], tot;
    struct edge {
        int to; int nxt;
    } e[100];
    void adde(int u, int v) {
        e[++ tot] = edge{v, head[u]};
        head[u] = tot;
        e[++ tot] = edge{u, head[v]};
        head[v] = tot;
    }
}
int top, curcol;
void vtdfs(int u, int f, int sum) {
    if(a[u] == curcol) {
        typ[u] == 1 ? sum ++ : sum --;
        if(!sum) {
            if(dfn[top] <= dfn[u] && dfn[u] < dfn[top] + sz[top]) {
                int v = u;
                for(int i = 17; ~i; i --) if(dep[v] - (1 << i) > dep[top]) v = fa[v][i];
                scl::mdf_insert(1, dfn[v] - 1, dfn[u], dfn[u] + sz[u] - 1);
                scl::mdf_insert(dfn[v] + sz[v], n, dfn[u], dfn[u] + sz[u] - 1);
            } else if(dfn[u] <= dfn[top] && dfn[top] < dfn[u] + sz[u]) {
                int v = top;
                for(int i = 17; ~i; i --) if(dep[v] - (1 << i) > dep[u]) v = fa[v][i];
                scl::mdf_insert(dfn[top], dfn[top] + sz[top] - 1, 1, dfn[v] - 1);
                scl::mdf_insert(dfn[top], dfn[top] + sz[top] - 1, dfn[v] + sz[v], n);
            } else {
                scl::mdf_insert(dfn[top], dfn[top] + sz[top] - 1, dfn[u], dfn[u] + sz[u] - 1);
            }
            return;
        }
        if(sum < 0) sum = 0;
    }
    for(int i = vt::head[u]; i; i = vt::e[i].nxt) {
        int &v = vt::e[i].to;
        if(v == f) continue;
        vtdfs(v, u, sum);
    }
}
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= n; i ++) {
        typ[i] = read(), a[i] = read();
        if(!mp[a[i]]) mp[a[i]] = ++ totmp, rmp[totmp] = a[i];
        col[mp[a[i]]].push_back(i);
    }
    for(int i = 1, u, v; i < n; i ++) {
        u = read(), v = read();
        to[u].push_back(v), to[v].push_back(u);
    }
    dfs(1, 0); st::init();
    for(int i = 1; i <= totmp; i ++) {
        sort(col[i].begin(), col[i].end(), cmp);
        szv = 0;
        va[++ szv] = col[i][0];
        for(int j = 1; j < col[i].size(); j ++) {
            va[++ szv] = lca(col[i][j - 1], col[i][j]);
            va[++ szv] = col[i][j];
        }
        sort(va + 1, va + szv + 1, cmp);
        szv = unique(va + 1, va + szv + 1) - va - 1;
        for(int j = 1; j < szv; j ++)
            vt::adde(lca(va[j], va[j + 1]), va[j + 1]);
        curcol = rmp[i];
        for(auto ele : col[i]) {
            if(typ[ele] == 1) top = ele, vtdfs(ele, 0, 0);
        }
        vt::tot = 0; for(int j = 1; j <= szv; j ++) vt::head[va[j]] = 0;
    }
    for(int i = 1, u, v; i <= m; i ++) {
        u = read(), v = read();
        scl::qry_insert(dfn[u], dfn[v]);
    }
    scl::work();
    for(int i = 1; i <= m; i ++)
        printf("%d\n", scl::ans[i]);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}