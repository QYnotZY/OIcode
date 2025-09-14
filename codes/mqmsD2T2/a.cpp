#include "bits/stdc++.h"
using namespace std;
namespace FastIO {
    template<typename T = int> T read() {
        char ch = getchar(); bool neg = 0; T res = 0;
        for(; !('0' <= ch && ch <= '9'); ch = getchar()) if(ch == '-') neg = !neg;
        for(; ('0' <= ch && ch <= '9'); ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ 48);
        return neg ? ~res + 1 : res;
    }
    char readch(bool acsp = 0) {
        char ch = getchar(); for(; !(33 - acsp <= ch && ch < 127); ch = getchar()); return ch;
    }
} using namespace FastIO;
typedef long long ll;
namespace Qiuyu3600 {
const int N = 2e5 + 10, inf = 1e9 + 7;
int n;
struct pt {int x, y; bool operator<(const pt &obj) const {return x < obj.x;}} a[N];
namespace smt {
    struct node {
        int sz;
        int maxx, ans;
        node() {sz = 1; maxx = ans = 0;}
        node(int v) {maxx = v, ans = sz = 1;}
    } tr[N << 2];
    int getans(int val, int p) {
        if(tr[p].sz == 1) return tr[p].maxx > val;
        if(tr[p << 1 | 1].maxx <= val) return getans(val, p << 1);
        else return getans(val, p << 1 | 1) + tr[p].ans - tr[p << 1 | 1].ans;
    }
    void pushup(int p) {
        tr[p].sz = tr[p << 1].sz + tr[p << 1 | 1].sz;
        tr[p].maxx = max(tr[p << 1].maxx, tr[p << 1 | 1].maxx);
        tr[p].ans = tr[p << 1 | 1].ans + getans(tr[p << 1 | 1].maxx, p << 1);
    }
    void build(int p = 1, int l = 1, int r = n) {
        if(l == r) return void(tr[p] = node());
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int x, int v, int p = 1, int l = 1, int r = n) {
        if(l == r) return void(tr[p] = node(v));
        int mid = l + r >> 1;
        if(x <= mid) update(x, v, p << 1, l, mid);
        else update(x, v, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    node res;
    void updres(int p) {
        res.ans += getans(res.maxx, p);
        res.maxx = max(tr[p].maxx, res.maxx);
    }
    void query_(int qr, int p = 1, int l = 1, int r = n) {
        if(r <= qr) return updres(p);
        int mid = l + r >> 1;
        if(mid < qr) query_(qr, p << 1 | 1, mid + 1, r);
        query_(qr, p << 1, l, mid);
    }
    int query(int qr) {
        if(qr < 1) return 0;
        res.ans = 0, res.maxx = 0;
        query_(qr);
        return res.ans;
    }
}
int v[N];
ll ans;
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++) a[i] = {read(), v[i] = read()};
    sort(v + 1, v + n + 1);
    for(int i = 1; i <= n; i ++) a[i].y = lower_bound(v + 1, v + n + 1, a[i].y) - v;
    sort(a + 1, a + n + 1);
    smt::build();
    for(int i = 1; i <= n; i ++) {
        ans += smt::query(a[i].y);
        smt::update(a[i].y, i);
    }
    printf("%lld", ans);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}