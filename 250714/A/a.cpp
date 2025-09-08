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
typedef unsigned long long ull;
namespace work {
const int N = 1e5 + 10;
int n, m, k;
vector<int> to[N];
struct func {
    ull f0, f1;
    void init(int typ, ull num) {
        if(typ == 1) {
            f0 = 0 & num;
            f1 = (1 << k) - 1 & num;
        } else if(typ == 2) {
            f0 = 0 | num;
            f1 = (1 << k) - 1 | num;
        } else {
            f0 = 0 ^ num;
            f1 = (1 << k) - 1 ^ num;
        }
    }
    func operator + (func obj) {
        func res;
        res.f0 = (~f0 & obj.f0) | (f0 & obj.f1);
        res.f1 = (~f1 & obj.f0) | (f1 & obj.f1);
        return res;
    }
} f[N];
int fa[N], dep[N], sz[N], hson[N];
int tot, dfn[N], redfn[N], top[N];
void dfs1(int u, int f) {
    fa[u] = f, dep[u] = dep[f] + 1, sz[u] = 1, hson[u] = 0;
    dfn[u] = ++ tot, redfn[tot] = u;
    for(auto v : to[u]) {
        if(v == f) continue;
        dfs1(v, u);
        if(sz[v] > sz[hson[u]]) hson[u] = v;
        sz[u] += sz[v];
    }
}
void dfs2(int u, int t) {
    top[u] = t;
    if(hson[u]) dfs2(hson[u], t);
    for(auto v : to[u]) {
        if(v == fa[u] || v == hson[u]) continue;
        dfs2(v, v);
    }
}
struct SMT {
    func up[N << 2], dn[N << 2];
    void pushup(int p) {
        up[p] = up[p << 1 | 1] + up[p << 1];
        dn[p] = dn[p << 1] + dn[p << 1 | 1];
    }
    void build(int p = 1, int l = 1, int r = n) {
        if(l == r) return void(up[p] = dn[p] = f[l]);
        int mid = l + r >> 1;
        build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int x, int p = 1, int l = 1, int r = n) {
        if(l == r) return void(up[l] = dn[l] = f[l]);
        int mid = l + r >> 1;
        if(x <= mid) update(x, p << 1, l, mid);
        else update(x, p << 1 | 1, mid + 1, r);
    }
    func query(int u, int ql, int qr, int p = 1, int l = 1, int r = n) {
        #ifdef db
        printf("%d %d %d %d  ", u, p, l, r); write<ull>(up[p].f0, ' '), write<ull>(up[p].f1, ' '), write<ull>(dn[p].f0, ' '), write<ull>(dn[p].f1);
        #endif
        func res; res.init(3, 0);
        if(ql > qr) return res;
        if(ql <= l && r <= qr) return u ? up[p] : dn[p];
        int mid = l + r >> 1;
        if(ql <= mid) res = u ? query(u, ql, qr, p << 1, l, mid) + res : res + query(u, ql, qr, p << 1, l, mid);
        if(qr > mid) res = u ? query(u, ql, qr, p << 1 | 1, mid + 1, r) + res : res + query(u, ql, qr, p << 1 | 1, mid + 1, r);
        return res;
    }
} smt;
void Hutao() {
    n = read(), m = read(), k = read();
    for(int i = 1; i <= n; i ++) {
        int a = read(); ull b = read<ull>();
        f[i].init(a, b);
    }
    for(int i = 1, u, v; i < n; i ++)
        u = read(), v = read(), to[u].push_back(v), to[v].push_back(u);
    dfs1(1, 0), dfs2(1, 1);
    smt.build();
    for(int i = 1; i <= m; i ++) {
        int op = read();
        if(op == 2) {
            int x = read(), y = read(); ull z = read<ull>();
            f[x].init(y, z);
            smt.update(x);
        } else {
            int x = read(), y = read(); ull z = read<ull>();
            func resup, resdn, res; ull ans = 0;
            resup.init(3, 0), resdn.init(3, 0);
            while(top[x] != top[y]) {
                if(dep[top[x]] < dep[top[y]]) {
                    resdn = smt.query(0, dfn[top[y]], dfn[y]) + resdn;
                    y = fa[top[y]];
                } else {
                    resup = resup + smt.query(1, dfn[top[x]], dfn[x]);
                    x = fa[top[x]];
                }
            }
            if(dep[x] < dep[y]) {
                resdn = smt.query(0, dfn[x], dfn[y]) + resdn;
            } else {
                resup = resup + smt.query(1, dfn[y], dfn[x]);
            }
            res = resup + resdn;
            #ifdef db
            write<ull>(res.f0, ' '); write<ull>(res.f1);
            #endif
            for(int i = k - 1; ~i; i --) {
                if(1ull << i >= z) {
                    if(res.f1 >> i & 1ull) ans |= 1ull << i;
                    z -= 1ull << i;
                }
            }
            write<ull>(ans);
        }
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}