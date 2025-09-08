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
typedef long long ll;
namespace work {
const int N = 1e6 + 10;
mt19937_64 Luck(time(0));
inline bool Fate() {return Luck() & 1;}
int n, m, d, ans;
vector<int> to[N];
int dep[N], c1, c2, dep1[N], dep2[N];
void dfs1(int u, int f) {
    dep[u] = dep[f] + 1;
    if(dep[u] > dep[c1]) c1 = u;
    for(auto v : to[u]) {
        if(v == f) continue;
        dfs1(v, u);
    }
}
void dfs2(int u, int f) {
    dep1[u] = dep1[f] + 1;
    if(dep1[u] > dep1[c2]) c2 = u;
    for(auto v : to[u]) {
        if(v == f) continue;
        dfs2(v, u);
    }
}
void dfs3(int u, int f) {
    dep2[u] = dep2[f] + 1;
    for(auto v : to[u]) {
        if(v == f) continue;
        dfs3(v, u);
    }
}
void Hutao() {
    n = read(), m = read(), d = read();
    if(n == m) {
        for(int i = 2, u; i <= n; i ++) {
            u = read();
            to[u].push_back(i), to[i].push_back(u);
        }
        dep[0] = dep1[0] = dep2[0] = -1; dfs1(1, 0); dfs2(c1, 0); dfs3(c2, 0);
        for(int i = 1; i <= n; i ++) if(dep1[i] <= d && dep2[i] <= d) ans ++;
        printf("%d", ans);
    }
    else if(m > 1 && d == 1) printf("0");
    else printf("%d", n);
}
}
int main() {
    freopen("tower.in", "r", stdin);
    freopen("tower.out", "w", stdout);
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}