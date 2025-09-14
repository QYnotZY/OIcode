#include "bits/stdc++.h"
using namespace std;
namespace FastIO {
    template<typename T = int> T read() {
        char ch = getchar(); bool neg = 0; T res = 0;
        for(; !('0' <= ch && ch <= '9'); ch = getchar()) if(ch == '-') neg = !neg;
        for(; ('0' <= ch && ch <= '9'); ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ 48);
        return neg ? ~res + 1 : res;
    }
    char readch(bool acsp = 0) {
        char ch = getchar(); for(; !(33 - acsp <= ch && ch < 127); ch = getchar()); return ch;
    }
} using namespace FastIO;
typedef long long ll;
namespace Qiuyu3600 {
const int N = 3e5 + 10, logn = 20;
const int mod = 998244353;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
int n, a[N];
namespace st {
    struct node {int pos, val; bool operator<(const node &obj) const {return val < obj.val;}} minn[logn][N];
    void init() {
        for(int i = 1; i <= n; i ++) minn[0][i] = {i, a[i]};
        for(int i = 1; i < logn; i ++)
            for(int j = 1; j + (1 << i) - 1 <= n; j ++)
                minn[i][j] = min(minn[i - 1][j], minn[i - 1][j + (1 << i - 1)]);
    }
    int query(int l, int r) {
        int log2n = __lg(r - l + 1);
        return min(minn[log2n][l], minn[log2n][r + 1 - (1 << log2n)]).pos;
    }
}
int dp[N];
int solve(int l, int r, int f) {
    if(l > r) return 0;
    int p = st::query(l, r);
    int lc = solve(l, p - 1, f | 2), rc = solve(p + 1, r, f | 1);
    dp[p] = Mult(dp[lc], dp[rc]);
    if((f & 1) == 1) dp[p] = Add(dp[p], dp[rc]);
    if((f & 2) == 2) dp[p] = Add(dp[p], dp[lc]);
    if((f & 3) == 3) dp[p] = Minus(dp[p], 1);
    return p;
}
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    st::init(); dp[0] = 1;
    int rt = solve(1, n, 0);
    printf("%d\n", dp[rt]);
}
}
int main() {
    int t = read(); while(t --) Qiuyu3600::Hutao();
    return 0;
}