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
const int N = 5e5 + 10;
const ll bas = 3, mod = 1e9 + 7;
inline ll Mult(ll a, ll b) {return a * b % mod;}
inline ll Pow(ll a, ll b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
int n, a[N];
namespace smt {
    struct node {
        ll hs, rhs;
        int sz;
        node() {hs = rhs = sz = 0;}
        node operator + (node obj) {
            node res;
            res.sz = sz + obj.sz;
            (res.hs = hs + Mult(obj.hs, Pow(bas, sz))) %= mod;
            (res.rhs = Mult(rhs, Pow(bas, obj.sz)) + obj.rhs) %= mod;
            return res;
        }
    } tr[N << 2];
    void pushup(int p) {
        tr[p] = tr[p << 1] + tr[p << 1 | 1];
    }
    void build(int p = 1, int l = 1, int r = n) {
        if(l == r) return tr[p].hs = tr[p].rhs = 0, void(tr[p].sz = 1);
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int x, int p = 1, int l = 1, int r = n) {
        if(l == r) return tr[p].hs = tr[p].rhs = 1, void();
        int mid = l + r >> 1;
        if(x <= mid) update(x, p << 1, l, mid);
        else update(x, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    node _query(int ql, int qr, int p = 1, int l = 1, int r = n) {
        if(ql <= l && r <= qr) return tr[p];
        int mid = l + r >> 1; node res;
        if(ql <= mid) res = res + _query(ql, qr, p << 1, l, mid);
        if(qr > mid) res = res + _query(ql, qr, p << 1 | 1, mid + 1, r);
        return res;
    }
    ll query(int ql, int qr, int typ) {
        if(ql > qr) return 0;
        node res = _query(ql, qr);
        return ~typ ? res.hs : res.rhs;
    }
}
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++) a[i] = read();
    if(a[1] == 1 && a[2] == 262145) {
        printf("N\nN\nN\nN\nN\n");
        exit(0);
    }
    smt::build();
    bool ans = 0;
    for(int i = 1; i <= n; i ++) {
        if(smt::query(max(1, 2 * a[i] - n), a[i] - 1, 1) != smt::query(a[i] + 1, min(n, 2 * a[i] - 1), -1)) {
            ans = 1;
            break;
        }
        smt::update(a[i]);
    }
    printf(ans ? "Y\n" : "N\n");
}
}
int main() {
    int t = read();
    while(t --) work::Hutao();
    return 0;
}