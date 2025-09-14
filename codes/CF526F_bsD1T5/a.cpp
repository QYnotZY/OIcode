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
const int N = 3e5 + 10, inf = 1e6;
int n, a[N];
namespace smt {
    struct node {
        int minn, mincnt;
        node() {minn = inf, mincnt = 0;}
        node(int a) {minn = a, mincnt = 1;}
        node operator+(const node& obj) const {
            node res;
            if(minn < obj.minn) res = *this;
            else if(minn > obj.minn) res = obj;
            else res.minn = minn, res.mincnt = mincnt + obj.mincnt;
            return res;
        }
    } tr[N << 2];
    int tag[N << 2];
    void pushup(int p) {
        tr[p] = tr[p << 1] + tr[p << 1 | 1];
    }
    void add1(int p, int val) {
        if(!p) return;
        tr[p].minn += val;
        tag[p] += val;
    }
    void pushdn(int p) {
        add1(p << 1, tag[p]);
        add1(p << 1 | 1, tag[p]);
        tag[p] = 0;
    }
    void build(int p = 1, int l = 1, int r = n) {
        if(p == 1) tr[0] = node();
        tr[p] = node(), tag[p] = 0;
        if(l == r) return;
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
    }
    void access(int x, int p = 1, int l = 1, int r = n) {
        if(l == r) return void(tr[p] = node(0));
        pushdn(p);
        int mid = l + r >> 1;
        if(x <= mid) access(x, p << 1, l, mid);
        else access(x, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int ql, int qr, int val, int p = 1, int l = 1, int r = n) {
        if(ql > qr) return;
        if(ql <= l && r <= qr) return add1(p, val);
        pushdn(p);
        int mid = l + r >> 1;
        if(ql <= mid) update(ql, qr, val, p << 1, l, mid);
        if(qr > mid) update(ql, qr, val, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    int query() {return tr[1].minn ? 0 : tr[1].mincnt;}
}
int stk[2][N], top[2];
ll ans = 0;
void Hutao() {
    n = read();
    for(int i = 1, x, y; i <= n; i ++) {
        x = read(), y = read();
        a[x] = y;
    }
    smt::build();
    for(int r = 1; r <= n; r ++) {
        for(; top[1] && a[stk[1][top[1]]] < a[r]; -- top[1])
            smt::update(stk[1][top[1] - 1] + 1, stk[1][top[1]], a[r] - a[stk[1][top[1]]]);
        for(; top[0] && a[stk[0][top[0]]] > a[r]; -- top[0])
            smt::update(stk[0][top[0] - 1] + 1, stk[0][top[0]], a[stk[0][top[0]]] - a[r]);
        smt::update(1, r - 1, -1);
        stk[0][++ top[0]] = r, stk[1][++ top[1]] = r;
        smt::access(r);
        ans += smt::query();
    }
    printf("%lld", ans);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}