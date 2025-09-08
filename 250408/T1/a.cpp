#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
char gc() {return getchar();}
template<typename T = int>
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
T read(bool ch = 0, bool sp = 0) {return ch ? readch(sp) : readnum<T>();}
}
using FastIO::read;
typedef long long ll;
typedef pair<ll, int> pli;
#define mkp make_pair

int n, m, s1, t1, s2, t2;
const ll inf = 1e12;
struct edge{
    int to;
    ll dis;
    int next;
} e[5050];
int head[1010], tote; int ind[1010];
void init_e(){
    tote = 0;
    for(int i = 1; i <= n; i ++)
        head[i] = -1, ind[i] = 0;
}
void add(int u, int v, ll w){
    e[++ tote] = {v, w, head[u]};
    ind[v] ++;
    head[u] = tote;
}
int tpn[1010], totv;
void toposort(){
    totv = 0;
    queue<int> q;
    for(int i = 1; i <= n; i ++)
        if(!ind[i]) q.push(i);
    while(q.size()){
        int u = q.front(); q.pop();
        tpn[++ totv] = u;
        for(int i = head[u]; ~i; i = e[i].next){
            int &v = e[i].to; ll &w = e[i].dis;
            ind[v] --;
            if(!ind[v]) q.push(v);
        }
    }
}
ll f[1010][1010];
void solve(){
    n = read(), m = read(), s1 = read(), t1 = read(), s2 = read(), t2 = read();
    init_e();
    for(int i = 1, u, v, w; i <= m; i ++){
        u = read(), v = read(), w = read();
        add(u, v, w);
    }
    toposort();
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            f[i][j] = inf;
    f[s1][s2] = 0;
    for(int i = 1; i <= n; i ++){
        int &u = tpn[i];
        for(int ii = head[u]; ~ii; ii = e[ii].next){
            int &v = e[ii].to; ll &w = e[ii].dis;
            for(int j = 1; j <= n; j ++){
                if(u == j || v == j) continue;
                f[v][j] = min(f[v][j], f[u][j] + w);
                f[j][v] = min(f[j][v], f[j][u] + w);
            }
        }
    }
    printf("%lld\n", f[t1][t2] ^ inf ? f[t1][t2] : -1ll);
} 
int main(){
    // freopen("railway.in", "r", stdin);
    // freopen("railway.out", "w", stdout);
    int q = read();
    while(q --)
        solve();
    return 0;
}