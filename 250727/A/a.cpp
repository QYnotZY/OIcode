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
int a, m, b;
char sb[20000010];
inline int Mult(int a, int b) {return 1ll * a * b % m;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
void Hutao() {
    scanf("%d%d", &a, &m);
    a %= m;
    int phi = m, m0 = m;
    for(int i = 2; i < sqrt(m0); i ++) {
        if(!(m0 % i)) phi = 1ll * phi * (i - 1) / i;
        while(!(m0 % i)) m0 /= i;
    }
    if(m0 ^ 1) phi = 1ll * phi * (m0 - 1) / m0;
    bool bgephi = 0;
    scanf("%s", sb);
    for(int i = 0; sb[i]; i ++) {
        if(bgephi) ((b *= 10) += sb[i] - '0') %= phi;
        else {
            (b *= 10) += sb[i] - '0';
            if(b >= phi) {
                b %= phi;
                bgephi = 1;
            }
        }
    }
    if(bgephi) b += phi;
    printf("%d", Pow(a, b));
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}