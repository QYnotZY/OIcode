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
const int inf = 2e7;
namespace work {
int n, m;
int a[N];
vector<int> to[N];

struct matrix {
    int a[2][2];
    void init(int a11, int a12, int a21, int a22) {
        a[0][0] = a11;
        a[0][1] = a12;
        a[1][0] = a21;
        a[1][1] = a22;
    }
    matrix operator * (matrix obj) {
        matrix res; res.init(-inf, -inf, -inf, -inf);
        for(int i = 0; i < 2; i ++)
          for(int j = 0; j < 2; j ++)
            for(int k = 0; k < 2; k ++)
                res.a[i][j] = max(res.a[i][j], a[i][k] + obj.a[k][j]);
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

int fa[N], sz[N], hson[N];
int dfn[N], redfn[N], top[N], end[N];
matrix op[N];
namespace pou {
    void dfs1(int u, int f) {
        fa[u] = f; sz[u] = 1; hson[u] = 0;
        for(auto v : to[u]) {
            if(v == f) continue;
            dfs1(v, u);
            if(sz[v] > sz[hson[u]])
                hson[u] = v;
            sz[u] += sz[v];
        }
    }
    int cur = 0;
    int f1[N], f0[N];
    void dfs2(int u, int t) {
        dfn[u] = ++ cur, redfn[cur] = u, top[u] = t;
        if(hson[u]) {
            dfs2(hson[u], t);
        } else {
            end[t] = u;
        }
        int s1u = a[u], s0u = 0;
        for(auto v : to[u]) {
            if(v == fa[u] || v == hson[u]) continue;
            dfs2(v, v);
            s1u += f0[v];
            s0u += f1[v];
        }
        f1[u] = max(s0u + f1[hson[u]], s1u + f0[hson[u]]);
        f0[u] = s0u + f1[hson[u]];
        op[u].init(s0u, s1u, s0u, -inf);
    }
    void work() {
        dfs1(1, 0);
        dfs2(1, 1);
    }
}
matrix sn[N << 2]; //sn : segment tree node
struct smt {
    void pushup(int p) {
        sn[p] = sn[p << 1] * sn[p << 1 | 1];
    }
    void create(int p = 1, int l = 1, int r = n) {
        if(l == r) {
            sn[p] = op[redfn[l]];
            return;
        }
        int mid = l + (r - l >> 1);
        create(p << 1, l, mid);
        create(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int x, int p = 1, int l = 1, int r = n) {
        if(l == r) {
            sn[p] = op[redfn[l]];
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
        matrix res; res.init(0, -inf, -inf, 0);
        if(ql <= mid) res = res * query(ql, qr, p << 1, l, mid);
        if(qr > mid) res = res * query(ql, qr, p << 1 | 1, mid + 1, r);
        return res;
    }
} tr;
pair<int, int> query(int u) {
    matrix res = tr.query(dfn[u], dfn[end[top[u]]]);
    return make_pair(max(res.a[0][0], res.a[0][1]), max(res.a[1][0], res.a[1][1]));
}
void update(int u, int x) {
    op[u].a[0][1] += x - a[u];
    a[u] = x;
    while(u) {
        pair<int, int> bef = query(top[u]);
        tr.update(dfn[u]);
        pair<int, int> aft = query(top[u]);
        u = fa[top[u]];
        op[u].a[0][0] += aft.first - bef.first;
        op[u].a[1][0] += aft.first - bef.first;
        op[u].a[0][1] += aft.second - bef.second;
    }
}
int Main() {
    n = read(), m = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    for(int i = 1, u, v; i < n; i ++) {
        u = read(), v = read();
        to[u].emplace_back(v);
        to[v].emplace_back(u);
    }
    pou::work();
    tr.create();
    #ifdef db
    #endif
    for(int x, y; m --;) {
        x = read(), y = read();
        update(x, y);
        write(query(1).first);
    }
    return 0;
}
}
int main() {
    return work::Main();
}