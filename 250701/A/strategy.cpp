#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// inline char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
inline char gc() {return getchar();}
template<typename T>
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
inline T read() {return readnum<T>();}
char wc[50]; int top;
template<typename T>
inline void writenum(T x, char sp){
    if(!x) return putchar('0'), void(putchar(sp));
    if(x < 0) putchar('-'), x = ~x + 1;
    top = 0;
    for(; x; x /= 10) wc[top ++] = x % 10 ^ 48;
    while(top --) putchar(wc[top]);
    putchar(sp);
}
template<typename T = int>
inline void write(T x, char sp = '\n'){
    writenum(x, sp);
}
}
using FastIO::read;
using FastIO::write;
typedef long long ll;
const int N = 3e5 + 10;
namespace work {
int n, m;
ll np;
inline ll move1(ll i) {
    return 2 * i - 1;
}
inline ll move2(ll i) {
    return np * np - (i - 1) * (i - 1);
}
ll pos[N];
ll sum;
struct data {
    ll sum, cnt;
} d1[N], d2[N];
ll bsans1(ll x) {
    ll l = np + 1, r = 0;
    while(l - 1 > r) {
        ll mid = l + r >> 1;
        if(d1[mid].sum <= x) l = mid;
        else r = mid;
    }
    return l;
}
ll bsans2(ll x) {
    ll l = np + 1, r = 0;
    while(l - 1 > r) {
        ll mid = l + r >> 1;
        if(d2[mid].sum <= x) l = mid;
        else r = mid;
    }
    return l;
}
ll ceilsqrt(ll x) {
    ll l = 0, r = N;
    while(l + 1 < r) {
        ll mid = l + r >> 1;
        if(mid * mid >= x) r = mid;
        else l = mid; 
    }
    return r;
}
int Main() {
    n = read(), m = read();
    for(int i = 1; i <= n; i ++) {
        int cur = read();
        if(cur)
            pos[++ np] = i;
        sum += np * np;
    }
    for(int i = np; i; i --) {
        ll dis = (n - np + i) - pos[i];
        d1[i].cnt = d1[i + 1].cnt + dis;
        d1[i].sum = d1[i + 1].sum + dis * move1(i);
    }
    for(int i = np; i; i --) {
        ll dis = pos[i] - pos[i - 1] - 1;
        d2[i].cnt = d2[i + 1].cnt + dis * (np - i + 1);
        d2[i].sum = d2[i + 1].sum + dis * move2(i);
    }
    for(ll op, x, tgt, ans; m --;) {
        op = read<ll>(), x = read<ll>();
        if(op == 1) {
            tgt = sum - x;
            if(tgt <= 0) {
                write(0);
                continue;
            }
            ll tmp = bsans1(tgt);
            if(tmp == 1) {
                if(d1[1].sum == tgt) write<ll>(d1[1].cnt);
                else write(-1);
                continue;
            }
            ans = d1[tmp].cnt, tgt -= d1[tmp].sum;
            ans += tgt / move1(tmp - 1), tgt %= move1(tmp - 1);
            if(tgt) ans ++;
            write<ll>(ans);
        }
        else {
            tgt = x - sum;
            if(tgt <= 0) {
                write(0);
                continue;
            }
            ll tmp = bsans2(tgt);
            if(tmp == 1) {
                if(d2[1].sum == tgt) write<ll>(d2[1].cnt);
                else write(-1);
                continue;
            }
            ans = d2[tmp].cnt, tgt -= d2[tmp].sum;
            ans += tgt / move2(tmp - 1) * (np - tmp + 2), tgt %= move2(tmp - 1);
            if(tgt)
                ans += ceilsqrt((tmp - 2) * (tmp - 2) + tgt) - tmp + 2;
            write<ll>(ans);
        }
    }
    return 0;
}
}
int main() {
    #ifndef db
    freopen("strategy.in", "r", stdin);
    freopen("strategy.out", "w", stdout);
    #endif
    return work::Main();
}