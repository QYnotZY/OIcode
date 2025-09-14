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
const int N = 1e5 + 10, logN = 17;
const int mod = 1e9 + 7;
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
int n, m;
int fa[logN][N];
void init() {
    for(int i = 0; i < logN; i ++)
        for(int j = 1; j <= n; j ++)
            fa[i][j] = j;
}
int find(int fl, int x) {return fa[fl][x] == x ? x : fa[fl][x] = find(fl, fa[fl][x]);}
void merge(int fl, int x, int y) {
    x = find(fl, x), y = find(fl, y);
    if(x == y) return;
    fa[fl][y] = x;
}
int l1, r1, l2, r2;
int vis[N], ans;
void Hutao() {
    n = read(), m = read();
    init();
    for(int i = 1; i <= m; i ++) {
        l1 = read(), r1 = read(), l2 = read(), r2 = read();
        for(int j = logN - 1; ~j; -- j)
            if(l1 + (1 << j) - 1 <= r1) {
                merge(j, l1, l2);
                l1 += 1 << j, l2 += 1 << j;
            }
    }
    for(int i = logN - 1; i; -- i)
        for(int j = 1; j + (1 << i) - 1 <= n; j ++) {
            merge(i - 1, j, find(i, j));
            merge(i - 1, j + (1 << i - 1), find(i, j) + (1 << i - 1));
        }
    for(int i = 1; i <= n; i ++)
        if(!vis[find(0, i)]) {
            vis[find(0, i)] = 1;
            ++ ans;
        }
    printf("%d\n", Mult(9, Pow(10, ans - 1)));
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}