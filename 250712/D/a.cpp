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
const int N1 = 5e3 + 10;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int n1, s, t;
struct edge {int to; ll lim, cost; int rev;} ;
struct pqnode {int u; ll dis; bool operator < (const pqnode& obj) const {return dis > obj.dis;}} ;
vector<edge> e[N1];
namespace nf {
    ll h[N1], dis[N1]; bool vis[N1];
    int cur[N1];
    ll sumcost;
    void init() {
        sumcost = 0;
        memset(h, 0x3f, sizeof h); h[s] = 0;
        memset(vis, 0, sizeof vis); vis[s] = 1;
        queue<int> q; q.push(s);
        while(q.size()) {
            int u = q.front(); q.pop(); vis[u] = 0;
            for(auto ele : e[u]) {
                int &v = ele.to;
                ll &w = ele.cost;
                if(ele.lim && h[v] > h[u] + w) {
                    h[v] = h[u] + w;
                    if(!vis[v]) vis[v] = 1, q.push(v);
                }
            }
        }
    }
    bool bfs() {
        memset(dis, 0x3f, sizeof dis); dis[s] = 0;
        memset(vis, 0, sizeof vis);
        priority_queue<pqnode> q;
        q.push({s, dis[s]});
        while(q.size()) {
            int u = q.top().u; q.pop();
            if(vis[u]) continue; //!
            vis[u] = 1;
            for(auto ele : e[u]) {
                int &v = ele.to; ll &cap = ele.lim, &w = ele.cost;
                if(cap && dis[v] > dis[u] + w + h[u] - h[v]) {
                    dis[v] = dis[u] + w + h[u] - h[v];
                    q.push({v, dis[v]});
                }
            }
        }
        return dis[t] ^ inf;
    }
    ll dfs(int u, ll flow) {
        if(u == t) return flow;
        ll res = 0;
        vis[u] = 1;
        for(int i = cur[u]; i < e[u].size() && flow; i ++) {
            cur[u] = i;
            int &v = e[u][i].to, &r = e[u][i].rev; ll &w = e[u][i].cost, &cap = e[u][i].lim;
            if(vis[v] || !cap || dis[v] != dis[u] + w + h[u] - h[v]) continue;
            int d = dfs(v, min(flow, cap));
            cap -= d, e[v][r].lim += d;
            flow -= d, res += d, sumcost += w * d;
        }
        vis[u] = 0;
        return res;
    }
    pair<ll, ll> pd() {
        ll maxflow = 0;
        init();
        while(bfs()) {
            memset(cur, 0, sizeof cur);
            memset(vis, 0, sizeof vis);
            maxflow += dfs(s, inf);
            for(int i = 1; i <= n1; i ++)
                h[i] += dis[i];
        }
        return make_pair(maxflow, sumcost);
    }
}
void adde(int u, int v, ll c, ll w) {
    int id1 = e[u].size(), id2 = e[v].size();
    e[u].push_back({v, c, w, id2});
    e[v].push_back({u, 0, -w, id1});
}
const int N = 1000 + 10;
int n, k, l[N], r[N], len[N], sum;
int dc[N];
void disc() {
    for(int i = 1; i <= n; i ++)
        dc[i] = l[i], dc[n + i] = r[i];
    sort(dc + 1, dc + 2 * n + 1);
    sum = unique(dc + 1, dc + 2 * n + 1) - dc - 1;
    for(int i = 1; i <= n; i ++)
        l[i] = lower_bound(dc + 1, dc + sum + 1, l[i]) - dc,
        r[i] = lower_bound(dc + 1, dc + sum + 1, r[i]) - dc;
}
void Hutao() {
    n = read(), k = read();
    for(int i = 1; i <= n; i ++)
        l[i] = read(), r[i] = read(), len[i] = r[i] - l[i], r[i] --;
    disc();
    n1 = sum + 2, s = sum + 1, t = n1;
    adde(s, 1, k, 0), adde(sum, t, k, 0);
    for(int i = 1; i < sum; i ++)
        adde(i, i + 1, k, 0);
    for(int i = 1; i <= n; i ++)
        adde(l[i], r[i], 1, -len[i]);
    write(-nf::pd().second);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}