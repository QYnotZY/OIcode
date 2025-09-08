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
const int N = 2e5 + 10;
int n, q;
char s0[N]; int lst[128]; int s1[N];
int pos0[N][27];
int sa[N], rk[N], ht[N], sa0[N], rk0[N << 1], ad[N];
int cnt[N];
void get_sa() {
    memset(rk0, -1, sizeof rk0);
    int m = n;
    for(int i = 1; i <= n; i ++) cnt[rk[i] = s1[i]] ++;
    for(int i = 1; i <= m; i ++) cnt[i] += cnt[i - 1];
    for(int i = n; i; i --) sa[cnt[rk[i]] --] = i;

    for(int w = 1, p = 0; ; w <<= 1, m = p, p = 0) {
        for(int i = n; i ^ n - w; -- i) sa0[++ p] = i;
        for(int i = 1; i <= n; i ++) if(sa[i] > w) sa0[++ p] = sa[i] - w;

        memset(cnt, 0, m + 1 << 2);
        for(int i = 1; i <= n; i ++) ++ cnt[ad[i] = rk[sa0[i]]];
        for(int i = 1; i <= m; i ++) cnt[i] += cnt[i - 1];
        for(int i = n; i; i --) sa[cnt[ad[i]] --] = sa0[i];

        p = 0; memcpy(rk0, rk, n + 1 << 2);
        for(int i = 1; i <= n; i ++) {
            if(i == 1 || rk0[sa[i]] != rk0[sa[i - 1]] || rk0[sa[i] + w] != rk0[sa[i - 1] + w]) ++ p;
            rk[sa[i]] = p;
        }
        if(p == n) break;
    }

    ht[1] = 0;
    for(int i = 1, cur = 0; i <= n; i ++) {
        if(rk[i] == 1) continue;
        for(cur = max(cur - 1, 0); s1[i + cur] == s1[sa[rk[i] - 1] + cur]; cur ++);
        ht[rk[i]] = cur;
    }
}
namespace st {
    int minn[20][N];
    inline int log2(int x) {int res = 0; while(x >>= 1) ++ res; return res;}
    void build() {
        for(int i = 1; i <= n; i ++) minn[0][i] = ht[i];
        for(int i = 1; i < 20; i ++)
            for(int j = 1; j <= n + 1 - (1 << i); j ++)
                minn[i][j] = min(minn[i - 1][j], minn[i - 1][j + (1 << i - 1)]);
    }
    int query(int l, int r) {
        int lg = log2(r - l + 1);
        return min(minn[lg][l], minn[lg][r + 1 - (1 << lg)]);
    }
}
int lcp1(int a, int b) {
    return a ^ b ? (rk[a] < rk[b] ? st::query(rk[a] + 1, rk[b]) : st::query(rk[b] + 1, rk[a])) : n - a + 1;
}
int lcp(int a, int b) {
    int i, j;
}
void Hutao() {
    n = read(), q = read();
    for(int i = 1; i <= n; i ++) {
        s0[i] = readch();
        if(lst[s0[i]]) s1[i] = i - lst[s0[i]];
        else s1[i] = 0;
        for(int j = lst[s0[i]] + 1; j <= i; j ++)
            pos0[j][s0[i] - 'a'] = i - j;
        lst[s0[i]] = i;
    }
    for(int i = 'a'; i <= 'z'; i ++)
        for(int j = lst[i] + 1; j <= n; j ++)
            pos0[j][s0[i] - 'a'] = n - j;
    s1[n + 1] = -1; 
    get_sa();
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}