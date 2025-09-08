#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
char gc() {return getchar();}
template<typename T = int>
inline T readnum(){
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
template<typename T = int>
T read() {return readnum<T>();}
}
using FastIO::read;
typedef long long ll;

const int N = 1e5 + 10;
namespace sol{
int n, k, q, cnt;
bitset<1 << 12> f[N + 12];
int a[14 * N]; inline int dca(int a, int b) {return (a - 1) * N + b;}
int Main(){
    n = read(), k = read(), q = read();
    for(int i = 1; i <= k; i ++)
        for(int j = 1; j <= n; j ++)
            a[dca(i, j)] = read();
    cnt = k;
    for(int i = 1; i <= k; i ++)
        for(int S = 0; S < 1 << k; S ++)
            f[i][S] = S & 1 << i - 1;
    for(int i = 1, op, x, y; i <= q; i ++){
        op = read(), x = read(), y = read();
        if(op == 1){
            ++ cnt;
            for(int S = 0; S < 1 << k; S ++)
                f[cnt][S] = f[x][S] | f[y][S];
        }
        if(op == 2){
            ++ cnt;
            for(int S = 0; S < 1 << k; S ++)
                f[cnt][S] = f[x][S] & f[y][S];
        }
        if(op == 3){
            for(int i = 1, lim = int(1.001e9), ans0 = 0, S = 0; lim; i ++, lim = ans0, ans0 = S = 0){
                for(int j = 1; j <= k; j ++)
                    if(ans0 < a[dca(j, y)] && a[dca(j, y)] < lim) ans0 = a[dca(j, y)];
                for(int j = k; j >= 1; j --)
                    S = S << 1 | (a[dca(j, y)] >= ans0);
                if(f[x][S]){
                    printf("%d\n", ans0);
                    break;
                }
            }
        }
    }
    return 0;
}
}
int main(){
    return sol::Main();
}