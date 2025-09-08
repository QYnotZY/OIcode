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
typedef unsigned long long ull;
namespace work {
const int N = 52;
int m, n;
ull val[N];
map<ull, int> buc;
vector<int> to[N];
int sz[N];
int minn, g1, g2;
void dfs1(int u, int f) {
    sz[u] = 1; int maxsz = 0;
    for(auto v : to[u]) {
        if(v == f) continue;
        dfs1(v, u);
        if(maxsz < sz[v]) maxsz = sz[v];
        sz[u] += sz[v];
    }
    maxsz = max(maxsz, n - sz[u]);
    if(minn > maxsz) minn = maxsz, g1 = g2 = u;
    else if(minn == maxsz) g2 = u;
}
ull hash(ull val) {
    ull res = val;
    res <<= 14;
    res ^= 123456789123456789ull;
    res >>= 7;
    res ^= 987654321123456789ull;
    res ^= val;
    res >>= 10;
    res ^= 102938475610293847ull;
    res <<= 2;
    res ^= val;
    res ^= 646464646464646464ull;
    return res;
}
ull dfs2(int u, int f) {
    ull res = 1;
    for(auto v : to[u]) {
        if(v == f) continue;
        res += hash(dfs2(v, u));
    }
    return res;
}
void Hutao() {
    m = read();
    for(int i = 1; i <= m; i ++) {
        n = read(); minn = n;
        if(n == 1) {
            val[i] = 1;
            goto A;
        }
        for(int i = 1; i <= n; i ++) vector<int> ().swap(to[i]);
        for(int i = 1, u; i <= n; i ++) {
            u = read();
            if(u) to[u].push_back(i), to[i].push_back(u);
        }
        dfs1(1, 0);
        val[i] = dfs2(g1, 0) + dfs2(g2, 0);
        A:;
        if(!buc[val[i]]) buc[val[i]] = i;
    }
    for(int i = 1; i <= m; i ++)
        printf("%d\n", buc[val[i]]);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}