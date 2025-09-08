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
#define int ll
namespace work {
const int N = 1e5 + 10, mod = 2147483648;
inline int Mod(int a) {return (a % mod + mod) % mod;}
inline int Add(int a, int b) {return Mod(a + b);}
inline int Minus(int a, int b) {return Mod(a - b);}
inline int Mult(int a, int b) {return Mod(a * b);}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
int t, n[N], m[N], a[N];
int sz;
int p[N];
bool cmp(int x, int y) {
    return a[x] < a[y];
}
namespace bit {
    int tr[N];
    inline int lowbit(int x) {return x & -x;}
    void add(int x, int val) {
        for(; x <= sz; x += lowbit(x)) tr[x] = Add(tr[x], val);
    }
    int query(int x) {
        int res = 0;
        for(; x; x -= lowbit(x)) res = Add(res, tr[x]);
        return res;
    }
}
int cnt[N], sum[N], sig[N], mu[N];
int ps[N];
int cmps(int x, int y) {
    return sig[x] < sig[y];
}
bool isnp[N];
vector<int> pri;
void Euler(int n) {
    mu[1] = 1, cnt[1] = 0, sum[1] = 1, sig[1] = 1; ps[1] = 1;
    for(int i = 2; i <= n; i ++) {
        ps[i] = i;
        if(!isnp[i]) {
            pri.push_back(i);
            mu[i] = -1;
            cnt[i] = 1;
            sum[i] = i + 1;
            sig[i] = i + 1;
        }
        for(auto j : pri) {
            if(i * j > n) break;
            isnp[i * j] = 1;
            if(!(i % j)) {
                mu[i * j] = 0;
                cnt[i * j] = cnt[i] + 1;
                sum[i * j] = sum[i] + Pow(j, cnt[i * j]);
                sig[i * j] = sig[i] / sum[i] * sum[i * j];
                break;
            }
            mu[i * j] = -mu[i];
            cnt[i * j] = 1;
            sum[i * j] = j + 1;
            sig[i * j] = sig[i] * (j + 1);
        }
    }
    sort(ps + 1, ps + n + 1, cmps);
}
int ans[N];
void Hutao() {
    Euler(100000);
    t = read();
    for(int i = 1; i <= t; i ++)
        n[i] = read(), m[i] = read(), a[i] = read(), p[i] = i, sz = max(sz, min(n[i], m[i]));
    sort(p + 1, p + t + 1, cmp);
    for(int cur = 1, i = 1; i <= t; i ++) {
        while(sig[ps[cur]] <= a[p[i]]) {for(int i = ps[cur]; i <= sz; i += ps[cur]) bit::add(i, Mult(sig[ps[cur]], mu[i / ps[cur]])); ++ cur;}
        for(int l = 1, r; l <= min(n[p[i]], m[p[i]]); l = r + 1) {
            r = min(n[p[i]] / (n[p[i]] / l), m[p[i]] / (m[p[i]] / l));
            r = min(r, min(n[p[i]], m[p[i]]));
            ans[p[i]] = Add(ans[p[i]], Mult(Minus(bit::query(r), bit::query(l - 1)), Mult(n[p[i]] / l, m[p[i]] / l)));
        }
    }
    for(int i = 1; i <= t; i ++) 
        printf("%d\n", ans[i]);
}
}
signed main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}