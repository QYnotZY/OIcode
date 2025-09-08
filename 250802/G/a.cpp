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
const int N = 40000, inf = 39989;
const double eps = 1e-5;
struct line {
    double k, b;
    line() {k = b = 0;}
    line(double k0, double b0) {k = k0; b = b0;}
    line(double x0, double y0, double x1, double y1) {
        if(x0 == x1) {k = 0; b = max(y0, y1); return;}
        k = (y1 - y0) / (x1 - x0);
        b = y0 - k * x0;
    }
    double f(double x) {
        return k * x + b;
    }
} ;
int cmp(double x, double y) {
    if(x - y > eps) return 1;
    if(y - x > eps) return -1;
    return 0;
}
namespace lcsmt {
    struct node {
        line l; int ans;
    } tr[N << 2];
    void spread(line f, int pos, int p, int l, int r) {
        if(l == r) {
            if(!tr[p].ans || cmp(f.f(l), tr[p].l.f(l)) == 1 || cmp(f.f(l), tr[p].l.f(l)) == 0 && pos < tr[p].ans) tr[p].l = f, tr[p].ans = pos;
            return;
        }
        if(!tr[p].ans) {
            tr[p].l = f, tr[p].ans = pos;
            return;
        }
        int mid = l + r >> 1;
        if(cmp(f.f(mid + 0.5), tr[p].l.f(mid + 0.5)) == 1) swap(f, tr[p].l), swap(tr[p].ans, pos);
        if(cmp(f.f(l), tr[p].l.f(l)) == 1 || cmp(f.f(l), tr[p].l.f(l)) == 0 && pos < tr[p].ans) spread(f, pos, p << 1, l, mid);
        if(cmp(f.f(r), tr[p].l.f(r)) == 1 || cmp(f.f(r), tr[p].l.f(r)) == 0 && pos < tr[p].ans) spread(f, pos, p << 1 | 1, mid + 1, r);
    }
    void build(int p = 1, int l = 1, int r = inf) {
        if(l == r) {
            tr[p].ans = 0;
            return;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
    }
    void update(line f, int pos, int ql, int qr, int p = 1, int l = 1, int r = inf) {
        if(ql <= l && r <= qr)
            return spread(f, pos, p, l, r);
        int mid = l + r >> 1;
        if(ql <= mid) update(f, pos, ql, qr, p << 1, l, mid);
        if(qr > mid) update(f, pos, ql, qr, p << 1 | 1, mid + 1, r);
    }
    int res; double val;
    void query(int x, int p = 1, int l = 1, int r = inf) {
        if(p == 1) res = 0;
        if(res == 0 || cmp(tr[p].l.f(x), val) == 1 || cmp(tr[p].l.f(x), val) == 0 && tr[p].ans < res) res = tr[p].ans, val = tr[p].l.f(x);
        if(l == r) return;
        int mid = l + r >> 1;
        if(x <= mid) query(x, p << 1, l, mid);
        else query(x, p << 1 | 1, mid + 1, r);
    }
}
int n;
void Hutao() {
    n = read();
    int op, x0, y0, x1, y1, cur = 0; int lstans = 0;
    for(int i = 1; i <= n; i ++) {
        op = read();
        if(op) {
            x0 = (read() + lstans - 1) % inf + 1, y0 = (read() + lstans - 1) % 1000000000 + 1;
            x1 = (read() + lstans - 1) % inf + 1, y1 = (read() + lstans - 1) % 1000000000 + 1;
            lcsmt::update(line(x0, y0, x1, y1), ++ cur, min(x0, x1), max(x0, x1));
        } else {
            x0 = (read() + lstans - 1) % inf + 1;
            lcsmt::query(x0);
            printf("%d\n", lstans = lcsmt::res);
        }
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}