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
const int N = 1e6 + 10, inf = 1e9;
int n;
template<typename T>
struct Heap {
    priority_queue<T> qa, qd;
    void push(T x) {qa.push(x);}
    void erase(T x) {qd.push(x);}
    T top() {
        while(qa.size() && qd.size() && qa.top() == qd.top()) {qa.pop(), qd.pop();}
        return qa.size() ? qa.top() : -inf;
    }
} ;
Heap<int> h[2][N];
struct SMTnode {
    int maxl, minr, ans;
} ;
struct SMT {
    SMTnode tr[N << 2];
    void pushup(int p) {
        tr[p].maxl = max(tr[p << 1].maxl, tr[p << 1 | 1].maxl);
        tr[p].minr = min(tr[p << 1].minr, tr[p << 1 | 1].minr);
        tr[p].ans = min(min(tr[p << 1].ans, tr[p << 1 | 1].ans), tr[p << 1 | 1].minr - tr[p << 1].maxl);
    }
    void create(int p = 1, int l = 1, int r = 1000000) {
        if(l == r) {
            tr[p].maxl = h[0][l].top();
            tr[p].minr = -h[1][r].top();
            tr[p].ans = -h[1][r].top() - h[0][l].top();
            return;
        }
        int mid = l + r >> 1;
        create(p << 1, l, mid);
        create(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update_pr(int x, int p = 1, int l = 1, int r = 1000000) {
        if(l == r) {
            tr[p].maxl = h[0][l].top();
            tr[p].minr = -h[1][r].top();
            tr[p].ans = -h[1][r].top() - h[0][l].top();
            return;
        }
        int mid = l + r >> 1;
        if(x <= mid) update_pr(x, p << 1, l, mid);
        else update_pr(x, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int typ, int ql, int qr) {
        typ ? h[1][ql].push(-qr) : h[1][ql].erase(-qr);
        update_pr(ql);
        typ ? h[0][qr].push(ql) : h[0][qr].erase(ql);
        update_pr(qr);
    }
    SMTnode query_pr(int ql, int qr, int p = 1, int l = 1, int r = 1000000) {
        if(ql <= l && r <= qr) return tr[p];
        int mid = l + r >> 1;
        if(ql <= mid && qr <= mid) return query_pr(ql, qr, p << 1, l, mid);
        if(ql > mid && qr > mid) return query_pr(ql, qr, p << 1 | 1, mid + 1, r);
        SMTnode p1 = query_pr(ql, qr, p << 1, l, mid), p2 = query_pr(ql, qr, p << 1 | 1, mid + 1, r);
        return SMTnode{max(p1.maxl, p2.maxl), min(p1.minr, p2.minr), min(min(p1.ans, p2.ans), p2.minr - p1.maxl)};
    }
    int query() {
        return query_pr(1, 1000000).ans;
    }
} smt;
Heap<int> suml, sumr;
void Hutao() {
    n = read();
    smt.create();
    for(int i = 1; i <= n; i ++) {
        char op = readch(); int l = read(), r = read();
        op == 'A' ? (suml.push(l), sumr.push(-r)) : (suml.erase(l), sumr.erase(-r));
        smt.update(op == 'A', l, r);
        if(suml.top() > -sumr.top()) printf("%d\n", smt.query());
        else printf("%d\n", - h[1][suml.top()].top() - h[0][-sumr.top()].top());
    }
}
}
int main() {
    #ifndef db
    freopen("bohemian.in", "r", stdin);
    freopen("bohemian.out", "w", stdout);
    #endif
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}