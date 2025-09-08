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
const int N = 7010;
const int mod = 998244353;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Pow_1(int b) {return b & 1 ? mod - 1 : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
int n, m;
int lim[N];
int f[N][N]; int g[N];
namespace dsu {
    int fa[N], maxlim[N];
    void init(int n) {for(int i = 1; i <= n; i ++) fa[i] = i, maxlim[i] = lim[i];}
    int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
    bool same(int x, int y) {return find(x) == find(y);}
    void merge(int x, int y) {x = find(x), y = find(y); fa[y] = x, maxlim[x] = max(maxlim[x], maxlim[y]);}
}
int stk[N], top;
void Hutao() {
    n = read(), m = read();
    lim[1] = n; for(int i = 2; i <= n; i ++) lim[i] = i;
    for(int i = 1, u, v; i <= m; i ++) {
        u = read(), v = read();
        lim[u] = max(lim[u], v);
    }
    dsu::init(n);
    for(int i = 1; i <= n; i ++) {
        while(top && lim[stk[top]] < lim[i]) {
            if(lim[stk[top]] >= i) if(!dsu::same(i, stk[top])) dsu::merge(i, stk[top]);
            -- top;
        }
        stk[++ top] = i;
    }
    for(int i = 1; i <= n; i ++) lim[i] = dsu::maxlim[dsu::find(i)];
    stack<pair<int, int> > s;
    for(int i = n; i; i --) {
        f[i][1] = 1;
        while(s.size()) {
            int curl, curr; tie(curl, curr) = s.top();
            if(curl > lim[i]) break;
            s.pop();
            int sz0 = curl - i, sz1 = curr - curl + 1;
            g[sz0 + 1] = 0;
            for(int j = sz0; j; j --) g[j] = Add(g[j + 1], f[i][j]);
            memset(f[i], 0, sz0 + 1 << 2);
            for(int j = 1; j <= sz0; j ++)
                for(int k = 1; k <= sz1; k ++)
                    f[i][j + k] = Add(f[i][j + k], Mult(f[curl][k], g[j]));
        }
        s.push(make_pair(i, lim[i]));
    }
    int ans = 0;
    for(int i = 1; i <= n; i ++) ans = Add(ans, f[1][i]);
    printf("%d\n", ans);
}
}
int main() {
    #ifndef db
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    #endif
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}