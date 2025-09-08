#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
char gc() {return getchar();}
template<typename T = int>
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
T read() {return readnum<T>();}
}
using FastIO::read;
typedef long long ll;

const int N = 2e5 + 10, mod = 1e9 + 7;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
vector<int> e[N];
int n, m, lim;
int f[N];
void dfs(int u, int fa, int l, int f1, int f2){
    f[u] = Add(f[u], f1);
    for(auto v : e[u]){
        if(v == fa) continue;
        if(l < lim) dfs(v, u, l + 1, f2, Add(f1, f2));
    }
}
int main(){
    freopen("fibtree.in", "r", stdin);
    freopen("fibtree.out", "w", stdout);
    n = read(), m = read();
    for(int i = 1, u, v; i < n; i ++){
        u = read(), v = read();
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    for(int i = 1; i <= m; i ++){
        int op = read();
        if(op == 1){
            int u = read(); lim = read();
            int a = read(), b = read();
            dfs(u, 0, 0, a, b);
        }
        if(op == 2){
            int u = read();
            printf("%d\n", f[u]);
        }
    }
    return 0;
}