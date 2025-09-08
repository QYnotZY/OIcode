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
#define rint register int
int n, m, a, b;
int v[30][10][10], v1[10][10];
int op[10][10];
int solve(int gapr, int gapc) {
    int res = 0, resr, resc, tmp;
    // #ifdef db
    // for(int i = 0; i < n; i ++) {
    //     for(int j = 0; j < m; j ++)
    //         printf("%d ", v1[i][j]);
    //     printf("\n");
    // }
    // #endif
    for(int i0 = 0; i0 < gapr; i0 ++) {
        for(int j0 = 0; j0 < gapc; j0 ++) {
            resr = resc = 0;
            for(int i = i0; i < n; i += gapr) {
                tmp = 0;
                for(int j = j0; j < m; j += gapc)
                    tmp ^= v1[i][j];
                resr += tmp;
            }
            for(int j = j0; j < m; j += gapc) {
                tmp = 0;
                for(int i = i0; i < n; i += gapr)
                    tmp ^= v1[i][j];
                resc += tmp;
            }
            res += max(resr, resc);
        }
    }
    // #ifdef db
    // printf("%d\n", res);
    // #endif
    return res;
}
int regular_dfs(int dig, int rc = 0, int id = 0) {
    if(rc == 2) {
        for(int i = 0; i < n; i ++)
            for(int j = 0; j < m; j ++)
                v1[i][j] = op[i][j] ^ (j ? v1[i][j - 1] : 0) ^ (i ? v1[i - 1][j] : 0) ^ (i && j ? v1[i - 1][j - 1] : 0);
        for(int i = 0; i < n; i ++)
            for(int j = 0; j < m; j ++)
                v1[i][j] ^= v[dig][i][j];
        return solve(a, b);
    }
    if(rc == 0 && id > n - a) return regular_dfs(dig, 1, 1);
    if(rc == 1 && id > m - b) return regular_dfs(dig, 2, 0);
    int res;
    if(rc == 0) {
        res = regular_dfs(dig, rc, id + 1);
        op[id][0] ^= 1; id + a < n && (op[id + a][0] ^= 1); b < m && (op[id][b] ^= 1); id + a < n && b < m && (op[id + a][b] ^= 1);
        res = min(res, regular_dfs(dig, rc, id + 1));
        op[id][0] ^= 1; id + a < n && (op[id + a][0] ^= 1); b < m && (op[id][b] ^= 1); id + a < n && b < m && (op[id + a][b] ^= 1);
    } else {
        res = regular_dfs(dig, rc, id + 1);
        op[0][id] ^= 1; a < n && (op[a][id] ^= 1); b + id < m && (op[0][b + id] ^= 1); a < n && b + id < m && (op[a][id + b] ^= 1);
        res = min(res, regular_dfs(dig, rc, id + 1));
        op[0][id] ^= 1; a < n && (op[a][id] ^= 1); b + id < m && (op[0][b + id] ^= 1); a < n && b + id < m && (op[a][id + b] ^= 1);
    }
    return res;
}
void regular_work() {
    ll res = 0;
    for(int dig = 0; dig < 30; dig ++) {
        // #ifdef db
        // for(int i = 0; i < n; i ++) {
        //     for(int j = 0; j < m; j ++)
        //         printf("%d ", v[dig][i][j]);
        //     printf("\n");
        // }
        // #endif
        res += 1ll * regular_dfs(dig) << dig;
    }
    printf("%lld\n", res);
}
void Hutao() {
    n = read(), m = read(), a = read(), b = read();
    for(rint i = 0, val; i < n; i ++)
        for(rint j = 0; j < m; j ++) {
            val = read();
            for(rint k = 0; k < 30; k ++)
                v[k][i][j] = val >> k & 1;
        }
    regular_work();
}
}
int main() {
    #ifndef db
    freopen("grapes.in", "r", stdin);
    freopen("grapes.out", "w", stdout);
    #endif
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}