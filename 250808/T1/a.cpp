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
typedef unsigned long long ull;
#define rint register int
namespace work {
const int N = 1e5 + 10, M = 3e5 + 10;
struct node {
    int ans;
    int sz;
    pair<int, int> a[4];
    node() {ans = sz = 0;}
    void init1(pair<int, int> v) {
        ans = 0;
        sz = v.second ? 2 : 1;
        a[0] = make_pair(v.first, v.first);
        a[1] = make_pair(v.second, v.second);
    }
    friend node operator + (const node& a, const node& b) {
        node res;
        res.ans = a.ans + b.ans;
        for(rint i = 0; i < a.sz; i ++) {
            for(rint j = 0; j < b.sz; j ++) {
                if(!~a.a[i].second || !~b.a[j].first || a.a[i].second != b.a[j].first) {
                    for(rint k = 0; k < res.sz; k ++)
                        if(res.a[k] == make_pair(a.a[i].first, b.a[j].second) || res.a[k] == make_pair(a.a[i].first, -1) || res.a[k] == make_pair(-1, b.a[j].second) || res.a[k] == make_pair(-1, -1))
                            goto Mark;
                    res.a[res.sz ++] = make_pair(a.a[i].first, b.a[j].second);
                }
                Mark:;
            }
        }
        if(res.sz) ++ res.ans;
        else {
            for(rint i = 0; i < a.sz; i ++) {
                for(rint j = 0; j < b.sz; j ++) {
                    for(rint k = 0; k < res.sz; k ++)
                        if(res.a[k] == make_pair(a.a[i].first, b.a[j].second) || res.a[k] == make_pair(a.a[i].first, -1) || res.a[k] == make_pair(-1, b.a[j].second) || res.a[k] == make_pair(-1, -1))
                            goto Mark0;
                    res.a[res.sz ++] = make_pair(a.a[i].first, b.a[j].second);
                    Mark0:;
                }
            }
        }
        return res;
    }
    void reverse() {
        for(rint i = 0; i < sz; i ++) swap(a[i].first, a[i].second);
    }
} ;
int n, m, q;
pair<int, int> a[N];
vector<pair<int, pair<int, int> > > e[N];
int walk[N];
namespace smt {
    node tr[N << 2];
    void pushup(int p) {
        tr[p] = tr[p << 1] + tr[p << 1 | 1];
    }
    void build(int p = 1, int l = 1, int r = n) {
        if(l == r) {
            tr[p].init1(a[walk[l]]);
            return;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    node query(int ql, int qr, int p = 1, int l = 1, int r = n) {
        if(ql <= l && r <= qr) return tr[p];
        int mid = l + r >> 1;
        if(qr <= mid) return query(ql, qr, p << 1, l, mid);
        if(ql > mid) return query(ql, qr, p << 1 | 1, mid + 1, r);
        return query(ql, qr, p << 1, l, mid) + query(ql, qr, p << 1 | 1, mid + 1, r);
    }
}
namespace hld {
    int fa[N], dep[N], sz[N], hson[N];
    void dfs1(int u, int f) {
        fa[u] = f, dep[u] = dep[f] + 1, sz[u] = 1, hson[u] = 0;
        for(auto ele : e[u]) {
            int &v = ele.first; pair<int, int> &w = ele.second;
            if(v == f) continue;
            a[v] = w;
            dfs1(v, u);
            if(sz[hson[u]] < sz[v]) hson[u] = v;
            sz[u] += sz[v];
        }
    }
    int dfn[N], totdfn;
    int top[N];
    void dfs2(int u, int t) {
        walk[dfn[u] = ++ totdfn] = u;
        top[u] = t;
        if(!hson[u]) return;
        dfs2(hson[u], t);
        for(auto ele : e[u]) {
            int &v = ele.first;
            if(v == fa[u] || v == hson[u]) continue;
            dfs2(v, v);
        }
    }
    void init() {
        dfs1(1, 0);
        dfs2(1, 1);
        smt::build();
    }
    int query(int u, int v) {
        node res1, res2; bool tag1 = 0, tag2 = 0;
        while(top[u] != top[v]) {
            if(dep[top[u]] <= dep[top[v]]) {
                (res2 = tag2 ? smt::query(dfn[top[v]], dfn[v]) + res2 : smt::query(dfn[top[v]], dfn[v])), tag2 = 1;
                v = fa[top[v]];
            } else {
                (res1 = tag1 ? smt::query(dfn[top[u]], dfn[u]) + res1 : smt::query(dfn[top[u]], dfn[u])), tag1 = 1;
                u = fa[top[u]];
            }
        }
        if(dep[u] < dep[v]) (res2 = tag2 ? smt::query(dfn[u] + 1, dfn[v]) + res2 : smt::query(dfn[u] + 1, dfn[v])), tag2 = 1;
        if(dep[v] < dep[u]) (res1 = tag1 ? smt::query(dfn[v] + 1, dfn[u]) + res1 : smt::query(dfn[v] + 1, dfn[u])), tag1 = 1;
        if(!tag1 || !tag2) return res1.ans + res2.ans;
        res1.reverse(); return (res1 + res2).ans;
    }
}
map<pair<int, int>, pair<int, int> > ed;
void Hutao() {
    #ifdef db
    clock_t start=clock();
    #endif
    n = read(), m = read();
    map<pair<int, int>, pair<int, int> >::iterator it;
    for(int i = 1, u, v, c; i <= m; i ++) {
        u = read(), v = read(), c = read();
        if(u > v) swap(u, v);
        if(ed.find(make_pair(u, v)) == ed.end()) ed[make_pair(u, v)] = make_pair(c, 0);
        else if(ed[make_pair(u, v)].first == -1) continue;
        else if(ed[make_pair(u, v)].first == c) continue;
        else if(!ed[make_pair(u, v)].second) ed[make_pair(u, v)].second = c;
        else if(ed[make_pair(u, v)].second == c) continue;
        else ed[make_pair(u, v)] = make_pair(-1, 0);
    }
    int u, v; pair<int, int> w;
    for(auto ele : ed) {
        tie(u, v) = ele.first; w = ele.second;
        e[u].push_back(make_pair(v, w));
        e[v].push_back(make_pair(u, w));
    }
    hld::init();
    q = read();
    while(q --) {
        u = read(), v = read();
        printf("%d\n", hld::query(u, v));
    }
    #ifdef db
    clock_t end=clock();
    cerr<<(double)(end-start)/CLOCKS_PER_SEC*1000<<"ms\n";
    #endif
}
}
int main() {
    freopen("colorful.in", "r", stdin);
    freopen("colorful.out", "w", stdout);
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}