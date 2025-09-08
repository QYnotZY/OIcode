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
int n, x, m, sg;
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++) {
        x = read(), m = read();
        if(x & 1) sg ^= x, ++ x, -- m;
        if(m & 1) sg ^= x + m - 1, -- m;
        if(m >> 1 & 1) sg ^= 1;
    }
    printf(sg ? "tolik" : "bolik");
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}