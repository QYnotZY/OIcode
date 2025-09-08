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
const int N = 2e5 + 10;
int n, m;
ll a[N], f[N];
int gcd(int a, int b) {return b ? gcd(b, a % b) : a;}
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= n; i ++) a[i] = read();
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; i ++) f[n] += a[i] * a[i];
    for(int i = 1, g; i <= m; i ++) {
        g = read();
        g = gcd(n, g);
        if(!f[g]) {
            for(int i = 0; i < g; i ++) {
                f[g] += a[1ll * i * n / g + 1] * a[1ll * i * n / g + 2] + a[1ll * i * n / g + n / g - 1] * a[1ll * i * n / g + n / g];
                for(int j = 1; j <= n / g - 2; j ++)
                    f[g] += a[1ll * i * n / g + j] * a[1ll * i * n / g + j + 2];
            }
        }
        printf("%lld\n", f[g]);
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}