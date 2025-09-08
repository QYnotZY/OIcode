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
const int N = 2e5 + 1000, sqN = 505, V = 105;
int n, b1;
int a[N];
int hd[sqN][V], tl[sqN][V], nxt[N], able[N];
inline int block(int i) {return (i + b1 - 1) / b1;}
inline int left(int i) {return b1 * (i - 1) + 1;}
inline int right(int i) {return b1 * i;}
void pushdown(int bid) {
    if(!able[bid]) return;
    able[bid] = 0;
    for(int i = 1; i <= 100; i ++)
        for(int j = hd[bid][i]; j; j = nxt[j])
            a[j] = i;
}
void pushup(int bid) {
    if(able[bid]) return;
    able[bid] = 1;
    for(int i = 1; i <= 100; i ++) hd[bid][i] = tl[bid][i] = 0;
    for(int i = left(bid); i <= right(bid) && i <= n; i ++) {
        nxt[i] = hd[bid][a[i]];
        hd[bid][a[i]] = i;
        if(!tl[bid][a[i]]) tl[bid][a[i]] = i;
    }
}
void splice(int bid, int x, int y) {
    if(!tl[bid][x]) return;
    if(!tl[bid][y]) {
        hd[bid][y] = hd[bid][x], tl[bid][y] = tl[bid][x];
        hd[bid][x] = tl[bid][x] = 0;
        return;
    }
    nxt[tl[bid][y]] = hd[bid][x];
    tl[bid][y] = tl[bid][x];
    hd[bid][x] = tl[bid][x] = 0;
}
void build() {
    int nbid = block(n);
    for(int i = 1; i <= nbid; i ++) pushup(i);
}
void modify(int l, int r, int x, int y) {
    int lbid = block(l), rbid = block(r);
    pushdown(lbid), pushdown(rbid);
    for(int i = l; i <= right(lbid) && i <= r; i ++)
        if(a[i] == x) a[i] = y;
    for(int i = lbid + 1; i < rbid; i ++)
        splice(i, x, y);
    if(lbid ^ rbid) for(int i = left(rbid); i <= r; i ++)
        if(a[i] == x) a[i] = y;
    pushup(lbid), pushup(rbid);
}
void query() {
    int nbid = block(n);
    for(int i = 1; i <= nbid; i ++) pushdown(i);
}
void Hutao() {
    n = read(); b1 = sqrt(n) + 1;
    for(int i = 1; i <= n; i ++) a[i] = read();
    build();
    int q = read();
    for(; q --;) {
        int l = read(), r = read(), x = read(), y = read();
        if(x ^ y) modify(l, r, x, y);
    }
    query();
    for(int i = 1; i <= n; i ++) printf("%d ", a[i]);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}