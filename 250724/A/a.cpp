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
const int N = 5e4 + 1000, sqN = 310;
int n, a[N];
ll sob[sqN], tag[sqN];
int b1;
inline int block(int i) {return (i + b1 - 1) / b1;}
inline int left(int bl) {return b1 * (bl - 1) + 1;}
inline int right(int bl) {return b1 * bl;}
void build() {
    int nbid = block(n);
    for(int i = 1; i <= nbid; i ++) {
        sob[i] = tag[i] = 0;
        for(int j = left(i); j <= right(i); j ++)
            sob[i] += a[j];
    }
}
void pushdown(int bid) {
    if(!tag[bid]) return;
    for(int i = left(bid); i <= right(bid); i ++)
        a[i] += tag[bid];
    tag[bid] = 0;
}
void modify(int l, int r, int ad) {
    int lbid = block(l), rbid = block(r);
    pushdown(lbid); pushdown(rbid);
    for(int i = l; i <= right(lbid) && i <= r; i ++) {
        a[i] += ad;
        sob[lbid] += ad;
    }
    for(int i = lbid + 1; i < rbid; i ++) {
        tag[i] += ad;
        sob[i] += ad * b1;
    }
    if(lbid ^ rbid) for(int i = left(rbid); i <= r; i ++) {
        a[i] += ad;
        sob[rbid] += ad;
    }
}
ll query(int l, int r) {
    int lbid = block(l), rbid = block(r);
    ll res = 0;
    pushdown(lbid), pushdown(rbid);
    for(int i = l; i <= right(lbid) && i <= r; i ++) {
        res += a[i];
    }
    for(int i = lbid + 1; i < rbid; i ++) {
        res += sob[i];
    }
    if(lbid ^ rbid) for(int i = left(rbid); i <= r; i ++) {
        res += a[i];
    }
    return res;
}
void Hutao() {
    n = read();
    b1 = sqrt(n) + 1;
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    build();
    for(int i = 1; i <= n; i ++) {
        int op = read(), l = read(), r = read(), c = read();
        if(op == 0) {
            modify(l, r, c);
        } else {
            printf("%lld\n", query(l, r) % (c + 1));
        }
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}