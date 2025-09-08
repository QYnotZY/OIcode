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
const int N = 2e5 + 10;
int mod;
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
int n, a[N];
vector<int> to[N];
int mul[N][41];
int fa[N];
void dfs(int u = 1, int f = 0) {
    fa[u] = f;
    for(auto v : to[u]) {
        if(v == f) continue;
        dfs(v, u);
    }
}
void Hutao() {
    n = read(), mod = read();
    for(int i = 1; i <= n; i ++)
        for(int j = 0; j <= 40; j ++)
            mul[i][j] = 1;
    for(int i = 1, u, v; i < n; i ++) {
        u = read(), v = read();
        to[u].push_back(v), to[v].push_back(u);
    }
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    dfs(1, 0);
    int q = read();
    int op, x, d, w; int u;
    while(q --) {
        op = read(), x = read();
        if(op == 1) {
            d = read(), w = read();
            for(u = x; d > 0 && u ^ 1; u = fa[u], d --)
                mul[u][d] = Mult(mul[u][d], w), mul[u][d - 1] = Mult(mul[u][d - 1], w);
            for(; ~d; d --) mul[u][d] = Mult(mul[u][d], w);
        } else {
            w = a[x];
            for(d = 0, u = x; u && d <= 40; u = fa[u], d ++)
                w = Mult(w, mul[u][d]);
            printf("%d\n", w);
        }
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}