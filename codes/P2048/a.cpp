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
const int N = 5e5 + 10, inf = 5e8 + 10;
int n, k, l0, r0, a[N], suma[N];
namespace hjtt {
    struct node {int val; int lc, rc;} tr[N << 5];
    int rt[N], tot;
    void pushup(int p) {
        int &lc = tr[p].lc, &rc = tr[p].rc;
        tr[p].val = tr[lc].val + tr[rc].val;
    }
    void update_(int x, int p, int p0, int l = -inf, int r = inf) {
        tr[p] = tr[p0];
        if(l == r) return void(++ tr[p].val);
        int mid = l + r >> 1;
        if(x <= mid) update_(x, tr[p].lc = ++ tot, tr[p0].lc, l, mid);
        else update_(x, tr[p].rc = ++ tot, tr[p0].rc, mid + 1, r);
        pushup(p);
    }
    void update(int x, int ver) {
        update_(x, rt[ver] = ++ tot, rt[ver - 1]);
    }
    int query_(int k, int pl, int pr, int l = -inf, int r = inf) {
        if(l == r) return l;
        int mid = l + r >> 1; int lval = tr[tr[pr].lc].val - tr[tr[pl].lc].val;
        if(lval >= k) return query_(k, tr[pl].lc, tr[pr].lc, l, mid);
        else return query_(k - lval, tr[pl].rc, tr[pr].rc, mid + 1, r);
    }
    int query(int ql, int qr, int k) {
        if(tr[rt[qr]].val - tr[rt[ql - 1]].val < k) return inf;
        return query_(k, rt[ql - 1], rt[qr]);
    }
}
int getkth(int r, int k) {
    if((r - l0 + 1) - max(r - r0 + 1, 1) + 1 < k) return -inf;
    return suma[r] - hjtt::query(max(r - r0 + 1, 1), r - l0 + 1, k);
}
priority_queue<pair<int, pair<int, int>>> q;
ll ans;
void Hutao() {
    n = read(), k = read(), l0 = read(), r0 = read();
    hjtt::update(0, 1);
    for(int i = 1; i <= n; i ++) {
        suma[i] = suma[i - 1] + (a[i] = read());
        hjtt::update(suma[i], i + 1);
    }
    for(int i = 1; i <= n; i ++) {
        q.push(make_pair(getkth(i, 1), make_pair(i, 1)));
    }
    for(int i = 1; i <= k; i ++) {
        pair<int, pair<int, int>> x = q.top(); q.pop();
        q.push(make_pair(getkth(x.second.first, x.second.second + 1), make_pair(x.second.first, x.second.second + 1)));
        ans += x.first;
    }
    printf("%lld\n", ans);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}