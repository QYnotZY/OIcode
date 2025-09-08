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
int n, k, a[N];
namespace smt {
    int tr[N << 2];
    void pushup(int p) {
        tr[p] = max(tr[p << 1], tr[p << 1 | 1]);
    }
    void build(int p = 1, int l = 1, int r = n) {
        if(l == r) return void(tr[p] = a[l]);
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int x, int v, int p = 1, int l = 1, int r = n) {
        if(l == r) return void(tr[p] = v);
        int mid = l + r >> 1;
        if(x <= mid) update(x, v, p << 1, l, mid);
        else update(x, v, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    int query_l(int v, int p, int l, int r) {
        if(l == r) return l;
        int mid = l + r >> 1;
        if(tr[p << 1 | 1] > v) return query_l(v, p << 1 | 1, mid + 1, r);
        else return query_l(v, p << 1, l, mid);
    }
    int queryl(int qr, int v, int p = 1, int l = 1, int r = n) {
        if(qr <= 0) return 0;
        if(r <= qr) return tr[p] > v ? query_l(v, p, l, r) : 0;
        int mid = l + r >> 1, tmp;
        if(qr > mid) {
            tmp = queryl(qr, v, p << 1 | 1, mid + 1, r);
            if(tmp) return tmp;
        }
        return queryl(qr, v, p << 1, l, mid);
    }
    int query_r(int v, int p, int l, int r) {
        if(l == r) return l;
        int mid = l + r >> 1;
        if(tr[p << 1] > v) return query_r(v, p << 1, l, mid);
        else return query_r(v, p << 1 | 1, mid + 1, r);
    }
    int queryr(int ql, int v, int p = 1, int l = 1, int r = n) {
        if(ql > n) return 0;
        if(ql <= l) return tr[p] > v ? query_r(v, p, l, r) : n + 1;
        int mid = l + r >> 1, tmp;
        if(ql <= mid) {
            tmp = queryr(ql, v, p << 1, l, mid);
            if(tmp ^ n + 1) return tmp;
        }
        return queryr(ql, v, p << 1 | 1, mid + 1, r);
    }
}
int f[N];
namespace ans {
    struct node {
        ll sum, tag, sz;
    } tr[N << 2];
    void pushup(int p) {
        tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
    }
    void upd1(int p, int v) {
        tr[p].sum += tr[p].sz * v;
        tr[p].tag += v;
    }
    void pushdown(int p) {
        upd1(p << 1, tr[p].tag);
        upd1(p << 1 | 1, tr[p].tag);
        tr[p].tag = 0;
    }
    void build(int p = 1, int l = 0, int r = n + 1) {
        tr[p].sz = r - l + 1; tr[p].tag = 0;
        if(l == r) return void(tr[p].sum = f[l]);
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int ql, int qr, int v, int p = 1, int l = 0, int r = n + 1) {
        if(ql > qr) return;
        if(ql <= l && r <= qr) return upd1(p, v);
        int mid = l + r >> 1;
        pushdown(p);
        if(ql <= mid) update(ql, qr, v, p << 1, l, mid);
        if(qr > mid) update(ql, qr, v, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    ll query(int ql, int qr, int p = 1, int l = 0, int r = n + 1) {
        if(ql <= l && r <= qr) return tr[p].sum;
        int mid = l + r >> 1; ll res = 0;
        pushdown(p);
        if(ql <= mid) res += query(ql, qr, p << 1, l, mid);
        if(qr > mid) res += query(ql, qr, p << 1 | 1, mid + 1, r);
        return res;
    }
}
inline int F(int i) {int x0 = smt::queryl(i - 1, a[i]), x1 = smt::queryr(i + 1, a[i]); return !x0 && !x1 ? 0 : 1 + max(ans::query(x0, x0), ans::query(x1, x1));}
int p[N];
bool cmp(int x, int y) {return a[x] > a[y];}
void Hutao() {
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i ++) scanf("%d", a + i), p[i] = i;
    sort(p + 1, p + n + 1, cmp);
    smt::build();
    f[0] = f[n + 1] = 0; int tmp = a[p[1]];
    for(int i = 1; i <= n; i ++)
        f[p[i]] = tmp == a[p[i]] ? 0 : 1 + max(f[smt::queryl(p[i] - 1, a[p[i]])], f[smt::queryr(p[i] + 1, a[p[i]])]);
    ans::build();
    int op, x, y;
    while(~scanf("%d", &op)) {
        if(op == 1) {
            x = read();
            if(a[x] < a[x + 1]) {
                y = smt::queryl(x - 1, a[x] - 1); if(a[y] != a[x]) ans::update(y + 1, x - 1, -1);
                y = smt::queryr(x + 2, a[x] - 1); if(a[y] != a[x]) ans::update(x + 2, y - 1, 1);
                ans::update(x, x, ans::query(x + 1, x + 1) - ans::query(x, x));
                swap(a[x], a[x + 1]), smt::update(x, a[x]), smt::update(x + 1, a[x + 1]);
                ans::update(x + 1, x + 1, F(x + 1) - ans::query(x + 1, x + 1));
            } else if(a[x] > a[x + 1]) {
                y = smt::queryl(x - 1, a[x + 1] - 1); if(a[y] != a[x + 1]) ans::update(y + 1, x - 1, 1);
                y = smt::queryr(x + 2, a[x + 1] - 1); if(a[y] != a[x + 1]) ans::update(x + 2, y - 1, -1);
                ans::update(x + 1, x + 1, ans::query(x, x) - ans::query(x + 1, x + 1));
                swap(a[x], a[x + 1]), smt::update(x, a[x]), smt::update(x + 1, a[x + 1]);
                ans::update(x, x, F(x) - ans::query(x, x));
            }
            #ifdef db
            for(int i = 1; i <= n; i ++) printf("%d ", ans::query(i, i)); printf("\n");
            #endif
        } else {
            x = read(), y = read();
            printf("%lld\n", 1ll * (y - x + 1) * (n - 1) + k * ans::query(x, y));
        }
    }
}
}
int main() {
    freopen("attack.in", "r", stdin);
    freopen("attack.out", "w", stdout);
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}