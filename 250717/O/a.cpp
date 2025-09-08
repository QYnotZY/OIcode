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
int n, m, k, maxa, maxb, mina, minb, minn, maxx;
ll suma, sumb;
void Hutao() {
    n = read(), m = read(), k = read();
    suma = sumb = maxa = maxb = 0; mina = minb = 1000000000;
    for(int i = 1, a; i <= n; i ++)
        a = read(), maxa = max(maxa, a), mina = min(mina, a), suma += a;
    for(int i = 1, b; i <= m; i ++)
        b = read(), maxb = max(maxb, b), minb = min(minb, b), sumb += b;
    if(mina < maxb) suma += maxb - mina;
    minn = min(mina, minb), maxx = max(maxa, maxb);
    if(k & 1) printf("%lld\n", suma);
    else printf("%lld\n", suma + minn - maxx);
}
}
int main() {
    int t = read();
    while(t --) work::Hutao();
    return 0;
}