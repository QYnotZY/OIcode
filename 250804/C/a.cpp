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
const int N = 2e5 + 1000, B = 500;
int n, m;
inline int Block(int i) {return (i - 1) / B + 1;}
inline int Left(int i) {return (i - 1) * B + 1;}
inline int Right(int i) {return min(n, i * B);}
int maxt;
int tagt;
ll cura[N];
ll kill[N << 1];
struct tower {
    ll c, r;
} a[N];
struct monster {
    int t; ll h;
} b[N];
ll ans;
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++)
        cura[i] = a[i].c = read(), a[i].r = read();
    m = read();
    for(int i = 1; i <= m; i ++)
        maxt = max(maxt, b[i].t = read()), b[i].h = read<ll>();
    ll tmpdiv, tmpmod;
    for(int i = 1; i <= Block(n); i ++) {
        memset(kill, 0, maxt + 1 << 3);
        for(int j = Left(i); j <= Right(i); j ++) {
            if(!a[j].r) continue;
            tmpdiv = a[j].c / a[j].r, tmpmod = a[j].c - tmpdiv * a[j].r;
            kill[1] += a[j].r;
            if(tmpdiv > maxt) continue;
            kill[tmpdiv + 1] += tmpmod - a[j].r;
            kill[tmpdiv + 2] -= tmpmod;
        }
        for(int j = 1; j <= maxt; j ++) kill[j] += kill[j - 1];
        for(int j = 1; j <= maxt; j ++) kill[j] += kill[j - 1];
        tagt = 0;
        for(int j = 1; j <= m; j ++) {
            if(!b[j].h) continue;
            if(tagt >= 0) {
                for(int k = Left(i); k <= Right(i); k ++) {
                    cura[k] = min(a[k].c, cura[k] + (b[j].t - tagt) * a[k].r);
                    if(b[j].h <= cura[k]) {
                        cura[k] -= b[j].h;
                        b[j].h = 0;
                    } else {
                        b[j].h -= cura[k];
                        cura[k] = 0;
                    }
                }
                if(b[j].h) tagt = -b[j].t;
                else tagt = b[j].t;
            } else {
                if(b[j].h <= kill[b[j].t + tagt]) {
                    for(int k = Left(i); k <= Right(i); k ++) {
                        cura[k] = min(a[k].c, (b[j].t + tagt) * a[k].r);
                        if(b[j].h <= cura[k]) {
                            cura[k] -= b[j].h;
                            b[j].h = 0;
                        } else {
                            b[j].h -= cura[k];
                            cura[k] = 0;
                        }
                    }
                    tagt = b[j].t;
                }
                else b[j].h -= kill[b[j].t + tagt], tagt = -b[j].t;
            }
        }
    }
    for(int i = 1; i <= m; i ++) ans += b[i].h;
    printf("%lld", ans);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}