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
const double eps = 1e-10;
int n, a[N];
double f1[N], f2[N];
int stk[N], top;
void Furina(int l, int r, int ql, int qr) {
    if(ql > qr) return;
    int qmid = ql + qr >> 1, mid;
    for(int i = l; i <= r && i <= qmid; i ++)
        if(f1[qmid] + eps < sqrt(qmid - i) + a[i]) {
            f1[qmid] = sqrt(qmid - i) + a[i];
            mid = i;
        }
    Furina(l, mid, ql, qmid - 1);
    Furina(mid, r, qmid + 1, qr);
}
void Citlali(int l, int r, int ql, int qr) {
    if(ql > qr) return;
    int qmid = ql + qr >> 1, mid;
    for(int i = r; i >= l && i >= qmid; i --)
        if(f2[qmid] + eps < sqrt(i - qmid) + a[i]) {
            f2[qmid] = sqrt(i - qmid) + a[i];
            mid = i;
        }
    Citlali(l, mid, ql, qmid - 1);
    Citlali(mid, r, qmid + 1, qr);
}
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    Furina(1, n, 1, n);
    Citlali(1, n, 1, n);
    for(int i = 1; i <= n; i ++)
        printf("%d\n", max((int)ceil(f1[i]), (int)ceil(f2[i])) - a[i]);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}