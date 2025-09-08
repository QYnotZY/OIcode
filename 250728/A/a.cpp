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
mt19937_64 rnd(time(0) ^ N);
ll mod = 817236541752384905ll;
inline ll Mod(ll a) {return (a % mod + mod) % mod;}
int n, a[N];
ll w[N], p[N], sum[N];
map<ll, int> buc;
namespace ST {
    int maxx[20][N], pos[20][N];
    inline int log2(int n) {int res = 0; while(n >>= 1) ++ res; return res;}
    void build() {
        for(int i = 1; i <= n; i ++) maxx[0][i] = a[i], pos[0][i] = i;
        for(int i = 1; i < 20; i ++)
            for(int j = 1; j <= n + 1 - (1 << i); j ++)
                if(maxx[i - 1][j] >= maxx[i - 1][j + (1 << i - 1)])
                    pos[i][j] = pos[i - 1][j], maxx[i][j] = maxx[i - 1][j];
                else
                    pos[i][j] = pos[i - 1][j + (1 << i - 1)], maxx[i][j] = maxx[i - 1][j + (1 << i - 1)];
    }
    int query_pos(int l, int r) {
        int lg = log2(r - l + 1);
        return maxx[lg][l] >= maxx[lg][r + 1 - (1 << lg)] ? pos[lg][l] : pos[lg][r + 1 - (1 << lg)];
    }
}
ll solve(int l, int r) {
    if(l > r) return 0;
    int mid = ST::query_pos(l, r);
    ll ans = solve(l, mid - 1) + solve(mid + 1, r);
    if(mid - l < r - mid) {
        for(int i = max(l, mid + 1 - a[mid]); i <= min(mid, r + 1 - a[mid]); i ++)
            if(Mod(sum[i + a[mid] - 1] - sum[i - 1]) == p[a[mid]]) ans ++;
    } else {
        for(int i = max(mid, l + a[mid] - 1); i <= min(r, mid - 1 + a[mid]); i ++)
            if(Mod(sum[i] - sum[i - a[mid]]) == p[a[mid]]) ans ++;
    }
    return ans;
}
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++) w[i] = Mod(rnd()), p[i] = Mod(p[i - 1] + w[i]);
    for(int i = 1; i <= n; i ++) {
        a[i] = read();
        sum[i] = Mod(sum[i - 1] + w[a[i]]);
    }
    ST::build();
    printf("%lld\n", solve(1, n));
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}