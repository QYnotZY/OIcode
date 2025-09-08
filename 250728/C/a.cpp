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
const int N = 5e5 + 10;
mt19937_64 my_rand(time(0) ^ 78ull << 13);
int n, m, q;
ll w[N], ind[N], ind0[N];
ll sum0, sum;
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= n; i ++) sum0 += w[i] = my_rand() % (LONG_LONG_MAX / N);
    for(int i = 1; i <= m; i ++) {
        int u = read(), v = read();
        ind0[v] += w[u];
    }
    for(int i = 1; i <= n; i ++) sum += ind[i] = ind0[i];
    q = read();
    for(int i = 1; i <= q; i ++) {
        int op = read(), u, v;
        op & 1 ? (u = read(), v = read()) : v = read();
        sum -= ind[v];
        if(op == 1) {
            ind[v] -= w[u];
        } else if(op == 2) {
            ind[v] = 0;
        } else if(op == 3) {
            ind[v] += w[u];
        } else {
            ind[v] = ind0[v];
        }
        sum += ind[v];
        printf(sum == sum0 ? "YES\n" : "NO\n");
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}