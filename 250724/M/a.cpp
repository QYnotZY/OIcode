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
const int N = 2e5 + 1000;
int n, m, b1;
int a[N];
int cnt[N], to[N];
inline int block(int i) {return (i + b1 - 1) / b1;}
inline int left(int i) {return (i - 1) * b1 + 1;}
inline int right(int i) {return i * b1;}
void pushup(int bid) {
    for(int i = min(n, right(bid)); i >= left(bid); -- i) {
        if(i + a[i] > min(right(bid), n)) cnt[i] = 1, to[i] = i + a[i];
        else cnt[i] = cnt[i + a[i]] + 1, to[i] = to[i + a[i]];
    }
}
void build() {
    for(int i = block(n); i; -- i) pushup(i);
}
void update(int x, int y) {
    a[x] = y;
    pushup(block(x));
}
int query(int x) {
    int res = 0;
    while(x <= n) {
        res += cnt[x];
        x = to[x];
    }
    return res;
}
void Hutao() {
    n = read(); b1 = sqrt(n) + 1;
    for(int i = 1; i <= n; i ++) a[i] = read();
    build();
    m = read();
    for(int i = 1; i <= m; i ++) {
        int op = read();
        if(op == 1) {
            int x = read() + 1;
            printf("%d\n", query(x));
        } else {
            int x = read() + 1, y = read();
            update(x, y);
        }
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}