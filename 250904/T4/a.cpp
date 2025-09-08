#include "bits/stdc++.h"
using namespace std;
namespace FastIO {
    template <typename T = int> T read() {
        char ch = '\0'; bool f = 0; T res = 0;
        for(; !('0' <= ch && ch <= '9'); ch = getchar()) if(ch == '-') f = !f;
        for(; '0' <= ch && ch <= '9'; ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ '0');
        return f ? ~res + 1 : res;
    }
    char readch(const int acsp = 0) {
        char ch = '\0';
        for(; !(33 - acsp <= ch && ch < 127); ch = getchar()) ;
        return ch;
    }
} using FastIO::read; using FastIO::readch;
typedef long long ll;
namespace Qiuyu3600 {
const int N = 505;
int n, m;
struct node {
    int v, x, y;
    bool operator<(const node& obj) const {
        return v < obj.v;
    }
} a[N * N];
int row[N], col[N], dp[N][N];
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            a[i * m - m + j] = {read(), i, j}, dp[i][j] = 0;
    sort(a + 1, a + n * m + 1);
    memset(row, 0, n + 1 << 2);
    memset(col, 0, m + 1 << 2);
    int ans = 0;
    for(int il = 1, ir; il <= n * m; il = ir) {
        for(ir = il; ir <= n * m && a[ir].v == a[il].v; ir ++);
        for(int i = il; i < ir; i ++) dp[a[i].x][a[i].y] = max(row[a[i].x], col[a[i].y]) + 1, ans = max(ans, dp[a[i].x][a[i].y]);
        for(int i = il; i < ir; i ++) row[a[i].x] = max(row[a[i].x], dp[a[i].x][a[i].y]), col[a[i].y] = max(col[a[i].y], dp[a[i].x][a[i].y]);
    }
    printf("%d\n", ans);
}
}
int main() {
    int t = read(); while(t --) Qiuyu3600::Hutao();
    return 0;
}