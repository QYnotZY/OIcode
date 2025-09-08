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
const int N = 1e5 + 10, eof = (1 << 30) + 0610;
int mod;
inline int Mod(int a) {return (a % mod + mod) % mod;}
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
int n, m, rt;
namespace dick {
    struct node {
        int fa, ch[3];
        int typ, chnsz, subsz;
        int val, chn, sub;
        int revtag, chntag, subtag;
    } tr[N * 3];
    int tot, rcyc[N];
    int newnode(int val = eof) {
        int p = rcyc[0] ? rcyc[rcyc[0] --] : ++ tot;
        tr[p].typ = tr[p].chnsz = val != eof;
        tr[p].val = tr[p].chn = val == eof ? 0 : val;
        return p;
    }
    void delnode(int p) {
        rcyc[++ rcyc[0]] = p;
        memset(tr + p, 0, sizeof(node));
    }
    #define fa(x) tr[x].fa
    #define lc(x) tr[x].ch[0]
    #define rc(x) tr[x].ch[1]
    #define mc(x) tr[x].ch[2]
    void print(int p) {
        printf("%d: ", p);
        printf("%d %d %d %d  ", fa(p), lc(p), rc(p), mc(p));
        printf("%d %d %d  ", tr[p].typ, tr[p].chnsz, tr[p].subsz);
        printf("%d %d %d  ", tr[p].val, tr[p].chn, tr[p].sub);
        printf("%d %d %d\n", tr[p].revtag, tr[p].chntag, tr[p].subtag);
    }
    void print() {
        for(int i = 1; i <= tot; i ++)
            if(i <= n || tr[i].fa)
                print(i);
    }
    inline bool isroot(int p) {return lc(fa(p)) ^ p && rc(fa(p)) ^ p;}
    inline int direct(int p) {return rc(fa(p)) == p;}
    void pushup(int p) {
        tr[p].chnsz = tr[p].typ + tr[lc(p)].chnsz + tr[rc(p)].chnsz;
        tr[p].subsz = tr[mc(p)].chnsz + tr[mc(p)].subsz + tr[lc(p)].subsz + tr[rc(p)].subsz;
        tr[p].chn = Add(tr[p].val, Add(tr[lc(p)].chn, tr[rc(p)].chn));
        tr[p].sub = Add(Add(tr[mc(p)].chn, tr[mc(p)].sub), Add(tr[lc(p)].sub, tr[rc(p)].sub));
    }
    inline void setfa(int p, int f, int typ) {if(p) tr[p].fa = f; if(f) tr[f].ch[typ] = p;}
    void upd1rev(int p) {
        swap(lc(p), rc(p));
        tr[p].revtag ^= 1;
    }
    void upd1cadd(int p, int val) {
        tr[p].val = Add(tr[p].val, Mult(val, tr[p].typ));
        tr[p].chn = Add(tr[p].chn, Mult(val, tr[p].chnsz));
        tr[p].chntag = Add(tr[p].chntag, val);
    }
    void upd1sadd(int p, int val) {
        tr[p].sub = Add(tr[p].sub, Mult(val, tr[p].subsz));
        tr[p].subtag = Add(tr[p].subtag, val);
    }
    void pushdown(int p) {
        if(tr[p].revtag) {
            if(lc(p)) upd1rev(lc(p));
            if(rc(p)) upd1rev(rc(p));
            tr[p].revtag = 0;
        }
        if(tr[p].chntag) {
            if(lc(p)) upd1cadd(lc(p), tr[p].chntag);
            if(rc(p)) upd1cadd(rc(p), tr[p].chntag);
            tr[p].chntag = 0;
        }
        if(tr[p].subtag) {
            if(lc(p)) upd1sadd(lc(p), tr[p].subtag);
            if(rc(p)) upd1sadd(rc(p), tr[p].subtag);
            if(mc(p)) upd1cadd(mc(p), tr[p].subtag), upd1sadd(mc(p), tr[p].subtag);
            tr[p].subtag = 0;
        }
    }
    void pushall(int p) {
        if(!isroot(p)) pushall(fa(p)); pushdown(p);
    }
    void rotate(int p) {
        int x = p, y = fa(x), z = fa(y), dir = direct(x), w = tr[x].ch[dir ^ 1];
        setfa(x, z, isroot(y) ? 2 : direct(y));
        setfa(y, x, dir ^ 1);
        setfa(w, y, dir);
        pushup(y), pushup(x);
    }
    void splay(int p, int goal = 0) {
        pushall(p);
        for(; fa(p) ^ goal && !isroot(p); rotate(p))
            if(fa(fa(p)) ^ goal && !isroot(fa(p)))
                rotate(direct(fa(p)) ^ direct(p) ? p : fa(p));
    }
    void destruct(int p) {
        if(lc(p)) {
            int u = lc(p); pushdown(u);
            while(rc(u)) pushdown(u = rc(u));
            splay(u, p);
            setfa(rc(p), u, 1);
            setfa(u, fa(p), 2);
            pushup(u), pushup(fa(p));
        } else {
            setfa(rc(p), fa(p), 2);
            pushup(fa(p));
        }
        delnode(p);
    }
    void splice(int p) {
        int f;
        splay(p), splay(f = fa(p));
        pushdown(p);
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
        int goal = p;
        splay(p);
        if(rc(p)) {
            int u = newnode();
            setfa(mc(p), u, 0);
            setfa(rc(p), u, 2);
            setfa(0, p, 1);
            setfa(u, p, 2);
            pushup(u), pushup(p);
        }
        while(fa(p)) {
            splice(fa(p));
            p = fa(p);
        }
        splay(goal);
    }
    void makeroot(int p) {access(p), upd1rev(p);}
    void expose(int x, int y) {makeroot(x), access(y);}
    int findroot(int p) {
        access(p);
        while(lc(p)) p = lc(p);
        return splay(p), p;
    }
    bool link(int x, int y) {
        if(findroot(x) == findroot(y)) return false;
        makeroot(x), access(y), setfa(x, y, 1), pushup(y); return true;
    }
    bool cut(int x, int y) {
        expose(x, y);
        if(lc(y) ^ x || rc(x)) return false;
        fa(x) = lc(y) = 0; pushup(y); return true;
    }
    void updatec(int x, int y, int z) {
        expose(x, y);
        upd1cadd(y, z);
    }
    int queryc(int x, int y) {
        expose(x, y);
        return tr[y].chn;
    }
    void updates(int x, int z) {
        expose(rt, x);
        tr[x].val = Add(tr[x].val, z);
        if(mc(x)) upd1sadd(mc(x), z);
        pushup(x);
    }
    int querys(int x) {
        expose(rt, x);
        return Add(tr[x].val, tr[mc(x)].sub);
    }
    #undef fa
    #undef lc
    #undef rc
    #undef mc
}
void Hutao() {
    n = read(), m = read(), rt = read(), mod = read();
    for(int i = 1, x; i <= n; i ++) {
        x = read();
        dick::newnode(Mod(x));
    }
    for(int i = 1, u, v; i < n; i ++) {
        u = read(), v = read();
        dick::link(u, v);
    }
    for(int i = 1, op, x, y, z; i <= m; i ++) {
        op = read(), x = read();
        if(op == 4) {
            printf("%d\n", dick::querys(x));
        } else {
            y = read();
            if(op == 2) {
                printf("%d\n", dick::queryc(x, y));
            } else if(op == 3) {
                dick::updates(x, y);
            } else {
                z = read();
                dick::updatec(x, y, z);
            }
        }
    }
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}