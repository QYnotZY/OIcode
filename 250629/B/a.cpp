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
typedef pair<int, int> pii;
const int N = 2e5 + 10;
const int inf = 1e9 + 7;
namespace work {
int t, n, m;
struct node {
    int u, v, w;
    bool operator < (node obj) {
        return w < obj.w;
    }
} e[N];
struct DSU {
    int fa[N];
    void init(int n) {
        for(int i = 1; i <= n; i ++)
            fa[i] = i;
    }
    int find(int x) {
        return fa[x] == x ? x : (fa[x] = find(fa[x]));
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    void merge(int x, int y) {
        x = find(x), y = find(y);
        fa[y] = x;
    }
} dsu;
vector<pii> to1[N];
int dep[N], maxp[N], minp[N];
void dfs(int u, int f) {
    if(f == 0) maxp[u] = 0, minp[u] = inf;
    dep[u] = dep[f] + 1;
    for(auto ele : to1[u]) {
        int &v = ele.first, &w = ele.second;
        if(v == f) continue;
        maxp[v] = max(maxp[u], w), minp[v] = min(minp[u], w);
        dfs(v, u);
    }
}
void init() {
    dsu.init(n);
    for(int i = 1; i <= n; i ++)
        vector<pii>().swap(to1[i]);
}
int Main() {
    t = read();
    while(t --) {
        n = read(), m = read();
        for(int i = 1; i <= m; i ++) {
            e[i].u = read(), e[i].v = read(), e[i].w = read();
        }
        sort(e + 1, e + m + 1);
        init();
        for(int i = 1, cnt = 0; i <= m && cnt < n - 1; i ++) {
            if(dsu.same(e[i].u, e[i].v)) continue;
            dsu.merge(e[i].u, e[i].v);
            cnt ++;
            to1[e[i].u].emplace_back(make_pair(e[i].v, e[i].w));
            to1[e[i].v].emplace_back(make_pair(e[i].u, e[i].w));
            #ifdef db
            printf("%d %d %d\n", e[i].u, e[i].v, e[i].w);
            #endif
            e[cnt] = e[i];
        }
        dfs(1, 0);
        int ans = maxp[n] + minp[n];
        for(int i = 1; i <= n - 1; i ++) {
            int key = (dep[e[i].u] < dep[e[i].v] ? e[i].v : e[i].u);
            ans = min(ans, max(maxp[key], maxp[n]) + min(minp[key], minp[n]));
        }
        write(ans);
    }
    return 0;
}
}
int main() {
    return work::Main();
}