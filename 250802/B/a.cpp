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
int n, m;
namespace smt {
    int get_cnt(int, int);
    struct node {
        double maxx;
        int cnt, ans;
        bool leaf;
    } tr[N << 2];
    int get_cnt(int p, double tgt) {
        if(tr[p].leaf) return tr[p].maxx > tgt;
        if(tr[p << 1].maxx <= tgt) return get_cnt(p << 1 | 1, tgt);
        else return get_cnt(p << 1, tgt) + tr[p].cnt;
    }
    void pushup(int p) {
        tr[p].maxx = max(tr[p << 1].maxx, tr[p << 1 | 1].maxx);
        tr[p].cnt = get_cnt(p << 1 | 1, tr[p << 1].maxx);
        tr[p].ans = tr[p << 1].ans + tr[p].cnt;
    }
    void build(int p = 1, int l = 1, int r = n) {
        if(l == r) {
            tr[p].leaf = 1;
            tr[p].maxx = 0;
            tr[p].cnt = 0;
            tr[p].ans = 1;
            return;
        }
        tr[p].leaf = 0;
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int x, double v, int p = 1, int l = 1, int r = n) {
        if(tr[p].leaf) return tr[p].maxx = v, void();
        int mid = l + r >> 1;
        if(x <= mid) update(x, v, p << 1, l, mid);
        else update(x, v, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    node res;
    void query(int ql, int qr, int p = 1, int l = 1, int r = n) {
        if(p == 1) res = node{0, 0, 0, 0};
        if(ql <= l && r <= qr) {
            res.cnt = get_cnt(p, res.maxx);
            res.ans += res.cnt;
            res.maxx = max(res.maxx, tr[p].maxx);
            return;
        }
        int mid = l + r >> 1;
        if(ql <= mid) query(ql, qr, p << 1, l, mid);
        if(qr > mid) query(ql, qr, p << 1 | 1, mid + 1, r);
    }
}
void Hutao() {
    n = read(), m = read();
    smt::build();
    for(int i = 1, x, y; i <= m; i ++) {
        x = read(), y = read();
        smt::update(x, 1.0 * y / x);
        smt::query(1, n);
        printf("%d\n", smt::res.ans);
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}