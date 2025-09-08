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
const int N = 1e5 + 10;
int b1;
int n, a[N], q;
int lst[N], pre[N], nxt[N], maxp[N];
int l[N], r[N];
int ans[N];
int p1[N], p2[N];
bool cmp1(int x, int y) {
    return r[x] < r[y];
}
bool cmp2(int x, int y) {
    if(l[x] / b1 == l[y] / b1)
        return l[x] / b1 & 1 ? r[x] > r[y] : r[x] < r[y];
    return l[x] / b1 < l[y] / b1;
}
namespace bit{
    int tr[N];
    inline int lowbit(int x) {return x & -x;}
    void add(int x, int v) {
        while(x <= n) {
            tr[x] += v;
            x += lowbit(x);
        }
    }
    int query(int x) {
        int res = 0;
        while(x) {
            res += tr[x];
            x -= lowbit(x);
        }
        return res;
    }
}
void Furina() {
    for(int x = 1, i = 1; x <= n; x ++) {
        if(pre[x]) bit::add(pre[x], -1);
        bit::add(x, 1);
        for(; i <= q && r[p1[i]] <= x; i ++)
            ans[p1[i]] = bit::query(x) - bit::query(l[p1[i]] - 1);
    }
}
int minn[N], maxx[N], cnt;
void Citlali() {
    int le = 1, ri = 1; minn[a[1]] = maxx[a[1]] = 1, cnt = 1;
    for(int i = 1; i <= q; i ++) {
        while(l[p2[i]] < le) {
            -- le;
            cnt -= minn[a[le]] ? int(maxp[minn[a[le]]] >= maxx[a[le]]) : 0;
            if(!minn[a[le]]) minn[a[le]] = maxx[a[le]] = le;
            else minn[a[le]] = le;
            cnt += minn[a[le]] ? int(maxp[minn[a[le]]] >= maxx[a[le]]) : 0;
        }
        while(ri < r[p2[i]]) {
            ++ ri;
            cnt -= minn[a[ri]] ? int(maxp[minn[a[ri]]] >= maxx[a[ri]]) : 0;
            if(!minn[a[ri]]) minn[a[ri]] = maxx[a[ri]] = ri;
            else maxx[a[ri]] = ri;
            cnt += minn[a[ri]] ? int(maxp[minn[a[ri]]] >= maxx[a[ri]]) : 0;
        }
        while(l[p2[i]] > le) {
            cnt -= minn[a[le]] ? int(maxp[minn[a[le]]] >= maxx[a[le]]) : 0;
            if(minn[a[le]] == maxx[a[le]]) minn[a[le]] = maxx[a[le]] = 0;
            else minn[a[le]] = nxt[le];
            cnt += minn[a[le]] ? int(maxp[minn[a[le]]] >= maxx[a[le]]) : 0;
            ++ le;
        }
        while(ri > r[p2[i]]) {
            cnt -= minn[a[ri]] ? int(maxp[minn[a[ri]]] >= maxx[a[ri]]) : 0;
            if(minn[a[ri]] == maxx[a[ri]]) minn[a[ri]] = maxx[a[ri]] = 0;
            else maxx[a[ri]] = pre[ri];
            cnt += minn[a[ri]] ? int(maxp[minn[a[ri]]] >= maxx[a[ri]]) : 0;
            -- ri;
        }
        if(!cnt) ++ ans[p2[i]];
    }
}
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++) {
        a[i] = read();
        pre[i] = lst[a[i]];
        if(lst[a[i]]) nxt[lst[a[i]]] = i;
        lst[a[i]] = i;
        
    }
    for(int i = n; i; i --) {
        if(!nxt[i]) maxp[i] = i;
        else if(nxt[i] - i == nxt[nxt[i]] - nxt[i]) maxp[i] = maxp[nxt[i]];
        else maxp[i] = nxt[i];
    }
    q = read();
    for(int i = 1; i <= q; i ++)
        l[i] = read(), r[i] = read(), p1[i] = p2[i] = i;
    b1 = int(1.0 * n / pow(q, 0.5) + 1e-6) + 1;
    sort(p1 + 1, p1 + q + 1, cmp1); Furina();
    sort(p2 + 1, p2 + q + 1, cmp2); Citlali();
    for(int i = 1; i <= q; i ++) printf("%d\n", ans[i]);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}