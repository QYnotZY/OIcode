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
typedef unsigned long long ull;
namespace work {
const int N = 808, N2 = 800 * 800 / 2 + 808, K = 304;
mt19937_64 my_rand(1145141);
int n, k;
struct node {
    int to, nxt;
} e[N << 1];
int tot, head[N];
inline void adde(int u, int v) {
    e[++ tot] = node{v, head[u]};
    head[u] = tot;
}
inline int id(int i, int j) {return (j * (j - 1) >> 1) + i;}
int ans[N2];
ull tag[N][N];
void dfs(int u, int f, int t, ull w) {
    tag[t][u] ^= w;
    for(int i = head[u]; ~i; i = e[i].nxt) {
        int &v = e[i].to;
        if(v == f) continue;
        dfs(v, u, t, w);
    }
}
void Hutao() {
    n = read(), k = read();
    for(int i = 1; i <= id(n, n); i ++) ans[i] = n;
    for(int i = 1, u, v; i <= k; i ++) {
        tot = 0; memset(head, -1, n + 1 << 2);
        for(int j = 1; j < n; j ++) {
            u = read(), v = read();
            adde(u, v), adde(v, u);
        }
        for(int u = 1; u <= n; u ++) {
            for(int i = head[u]; ~i; i = e[i].nxt) {
                ull w = my_rand();
                int &v = e[i].to;
                dfs(v, u, u, w);
            }
        }
    }
    for(int u = 1; u <= n; u ++) 
        for(int i = 1; i <= n; i ++)
            for(int j = i + 1; j <= n; j ++)
                if(u != i && u != j && tag[u][i] == tag[u][j])
                    ans[id(i, j)] --;
    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= n; j ++) {
            if(i == j) printf("1 ");
            else if(i < j) printf("%d ", ans[id(i, j)]);
            else printf("%d ", ans[id(j, i)]);
        }
        printf("\n");
    }
}
}
int main() {
    freopen("seert.in", "r", stdin);
    freopen("seert.out", "w", stdout);
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}