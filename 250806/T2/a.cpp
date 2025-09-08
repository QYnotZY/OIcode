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
const int N = 3e5 + 10;
mt19937 my_rand(1145141);
int n, m;
int a[N];
namespace treap {
    int rt, tot;
    struct node {
        int key, lc, rc, sz;
        int val;
        ll sum, ans;
    } tr[N];
    void pushup(int p) {
        int &lc = tr[p].lc, &rc = tr[p].rc;
        tr[p].sz = tr[lc].sz + 1 + tr[rc].sz;
        tr[p].sum = tr[lc].sum + tr[rc].sum + tr[p].val;
        tr[p].ans = max(tr[lc].ans, tr[lc].sum + tr[p].val + max(0ll, tr[rc].ans));
    }
    int newnode(int val) {
        tr[++ tot].key = my_rand(), tr[tot].lc = tr[tot].rc = 0, tr[tot].sz = 1;
        tr[tot].val = val;
        tr[tot].sum = val, tr[tot].ans = max(0, val);
        return tot;
    }
    void split(int p, int k, int &x, int &y) {
        if(!p) return x = y = 0, void();
        int &lc = tr[p].lc, &rc = tr[p].rc;
        if(tr[lc].sz < k) {
            x = p;
            split(rc, k - tr[lc].sz - 1, rc, y);
        } else {
            y = p;
            split(lc, k, x, lc);
        }
        pushup(p);
    }
    int merge(int x, int y) {
        if(!x || !y) return x | y;
        int p;
        if(tr[x].key >= tr[y].key) {
            p = x;
            tr[p].rc = merge(tr[p].rc, y);
        } else {
            p = y;
            tr[p].lc = merge(x, tr[p].lc);
        }
        pushup(p);
        return p;
    }
    void insert(int pos, int val) {
        int A, B, C;
        B = newnode(val);
        split(rt, pos, A, C);
        rt = merge(merge(A, B), C);
    }
    void update(int l, int r, int k) {
        int A, B, C, D;
        split(rt, l - 1, A, rt);
        split(rt, k, B, rt);
        split(rt, r + 1 - l - k, C, D);
        rt = merge(merge(A, C), merge(B, D));
    }
    int query_pr(int p) {
        int &lc = tr[p].lc, &rc = tr[p].rc;
        ll lans = tr[lc].ans, pans = tr[lc].sum + tr[p].val, rans = tr[lc].sum + tr[p].val + tr[rc].ans;
        if(lans >= max(pans, rans)) return query_pr(lc);
        if(pans >= rans) return tr[lc].sz + 1;
        return tr[lc].sz + 1 + query_pr(rc);
    }
    int query() {
        if(tr[rt].ans <= 0) return 0;
        return query_pr(rt);
    }
}
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= n; i ++) {
        a[i] = read();
        treap::insert(i - 1, (a[i] - 1 << 1) - n + 1);
    }
    for(int i = 1, l, r, k; i <= m; i ++) {
        l = read(), r = read(), k = read();
        treap::update(l, r, k);
        printf("%d\n", treap::query());
    }
}
}
int main() {
    #ifndef db
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    #endif
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}