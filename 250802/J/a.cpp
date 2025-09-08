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
int n, m, a[N];
ll div(ll a, ll b) {if(b < 0) a = -a, b = -b; return a < 0 ? (a - b + 1) / b : a / b;}
namespace smtb {
    struct node {
        ll sz, minn, maxx;
        ll tag1, sum;
    } tr[N << 2];
    void pushup(int p) {
        tr[p].minn = min(tr[p << 1].minn, tr[p << 1 | 1].minn);
        tr[p].maxx = max(tr[p << 1].maxx, tr[p << 1 | 1].maxx);
        tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
    }
    void upd1(int p, ll v) {
        tr[p].minn += v;
        tr[p].maxx += v;
        tr[p].sum += v * tr[p].sz;
        tr[p].tag1 += v;
    }
    void pushdown(int p) {
        upd1(p << 1, tr[p].tag1);
        upd1(p << 1 | 1, tr[p].tag1);
        tr[p].tag1 = 0;
    }
    void build(int p = 1, int l = 1, int r = n) {
        tr[p].sz = r - l + 1;
        if(l == r) {
            tr[p].minn = tr[p].maxx = tr[p].sum = a[l];
            return;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update_plus(int ql, int qr, ll v, int p = 1, int l = 1, int r = n) {
        if(ql <= l && r <= qr) return upd1(p, v);
        int mid = l + r >> 1;
        pushdown(p);
        if(ql <= mid) update_plus(ql, qr, v, p << 1, l, mid);
        if(qr > mid) update_plus(ql, qr, v, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update_div(int ql, int qr, ll d, int p = 1, int l = 1, int r = n) {
        if(ql <= l && r <= qr) {
            if(tr[p].maxx - div(tr[p].maxx, d) != tr[p].minn - div(tr[p].minn, d)) {
                int mid = l + r >> 1;
                pushdown(p);
                update_div(ql, qr, d, p << 1, l, mid);
                update_div(ql, qr, d, p << 1 | 1, mid + 1, r);
                pushup(p);
                return;
            }
            ll v = div(tr[p].minn, d) - tr[p].minn;
            upd1(p, v);
            return;
        }
        int mid = l + r >> 1;
        pushdown(p);
        if(ql <= mid) update_div(ql, qr, d, p << 1, l, mid);
        if(qr > mid) update_div(ql, qr, d, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    ll query_plus(int ql, int qr, int p = 1, int l = 1, int r = n) {
        if(ql <= l && r <= qr) return tr[p].sum;
        int mid = l + r >> 1; ll res = 0;
        pushdown(p);
        if(ql <= mid) res += query_plus(ql, qr, p << 1, l, mid);
        if(qr > mid) res += query_plus(ql, qr, p << 1 | 1, mid + 1, r);
        return res;
    }
    ll query_min(int ql, int qr, int p = 1, int l = 1, int r = n) {
        if(ql <= l && r <= qr) return tr[p].minn;
        int mid = l + r >> 1; ll res = 1e15;
        pushdown(p);
        if(ql <= mid) res = min(res, query_min(ql, qr, p << 1, l, mid));
        if(qr > mid) res = min(res, query_min(ql, qr, p << 1 | 1, mid + 1, r));
        return res;
    }
}
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= n; i ++) a[i] = read();
    smtb::build();
    for(int i = 1, op, l, r, x; i <= m; i ++) {
        op = read();
        if(op == 1) {
            l = read() + 1, r = read() + 1, x = read();
            smtb::update_plus(l, r, x);
        } else if(op == 2) {
            l = read() + 1, r = read() + 1, x = read();
            smtb::update_div(l, r, x);
        } else if (op == 3) {
            l = read() + 1, r = read() + 1;
            printf("%lld\n", smtb::query_min(l, r));
        } else {
            l = read() + 1, r = read() + 1;
            printf("%lld\n", smtb::query_plus(l, r));
        }
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}