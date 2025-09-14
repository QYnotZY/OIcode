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
int n, q;
namespace smt {
    struct node {
        int a, b, ans;
        node() {a = ans = -inf, b = inf;}
    } tr[N << 2];
    void pushup(int p) {
        tr[p].a = -inf;
        tr[p].b = min(tr[p << 1].b, tr[p << 1 | 1].b);
        tr[p].ans = max(tr[p << 1].ans, tr[p << 1 | 1].ans);
    }
    void cov1(int p, int v) {
        tr[p].a = max(tr[p].a, v);
        tr[p].ans = max(tr[p].ans, v - tr[p].b);
    }
    void cov2(int p, int v) {
        tr[p].a = -inf;
        tr[p].b = v;
    }
    void pushdn(int p) {
        cov1(p << 1, tr[p].a);
        cov1(p << 1 | 1, tr[p].a);
        tr[p].a = -inf;
    }
    void build(int p = 1, int l = 1, int r = n) {
        tr[p] = node();
        if(l == r) return;
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
    }
    void upda(int ql, int qr, int v, int p = 1, int l = 1, int r = n) {
        if(ql > qr) return;
        if(ql <= l && r <= qr) return cov1(p, v);
        pushdn(p);
        int mid = l + r >> 1;
        if(ql <= mid) upda(ql, qr, v, p << 1, l, mid);
        if(mid < qr) upda(ql, qr, v, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void updb(int x, int v, int p = 1, int l = 1, int r = n) {
        if(l == r) return cov2(p, v);
        pushdn(p);
        int mid = l + r >> 1;
        if(x <= mid) updb(x, v, p << 1, l, mid);
        else updb(x, v, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    int query(int ql, int qr, int p = 1, int l = 1, int r = n) {
        if(ql <= l && r <= qr) return tr[p].ans;
        pushdn(p);
        int mid = l + r >> 1, res = -inf;
        if(ql <= mid) res = max(res, query(ql, qr, p << 1, l, mid));
        if(mid < qr) res = max(res, query(ql, qr, p << 1 | 1, mid + 1, r));
        return res;
    }
}
struct node {
    int h, a, b;
} a[N];
vector<int> add[N], del[N];
struct qry {
    int l, r, id;
    bool operator<(const qry &obj) const {
        return r < obj.r;
    }
} qry[N];
int ans[N];
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++)
        a[i] = {read(), read(), read()};
    q = read();
    for(int i = 1; i <= q; i ++)
        qry[i] = {read(), read(), i};
    sort(qry + 1, qry + q + 1);
    memset(ans, -1, sizeof(ans));
    smt::build();
    for(int i = 1, qi = 1; i <= n; i ++) {
        if(i + a[i].a <= n) add[i + a[i].a].push_back(i);
        if(i + a[i].b + 1 <= n) del[i + a[i].b + 1].push_back(i);
        for(auto ele : add[i]) {smt::updb(ele, a[ele].h);}
        for(auto ele : del[i]) {smt::updb(ele, inf);}
        smt::upda(max(i - a[i].b, 1), max(i - a[i].a, 0), a[i].h);
        for(; qi <= q && qry[qi].r <= i; qi ++)
            ans[qry[qi].id] = max(ans[qry[qi].id], smt::query(qry[qi].l, qry[qi].r));
    }
    smt::build();
    for(int i = 1, qi = 1; i <= n; i ++) {
        if(i + a[i].a <= n) add[i + a[i].a].push_back(i);
        if(i + a[i].b + 1 <= n) del[i + a[i].b + 1].push_back(i);
        for(auto ele : add[i]) {smt::updb(ele, -a[ele].h);}
        for(auto ele : del[i]) {smt::updb(ele, inf);}
        smt::upda(max(i - a[i].b, 1), max(i - a[i].a, 0), -a[i].h);
        for(; qi <= q && qry[qi].r <= i; qi ++)
            ans[qry[qi].id] = max(ans[qry[qi].id], smt::query(qry[qi].l, qry[qi].r));
    }
    for(int i = 1; i <= q; i ++) printf("%d\n", ans[i]);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}