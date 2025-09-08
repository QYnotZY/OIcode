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
const int N = 1e5 + 10, cnt = 20;
int n, a[N], b[N];
int ans;
int f[N][cnt + 1];
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++) a[i] = read();
    for(int i = 1; i <= n; i ++) {
        b[i] = read();
        a[i] = (b[i] - a[i] + 4) % 4;
    }
    f[0][0] = 0;
    for(int i = 1; i < cnt; i ++) f[0][i] = 4 * cnt;
    for(int i = 1; i <= n; i ++) {
        for(int j = 0; j < cnt; j ++) {
            f[i][j] = f[i - 1][0] + max(0, a[i] + 4 * j - a[i - 1]);
            for(int k = 1; k < cnt; k ++)
                f[i][j] = min(f[i][j], f[i - 1][k] + max(0, a[i] + 4 * j - a[i - 1] - 4 * k));
        }
    }
    int ans = f[n][0];
    for(int i = 1; i < cnt; i ++)
        ans = min(ans, f[n][i]);
    printf("%d\n", ans);
}
}
int main() {
    #ifndef db
    freopen("rotate.in", "r", stdin);
    freopen("rotate.out", "w", stdout);
    #endif
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}