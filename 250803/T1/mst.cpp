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
const int N = 1e5 + 10, M = 1e6 + 10;
int n, m;
int ans[M];
namespace dsu {
    int fa[N];
    vector<pair<int, int> > e[N];
    void init(int n) {
        for(int i = 1; i <= n; i ++) fa[i] = i;
    }
    void insert(int id, int u, int v) {
        e[u].push_back(make_pair(v, id));
        e[v].push_back(make_pair(u, id));
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    void merge(int x, int y, int w) {
        x = find(x), y = find(y);
        if(e[x].size() < e[y].size()) swap(x, y);
        for(auto &ele : e[y]) {
            int &v = ele.first, &id = ele.second;
            if(~ans[id] || find(v) == y) continue;
            if(find(v) == x) {
                ans[id] = w;
            } else {
                e[x].push_back(ele);
            }
        }
        fa[y] = x;
    }
}
struct edge {
    int u, v, w;
    bool operator < (edge obj) {
        return w < obj.w;
    }
} e[M];
void Hutao() {
    #ifdef db
    clock_t start=clock();
    #endif
    n = read();
    dsu::init(n);
    m = read();
    memset(ans + 1, -1, m << 2);
    for(int i = 1; i <= m; i ++) {
        e[i].u = read(), e[i].v = read(), e[i].w = read();
        dsu::insert(i, e[i].u, e[i].v);
    }
    sort(e + 1, e + m + 1);
    for(int i = 1, cnt = 0; cnt < n - 1; i ++) {
        if(dsu::same(e[i].u, e[i].v)) continue;
        cnt ++;
        dsu::merge(e[i].u, e[i].v, e[i].w);
    }
    for(int i = 1; i <= m; i ++)
        printf("%d\n", ans[i]);
    #ifdef db
    clock_t end=clock();
    cerr<<(double)(end-start)/CLOCKS_PER_SEC*1000<<"ms\n";
    #endif
}
}
int main() {
    freopen("mst.in", "r", stdin);
    freopen("mst.out", "w", stdout);
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}