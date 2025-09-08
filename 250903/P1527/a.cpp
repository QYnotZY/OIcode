#include "bits/stdc++.h"
using namespace std;
namespace FastIO {
    template <typename T = int> T read() {
        char ch = '\0'; bool f = 0; T res = 0;
        for(; !('0' <= ch && ch <= '9'); ch = getchar()) if(ch == '-') f = !f;
        for(; '0' <= ch && ch <= '9'; ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ '0');
        return f ? ~res + 1 : res;
    }
    char readch(const int acsp = 0) {
        char ch = '\0';
        for(; !(33 - acsp <= ch && ch < 127); ch = getchar()) ;
        return ch;
    }
} using FastIO::read; using FastIO::readch;
typedef long long ll;
namespace Qiuyu3600 {
const int N = 505, Q = 6e4 + 10;
int n, q;
struct VAL {
    int v, x, y;
    bool operator < (const VAL& obj) const {
        return v <= obj.v;
    }
} val[N * N];
namespace bit2 {
    int tr[N][N]; int res;
    inline int lowbit(int x) {return x & -x;}
    inline void init() {memset(tr, 0, sizeof(tr));}
    inline void add(int x, int y, int val) {for(; x <= n; x += lowbit(x)) for(int iy = y; iy <= n; iy += lowbit(iy)) tr[x][iy] += val;}
    inline int query(int x, int y) {for(res = 0; x; x -= lowbit(x)) for(int iy = y; iy; iy -= lowbit(iy)) res += tr[x][iy]; return res;}
}
struct QRY {
    int x1, y1, x2, y2, k;
} qry[Q];
int qmat(int x1, int y1, int x2, int y2) {
    return bit2::query(x2, y2) - bit2::query(x1 - 1, y2) - bit2::query(x2, y1 - 1) + bit2::query(x1 - 1, y1 - 1);
}
int p[Q], tmp[Q];
int ans[Q];
void solve(int l, int r, int ql, int qr) {
    if(ql > qr) return;
    if(l == r) {
        for(int i = ql; i <= qr; i ++)
            ans[p[i]] = val[r].v;
        return;
    }
    int mid = l + r >> 1;
    for(int i = l; i <= mid; i ++) bit2::add(val[i].x, val[i].y, 1);
    int tl = ql - 1, tr = qr + 1;
    for(int i = ql, qres; i <= qr; i ++) {
        qres = qmat(qry[p[i]].x1, qry[p[i]].y1, qry[p[i]].x2, qry[p[i]].y2);
        if(qres >= qry[p[i]].k) {
            tmp[++ tl] = p[i];
        } else {
            qry[p[i]].k -= qres;
            tmp[-- tr] = p[i];
        }
    }
    for(int i = ql; i <= qr; i ++) p[i] = tmp[i];
    for(int i = l; i <= mid; i ++) bit2::add(val[i].x, val[i].y, -1);
    solve(l, mid, ql, tl);
    solve(mid + 1, r, tr, qr);
}
void Hutao() {
    n = read(), q = read();
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            val[(i - 1) * n + j] = {read(), i, j};
    sort(val + 1, val + n * n + 1);
    for(int i = 1; i <= q; i ++) {
        qry[i] = {read(), read(), read(), read(), read()};
        p[i] = i;
    }
    solve(1, n * n, 1, q);
    for(int i = 1; i <= q; i ++) printf("%d\n", ans[i]);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}