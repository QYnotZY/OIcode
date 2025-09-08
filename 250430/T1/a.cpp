#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
char buf[1 << 20], *p1, *p2;
inline char gc(){
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
}
// inline char gc() {return getchar();}
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
typedef pair<int, int> pii;
const int infN = 1e5, N = 1e5 + 10, inf = 1e9, mod = 1e9 + 9;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a + mod - b : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
namespace work {
int n, m, k;
int ans[N];
namespace maths {
    int fac[N], ifac[N];
    int power(int a, int b) {
        int res = 1;
        for(; b; b >>= 1, a = Mult(a, a))
            if(b & 1) res = Mult(res, a);
        return res;
    }
    void static_init() {
        fac[0] = 1;
        for(int i = 1; i <= infN; i ++)
            fac[i] = Mult(fac[i - 1], i);
        ifac[infN] = power(fac[infN], mod - 2);
        for(int i = infN - 1; i >= 0; i --)
            ifac[i] = Mult(ifac[i + 1], i + 1);
    }
    int C(int n, int m) {
        if(n < m) return 0;
        return Mult(fac[n], Mult(ifac[m], ifac[n - m]));
    }
} using maths::C;
void static_init() {
    maths::static_init();
}
namespace llfs {
    int tot, head[N];
    struct node {
        int to, dis;
        int nxt;
    } e[N << 1];
    void init(int n) {
        tot = -1;
        for(int i = 1; i <= n; i ++)
            head[i] = -1;
    }
    void add(int u, int v, int w) {
        e[++ tot] = {v, w, head[u]};
        head[u] = tot;
        e[++ tot] = {u, w, head[v]};
        head[v] = tot;
    }
} using llfs::head; using llfs::e;
int cnt[N];
ll dep[N];
int fa[N * 20];
void get_cnt(int u = 1, int f = 0) {
    if(!f) dep[u] = 0;
    fa[u] = f;
    int key = u;
    for(int i = 1; i <= 16; i ++)
        fa[u + i * (n + 1)] = fa[fa[u + (i - 1) * (n + 1)] + (i - 1) * (n + 1)];
    for(int i = 16; i >= 0; i --)
        if(fa[key + i * (n + 1)] && dep[u] - dep[fa[key + i * (n + 1)]] <= (ll)k)
            key = fa[key + i * (n + 1)];
    cnt[key] ++;
    for(int ii = head[u]; ~ii; ii = e[ii].nxt) {
        int &v = e[ii].to, &w = e[ii].dis;
        if(v == f) continue;
        dep[v] = dep[u] + w;
        get_cnt(v, u);
    }
}
bitset<N> vis;
int sz[N], sz0;
pii dfs_find_root(int u, int f = 0) {
    sz[u] = 1;
    int mxsz = 0;
    pii res = {0, inf}, tmp;
    for(int ii = head[u]; ~ii; ii = e[ii].nxt) {
        int &v = e[ii].to, &w = e[ii].dis;
        if(v == f || vis[v]) continue;
        tmp = dfs_find_root(v, u);
        if(res.second > tmp.second) res = tmp;
        sz[u] += sz[v];
        mxsz = max(mxsz, sz[v]);
    }
    mxsz = max(mxsz, sz0 - sz[u]);
    if(res.second > mxsz) res = {u, mxsz};
    return res;
}
int find_root(int u) {
    sz0 = sz[u] ? sz[u] : n;
    return dfs_find_root(u).first;
}
vector<int> pts;
void dfs_deal(int u, int f) {
    if(dep[u] > k) return;
    pts.push_back(u);
    for(int ii = head[u]; ~ii; ii = e[ii].nxt) {
        int &v = e[ii].to, &w = e[ii].dis;
        if(v == f || vis[v]) continue;
        dep[v] = dep[u] + w;
        dfs_deal(v, u);
    }
}
bool cmp(int a, int b) {
    return dep[a] < dep[b];
}
void solve(int u = 1) {
    int rt = find_root(u);
    vector<int>().swap(pts);
    dep[rt] = 0;
    dfs_deal(rt, 0);
    sort(pts.begin(), pts.end(), cmp);
    int vsz = pts.size();
    for(int i = 0, j = vsz - 1; i < vsz; i ++) {
        while(j >= 0 && dep[pts[j]] + dep[pts[i]] > k) j --;
        ans[pts[i]] += j + 1;
    }
    for(int ii = head[rt]; ~ii; ii = e[ii].nxt) {
        int &v = e[ii].to, &w = e[ii].dis;
        if(vis[v]) continue;
        vector<int>().swap(pts);
        dep[v] = w;
        dfs_deal(v, rt);
        sort(pts.begin(), pts.end(), cmp);
        vsz = pts.size();
        for(int i = 0, j = vsz - 1; i < vsz; i ++) {
            while(j >= 0 && dep[pts[j]] + dep[pts[i]] > k) j --;
            ans[pts[i]] -= j + 1;
        }
    }
    vis[rt] = 1;
    for(int ii = head[rt]; ~ii; ii = e[ii].nxt) {
        int &v = e[ii].to;
        if(vis[v]) continue;
        solve(v);
    }
}
void init() {
    n = read(), m = read(), k = read();
    llfs::init(n);
    for(int i = 1, u, v, w; i < n; i ++) {
        u = read(), v = read(), w = read();
        llfs::add(u, v, w);
    }
    for(int i = 0; i <= n; i ++) {
        dep[i] = sz[i] = cnt[i] = vis[i] = ans[i] = 0;
        for(int j = 0; j <= 16; j ++)
            fa[i + j * (n + 1)] = 0;
    }
    sz0 = 0;
}
void print() {
    int res = C(ans[1], m);
    for(int i = 2; i <= n; i ++)
        res = Add(res, Minus(C(ans[i], m), C(ans[i] - cnt[i], m)));
    write(res);
}
int Main() {
    static_init();
    read();
    int t = read();
    while(t --) {
        init();
        get_cnt();
        solve();
        print();
    }
    return 0;
}
}
int main() {
    #ifndef db
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    #endif
    return work::Main();
}