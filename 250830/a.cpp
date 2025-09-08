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
const int N = 1e5 + 10;
struct ANS {
    int null, len, max1, max2, ans;
    ANS() {null = len = max1 = max2 = ans = 0;};
    ANS(int ex, int val) {null = ex ^ 1, len = val, max1 = max2 = ex ? val : 0, ans = 0;}
    friend ANS operator ~ (const ANS& a) {
        ANS res = a;
        swap(res.max1, res.max2);
        return res;
    }
    friend ANS operator + (const ANS& a, const ANS& b) {
        ANS res;
        res.len = a.len + b.len;
        if(a.null && b.null) res.null = 1;
        else if(a.null) {
            res.max1 = b.max1 + a.len;
            res.max2 = b.max2;
            res.ans = b.ans;
        } else if(b.null) {
            res.max1 = a.max1;
            res.max2 = a.max2 + b.len;
            res.ans = a.ans;
        } else {
            res.max1 = max(a.max1, b.max1 + a.len);
            res.max2 = max(b.max2, a.max2 + b.len);
            res.ans = max(max(a.ans, b.ans), a.max2 + b.max1);
        }
        return res;
    }
    friend ANS operator | (const ANS& a, const ANS& b) {
        ANS res;
        res.len = 0;
        if(a.null && b.null) res.null = 1;
        else if(a.null) {
            res.max1 = b.max1, res.max2 = b.max2, res.ans = b.ans;
        } else if(b.null) {
            res.max1 = a.max1, res.max2 = a.max2, res.ans = a.ans;
        } else {
            res.max1 = max(a.max1, b.max1);
            int tmp = min(a.max1, b.max1);
            res.max2 = max(tmp, max(a.max2, b.max2));
            res.ans = max(a.ans, b.ans);
        }
        return res;
    }
    ANS trans() {
        ANS res;
        res.null = this->null;
        res.len = 0;
        res.max1 = this->max1;
        res.max2 = -1e9;
        res.ans = this->ans;
        return res;
    }
    ANS trans(const int& c, const int& v) {
        ANS res;
        res.null = this->null;
        res.len = v;
        if(res.null) {
            if(!c) return res;
            res.null = 0, res.max1 = res.max2 = v, res.ans = 0;
            return res;
        }
        res.max1 = this->max1 + v; if(c) res.max1 = max(res.max1, v);
        res.max2 = res.max1;
        int tmp = this->max2; if(c) tmp = max(tmp, 0);
        res.ans = max(this->ans, this->max1 + tmp + v); if(c) res.ans = max(res.ans, v);
        return res;
    }
} ;
namespace satt {
    struct node {
        int fa, ch[3];
        int typ;
        int col, val; ANS ans;
        int revtag;
    } tr[N << 2];
    int tot, rcyc[N << 1];
    #define fa(x) tr[x].fa
    #define lc(x) tr[x].ch[0]
    #define rc(x) tr[x].ch[1]
    #define mc(x) tr[x].ch[2]
    int newnode(int typ, int col = 0, int val = 0) {
        int p = rcyc[0] ? rcyc[rcyc[0] --] : ++ tot;
        memset(tr + p, 0, sizeof(node));
        tr[p].typ = typ; tr[p].col = col; tr[p].val = val;
        tr[p].ans = ANS(col, val);
        return p;
    }
    void delnode(int p) {
        rcyc[++ rcyc[0]] = p;
    }
    void pushup(int p) {
        if(!p) return;
        if(tr[p].typ) tr[p].ans = tr[lc(p)].ans + tr[mc(p)].ans.trans(tr[p].col, tr[p].val) + tr[rc(p)].ans;
        else tr[p].ans = tr[lc(p)].ans | tr[mc(p)].ans.trans() | tr[rc(p)].ans;
    }
    void upd1vc(int p) {
        if(!tr[p].typ) return;
        tr[p].col ^= 1;
    }
    void upd1rev(int p) {
        if(!tr[p].typ) return;
        swap(lc(p), rc(p));
        tr[p].ans = ~tr[p].ans;
        tr[p].revtag ^= 1;
    }
    void pushdown(int p) {
        if(tr[p].typ)
            if(tr[p].revtag) {
                upd1rev(lc(p)), upd1rev(rc(p));
                tr[p].revtag = 0;
            }
    }
    inline bool isroot(int p) {return lc(fa(p)) ^ p && rc(fa(p)) ^ p;}
    inline int direct(int p) {return rc(fa(p)) == p;}
    inline void setfa(int p, int f, int dir) {if(p) fa(p) = f; if(f) tr[f].ch[dir] = p, pushup(f);}
    void rotate(int p) {
        int x = p, y = fa(x), z = fa(y), d1 = direct(x), w = tr[x].ch[d1 ^ 1], d2 = isroot(y) ? 2 : direct(y);
        setfa(w, y, d1), setfa(y, x, d1 ^ 1), setfa(x, z, d2);
    }
    void pushall(int p) {if(!isroot(p)) pushall(fa(p)); pushdown(p);}
    void splay(int p, int aim = 0) {
        pushall(p);
        for(; !isroot(p) && fa(p) ^ aim; rotate(p))
            if(!isroot(fa(p)) && fa(fa(p)) ^ aim) rotate(direct(fa(p)) == direct(p) ? fa(p) : p);
    }
    void destruct(int p) {
        if(lc(p)) {
            int u = lc(p); pushdown(u);
            while(rc(u)) pushdown(u = rc(u));
            splay(u, p);
            setfa(rc(p), u, 1);
            setfa(u, fa(p), 2);
        } else setfa(rc(p), fa(p), 2);
        delnode(p);
    }
    void splice(int p) {
        int f;
        splay(p), splay(f = fa(p)), pushdown(p);
        if(rc(f)) {
            swap(fa(mc(p)), fa(rc(f)));
            swap(mc(p), rc(f));
        } else {
            setfa(mc(p), f, 1);
            destruct(p);
        }
        pushup(p), pushup(f);
    }
    void access(int p) {
        splay(p);
        if(rc(p)) {
            int u = newnode(0);
            setfa(mc(p), u, 0);
            setfa(rc(p), u, 2);
            setfa(0, p, 1);
            setfa(u, p, 2);
        }
        for(; fa(p); p = fa(p)) splice(fa(p));
    }
    void makeroot(int p) {access(p), splay(p); upd1rev(p);}
    void expose(int x, int y) {makeroot(x); access(y), splay(y);}
    int findroot(int p) {
        access(p), splay(p);
        while(lc(p)) pushdown(p = lc(p));
        return splay(p), p;
    }
    void link(int x, int y) {
        if(findroot(x) == findroot(y)) return;
        expose(x, y); setfa(x, y, 1);
    }
    void cut(int x, int y) {
        expose(x, y);
        if(lc(y) ^ x || rc(x)) return;
        setfa(x, 0, 0), setfa(0, y, 0);
    }
    void update(int x) {
        access(x), splay(x); upd1vc(x), pushup(x);
    }
    int query() {
        makeroot(1);
        return tr[1].ans.null ? -1 : tr[1].ans.ans;
    }
    #undef fa
    #undef lc
    #undef rc
    #undef mc
}
int n, q;
void Hutao() {
    n = read();
    satt::tr[0].ans.null = 1;
    for(int i = 1; i <= n; i ++) satt::newnode(1, 1, 0);
    for(int i = 1, u, v, w, p; i < n; i ++) {
        u = read(), v = read(), w = read();
        p = satt::newnode(1, 0, w);
        satt::link(u, p), satt::link(p, v);
    }
    q = read();
    char op;
    for(int i = 1, x; i <= q; i ++) {
        op = readch();
        if(op == 'C') x = read(), satt::update(x);
        else x = satt::query(), printf(~x ? "%d\n" : "They have disappeared.\n", x);
    }
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}