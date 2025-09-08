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
int n, m;
struct node {
    int delt, val;
    bool operator < (const node &obj) const {
        return val < obj.val;
    }
} a[N];
ll ans[N];
namespace bit {
    int tr[N], res;
    inline int lowbit(int x) {return x & -x;}
    inline void init() {memset(tr, 0, n + 1 << 2);}
    inline void add(int x, int v) {for(; x <= n; x += lowbit(x)) tr[x] += v;}
    inline int query(int x) {for(res = 0; x; x -= lowbit(x)) res += tr[x]; return res;}
}
void solve(int l, int r) {
    if(l == r) return;
    int mid = l + r >> 1, i, j;
    solve(l, mid), solve(mid + 1, r);
    sort(a + l, a + mid + 1), sort(a + mid + 1, a + r + 1);
    for(i = l, j = mid + 1; i <= mid; i ++) {
        while(j <= r && a[j].val < a[i].val) bit::add(a[j ++].delt, 1);
        ans[a[i].delt] += j - mid - 1 - bit::query(a[i].delt);
    }
    for(int k = mid + 1; k < j; k ++) bit::add(a[k].delt, -1);
    for(i = r, j = mid; i ^ mid; i --) {
        while(j >= l && a[j].val > a[i].val) bit::add(a[j --].delt, 1);
        ans[a[i].delt] += mid - j - bit::query(a[i].delt);
    }
    for(int k = j + 1; k <= mid; k ++) bit::add(a[k].delt, -1);
}
int re[N];
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= n; i ++) re[a[i].val = read()] = i, a[i].delt = m + 1;
    for(int i = 1; i <= m; i ++) a[re[read()]].delt = i;
    for(int i = 1; i <= n; i ++) ans[0] += i - 1 - bit::query(a[i].val), bit::add(a[i].val, 1);
    bit::init();
    solve(1, n);
    printf("%lld\n", ans[0]);
    for(int i = 1; i < m; i ++) {
        ans[i] = ans[i - 1] - ans[i];
        printf("%lld\n", ans[i]);
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}