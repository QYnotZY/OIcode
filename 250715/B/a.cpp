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
const int N = 2e5 + 10;
int n, m, k;
vector<int> to[N], rto[N];
int ind[N];
int f[N], rf[N];
int tp[N], tot, ans[N];
int u[N], v[N];
bool vis[N];
void Hutao() {
    n = read(), m = read(), k = read();
    for(int i = 1; i <= m; i ++) {
        u[i] = read(), v[i] = read();
        to[u[i]].push_back(v[i]); ind[v[i]] ++;
        rto[v[i]].push_back(u[i]);
    }
    queue<int> q;
    for(int i = 1; i <= n; i ++) if(!ind[i]) q.push(i);
    while(q.size()) {
        int u = q.front(); q.pop();
        tp[++ tot] = u;
        for(auto v : to[u]) if(!(-- ind[v])) q.push(v);
    }
    int cur = 0;
    for(int i = 1; i <= n; i ++) {
        for(auto v : to[tp[i]]) f[v] = max(f[v], f[tp[i]] + 1);
        ans[tp[i]] = max(ans[tp[i]], cur); cur = max(cur, f[tp[i]]);
    }
    #ifdef db
    for(int i = 1; i <= n; i ++) printf("%d ", f[i]); printf("\n");
    for(int i = 1; i <= n; i ++) printf("%d ", rf[i]); printf("\n");
    #endif
    cur = 0;
    for(int i = n; i; i --) {
        for(auto v : rto[tp[i]]) rf[v] = max(rf[v], rf[tp[i]] + 1);
        ans[tp[i]] = max(ans[tp[i]], cur); cur = max(cur, rf[tp[i]]);
    }
    multiset<int> s; s.insert(0);
    for(int i = 1; i <= n; i ++) {
        for(auto v : rto[tp[i]]) s.erase(s.find(f[v] + 1 + rf[tp[i]]));
        ans[tp[i]] = max(ans[tp[i]], *s.rbegin());
        for(auto v : to[tp[i]]) s.insert(f[tp[i]] + 1 + rf[v]);
    }
    for(int i = 1; i <= k; i ++) {
        int op = read(), x = read();
        if(op == 3) {
            write(f[u[x]] + 1 + rf[v[x]]);
        } else if(op == 2) {
            write(f[x] + rf[x]);
        } else {
            write(ans[x]);
        }
    }
}
}
int main() {
    #ifndef db
    freopen("storm_wind.in", "r", stdin);
    freopen("storm_wind.out", "w", stdout);
    #endif
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}