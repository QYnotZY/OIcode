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
const int N = 1e5 + 10, logn = 18;
int n, k, q;
int h[N];
int stk[N], top;
int l[logn][N], r[logn][N];
void Hutao() {
    n = read(), k = read(), q = read();
    for(int i = 1; i <= n; i ++) h[i] = read();
    for(int i = 1; i <= n; i ++) {
        for(; top && h[stk[top]] <= h[i]; -- top) {
            r[0][stk[top]] = i;
            if(h[stk[top]] == h[i]) l[0][i] = stk[top];
        }
        if(!l[0][i]) l[0][i] = top ? stk[top] : 1;
        stk[++ top] = i;
    } r[0][n] = n;
    for(int i = 1; i < logn; i ++)
        for(int j = 1; j <= n; j ++) {
            l[i][j] = min(l[i - 1][l[i - 1][j]], l[i - 1][r[i - 1][j]]);
            r[i][j] = max(r[i - 1][l[i - 1][j]], r[i - 1][r[i - 1][j]]);
        }
    for(int i = 1, lu, ru, lv, rv, lt, rt, res; i <= q; i ++) {
        res = 0;
        lu = ru = read(), lv = rv = read();
        if(lu > lv) swap(lu, lv), swap(ru, rv);
        for(int j = logn - 1; ~j; -- j) {
            lt = min(l[j][lu], l[j][ru]), rt = max(r[j][lu], r[j][ru]);
            if(rt < lv) lu = lt, ru = rt, res += 1 << j;
        }
        for(int j = logn - 1; ~j; -- j) {
            lt = min(l[j][lv], l[j][rv]), rt = max(r[j][lv], r[j][rv]);
            if(ru < lt) lv = lt, rv = rt, res += 1 << j;
        }
        printf("%d\n", res);
    }
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}