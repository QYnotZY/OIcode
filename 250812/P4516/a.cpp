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
const int N = 1e5 + 10, M = 105;
const int mod = 1000000007;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline void chkAdd(int &a, int b) {a = Add(a, b);}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
int n, m;
vector<int> to[N];
int sz[N];
int dp[N][M][2][2], tmp[M][2][2];
void solve(int u, int f) {
    sz[u] = 1;
    dp[u][0][0][0] = 1, dp[u][1][1][0] = 1;
    for(auto v : to[u]) {
        if(v == f) continue;
        solve(v, u);
        for(int i = 0; i <= min(sz[u], m); i ++)
            for(int j = 0; j <= min(sz[v], m - i); j ++) {
                chkAdd(tmp[i + j][0][0], Mult(dp[u][i][0][0], dp[v][j][0][1]));
                chkAdd(tmp[i + j][0][1], Add(Mult(dp[u][i][0][1], Add(dp[v][j][0][1], dp[v][j][1][1])), Mult(dp[u][i][0][0], dp[v][j][1][1])));
                chkAdd(tmp[i + j][1][0], Mult(dp[u][i][1][0], Add(dp[v][j][0][0], dp[v][j][0][1])));
                chkAdd(tmp[i + j][1][1], Add(Mult(dp[u][i][1][0], Add(dp[v][j][1][0], dp[v][j][1][1])), Mult(dp[u][i][1][1], Add(Add(dp[v][j][0][0], dp[v][j][0][1]), Add(dp[v][j][1][0], dp[v][j][1][1])))));
            }
        sz[u] += sz[v];
        for(int i = 0; i <= min(sz[u], m); i ++) dp[u][i][0][0] = tmp[i][0][0], tmp[i][0][0] = 0, dp[u][i][0][1] = tmp[i][0][1], tmp[i][0][1] = 0, dp[u][i][1][0] = tmp[i][1][0], tmp[i][1][0] = 0, dp[u][i][1][1] = tmp[i][1][1], tmp[i][1][1] = 0;
    }
}
void Hutao() {
    n = read(), m = read();
    for(int i = 1, u, v; i < n; i ++) {
        u = read(), v = read();
        to[u].push_back(v);
        to[v].push_back(u);
    }
    solve(1, 0);
    printf("%d\n", Add(dp[1][m][0][1], dp[1][m][1][1]));
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}