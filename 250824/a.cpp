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
mt19937 fate(time(0) << 1 | 1);
namespace Qiuyu3600 {
const int N = 5e5 + 10, eof = 1e4;
namespace fhqt {
    struct info {
        int sum, premax, sufmax, ans;
        info() {sum = premax = sufmax = ans = 0;}
        info(int onum) {sum = onum = premax = sufmax = ans = onum;}
        info(int onum, int sz) {sum = onum * sz; premax = sufmax = ans = onum > 0 ? onum * sz : onum;}
        info(int osum, int opremax, int osufmax, int oans) {tie(sum, premax, sufmax, ans) = tie(osum, opremax, osufmax, oans);}
        friend info operator + (const info& a, const info& b) {
            return info(a.sum + b.sum, max(a.premax, a.sum + b.premax), max(a.sufmax + b.sum, b.sufmax), max(a.sufmax + b.premax, max(a.ans, b.ans)));
        }
    } ;
    int rt, tot, rcyc[N], cch[N];
    struct node {
        int key, sz, lc, rc;
        int val; info ans;
        int asgn_tag, rev_tag;
    } tr[N];
    int newnode(int val) {
        int p = rcyc[0] ? rcyc[rcyc[0] --] : ++ tot; assert(p);
        tr[p].key = fate(); tr[p].sz = 1; tr[p].lc = tr[p].rc = 0;
        tr[p].val = val; tr[p].ans = info(val);
        tr[p].asgn_tag = eof, tr[p].rev_tag = 0;
        return p;
    }
    void delnode(int p) {
        rcyc[++ rcyc[0]] = p;
    }
    void pushup(int p) {
        int &lc = tr[p].lc, &rc = tr[p].rc;
        tr[p].sz = tr[lc].sz + 1 + tr[rc].sz;
        tr[p].ans = tr[lc].ans + info(tr[p].val) + tr[rc].ans;
    }
    void upd1_asgn(int p, int val) {
        if(!p) return;
        tr[p].val = val;
        tr[p].ans = info(val, tr[p].sz);
        tr[p].asgn_tag = val;
    }
    void upd1_rev(int p) {
        if(!p) return;
        swap(tr[p].lc, tr[p].rc);
        swap(tr[p].ans.premax, tr[p].ans.sufmax);
        tr[p].rev_tag ^= 1;
    }
    void pushdown(int p) {
        int &lc = tr[p].lc, &rc = tr[p].rc;
        if(tr[p].asgn_tag ^ eof) {
            if(lc) upd1_asgn(lc, tr[p].asgn_tag);
            if(rc) upd1_asgn(rc, tr[p].asgn_tag);
            tr[p].asgn_tag = eof;
        }
        if(tr[p].rev_tag) {
            if(lc) upd1_rev(lc);
            if(rc) upd1_rev(rc);
            tr[p].rev_tag = 0;
        }
    }
    void split(int p, int k, int& x, int& y) {
        if(!p) return x = y = 0, void();
        pushdown(p);
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
        if(tr[x].key > tr[y].key) {
            p = x; pushdown(p);
            tr[p].rc = merge(tr[p].rc, y);
        } else {
            p = y; pushdown(p);
            tr[p].lc = merge(x, tr[p].lc);
        }
        return pushup(p), p;
    }
    int build(int l, int r) {
        if(l == r) return newnode(cch[l]);
        int mid = l + r >> 1;
        return merge(build(l, mid), build(mid + 1, r));
    }
    void ins(int pos, int tot) {
        int A, B, C;
        split(rt, pos, A, C);
        B = build(1, tot);
        rt = merge(A, merge(B, C));
    }
    void destruct(int p) {
        if(tr[p].lc) destruct(tr[p].lc);
        if(tr[p].rc) destruct(tr[p].rc);
        delnode(p);
    }
    void del(int pos, int tot) {
        int A, B, C;
        split(rt, pos - 1, A, rt);
        split(rt, tot, B, C);
        if(B) destruct(B);
        rt = merge(A, C);
    }
    void asgn(int pos, int tot, int val) {
        int A, B, C;
        split(rt, pos - 1, A, rt);
        split(rt, tot, B, C);
        upd1_asgn(B, val);
        rt = merge(A, merge(B, C));
    }
    void rev(int pos, int tot) {
        int A, B, C;
        split(rt, pos - 1, A, rt);
        split(rt, tot, B, C);
        upd1_rev(B);
        rt = merge(A, merge(B, C));
    }
    int sum(int pos, int tot) {
        int A, B, C, res;
        split(rt, pos - 1, A, rt);
        split(rt, tot, B, C);
        res = tr[B].ans.sum;
        rt = merge(A, merge(B, C));
        return res;
    }
    int maxsum() {
        return tr[rt].ans.ans;
    }
}
int n, m;
char op[10];
void Hutao() {
    n = read(), m = read();
    fhqt::tr[0].ans.ans = -eof;
    for(int i = 1; i <= n; i ++)
        fhqt::cch[i] = read();
    fhqt::ins(0, n);
    for(int i = 1, p, t, v; i <= m; i ++) {
        scanf("%s", op);
        if(op[2] == 'X') {
            printf("%d\n", fhqt::maxsum());
        } else {
            p = read(), t = read();
            if(op[2] == 'S') {
                for(int j = 1; j <= t; j ++)
                    fhqt::cch[j] = read();
                fhqt::ins(p, t);
            } else if(op[2] == 'L') {
                fhqt::del(p, t);
            } else if(op[2] == 'K') {
                v = read();
                fhqt::asgn(p, t, v);
            } else if(op[2] == 'V') {
                fhqt::rev(p, t);
            } else {
                printf("%d\n", fhqt::sum(p, t));
            }
        }
    }
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}