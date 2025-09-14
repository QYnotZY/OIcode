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
const int N = 210, inf = 1e5;
int n, m, x, y, k;
char mp[N][N];
int f[N][N];
struct node {int t, v;} que[N]; int ql, qr;
void Hutao() {
    n = read(), m = read(), x = read(), y = read(), k = read();
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++) {
            mp[i][j] = readch();
            f[i][j] = -inf;
        }
    f[x][y] = 0;
    for(int t = 1, l, d; t <= k; t ++) {
        l = read(), d = read(), l = d - l + 1, d = read();
        switch(d) {
            case 1 :
            for(int j = 1; j <= m; j ++) {
                ql = qr = 0;
                for(int i = n; i; -- i) {
                    if(mp[i][j] == 'x') {ql = qr = 0; continue;}
                    while(ql ^ qr && que[ql].t > i + l) ++ ql;
                    while(ql ^ qr && que[qr - 1].v <= f[i][j] + i) -- qr;
                    que[qr ++] = {i, f[i][j] + i};
                    f[i][j] = que[ql].v - i;
                }
            } break;
            case 2 :
            for(int j = 1; j <= m; j ++) {
                ql = qr = 0;
                for(int i = 1; i <= n; i ++) {
                    if(mp[i][j] == 'x') {ql = qr = 0; continue;}
                    while(ql ^ qr && que[ql].t < i - l) ++ ql;
                    while(ql ^ qr && que[qr - 1].v <= f[i][j] - i) -- qr;
                    que[qr ++] = {i, f[i][j] - i};
                    f[i][j] = que[ql].v + i;
                }
            } break;
            case 3 :
            for(int i = 1; i <= n; i ++) {
                ql = qr = 0;
                for(int j = m; j; -- j) {
                    if(mp[i][j] == 'x') {ql = qr = 0; continue;}
                    while(ql ^ qr && que[ql].t > j + l) ++ ql;
                    while(ql ^ qr && que[qr - 1].v <= f[i][j] + j) -- qr;
                    que[qr ++] = {j, f[i][j] + j};
                    f[i][j] = que[ql].v - j;
                }
            } break;
            case 4 :
            for(int i = 1; i <= n; i ++) {
                ql = qr = 0;
                for(int j = 1; j <= m; j ++) {
                    if(mp[i][j] == 'x') {ql = qr = 0; continue;}
                    while(ql ^ qr && que[ql].t < j - l) ++ ql;
                    while(ql ^ qr && que[qr - 1].v <= f[i][j] - j) -- qr;
                    que[qr ++] = {j, f[i][j] - j};
                    f[i][j] = que[ql].v + j;
                }
            } break;
        }
    }
    int ans = -inf;
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            ans = max(ans, f[i][j]);
    printf("%d", ans);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}