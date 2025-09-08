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
const int N = 310, M = 2e5 + 10;
int n, q;
int a[N][N];
struct QRY {
    int x1, y1, x2, y2;
} qry[M];
int p[M], tmp[M];
ll dp[N][N][N];
ll ans[M];
void solve(int lx, int rx, int ly, int ry, int lq, int rq) {
    if(lx == rx && ly == ry) {
        for(int i = lq; i <= rq; i ++)
            ans[p[i]] = a[lx][ry];
        return;
    }
    if(rx - lx >= ry - ly) {
        int midx = lx + rx >> 1;
        for(int j1 = ly; j1 <= ry; j1 ++) {
            for(int i = lx; i <= rx; i ++)
                for(int j = ly; j <= ry; j ++)
                    dp[j1][i][j] = 0;
            dp[j1][midx][j1] = a[midx][j1];
            for(int j = j1 - 1; j >= ly; j --)
                dp[j1][midx][j] = dp[j1][midx][j + 1] + a[midx][j];
            for(int i = midx - 1; i >= lx; i --) {
                dp[j1][i][j1] = dp[j1][i + 1][j1] + a[i][j1];
                for(int j = j1 - 1; j >= ly; j --) {
                    dp[j1][i][j] = min(dp[j1][i][j + 1], dp[j1][i + 1][j]) + a[i][j];
                }
            }
            for(int j = j1 + 1; j <= ry; j ++)
                dp[j1][midx][j] = dp[j1][midx][j - 1] + a[midx][j];
            for(int i = midx + 1; i <= rx; i ++) {
                dp[j1][i][j1] = dp[j1][i - 1][j1] + a[i][j1];
                for(int j = j1 + 1; j <= ry; j ++) {
                    dp[j1][i][j] = min(dp[j1][i][j - 1], dp[j1][i - 1][j]) + a[i][j];
                }
            }
        }
        int left = lq, right = rq; ll res;
        for(int i = lq; i <= rq; i ++) {
            if(qry[p[i]].x2 <= midx)
                tmp[left ++] = p[i];
            else if(qry[p[i]].x1 > midx)
                tmp[right --] = p[i];
            else {
                int &x1 = qry[p[i]].x1, &y1 = qry[p[i]].y1, &x2 = qry[p[i]].x2, &y2 = qry[p[i]].y2;
                res = 1e18;
                for(int j = y1; j <= y2; j ++)
                    res = min(res, dp[j][x1][y1] + dp[j][x2][y2] - a[midx][j]);
                ans[p[i]] = res;
            }
        }
        for(int i = lq; i <= rq; i ++) p[i] = tmp[i];
        solve(lx, midx, ly, ry, lq, left - 1);
        solve(midx + 1, rx, ly, ry, right + 1, rq);
    } else {
        int midy = ly + ry >> 1;
        for(int i1 = lx; i1 <= rx; i1 ++) {
            for(int i = lx; i <= rx; i ++)
                for(int j = ly; j <= ry; j ++)
                    dp[i1][i][j] = 0;
            dp[i1][i1][midy] = a[i1][midy];
            for(int i = i1 - 1; i >= lx; i --)
                dp[i1][i][midy] = dp[i1][i + 1][midy] + a[i][midy];
            for(int j = midy - 1; j >= ly; j --) {
                dp[i1][i1][j] = dp[i1][i1][j + 1] + a[i1][j];
                for(int i = i1 - 1; i >= lx; i --) {
                    dp[i1][i][j] = min(dp[i1][i][j + 1], dp[i1][i + 1][j]) + a[i][j];
                }
            }
            for(int i = i1 + 1; i <= rx; i ++)
                dp[i1][i][midy] = dp[i1][i - 1][midy] + a[i][midy];
            for(int j = midy + 1; j <= ry; j ++) {
                dp[i1][i1][j] = dp[i1][i1][j - 1] + a[i1][j];
                for(int i = i1 + 1; i <= rx; i ++) {
                    dp[i1][i][j] = min(dp[i1][i][j - 1], dp[i1][i - 1][j]) + a[i][j];
                }
            }
        }
        int left = lq, right = rq; ll res;
        for(int i = lq; i <= rq; i ++) {
            if(qry[p[i]].y2 <= midy)
                tmp[left ++] = p[i];
            else if(qry[p[i]].y1 > midy)
                tmp[right --] = p[i];
            else {
                int &x1 = qry[p[i]].x1, &y1 = qry[p[i]].y1, &x2 = qry[p[i]].x2, &y2 = qry[p[i]].y2;
                res = 1e18;
                for(int i = x1; i <= x2; i ++)
                    res = min(res, dp[i][x1][y1] + dp[i][x2][y2] - a[i][midy]);
                ans[p[i]] = res;
            }
        }
        for(int i = lq; i <= rq; i ++) p[i] = tmp[i];
        solve(lx, rx, ly, midy, lq, left - 1);
        solve(lx, rx, midy + 1, ry, right + 1, rq);
    }
}
void Hutao() {
    n = read(), q = read();
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            a[i][j] = read();
    for(int i = 1; i <= q; i ++)
        qry[i].x1 = read(), qry[i].x2 = read(), qry[i].y1 = read(), qry[i].y2 = read(), p[i] = i;
    solve(1, n, 1, n, 1, q);
    for(int i = 1; i <= q; i ++)
        printf("%lld\n", ans[i]);
}
}
int main() {
    freopen("glyph.in", "r", stdin);
    freopen("glyph.out", "w", stdout);
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}