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
struct DSU {
    int n, fa[N];
    void init(int n) {
        this -> n = n;
        for(int i = 1; i <= n; i ++)
            fa[i] = i;
    }
    int find(int u) {
        return fa[u] == u ? u : fa[u] = find(fa[u]);
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }
    void merge(int u, int v) {
        fa[find(v)] = find(u);
    }
} dsu;
int n, m, cnt[N][11], rst[11];
int ans[N];
void solve() {
    n = read(), m = read();
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= 10; j ++)
            cnt[i][j] = 0;
    dsu.init(n);
    for(int i = 1; i <= m; i ++) {
        int a = read(), d = read(), k = read();
        cnt[a][d] = max(cnt[a][d], k);
    }
    for(int d = 1; d <= 10; d ++) {
        for(int i = 0; i < d; i ++) rst[i] = 0;
        for(int i = 1; i <= n; i ++) {
            if(rst[i % d]) {
                rst[i % d] --;
                if(!dsu.same(i, i - d)) dsu.merge(i, i - d);
            }
            if(cnt[i][d] > rst[i % d]) rst[i % d] = cnt[i][d];
        }
    }
    for(int i = 0; i <= n; i ++)
        ans[i] = 0;
    for(int i = 1; i <= n; i ++)
        ans[dsu.find(i)] = 1;
    for(int i = 1; i <= n; i ++)
        *ans += ans[i];
    write(*ans);
}
int Main() {
    int t = read();
    while(t --) solve();
    return 0;
}
}
int main() {
    return work::Main();
}