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
namespace SAsort {
    int sa[N], sa0[N], rk[N], rk0[N << 1], ad[N];
    int buc[N];
    void sort(int n, char *s) {
        int m = 127, cnt = 0;
        for(int i = 1; i <= n; i ++) buc[rk[i] = s[i]] ++;
        for(int i = 1; i <= m; i ++) buc[i] += buc[i - 1];
        for(int i = n; i; i --) sa[buc[s[i]] --] = i;

        for(int w = 1; ; w <<= 1, m = cnt, cnt = 0) {
            #ifdef db
            for(int i = 1; i <= n; i ++)
                printf("%d ", SAsort::sa[i]);
            printf("\n");
            #endif
            for(int i = n; i + w > n; i --) sa0[++ cnt] = i;
            for(int i = 1; i <= n; i ++) if(sa[i] - w > 0) sa0[++ cnt] = sa[i] - w;

            for(int i = 1; i <= m; i ++) buc[i] = 0;
            for(int i = 1; i <= n; i ++) ++ buc[ad[i] = rk[sa0[i]]];
            for(int i = 1; i <= m; i ++) buc[i] += buc[i - 1];
            for(int i = n; i; i --) sa[buc[ad[i]] --] = sa0[i];

            cnt = 0; for(int i = 1; i <= n; i ++) rk0[i] = rk[i];
            for(int i = 1; i <= n; i ++)
                rk[sa[i]] = rk0[sa[i]] == rk0[sa[i - 1]] && rk0[sa[i] + w] == rk0[sa[i - 1] + w] ? cnt : ++ cnt;
            if(cnt == n) return;
        }
    }
}
char s[N];
int n;
void Hutao() {
    scanf("%s", s + 1); n = strlen(s + 1);
    SAsort::sort(n, s);
    for(int i = 1; i <= n; i ++)
        printf("%d ", SAsort::sa[i]);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}