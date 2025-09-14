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
const int N = 1e5 + 10, M = 3e5 + 10;
namespace dsu {
    int fa[N], sz[N], cnt;
    pair<int, int> stk[N]; int top;
    void init(int n) {
        for(int i = 1; i <= n; i ++)
            fa[i] = i, sz[i] = 1;
        cnt = n;
        top = 0;
    }
    int find(int x) {return fa[x] == x ? x : find(fa[x]);}
    void merge(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return;
        if(sz[x] < sz[y]) swap(x, y);
        cnt -= sz[x] & 1, cnt -= sz[y] & 1;
        fa[y] = x, sz[x] += sz[y];
        cnt += sz[x] & 1;
        stk[++ top] = make_pair(x, y);
    }
    int record() {return top;}
    void undo(int t) {
        for(int x, y; top > t; top --) {
            x = stk[top].first, y = stk[top].second;
            cnt -= sz[x] & 1;
            fa[y] = y, sz[x] -= sz[y];
            cnt += sz[x] & 1, cnt += sz[y] & 1;
        }
    }
    bool check() {return !cnt;}
}
int n, m;
struct node {
    int u, v, w, t;
    bool operator<(const node &obj) const {
        return w < obj.w;
    }
} ed[M], ed0[M];
int ans[M];
void solve(int ql, int qr, int vl, int vr) {
    #ifdef db
    printf("%d %d %d %d\n", ql, qr, vl, vr);
    #endif
    if(ql > qr) return;
    int qmid = ql + qr >> 1, vmid = -1, rec = dsu::record();
    for(int i = ql; i <= qmid; i ++) if(ed0[i].t < vl) dsu::merge(ed0[i].u, ed0[i].v);
    for(int i = vl; i <= vr; i ++) {
        if(ed[i].t <= qmid) dsu::merge(ed[i].u, ed[i].v);
        if(dsu::check()) {vmid = i; break;}
    }
    dsu::undo(rec);
    if(vmid == -1) {
        for(int i = ql; i <= qmid; i ++)
            ans[i] = -1;
        for(int i = ql; i <= qmid; i ++) if(ed0[i].t < vl) dsu::merge(ed0[i].u, ed0[i].v);
        solve(qmid + 1, qr, vl, vr);
        dsu::undo(rec);
    } else {
        ans[qmid] = ed[vmid].w;
        for(int i = vl; i <= vmid; i ++) if(ed[i].t < ql) dsu::merge(ed[i].u, ed[i].v);
        solve(ql, qmid - 1, vmid, vr);
        dsu::undo(rec);
        for(int i = ql; i <= qmid; i ++) if(ed0[i].t < vl) dsu::merge(ed0[i].u, ed0[i].v);
        solve(qmid + 1, qr, vl, vmid);
        dsu::undo(rec);
    }
}
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= m; i ++)
        ed0[i] = ed[i] = {read(), read(), read(), i};
    sort(ed + 1, ed + m + 1);
    for(int i = 1; i <= m; i ++)
        ed0[ed[i].t].t = i;
    dsu::init(n);
    solve(1, m, 1, m);
    for(int i = 1; i <= m; i ++) printf("%d\n", ans[i]);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}