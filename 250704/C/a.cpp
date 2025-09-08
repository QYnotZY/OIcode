#include "bits/stdc++.h"
#define int long long
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
const int N = 2e5 + 10;
namespace work {
int n, m, n1, a[N], u[N], v[N];
vector<int> to[N];
set<int> to1[N];
int indeg[N];
int cur, dfn[N], low[N];
int scc[N], sz[N], szw[N];
int stk[N], top; bool instk[N];
void tarjan(int u) {
    dfn[u] = ++ cur, low[u] = cur;
    stk[++ top] = u, instk[u] = 1;
    for(auto v : to[u]) {
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(instk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]) {
        ++ n1;
        do {
            scc[stk[top]] = n1;
            sz[n1] ++;
            szw[n1] += a[stk[top]];
            instk[stk[top]] = 0;
        } while(stk[top --] ^ u);
    }
}
int lim[N], f[N];
void solve() {
    n = read(), m = read();
    cur = n1 = 0;
    for(int i = 1; i <= n; i ++){
        a[i] = read(), instk[i] = indeg[i] = dfn[i] = low[i] = scc[i] = sz[i] = szw[i] = lim[i] = f[i] = 0;
        vector<int> ().swap(to[i]);
        set<int> ().swap(to1[i]);
    }
    for(int i = 1; i <= m; i ++) {
        u[i] = read(), v[i] = read();
        to[u[i]].emplace_back(v[i]);
    }
    for(int i = 1; i <= n; i ++) if(!dfn[i]) tarjan(i);
    for(int i = 1; i <= m; i ++) {
        if(scc[u[i]] == scc[v[i]] || to1[scc[u[i]]].find(scc[v[i]]) != to1[scc[u[i]]].end()) continue;
        to1[scc[u[i]]].insert(scc[v[i]]);
        indeg[scc[v[i]]] ++;
    }
    queue<int> q;
    for(int i = 1; i <= n1; i ++)
        if(!indeg[i]) lim[i] = sz[i], f[i] = szw[i], q.push(i);
    while(q.size()) {
        int u = q.front(); q.pop();
        for(auto v : to1[u]) {
            if(!(--indeg[v])) q.push(v);
            if(lim[v] < lim[u] + sz[v]) lim[v] = lim[u] + sz[v], f[v] = f[u] + szw[v];
            else if(lim[v] == lim[u] + sz[v]) f[v] = min(f[v], f[u] + szw[v]);
        }
    }
    int maxx = 0, ans;
    for(int i = 1; i <= n1; i ++) {
        if(lim[i] > maxx) maxx = lim[i], ans = f[i];
        else if(lim[i] == maxx) ans = min(ans, f[i]);
    }
    write(maxx, ' '), write(ans);
}
signed Main() {
    int t = read();
    while(t --) solve();
    return 0;
}
}
signed main() {
    return work::Main();
}