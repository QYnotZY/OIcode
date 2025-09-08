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
const int N = 2e5 + 10;
namespace work {
int n, k, a[N]; ll ans;
vector<int> apos[N];
int lg[N], rg[N], ls[N], rs[N];
int stk[N], top;
int Main() {
    n = read(), k = read(), ans = 0;
    for(int i = 1; i <= n; i ++) {
        vector<int> ().swap(apos[i]);
    }
    top = 0;
    stk[top] = 0;
    for(int i = 1; i <= n; i ++) {
        a[i] = read();
        apos[a[i]].emplace_back(i);
        while(top && a[stk[top]] > a[i]) -- top;
        ls[i] = stk[top];
        stk[++ top] = i;
    }
    top = 0;
    for(int i = 1; i <= n; i ++) {
        while(top && a[stk[top]] <= a[i]) -- top;
        lg[i] = stk[top];
        stk[++ top] = i;
    }
    top = 0;
    stk[top] = n + 1;
    for(int i = n; i; i --) {
        while(top && a[stk[top]] >= a[i]) -- top;
        rs[i] = stk[top];
        stk[++ top] = i;
    }
    top = 0;
    for(int i = n; i; i --) {
        while(top && a[stk[top]] < a[i]) -- top;
        rg[i] = stk[top];
        stk[++ top] = i;
    }
    #ifdef db
    for(int i = 1; i <= n; i ++)
        printf("%d : %d %d %d %d\n", i, ls[i], rs[i], lg[i], rg[i]);
    #endif
    for(int i = max(1, k - n); i <= min(n, k - 1); i ++) {
        int sz1 = apos[i].size(), sz2 = apos[k - i].size();
        for(int j = 0, l = 0, r = 0, sum = 0; j < sz1; j ++) {
            int i1 = apos[i][j];
            while(l < sz2 && i1 >= apos[k - i][l]) sum -= rg[apos[k - i][l]] - apos[k - i][l], l ++;
            while(r < sz2 && rs[i1] > lg[apos[k - i][r]]) sum += rg[apos[k - i][r]] - apos[k - i][r], r ++;
            ans += ll(i1 - ls[i1]) * sum;
            #ifdef db
            printf("%d %d %d %d\n", i, j, l, r);
            #endif
        }
    }
    write<ll>(ans);
    return 0;
}
}
int main() {
    int t = read();
    while(t --) work::Main();
    return 0;
}