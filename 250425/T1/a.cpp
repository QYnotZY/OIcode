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

const int N = 1010;
namespace sol{
void solve();
int Main(){
    int t = read();
    while(t --) solve();
    return 0;
}
namespace dsu{
    int fa[N], sz[N];
    void init(int n){
        for(int i = 1; i <= n; i ++){
            fa[i] = i;
            sz[i] = 1;
        }
    }
    int find(int x){
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    bool same(int u, int v){
        return find(u) == find(v);
    }
    int size(int u){
        return sz[find(u)];
    }
    void merge(int u, int v){
        if(same(u, v)) return;
        u = find(u), v = find(v);
        fa[v] = u; sz[u] += sz[v];
    }
}
int n;
bitset<N> vis;
int siz[N], cnt;
int ans;
void solve(){
    n = read();
    dsu::init(n);
    for(int i = 1; i <= n; i ++)
        vis[i] = 0;
    cnt = 0, ans = 0;
    for(int i = 1, x; i <= n; i ++)
        x = read(), dsu::merge(i, x);
    for(int i = 1; i <= n; i ++){
        if(vis[dsu::find(i)] == 0){
            vis[dsu::find(i)] = 1;
            siz[++ cnt] = dsu::size(i);
        }
    }
    sort(siz + 1, siz + cnt + 1, greater<int>());
    for(int i = cnt; i >= 0; -- i){
        if(siz[i] ^ 1){
            ans = cnt - i;
            break;
        }
    }
    for(int i = 1; i <= n; i ++){
        int x = 0, y = 0;
        for(int j = 1; j <= cnt; j ++){
            x += siz[j] / i;
            if(siz[j] / i) y += siz[j] % i;
        }
        #ifdef db
        printf("%d %d %d\n", i, x, y);
        #endif
        ans = max(ans, x * (i - 1) + y);
    }
    printf("%d\n", ans);
}
}
int main(){
    #ifndef db
    freopen("password.in", "r", stdin);
    freopen("password.out", "w", stdout);
    #endif
    return sol::Main();
}