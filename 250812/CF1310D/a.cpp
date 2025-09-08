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
const int N = 100, K = 20;
mt19937_64 my_rand(time(0) << 1 | 1);
int n, m;
int w[N][N];
int col[N];
ll dp[K][N], ans = 1e18;
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            w[i][j] = read();
    int cnt = 5000;
    while(cnt --) {
        memset(dp, 0x3f, sizeof dp);
        for(int i = 1; i <= n; i ++) col[i] = my_rand() & 1;
        dp[0][1] = 0;
        for(int i = 0; i < m; i ++)
            for(int j = 1; j <= n; j ++)
                for(int k = 1; k <= n; k ++)
                    if(col[j] != col[k])
                        dp[i + 1][k] = min(dp[i + 1][k], dp[i][j] + w[j][k]);
        ans = min(ans, dp[m][1]);
    }
    printf("%lld", ans);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}