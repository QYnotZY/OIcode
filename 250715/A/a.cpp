#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// inline char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
inline char gc() {return getchar();}
template<typename T>
inline T readnum(){
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
template<typename T = int>
inline T read() {return readnum<T>();}
char wc[50]; int top;
template<typename T>
inline void writenum(T x, char sp){
    if(!x) return putchar('0'), void(putchar(sp));
    if(x < 0) putchar('-'), x = ~x + 1;
    top = 0;
    for(; x; x /= 10) wc[top ++] = x % 10 ^ 48;
    while(top --) putchar(wc[top]);
    putchar(sp);
}
template<typename T = int>
inline void write(T x, char sp = '\n'){
    writenum(x, sp);
}
}
using FastIO::read;
using FastIO::write;
typedef long long ll;
namespace work {
const int N = 5e5 + 10;
int n, k, a[N], b[N], t[N];
int pa[N], pb[N], rkal[N], rkar[N], rkbl[N], rkbr[N];
int cur;
ll ans;
bool cmpa(int x, int y) {
    return a[x] > a[y];
}
bool cmpb(int x, int y) {
    return b[x] < b[y];
}
struct maxab {
    int pos, val, t;
    bool operator < (const maxab &obj) const {return val > obj.val;}
} ;
struct minab {
    int pos, val, t;
    bool operator < (const minab &obj) const {return val < obj.val;}
} ;
priority_queue<maxab> qmax;
priority_queue<minab> qmin;
void Hutao() {
    n = read(), k = read();    
    for(int i = 1; i <= n; i ++) {
        a[i] = read(); t[i] = 0;
        pa[i] = i, pb[i] = i;
    }
    
    for(int i = 1; i <= n; i ++) {
        b[i] = read(); ans += abs(a[i] - b[i]);
    }
    if(n == 2) {
        if(k & 1) {
            write(abs(a[1] - b[2]) + abs(a[2] - b[1]));
            return;
        }
        write(abs(a[1] - b[1]) + abs(a[2] - b[2]));
        return;
    }
    sort(pa + 1, pa + n + 1, cmpa);
    sort(pb + 1, pb + n + 1, cmpb);
    for(int i = 1, j = 1; i <= n; i = j) {
        while(j <= n && a[pa[j]] == a[pa[i]]) j ++;
        for(int k = i; k < j; k ++) {
            rkal[pa[k]] = i, rkar[pa[k]] = j - 1;
        }
    }
    for(int i = 1, j = 1; i <= n; i = j) {
        while(j <= n && b[pb[j]] == b[pb[i]]) j ++;
        for(int k = i; k < j; k ++) {
            rkbl[pb[k]] = i, rkbr[pb[k]] = j - 1;
        }
    }
    for(int i = 1; i <= n; i ++) {
        if(max(rkal[i], rkbl[i]) <= min(rkar[i], rkbr[i])) continue;
        qmax.push({i, max(a[i], b[i]), 0});
        qmin.push({i, min(a[i], b[i]), 0});
    }
    for(cur = 1; cur <= k; cur ++) {
        if(qmax.size() == 0 || qmin.size() == 0) break;
        maxab m1 = qmax.top(); qmax.pop();
        minab m2 = qmin.top(); qmin.pop();
        while(qmax.size() && m1.t < t[m1.pos]) {m1 = qmax.top(); qmax.pop();}
        while(qmin.size() && m2.t < t[m2.pos]) {m2 = qmin.top(); qmin.pop();}
        if(qmax.size() == 0 || qmin.size() == 0) break;
        if(m2.val - m1.val <= 0) break;
// printf("%d %d\n", m1.pos, m2.pos);
        ans += m2.val - m1.val << 1;
        swap(a[m1.pos], a[m2.pos]);
        swap(rkal[m1.pos], rkal[m2.pos]);
        swap(rkar[m1.pos], rkar[m2.pos]);
// printf("%d %d %d %d\n", rkal[m1.pos], rkar[m1.pos], rkbl[m1.pos], rkbr[m1.pos]);
        if(max(rkal[m1.pos], rkbl[m1.pos]) <= min(rkar[m1.pos], rkbr[m1.pos])) t[m1.pos] = k + 1;
        else t[m1.pos] = cur, qmax.push({m1.pos, max(a[m1.pos], b[m1.pos]), t[m1.pos]}), qmin.push({m1.pos, min(a[m1.pos], b[m1.pos]), t[m1.pos]});
// printf("%d %d %d %d\n", rkal[m2.pos], rkar[m2.pos], rkbl[m2.pos], rkbr[m2.pos]);
        if(max(rkal[m2.pos], rkbl[m2.pos]) <= min(rkar[m2.pos], rkbr[m2.pos])) t[m2.pos] = k + 1;
        else t[m2.pos] = cur, qmax.push({m2.pos, max(a[m2.pos], b[m2.pos]), t[m2.pos]}), qmin.push({m2.pos, min(a[m2.pos], b[m2.pos]), t[m2.pos]});
    }
    write(ans);
}
}
int main() {
    #ifndef db
    freopen("wap.in", "r", stdin);
    freopen("wap.out", "w", stdout);
    #endif
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}