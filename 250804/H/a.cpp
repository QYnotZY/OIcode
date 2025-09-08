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
const int N = 505;
int n, m, a[N][N], x1[N * N], x2[N * N], y1[N * N], y2[N * N], b[N][N], cnt;
void Hutao() {
    n = read(); m = read();
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++) {
            a[i][j] = read();
            if(!x1[a[i][j]]) cnt ++;
            if(!x1[a[i][j]] || x1[a[i][j]] > i) x1[a[i][j]] = i;
            if(!x2[a[i][j]] || x2[a[i][j]] < i) x2[a[i][j]] = i;
            if(!y1[a[i][j]] || y1[a[i][j]] > j) y1[a[i][j]] = j;
            if(!y2[a[i][j]] || y2[a[i][j]] < j) y2[a[i][j]] = j;
        }
    if(cnt <= m) {
        printf("%d", m - cnt);
        return;
    }
    for(int l = 1; l <= n; l ++) {
        memset(b, 0, sizeof b);
        for(int i = 1; i <= n * n; i ++) {
            if(!x1[i]) continue;
            int xl = max(1, x2[i] - l + 1), xr = min(n - l + 1, x1[i]), yl = max(1, y2[i] - l + 1), yr = min(n - l + 1, y1[i]);
            if(xl > xr || yl > yr) continue;
            b[xl][yl] ++; b[xr + 1][yr + 1] ++;
            b[xr + 1][yl] --; b[xl][yr + 1] --;
        }
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= n; j ++)
                b[i][j] += b[i][j - 1];
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= n; j ++)
                b[i][j] += b[i - 1][j];
        for(int i = 1; i <= n - l + 1; i ++)
            for(int j = 1; j <= n - l + 1; j ++)
                if(b[i][j] == cnt - m || b[i][j] - 1 == cnt - m) {
                    printf("1\n");
                    return;
                }
    }
    printf("2\n");
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}