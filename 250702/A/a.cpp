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
const int N = 5e5 + 10;
namespace work {
int n;
int a[N];
vector<int> to[N];
int fa[N];
int ans[N];
void dfs(int u, int f) {
    fa[u] = f;
    set<int> s;
    for(auto v : to[u]) {
        if(v == f) continue;
        if(a[v] == a[u]) ans[a[v]] = 1;
        if(a[v] == a[fa[u]]) ans[a[v]] = 1;
        if(s.find(a[v]) != s.end()) ans[a[v]] = 1;
        else s.insert(a[v]);
        dfs(v, u);
    }
}
void solve() {
    n = read();
    for(int i = 1; i <= n; i ++) {
        a[i] = read();
        vector<int> ().swap(to[i]);
        ans[i] = 0;
    }
    for(int i = 1; i < n; i ++) {
        int u = read(), v = read();
        to[u].emplace_back(v);
        to[v].emplace_back(u);
    }
    dfs(1, 0);
    for(int i = 1; i <= n; i ++)
        printf("%d", ans[i]);
    printf("\n");
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