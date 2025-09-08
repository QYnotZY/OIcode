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

const int N = 4e4 + 10;
int n, m, ans;
namespace llfs{
    int tot, head[N];
    struct edge{
        int to; int dis;
        int nxt;
    } e[N << 1];
    void init(){
        tot = 0;
        for(int i = 1; i <= n; i ++)
            head[i] = -1;
    }
    void add(int u, int v, int w){
        e[++ tot] = {v, w, head[u]};
        head[u] = tot;
    }
}
bool del[N];
#define iter(u, v, w) for(int ii = llfs::head[u], v = llfs::e[ii].to, w = llfs::e[ii].dis; ~ii; ii = llfs::e[ii].nxt, v = llfs::e[ii].to, w = llfs::e[ii].dis)
namespace fr{
    int sz[N], sumsz;
    pair<int, int> res;
    void dfs_findroot(int u, int f){
        sz[u] = 1;
        int maxv = 0;
        iter(u, v, w){
            if(del[v] || v != f) continue;
            dfs_findroot(v, u);
            maxv = max(maxv, sz[v]);
            sz[u] += sz[v];
        }
        maxv = max(maxv, sumsz - sz[u]);
        if(maxv < res.second) res.first = u, res.second = maxv;
    }
    int findroot(int u){
        res = make_pair(0, n);
        sumsz = sz[u] ? sz[u] : n;
        dfs_findroot(u, 0);
        return res.first;
    }
}
namespace cc{
    int dis[N], cnt, curdis[N];
    void getdis(int u, int f){
        curdis[++ cnt] = dis[u];
        iter(u, v, w){
            if(del[v] || v == f) continue;
            dis[v] = dis[u] + w;
            getdis(v, u);
        }
    }
    void calc(int u){
        del[u] = 1;
        dis[u] = curdis[cnt = 1] = 0;
        int tmp = 0;
        iter(u, v, w){
            if(del[v]) continue;
            int cnt0 = cnt;
            dis[v] = w;
            getdis(v, u);
            #ifdef db
            for(int i = cnt0 + 1; i <= cnt; i ++)
                printf("%d ", curdis[i]);
            #endif
            sort(curdis + cnt0 + 1, curdis + cnt + 1);
            for(int l = cnt0 + 1, r = cnt; l <= cnt; l ++){
                while(r <= cnt && curdis[l] + curdis[r] > m) -- r;
                tmp += max(r - l, 0);
            }
            #ifdef db
            printf(": %d\n", tmp);
            #endif
        }
        ans -= tmp;
        #ifdef db
        printf("ans : %d\n", ans);
        #endif
        sort(curdis + 1, curdis + cnt + 1);
        #ifdef db
        for(int i = 1; i <= cnt; i ++)
            printf("%d ", curdis[i]);
        printf(":\n");
        #endif
        for(int l = 1, r = cnt; l <= cnt; l ++){
            while(r > l && curdis[l] + curdis[r] > m) -- r;
            ans += max(r - l, 0);
            #ifdef db
            printf("%d ", ans);
            #endif
        }
        #ifdef db
        printf("\n");
        #endif
    }
}
void solve(int u){
    u = fr::findroot(u);
    #ifdef db
    printf("devide %d:\n", u);
    #endif
    cc::calc(u);
    iter(u, v, w){
        if(del[v]) continue;
        solve(v);
    }
}
int main(){
    n = read();
    llfs::init();
    for(int i = 1; i < n; i ++){
        int u = read(), v = read(), w = read();
        llfs::add(u, v, w), llfs::add(v, u, w);
    }
    m = read();
    solve(1);
    printf("%d", ans);
    return 0;
}
//bug:
//双指针写法
//找重心