#include<bits/stdc++.h>
using namespace std;
constexpr int N = 500005, V = 10000000;
int n, m;
struct disc {
    vector<int> e;
    map<int, int> m;
    int cnt = 0;
    void insert(int v) {
        e.push_back(v);
    }
    void calc() {
        sort(e.begin(), e.end());
        for(int i = 0; i < e.size(); i ++) {
            if(!m[e[i]]) m[e[i]] = ++ cnt;
        }
        return ;
    }
    const int operator [] (int v) {
        return m[v];
    }
} disc;
struct point {
    int x, y, test;
} a[N];
bool cmp(point a, point b) {
    return a.x < b.x;
}
struct ask {
    int x, y, u, v;
} q[N];
struct sgt {
    int root[N];
    int tree[N << 5];
    int ls[N << 5], rs[N << 5];
    int cnt;
    void pushup(int p) {
        tree[p] = tree[ls[p]] + tree[rs[p]];
        return ;
    }
    void build(int l, int r, int p, int id) {
        tree[p] = tree[id];
        if(l == r) return ;
        if(!p) return ;
        int mid = (l + r) >> 1;
        if(ls[id]) ls[p] = ++ cnt;
        if(rs[id]) rs[p] = ++ cnt;
        build(l, mid, ls[p], ls[id]);
        build(mid + 1, r, rs[p], rs[id]);
        return ;
    }
    void update(int l, int r, int x, int p, int id, int test) {
        if(l == r) {
            tree[p] += test;
            return ;
        }
        int mid = (l + r) >> 1;
        if(x <= mid) {
            if(!ls[p]) ls[p] = ++ cnt;
            update(l, mid, x, ls[p], ls[id], test);
        } else {
            if(!rs[p]) rs[p] = ++ cnt;
            update(mid + 1, r, x, rs[p], rs[id], test);
        }
        pushup(p);
        return ;
    }
    int query(int l, int r, int s, int t, int p) {
        if(t < l || r < s || !p) return 0;
        if(l <= s && t <= r) return tree[p];
        int mid = (s + t) >> 1;
        return query(l, r, s, mid, ls[p]) + query(l, r, mid + 1, t, rs[p]);
    }
    int query(int x, int y, int u, int v) {
        return query(0, V, y, v, root[u]) - query(0, V, y, v, root[x - 1]);
    }
} sgt;
signed main() {
    cin >> n >> m;
    for(int i = 1; i <= n; i ++) {
        cin >> a[i].x >> a[i].y;
        a[i].test = 1;
        disc.insert(a[i].x);
    }
    for(int i = 1; i <= m; i ++) {
        cin >> q[i].x >> q[i].y >> q[i].u >> q[i].v;
        disc.insert(q[i].x - 1);
        disc.insert(q[i].u);
    }
    disc.calc();
    sort(a + 1, a + 1 + n, cmp);
    int h = 1;
    for(int i = 1; i <= disc.cnt; i ++) {
        sgt.root[i] = ++ sgt.cnt;
        sgt.build(0, V, sgt.root[i], sgt.root[i - 1]);
        while(h <= n && disc[a[h].x] == i) {
            sgt.update(0, V, a[h].y, sgt.root[i], sgt.root[i - 1], a[h].test);
            h ++;
        }
    }
    for(int i = 1; i <= m; i ++) {
        printf("%d\n", sgt.query(disc[q[i].x], q[i].y, disc[q[i].u], q[i].v));
    }
    return 0;
}