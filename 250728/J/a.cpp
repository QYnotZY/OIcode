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
mt19937_64 rnd(time(0) ^ 998244353);
int n, q, a[N], op[N], x[N], y[N], z[N];
const int cnt = 25; const ll V = 3e12;
struct BIT {
    ll tr[N];
    inline int lowbit(int x) {return x & -x;}
    void add(int x, ll v) {for(; x <= n; x += lowbit(x)) tr[x] += v;}
    ll query(int x) {
        ll res = 0;
        for(; x; x -= lowbit(x)) res += tr[x];
        return res;
    }
} tr[cnt + 1];
ll w[N << 1][cnt + 1];
int num[N << 1], tot;
void disc() {
    sort(num + 1, num + tot + 1);
    tot = unique(num + 1, num + tot + 1) - num;
    for(int i = 1; i <= n; i ++) a[i] = lower_bound(num + 1, num + tot + 1, a[i]) - num;
    for(int i = 1; i <= q; i ++) if(op[i] == 1) y[i] = lower_bound(num + 1, num + tot + 1, y[i]) - num;
    for(int i = 1; i <= tot; i ++)
        for(int j = 1; j <= cnt; j ++)
            w[i][j] = rnd() % V;
}
void Hutao() {
    n = read(), q = read();
    for(int i = 1; i <= n; i ++) {
        a[i] = read();
        num[i] = a[i];
    }
    tot = n;
    for(int i = 1; i <= q; i ++) {
        op[i] = read(); x[i] = read(); y[i] = read();
        if(op[i] == 2) z[i] = read();
        else num[++ tot] = y[i];
    }
    disc();
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= cnt; j ++)
            tr[j].add(i, w[a[i]][j]);
    for(int i = 1; i <= q; i ++) {
        if(op[i] == 1) {
            for(int j = 1; j <= cnt; j ++) {
                ll tmp = w[y[i]][j] - w[a[x[i]]][j];
                tr[j].add(x[i], tmp);
            }
            a[x[i]] = y[i];
        } else {
            bool ans = 1;
            for(int j = 1; j <= cnt; j ++) {
                if((tr[j].query(y[i]) - tr[j].query(x[i] - 1)) % ll(z[i])) {
                    ans = 0;
                    break;
                }
            }
            printf(ans ? "YES\n" : "NO\n");
        }
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}