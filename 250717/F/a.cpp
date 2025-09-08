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
int n, a[105];
ll sum;
int bas[31];
bool insert(int x) {
    for(int i = 30; ~i; -- i) {
        if(!(x >> i & 1)) continue;
        if(!bas[i]) {bas[i] = x; return true;}
        else x ^= bas[i];
    }
    return false;
}
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++) a[i] = read();
    sort(a + 1, a + n + 1, greater<int>());
    for(int i = 1; i <= n; i ++)
        if(!insert(a[i])) sum += a[i];
    printf("%lld", sum);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}