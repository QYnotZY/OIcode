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
const int N = 5e4 + 10;
int n, m, q;
struct dsu {
    int fa[N], sz[N]; tuple<int, int, int> stk[N]; int top;
    ll sum;
    void init(int n) {
        for(int i = 1; i <= n; i ++) fa[i] = i, sz[i] = 1;
        top = 0; sum = 0;
    }
    int find(int x) {return fa[x] == x ? x : find(fa[x]);}
    bool same(int x, int y) {return find(x) == find(y);}
    void merge(int x, int y, int w) {
        x = find(x), y = find(y);
        if(sz[x] < sz[y]) swap(x, y);
        fa[y] = x; sz[x] += sz[y]; sum += w; stk[++ top] = make_tuple(x, y, w);
    }
    int record() {return top;}
    void undo(int aim) {
        for(int x, y, w; top ^ aim; top --) {
            tie(x, y, w) = stk[top];
            fa[y] = y; sz[x] -= sz[y]; sum -= w;
        }
    }
} lts;
struct edge {
    int u, v, w;
} ed[N];
struct QRY {
    int id, val;
} qry[N];
struct node {
    int id, sta;
    bool operator < (const node& obj) const {
        return ed[id].w < ed[obj.id].w;
    }
} ;
vector<node> con[20], cont; vector<int> mut[20];
int lts_rec[20];
int mdfnow[N];
ll ans[N];
void pushdown(int l, int r, int d) {
    cont = con[d - 1];
    if(l ^ r) for(int i = l; i <= r; i ++) if(!mdfnow[qry[i].id]) mdfnow[qry[i].id] = 1, mut[d].push_back(qry[i].id);
    for(auto id : mut[d - 1]) if(!mdfnow[id]) mdfnow[id] = -1, cont.push_back({id, 0});
    sort(cont.begin(), cont.end());
    for(auto& ele : cont) {
        if(!lts.same(ed[ele.id].u, ed[ele.id].v)) {
            lts.merge(ed[ele.id].u, ed[ele.id].v, ed[ele.id].w);
        } else ele.sta = -1;
    }
    lts.undo(lts_rec[d - 1]);
    for(auto& id : mut[d]) {
        if(!lts.same(ed[id].u, ed[id].v)) {
            lts.merge(ed[id].u, ed[id].v, 0);
        }
    }
    for(auto& ele : cont) {
        if(!lts.same(ed[ele.id].u, ed[ele.id].v)) {
            lts.merge(ed[ele.id].u, ed[ele.id].v, ed[ele.id].w);
            ele.sta = 1;
        }
    }
    lts.undo(lts_rec[d - 1]);
    for(auto& ele : cont) {
        if(ele.sta == 1) lts.merge(ed[ele.id].u, ed[ele.id].v, ed[ele.id].w);
        else if(ele.sta == 0) con[d].push_back(ele);
    }
    lts_rec[d] = lts.record();
    for(auto id : mut[d - 1]) mdfnow[id] = 0;
}
void pushup(int d) {
    mut[d].clear();
    lts.undo(lts_rec[d - 1]);
    con[d].clear();
    lts_rec[d] = 0;
}
void solve(int l, int r, int d) {
    if(l == r) {
        ed[qry[l].id].w = qry[l].val;
        pushdown(l, r, d);
        ans[l] = lts.sum;
        return pushup(d);
    }
    pushdown(l, r, d);
    int mid = l + r >> 1;
    solve(l, mid, d + 1);
    solve(mid + 1, r, d + 1);
    pushup(d);
}
void Hutao() {
    n = read(), m = read(), q = read();
    lts.init(n);
    for(int i = 1; i <= m; i ++)
        ed[i] = {read(), read(), read()};
    for(int i = 1; i <= q; i ++) {
        qry[i] = {read(), read()};
        mdfnow[qry[i].id] = 1;
    }
    for(int i = 1; i <= m; i ++) {
        if(mdfnow[i]) mdfnow[i] = 0, mut[0].push_back(i);
        else con[0].push_back({i, 0});
    }
    solve(1, q, 1);
    for(int i = 1; i <= q; i ++) printf("%lld\n", ans[i]);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}