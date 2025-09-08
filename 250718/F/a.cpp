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
const int N = 3e5 + 10;
const ll inf = 2e18;
namespace SA {
    int sa[N], sa0[N], rk[N], rk0[N << 1], ad[N];
    int buc[N];
    void sort(int n, char *s) {
        int m = 127, cnt = 0;
        for(int i = 1; i <= n; i ++) buc[rk[i] = s[i]] ++;
        for(int i = 1; i <= m; i ++) buc[i] += buc[i - 1];
        for(int i = n; i; i --) sa[buc[s[i]] --] = i;

        for(int w = 1; ; w <<= 1, m = cnt, cnt = 0) {
            for(int i = n; i + w > n; i --) sa0[++ cnt] = i;
            for(int i = 1; i <= n; i ++) if(sa[i] - w > 0) sa0[++ cnt] = sa[i] - w;

            for(int i = 1; i <= m; i ++) buc[i] = 0;
            for(int i = 1; i <= n; i ++) ++ buc[ad[i] = rk[sa0[i]]];
            for(int i = 1; i <= m; i ++) buc[i] += buc[i - 1];
            for(int i = n; i; i --) sa[buc[ad[i]] --] = sa0[i];

            cnt = 0; for(int i = 1; i <= n; i ++) rk0[i] = rk[i];
            for(int i = 1; i <= n; i ++)
                rk[sa[i]] = rk0[sa[i]] == rk0[sa[i - 1]] && rk0[sa[i] + w] == rk0[sa[i - 1] + w] ? cnt : ++ cnt;
            if(cnt == n) return;
        }
    }
    int ht[N];
    void get_height(int n, char *s) {
        for(int i = 1, j = 0; i <= n; i ++) {
            j = max(j - 1, 0);
            while(s[i + j] == s[sa[rk[i] - 1] + j]) j ++;
            ht[rk[i]] = j;
        }
    }
}
int n, a[N];
char s[N];
int ad[4];
pair<ll, ll> curans;
namespace dsu {
    int fa[N], sz[N], max1[N], max2[N], min2[N], min1[N];
    void init(int n) {
        for(int i = 1; i <= n; i ++) {
            fa[i] = i, sz[i] = 1, max1[i] = min1[i] = a[i], max2[i] = int(-1e9), min2[i] = int(1e9);
        }
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if(u == v) return;
        if(sz[u] > 1) curans.first -= 1ll * sz[u] * (sz[u] - 1) >> 1;
        if(sz[v] > 1) curans.first -= 1ll * sz[v] * (sz[v] - 1) >> 1;
        fa[v] = u, sz[u] += sz[v];
        ad[0] = max1[u], ad[1] = max2[u], ad[2] = max1[v], ad[3] = max2[v];
        sort(ad, ad + 4);
        max1[u] = ad[3], max2[u] = ad[2];
        ad[0] = min1[u], ad[1] = min2[u], ad[2] = min1[v], ad[3] = min2[v];
        sort(ad, ad + 4);
        min1[u] = ad[0], min2[u] = ad[1];
        curans.first += 1ll * sz[u] * (sz[u] - 1) >> 1, curans.second = max(curans.second, max(1ll * max1[u] * max2[u], 1ll * min1[u] * min2[u]));
    }
}
vector<int> add[N];
pair<ll, ll> ans[N];
void Hutao() {
    curans = make_pair(0, -inf);
    scanf("%d%s", &n, s + 1);
    for(int i = 1; i <= n; i ++) scanf("%d", a + i);
    dsu::init(n);
    SA::sort(n, s);
    SA::get_height(n, s);
    for(int i = 2; i <= n; i ++)
        add[SA::ht[i]].push_back(i);
    for(int i = n - 1; ~i; i --) {
        for(auto ele : add[i])
            dsu::merge(SA::sa[ele - 1], SA::sa[ele]);
        ans[i] = curans;
    }
    for(int i = 0; i < n; i ++) 
        printf("%lld %lld\n", ans[i].first, ans[i].second == -inf ? 0 : ans[i].second);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}