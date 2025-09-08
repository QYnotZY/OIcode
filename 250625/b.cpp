#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// inline char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
inline char gc() {return getchar();}
template<typename T>
inline T readnum(){
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
template<typename T = int>
inline T read() {return readnum<T>();}
char wc[50]; int top;
template<typename T>
inline void writenum(T x, char sp){
    if(!x) return putchar('0'), void(putchar(sp));
    if(x < 0) putchar('-'), x = ~x + 1;
    top = 0;
    for(; x; x /= 10) wc[top ++] = x % 10 ^ 48;
    while(top --) putchar(wc[top]);
    putchar(sp);
}
template<typename T = int>
inline void write(T x, char sp = '\n'){
    writenum(x, sp);
}
}
using FastIO::read;
using FastIO::write;
typedef long long ll;
const int N = 1e5 + 10;
const int mod = 998244353;
namespace work {
inline int Mod(int a) {return (a % mod + mod) % mod;}
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Sq(int a) {return Mult(a, a);}
inline int Pow(int a, int b) {
    return b ? Mult(Sq(Pow(a, b >> 1)), (b & 1 ? a : 1)) : 1;
}
inline int Inv(int a) {return Pow(a, mod - 2);
}
int n, m;
vector<int> to[N], to1[N];

vector<pair<int, int> > nte;
int fa[N], sz[N], hson[N], dep[N];
int dfn[N], redfn[N], top[N], end[N];
struct dx {
    int val, cnt0;
    int v() {return cnt0 ? 0 : val;}
    dx operator * (int obj) {
        return obj ? dx{Mult(val, obj), cnt0} : dx{val, cnt0 + 1};
    }
    dx operator / (int obj) {
        return obj ? dx{Mult(val, Inv(obj)), cnt0} : dx{val, cnt0 - 1};
    }
} p0[N], pa[N];

namespace pou {
    bitset<N> vis;
    int f1[N], f0[N];
    void dfs1(int u, int f) {
        fa[u] = f, sz[u] = 1, dep[u] = dep[f] + 1, vis[u] = 1;
        for(auto v : to[u]) {
            if(v == f) continue;
            if(vis[v]) {
                if(dep[u] < dep[v]) nte.emplace_back(make_pair(u, v));
                continue;
            }
            to1[u].emplace_back(v);
            to1[v].emplace_back(u);
            dfs1(v, u);
            if(sz[v] > sz[hson[u]]) hson[u] = v;
            sz[u] += sz[v];
        }
    }
    int cur = 0;
    void dfs2(int u, int t) {
        dfn[u] = ++ cur, redfn[cur] = u, top[u] = t;
        f1[u] = 1, f0[u] = 1;
        if(hson[u]) {
            dfs2(hson[u], t);
        } else {
            end[t] = u;
        }
        for(auto v : to1[u]) {
            if(v == fa[u] || v == hson[u]) continue;
            dfs2(v, v);
            f1[u] = Mult(f1[u], f0[v]);
            f0[u] = Mult(f0[u], Add(f0[v], f1[v]));
        }
        pa[u] = {f0[u], 0};
        p0[u] = {f1[u], 0};
        #ifdef db
        printf("%d %d %d\n", u, p0[u], pa[u]);
        #endif
        f1[u] = Mult(f1[u], f0[hson[u]]);
        f0[u] = Mult(f0[u], Add(f0[hson[u]], f1[hson[u]]));
    }
}

struct matrix {
    int a[2][2];
    void init(int a11, int a12, int a21, int a22) {
        a[0][0] = a11;
        a[0][1] = a12;
        a[1][0] = a21;
        a[1][1] = a22;
    }
    matrix operator * (matrix obj) {
        matrix res; res.init(0, 0, 0, 0);
        for(int i = 0; i < 2; i ++)
          for(int j = 0; j < 2; j ++)
            for(int k = 0; k < 2; k ++)
                res.a[i][j] = Add(res.a[i][j], Mult(a[i][k], obj.a[k][j]));
        return res;
    }
    #ifdef db
    void print() {
        for(int i = 0; i < 2; i ++){
            for(int j = 0; j < 2; j ++)
                printf("%d ", a[i][j]);
            printf("\n");
        }
    }
    #endif
} ;

matrix sn[N << 2]; //sn : segment tree node
struct smt {
    void pushup(int p) {
        sn[p] = sn[p << 1] * sn[p << 1 | 1];
    }
    void create(int p = 1, int l = 1, int r = n) {
        if(l == r) {
            sn[p].init(0, p0[redfn[l]].v(), pa[redfn[l]].v(), pa[redfn[l]].v());
            return;
        }
        int mid = l + (r - l >> 1);
        create(p << 1, l, mid);
        create(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int x, int p = 1, int l = 1, int r = n) {
        if(l == r) {
            sn[p].init(0, p0[redfn[l]].v(), pa[redfn[l]].v(), pa[redfn[l]].v());
            return;
        }
        int mid = l + (r - l >> 1);
        if(x <= mid) {
            update(x, p << 1, l, mid);
        } else {
            update(x, p << 1 | 1, mid + 1, r);
        }
        pushup(p);
    }
    matrix query(int ql, int qr, int p = 1, int l = 1, int r = n) {
        if(ql <= l && r <= qr) {
            return sn[p];
        }
        int mid = l + (r - l >> 1);
        matrix res; res.init(1, 0, 0, 1);
        if(ql <= mid) res = res * query(ql, qr, p << 1, l, mid);
        if(qr > mid) res = res * query(ql, qr, p << 1 | 1, mid + 1, r);
        return res;
    }
} tr;

pair<int, int> query(int u) {
    matrix res = tr.query(dfn[u], dfn[end[top[u]]]);
    return make_pair(res.a[0][1], res.a[1][1]);
}
void update(int u, int typ) {
    if(typ == 1) pa[u] = pa[u] * 0;
    else pa[u] = pa[u] / 0;
    while(u) {
        pair<int, int> bef = query(top[u]);
        tr.update(dfn[u]);
        pair<int, int> aft = query(top[u]);
        u = fa[top[u]];
        p0[u] = p0[u] / bef.second * aft.second;
        pa[u] = pa[u] / Add(bef.first, bef.second) * Add(aft.first, aft.second);
    }
}

void init() {
    pou::f0[0] = 1;
    pou::dfs1(1, 0);
    pou::dfs2(1, 1);
    tr.create();
}
int ans, cnt;
void dfs(int dep) {
    if(dep >= nte.size()) {
        pair<int, int> tmp = query(1);
        int curans = Add(tmp.first, tmp.second);
        #ifdef db
        printf("%d ", curans);
        #endif
        cnt & 1 ? (ans = Minus(ans, curans)) : (ans = Add(ans, curans));
        return;
    }
    dfs(dep + 1);
    cnt ++; update(nte[dep].first, 1); update(nte[dep].second, 1);
    dfs(dep + 1);
    cnt --; update(nte[dep].first, -1); update(nte[dep].second, -1);
}

int Main() {
    n = read(), m = read();
    for(int i = 1, u, v; i <= m; i ++) {
        u = read(), v = read();
        to[u].emplace_back(v);
        to[v].emplace_back(u);
    }
    init();
    dfs(0);
    write(ans);
    return 0;
}
}
int main() {
    return work::Main();
}