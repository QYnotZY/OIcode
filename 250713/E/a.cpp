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
using FastIO::readch;
using FastIO::write;
typedef long long ll;
namespace work {
const int N = 1e5 + 10;
int n; ll m, inv10;
inline ll exgcd(ll a, ll b, ll &x, ll &y) {
    if(b == 0)
        return (x = 1, y = 0, a);
    ll g = exgcd(b, a % b, y, x);
    return (y -= a / b * x, g);
}
inline ll Mod(ll a) {return (a % m + m) % m;}
inline ll Inv(ll a) {ll x, y; exgcd(a, m, x, y); return Mod(x);}
inline ll Pow(ll a, int b) {return b ? Pow(a * a % m, b >> 1) * (b & 1 ? a : 1) % m : 1;}
vector<pair<int, ll> > e[N];
int dfn[N], redfn[N], tot, sz[N], dep[N], hson[N];
ll down[N], up[N];
void Citlali(int u = 1, int f = 0) {
    dfn[u] = ++ tot, redfn[tot] = u, sz[u] = 1, dep[u] = dep[f] + 1, hson[u] = 0;
    for(auto ele : e[u]) {
        int &v = ele.first;
        ll &w = ele.second;
        if(v == f) continue;
        down[v] = Mod(Mod(down[u] * 10) + w);
        up[v] = Mod(up[u] + Mod(w * Pow(10, dep[u])));
        Citlali(v, u);
        if(sz[v] > sz[hson[u]]) hson[u] = v;
        sz[u] += sz[v];
    }
}
map<ll, int> buc1, buc2;
ll ans;
int query1(int lca, int u) {
    return buc1[Mod(Mod(down[lca] - Mod((up[u] - up[lca]) * Pow(inv10, dep[lca]))) * Pow(inv10, dep[lca]))];
}
int query2(int lca, int u) {
    return buc2[Mod(Mod(-down[u] + Mod(down[lca] * Pow(10, dep[u] - dep[lca]))) * Mod(Pow(inv10, dep[u] - dep[lca]) * Pow(10, dep[lca])) + up[lca])];
}
void add1(int u) {
    ++ buc1[Mod(down[u] * Pow(inv10, dep[u]))];
}
void add2(int u) {
    ++ buc2[up[u]];
}
void Furina(int u = 1, int f = 0, int clr = 0) {
    int res = 0;
    for(auto ele : e[u]) if(ele.first != f && ele.first != hson[u]) Furina(ele.first, u, 1);
    if(hson[u]) Furina(hson[u], u, 0);
    res += query1(u, u) + query2(u, u); add1(u), add2(u);
    for(auto ele : e[u]) {
        int &v = ele.first;
        if(v == f || v == hson[u]) continue;
        for(int i = dfn[v]; i < dfn[v] + sz[v]; i ++) 
        res += query1(u, redfn[i]) + query2(u, redfn[i]);
        for(int i = dfn[v]; i < dfn[v] + sz[v]; i ++) add1(redfn[i]), add2(redfn[i]);
    }
    if(clr) {
        map<ll, int> ().swap(buc1);
        map<ll, int> ().swap(buc2);
    }
    ans += res;
}
void Hutao() {
    n = read(), m = read<ll>(), inv10 = Inv(10);
    dep[0] = -1;
    for(int i = 1; i < n; i ++) {
        int u = read() + 1, v = read() + 1, w = read();
        e[u].push_back(make_pair(v, w));
        e[v].push_back(make_pair(u, w));
    }
    Citlali();
    Furina();
    printf("%lld", ans);
}
}
signed main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}