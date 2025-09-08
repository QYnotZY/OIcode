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
int n; char s[N];
int buc[N], sa[N], rk[N], sa0[N], rk0[N], ad[N];
void Hutao() {
    scanf("%d%s", &n, s);
    int m = 127, cnt = 0;
    for(int i = 0; i < 1 << n; i ++) ++ buc[rk[i] = s[i]];
    for(int i = 1; i <= m; i ++) buc[i] += buc[i - 1];
    for(int i = (1 << n) - 1; ~i; i --) sa[buc[rk[i]] --] = i;

    for(int w = 1; w < 1 << n; w <<= 1, m = cnt, cnt = 0) {
        for(int i = 1; i <= 1 << n; i ++) sa0[i] = sa[i] ^ w;

        for(int i = 0; i <= m; i ++) buc[i] = 0;
        for(int i = 1; i <= 1 << n; i ++) ++ buc[ad[i] = rk[sa0[i]]];
        for(int i = 1; i <= m; i ++) buc[i] += buc[i - 1];
        for(int i = 1 << n; i; i --) sa[buc[ad[i]] --] = sa0[i];

        for(int i = 0; i < 1 << n; i ++) rk0[i] = rk[i];

        for(int i = 1; i <= 1 << n; i ++) {
            if(rk0[sa[i]] ^ rk0[sa[i - 1]] || rk0[sa[i] ^ w] ^ rk0[sa[i - 1] ^ w]) ++ cnt;
            rk[sa[i]] = cnt;
        }
        if(cnt == 1 << n) break;
    }
    int e = sa[1];
    #ifdef db
    printf("%d\n", e);
    #endif
    for(int i = 0; i < 1 << n; i ++) putchar(s[i ^ e]);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}