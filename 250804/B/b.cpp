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
char s[N];
void Hutao() {
    scanf("%s", s);
    int cnt = 0, sum = 0, ans = 0;
    for(int i = 2; s[i]; i ++) {
        if(s[i - 2] == 'A' && s[i - 1] == 'B' && s[i] == 'C') cnt ++, sum ++;
        if(s[i - 2] == 'C' && s[i - 1] == 'B' && s[i] == 'A') sum --;
        if(sum < 0) sum = 0;
        ans = max(sum, ans);
    }
    printf("%d", cnt - ans);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}