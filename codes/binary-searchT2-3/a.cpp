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
const int N = 2010;
int n, m, a1[N][N], a2[N][N], a3[N][N], a4[N][N];
int minn, maxx;
bool check1(int mid) {
    for(int i = 1, j, lj = m + 1; i <= n; i ++) {
        for(j = 1; j < lj; j ++)
            if(a1[i][j] > minn + mid) break;
        lj = j;
        for(; j <= m; j ++)
            if(a1[i][j] < maxx - mid) return false;
    }
    return true;
}
bool check2(int mid) {
    for(int i = 1, j, lj = n + 1; i <= m; i ++) {
        for(j = 1; j < lj; j ++)
            if(a2[i][j] > minn + mid) break;
        lj = j;
        for(; j <= n; j ++)
            if(a2[i][j] < maxx - mid) return false;
    }
    return true;
}
bool check3(int mid) {
    for(int i = 1, j, lj = m + 1; i <= n; i ++) {
        for(j = 1; j < lj; j ++)
            if(a3[i][j] > minn + mid) break;
        lj = j;
        for(; j <= m; j ++)
            if(a3[i][j] < maxx - mid) return false;
    }
    return true;
}
bool check4(int mid) {
    for(int i = 1, j, lj = n + 1; i <= m; i ++) {
        for(j = 1; j < lj; j ++)
            if(a4[i][j] > minn + mid) break;
        lj = j;
        for(; j <= n; j ++)
            if(a4[i][j] < maxx - mid) return false;
    }
    return true;
}
bool check(int mid) {return check1(mid) || check2(mid) || check3(mid) || check4(mid);}
void Hutao() {
    n = read(), m = read(); minn = 1e9, maxx = 0;
    for(int i = 1, a; i <= n; i ++)
        for(int j = 1; j <= m; j ++) {
            a1[i][j] = a2[m-j+1][i] = a3[n-i+1][m-j+1] = a4[j][n-i+1] = a = read();
            minn = min(minn, a), maxx = max(maxx, a);
        }
    int l = -1, r = maxx - minn;
    while(l + 1 < r) (check(l + r >> 1) ? r : l) = l + r >> 1;
    printf("%d", r);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}