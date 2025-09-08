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
const int N = 1010;
int n, m;
double f[N][N]; bool vis[N][N];
#define TMP (1.0 / (j + 1) + (1.0 * j / (j + 1) * (1 - dfs(j - 1, i))))
#define P ((TMP - 1.0 * j / (j + 1) * (1 - dfs(j - 1, i))) / (dfs(j, i - 1) - 1.0 * j / (j + 1) * (1 - dfs(j - 1, i)) + TMP))
#define RES (P + (1 - P) * 1.0 * j / (j + 1) * (1 - dfs(j - 1, i)))
double dfs(int i, int j) {
    if(vis[i][j]) return f[i][j];
    vis[i][j] = 1;
    return f[i][j] = RES;
}
void Hutao() {
    n = read(), m = read();
    for(int i = 0; i <= max(n, m); i ++) vis[i][0] = 1, f[i][0] = 1.0;
    for(int j = 1; j <= max(n, m); j ++) vis[0][j] = 1, f[0][j] = 1.0 / (1.0 + j);
    printf("%f %f\n", dfs(n, m), 1 - dfs(n, m));
}
}
int main() {
    #ifndef db
    freopen("landlords.in", "r", stdin);
    freopen("landlords.out", "w", stdout);
    #endif
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}