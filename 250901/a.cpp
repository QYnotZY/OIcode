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
const int N = 3e5 + 10;
namespace satt {
    struct node {
        int fa, ch[3];
        int typ;
        int sz, maxsz;
        int revtag;
    } tr[N << 1];
    int tot, rcyc[N];
    int newnode(int typ) {
        int p = rcyc[0] ? rcyc[rcyc[0] --] : ++ tot;
        memcpy(tr + p, tr, sizeof(node));
        tr[p].typ = tr[p].sz = typ;
        return p;
    }
    void delnode(int p) {
        rcyc[++ rcyc[0]] = p;
    }
    void init() {
        memset(tr, 0, sizeof(node));
        tot = 0, rcyc[0] = 0;
    }
    #define fa(x) tr[x].fa
    #define lc(x) tr[x].ch[0]
    #define rc(x) tr[x].ch[1]
    #define mc(x) tr[x].ch[2]
    void pushup(int p) {
        if(tr[p].typ) {
            tr[p].sz = tr[lc(p)].sz + tr[rc(p)].sz + tr[mc(p)].sz + 1;
        } else {
            tr[p].sz = tr[lc(p)].sz + tr[rc(p)].sz + tr[mc(p)].sz;
            tr[p].maxsz = max(tr[mc(p)].sz, max(tr[lc(p)].maxsz, tr[rc(p)].maxsz));
        }
    }
    void upd1rev(int p) {
        if(!tr[p].typ) return;
        swap(lc(p), rc(p));
        tr[p].revtag ^= 1;
    }
    void pushdown(int p) {
        if(tr[p].revtag) {
            upd1rev(lc(p)), upd1rev(rc(p));
            tr[p].revtag ^= 1;
        }
    }
    inline bool isroot(int p) {return lc(fa(p)) ^ p && rc(fa(p)) ^ p;}
    inline int direct(int p) {return rc(fa(p)) == p;}
    inline void setfa(int p, int f, int dir) {if(p) fa(p) = f; if(f) tr[f].ch[dir] = p, pushup(f);}
    void rotate(int p) {
        int x = p, y = fa(x), z = fa(y), dx = direct(x), w = tr[x].ch[dx ^ 1], dy = isroot(y) ? 2 : direct(y);
        setfa(w, y, dx), setfa(y, x, dx ^ 1), setfa(x, z, dy);
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
    int findroot(int p) {
        access(p), splay(p);
        while(lc(p)) pushdown(p = lc(p));
        return splay(p), p;
    }
    void expose(int x, int y) {makeroot(x); access(y), splay(y);}
    void link(int x, int y) {
        if(findroot(x) == findroot(y)) return;
        expose(x, y); setfa(x, y, 1);
    }
    void cut(int x, int y) {
        expose(x, y);
        if(lc(y) ^ x || rc(x)) return;
        setfa(x, 0, 0), setfa(0, y, 0);
    }
    int c1, c2;
    void search(int p, int sum, int addl, int addr) {
        pushdown(p);
        if(tr[p].typ) {
            if(lc(p) && (tr[lc(p)].sz + addl) << 1 >= sum) {
                if((tr[lc(p)].sz + addl) << 1 == sum) (c1 ? c2 : c1) = p;
                return search(lc(p), sum, addl, addr + tr[p].sz - tr[lc(p)].sz);
            }
            if(rc(p) && (tr[rc(p)].sz + addr) << 1 >= sum) {
                if((tr[rc(p)].sz + addr) << 1 == sum) (c1 ? c2 : c1) = p;
                return search(rc(p), sum, addl + tr[p].sz - tr[rc(p)].sz, addr);
            }
            if(mc(p) && tr[mc(p)].maxsz << 1 >= sum) {
                if(tr[mc(p)].maxsz << 1 == sum) (c1 ? c2 : c1) = p;
                return search(mc(p), sum, sum - tr[mc(p)].maxsz, 0);
            }
            (c1 ? c2 : c1) = p;
        } else {
            if(tr[p].maxsz == tr[lc(p)].maxsz) return search(lc(p), sum, addl, addr);
            if(tr[p].maxsz == tr[rc(p)].maxsz) return search(rc(p), sum, addl, addr);
            search(mc(p), sum, addl, addr);
        }
    }
    int query(int x) {
        makeroot(x);
        c1 = c2 = 0;
        search(x, tr[x].sz, 0, 0);
        if(c1) access(c1), splay(c1);
        if(c2) access(c2), splay(c2);
        return c1 + c2;
    }
    #undef fa
    #undef lc
    #undef rc
    #undef mc
}
int n, ed[N][2];
ll ans;
void Hutao() {
    satt::init(); ans = 0;
    n = read();
    for(int i = 1; i <= n; i ++) satt::newnode(1);
    for(int i = 1; i < n; i ++) {
        ed[i][0] = read(), ed[i][1] = read();
        satt::link(ed[i][0], ed[i][1]);
    }
    for(int i = 1; i < n; i ++) {
        satt::cut(ed[i][0], ed[i][1]);
        ans += satt::query(ed[i][0]) + satt::query(ed[i][1]);
        satt::link(ed[i][0], ed[i][1]);
    }
    printf("%lld\n", ans);
}
}
int main() {
    int t = read(); while(t --) Qiuyu3600::Hutao();
    return 0;
}