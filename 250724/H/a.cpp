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
inline ll gcd(ll x, ll y) {return y ? gcd(y, x % y) : x;}
const int N = 5e4 + 10;
int n, q, b1;
int a[N];
struct QRY {
    int l, r, id;
    bool operator < (QRY obj) {
        if(l / b1 == obj.l / b1)
            return l / b1 & 1 ? r > obj.r : r < obj.r;
        return l / b1 < obj.l / b1;
    }
} qry[N];
ll ans[N], sum[N];
ll res, cnt[N];
void move(int pos, int typ) {
    res -= cnt[a[pos]] * (cnt[a[pos]] - 1) >> 1;
    cnt[a[pos]] += typ;
    res += cnt[a[pos]] * (cnt[a[pos]] - 1) >> 1;
}
void Hutao() {
    n = read(), q = read(), b1 = int(1.0 * n / pow(q, 0.5) + 1e-6);
    for(int i = 1; i <= n; i ++) a[i] = read();
    for(int i = 1; i <= q; i ++) {
        qry[i].l = read(), qry[i].r = read(), qry[i].id = i;
    }
    sort(qry + 1, qry + q + 1);
    int l = 1, r = 1; move(1, 1);
    for(int i = 1; i <= q; i ++) {
        while(qry[i].l < l) move(-- l, 1);
        while(r < qry[i].r) move(++ r, 1);
        while(l < qry[i].l) move(l ++, -1);
        while(qry[i].r < r) move(r --, -1);
        ans[qry[i].id] = res;
        sum[qry[i].id] = 1ll * (r - l + 1) * (r - l) >> 1;
    }
    for(int i = 1; i <= q; i ++) {
        if(ans[i] == 0) printf("0/1\n");
        else printf("%lld/%lld\n", ans[i] / gcd(ans[i], sum[i]), sum[i] / gcd(ans[i], sum[i]));
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}