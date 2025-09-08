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
const int N = 1e6 + 10;
int n, k, a[N], sumb;
ll suma[N], p[N];
char s;
ll f[N], g[N];
ll getx(int i) {return i;}
ll gety(int i) {return f[i] - suma[p[i] - 1] + (p[i] - 1) * i;}
int q[N], head, tail;
bool Skirk(ll slp) {
    f[0] = 0, g[0] = 0;
    head = 0, tail = 1, q[0] = 0;
    for(int i = 1; i <= n; i ++) {
        while(head + 1 < tail && gety(q[head]) - i * getx(q[head]) > gety(q[head + 1]) - i * getx(q[head + 1])) ++ head;
        f[i] = gety(q[head]) - i * getx(q[head]) + suma[i] - slp; g[i] = g[q[head]] + 1;
        while(head + 1 < tail && (gety(q[tail - 1]) - gety(q[tail - 2])) * (getx(i) - getx(q[tail - 2])) >= (gety(i) - gety(q[tail - 2])) * (getx(q[tail - 1]) - getx(q[tail - 2]))) -- tail;
        q[tail ++] = i;
    }
    return g[n] <= k;
}
void Hutao() {
    n = read(), k = read();
    p[0] = 1, a[0] = 0;
    int cnt = 0;
    for(int i = 1; i <= n << 1; i ++) {
        s = readch();
        if(s == 'A') {
            a[++ cnt] = sumb; suma[cnt] = suma[cnt - 1] + a[cnt];
            for(int j = a[cnt - 1]; j < a[cnt]; j ++)
                p[j] = max(j + 1, cnt);
        } else
            sumb ++;
    }
    for(int i = a[n]; i <= n; i ++)
        p[i] = n + 1;
    ll l = - 1ll * n * (n - 1) / 2, r = 1;
    while(l + 1 < r) (Skirk(l + r >> 1) ? l : r) = l + r >> 1;
    Skirk(l); ll ans = f[n] + l * k;
    printf("%lld\n", ans);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}