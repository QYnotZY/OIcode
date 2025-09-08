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
const int N = 3e5 + 10;
int n;
vector<int> to[N];
int dep[N], maxdep, cnt[N], sumc[N];
int sz[N];
ll ans;
void Citlali(int u = 1, int f = 0) {
    ll pairs = 0;
    maxdep = max(maxdep, dep[u] = dep[f] + 1), cnt[dep[u]] ++;
    sz[u] = 0;
    for(auto v : to[u]) {
        if(v == f) continue;
        Citlali(v, u);
        pairs += 1ll * sz[u] * sz[v];
        sz[u] += sz[v];
    }
    sz[u] ++;
    ans -= pairs * (2 * dep[u] + 1);
    if(!f) {
        sumc[maxdep + 1] = 0;
        for(int i = maxdep; i; i --)
            sumc[i] = sumc[i + 1] + cnt[i];
    }
}
void Hutao() {
    n = read();
    ans = maxdep = 0;
    for(int i = 1; i <= n; i ++) {
        vector<int> ().swap(to[i]);
        cnt[i] = 0;
    }
    for(int i = 1, u, v; i < n; i ++) {
        u = read(), v = read();
        to[u].emplace_back(v);
        to[v].emplace_back(u);
    }
    Citlali();
    for(int i = maxdep; i; i --) {
        ll pairs = 1ll * cnt[i] * (cnt[i] - 1) / 2;
        ans += pairs * 2 * i;
    }
    for(int i = 1; i <= n; i ++) {
        ll pairs = 1ll * sumc[dep[i] + 1] - sz[i] + 1;
        ans += pairs * 2 * dep[i];
    }
    write<ll>(ans);
}
}
int main() {
    int t = read();
    while(t --) work::Hutao();
    return 0;
}