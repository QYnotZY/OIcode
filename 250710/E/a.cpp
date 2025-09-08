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
const int N1 = 1.2e4 + 10;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int S, T;
struct node {int to; ll lim, cost; int rev;} ;
vector<node> e[N1];
namespace costflow {
    ll dis[N1]; bool vis[N1]; int cur[N1];
    ll cost;
    bool bfs() {
        memset(vis, 0, sizeof vis); vis[S] = 1;
        memset(dis, 0x3f, sizeof dis); dis[S] = 0;
        queue<int> q; q.push(S);
        while(q.size()) {
            int u = q.front(); q.pop(); vis[u] = 0;
            for(auto ele : e[u]) {
                int &v = ele.to; ll &w = ele.lim, &c = ele.cost;
                if(w && dis[v] > dis[u] + c) {
                    dis[v] = dis[u] + c;
                    if(!vis[v]) q.push(v), vis[v] = 1;
                }
            }
        }
        return dis[T] ^ inf;
    }
    ll dfs(int u, ll flow) {
        if(u == T) return flow;
        ll res = 0;
        vis[u] = 1;
        for(int i = cur[u]; i < e[u].size() && flow; i ++) {
            cur[u] = i;
            int &v = e[u][i].to, &rev = e[u][i].rev; ll &lim = e[u][i].lim, &c = e[u][i].cost;
            if(vis[v] || !lim || dis[v] ^ dis[u] + c) continue;
            int d = dfs(v, min(flow, lim));
            lim -= d, e[v][rev].lim += d;
            flow -= d; res += d, cost += c * d;
        }
        vis[u] = 0;
        return res;
    }
    ll Dinic() {
        ll res = 0;
        while(bfs())
            memset(cur, 0, sizeof cur), 
            res += dfs(S, inf);
        return res;
    }
}
void adde(int u, int v, ll w, ll c) {
    int id1 = e[u].size(), id2 = e[v].size();
    e[u].push_back({v, w, c, id2});
    e[v].push_back({u, 0, -c, id1});
}
const int N = 3e3 + 10;
int n, a[N];
void Hutao() {
    n = read();
    S = 4 * n + 3, T = 4 * n + 1;
    int s = 4 * n + 2; adde(S, s, 4, 0);
    for(int i = 1; i <= n; i ++) {
        a[i] = read();
        adde(s, i, inf, 0), adde(n + i, T, inf, 0);
        adde(i, n + i, 1, -1);
        adde(2 * n + i, i, inf, 0), adde(3 * n + i, i, inf, 0);
    }
    for(int i = 1; i <= n; i ++) {
        for(int j = i + 1; j <= n; j ++)
            if(a[i] % 7 == a[j] % 7) {adde(2 * n + i, 2 * n + j, inf, 0), adde(n + i, 2 * n + j, inf, 0); break;}
        for(int j = i + 1; j <= n; j ++)
            if(a[i] == a[j]) {adde(3 * n + i, 3 * n + j, inf, 0); break;}
        for(int j = i + 1; j <= n; j ++)
            if(a[i] == a[j] + 1) {adde(n + i, 3 * n + j, inf, 0); break;}
        for(int j = i + 1; j <= n; j ++)
            if(a[i] == a[j] - 1) {adde(n + i, 3 * n + j, inf, 0); break;}
    }
    costflow::Dinic();
    write(-costflow::cost);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}