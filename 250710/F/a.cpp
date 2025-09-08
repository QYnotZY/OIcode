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
namespace work {
const int N1 = 1000 + 5;
const ll inf = 0x3f3f3f3f3f3f3f3f;
struct node {int to; ll lim; int rev;};
vector<node> e[N1];
int s, t;
namespace maxflow {
    ll dis[N1]; int cur[N1];
    bool bfs() {
        memset(dis, 0x3f, sizeof dis); dis[s] = 0;
        queue<int> q; q.push(s); int u, v; ll lim;
        while(q.size()) {
            u = q.front(); q.pop();
            for(auto ele : e[u]) {
                v = ele.to, lim = ele.lim;
                if(lim && dis[v] >= inf) {dis[v] = dis[u] + 1; q.push(v);}
            }
        }
        return dis[t] ^ inf;
    }
    ll dfs(int u, ll flow) {
        if(u == t) return flow;
        ll res = 0;
        for(int i = cur[u]; i < e[u].size() && flow; i ++) {
            cur[u] = i;
            int &v = e[u][i].to, &rev = e[u][i].rev; ll &lim = e[u][i].lim;
            if(!lim || dis[v] ^ dis[u] + 1) continue;
            ll d = dfs(v, min(flow, lim));
            e[u][i].lim -= d, e[v][rev].lim += d;
            res += d;
            flow -= d;
        }
        return res;
    }
    ll Dinic() {
        ll res = 0;
        while(bfs())
            memset(cur, 0, sizeof cur),
            res += dfs(s, inf);
        return res;
    }
}
void adde(int u, int v, ll w) {
    int id1 = e[u].size(), id2 = e[v].size();
    e[u].push_back({v, w, id2});
    e[v].push_back({u, 0, id1});
}
const int N = 300 + 10;
int n, m, a[N], b[N], ans;
void Hutao() {
    n = read(), m = read();
    s = 2 * n + 1, t = 2 * n + 2;
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    for(int i = 1; i <= n; i ++) {
        b[i] = read();
        adde(i, n + i, a[i] + abs(b[i]));
        if(b[i] > 0) {
            adde(s, i, 2 * b[i]);
            ans += b[i];
        } else {
            adde(n + i, t, -2 * b[i]);
            ans -= b[i];
        }
    }
    for(int i = 1, u, v; i <= m; i ++) {
        u = read(), v = read();
        adde(n + u, v, inf);
        adde(n + v, u, inf);
    }
    write(ans - maxflow::Dinic());
}
}
signed main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}