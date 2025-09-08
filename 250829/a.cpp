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
const int N = 1e5 + 10, eof = INT32_MIN, inf = INT32_MAX;
namespace satt {
    struct node {
        int fa, ch[3];
        int typ, chnsz, subsz;
        int val, chnsum, chnmin, chnmax, subsum, submin, submax;
        int revtag, ccovtag, caddtag, scovtag, saddtag;
    } tr[N << 1];
    int rt, tot, rcyc[N];
    void getnode0() {
        memset(tr, 0, sizeof(node));
        tr[0].chnmin = tr[0].submin = inf;
        tr[0].chnmax = tr[0].submax = -inf;
        tr[0].ccovtag = tr[0].scovtag = eof;
    }
    int newnode(int typ) {
        int p = rcyc[0] ? rcyc[rcyc[0] --] : ++ tot;
        memcpy(tr + p, tr, sizeof(node));
        tr[p].typ = tr[p].chnsz = typ;
        return p;
    }
    void delnode(int p) {
        rcyc[++ rcyc[0]] = p;
    }
    void build(int n) {
        getnode0();
        for(int i = 1; i <= n; i ++) newnode(1);
    }
    #define fa(x) tr[x].fa
    #define lc(x) tr[x].ch[0]
    #define rc(x) tr[x].ch[1]
    #define mc(x) tr[x].ch[2]
    void pushup(int p) {
        if(!p) return;
        tr[p].chnsz = tr[p].typ + tr[lc(p)].chnsz + tr[rc(p)].chnsz;
        tr[p].subsz = tr[mc(p)].chnsz + tr[mc(p)].subsz + tr[lc(p)].subsz + tr[rc(p)].subsz;
        if(tr[p].typ) {
            tr[p].chnsum = tr[p].val + tr[lc(p)].chnsum + tr[rc(p)].chnsum;
            tr[p].chnmin = min(tr[p].val, min(tr[lc(p)].chnmin, tr[rc(p)].chnmin));
            tr[p].chnmax = max(tr[p].val, max(tr[lc(p)].chnmax, tr[rc(p)].chnmax));
            tr[p].subsum = tr[mc(p)].subsum + tr[lc(p)].subsum + tr[rc(p)].subsum;
            tr[p].submin = min(tr[mc(p)].submin, min(tr[lc(p)].submin, tr[rc(p)].submin));
            tr[p].submax = max(tr[mc(p)].submax, max(tr[lc(p)].submax, tr[rc(p)].submax));
        } else {
            tr[p].subsum = tr[mc(p)].chnsum + tr[mc(p)].subsum + tr[lc(p)].subsum + tr[rc(p)].subsum;
            tr[p].submin = min(min(tr[mc(p)].chnmin, tr[mc(p)].submin), min(tr[lc(p)].submin, tr[rc(p)].submin));
            tr[p].submax = max(max(tr[mc(p)].chnmax, tr[mc(p)].submax), max(tr[lc(p)].submax, tr[rc(p)].submax));
        }
    }
    void upd1rev(int p) {
        if(!tr[p].typ) return;
        swap(lc(p), rc(p));
        tr[p].revtag ^= 1;
    }
    void upd1ccov(int p, int v) {
        if(!tr[p].typ) return;
        tr[p].val = v;
        tr[p].chnsum = v * tr[p].chnsz;
        tr[p].chnmin = tr[p].chnmax = v;
        tr[p].ccovtag = v, tr[p].caddtag = 0;
    }
    void upd1cadd(int p, int v) {
        if(!tr[p].typ) return;
        tr[p].val += v;
        tr[p].chnsum += v * tr[p].chnsz;
        tr[p].chnmin += v, tr[p].chnmax += v;
        tr[p].caddtag += v;
    }
    void upd1scov(int p, int v) {
        if(!tr[p].subsz) return; // !
        tr[p].subsum = v * tr[p].subsz;
        tr[p].submin = tr[p].submax = v;
        tr[p].scovtag = v, tr[p].saddtag = 0;
    }
    void upd1sadd(int p, int v) {
        if(!tr[p].subsz) return;
        tr[p].subsum += v * tr[p].subsz;
        tr[p].submin += v, tr[p].submax += v;
        tr[p].saddtag += v;
    }
    void pushdown(int p) {
        if(tr[p].typ) {
            if(tr[p].revtag) {
                upd1rev(lc(p));
                upd1rev(rc(p));
                tr[p].revtag = 0;
            }
            if(tr[p].ccovtag ^ eof) {
                upd1ccov(lc(p), tr[p].ccovtag);
                upd1ccov(rc(p), tr[p].ccovtag);
                tr[p].ccovtag = eof;
            }
            if(tr[p].caddtag) {
                upd1cadd(lc(p), tr[p].caddtag);
                upd1cadd(rc(p), tr[p].caddtag);
                tr[p].caddtag = 0;
            }
            if(tr[p].scovtag ^ eof) {
                upd1scov(lc(p), tr[p].scovtag);
                upd1scov(rc(p), tr[p].scovtag);
                upd1scov(mc(p), tr[p].scovtag);
                tr[p].scovtag = eof;
            }
            if(tr[p].saddtag) {
                upd1sadd(lc(p), tr[p].saddtag);
                upd1sadd(rc(p), tr[p].saddtag);
                upd1sadd(mc(p), tr[p].saddtag);
                tr[p].saddtag = 0;
            }
        } else {
            if(tr[p].scovtag ^ eof) {
                upd1scov(lc(p), tr[p].scovtag);
                upd1scov(rc(p), tr[p].scovtag);
                upd1ccov(mc(p), tr[p].scovtag), upd1scov(mc(p), tr[p].scovtag);
                tr[p].scovtag = eof;
            }
            if(tr[p].saddtag) {
                upd1sadd(lc(p), tr[p].saddtag);
                upd1sadd(rc(p), tr[p].saddtag);
                upd1cadd(mc(p), tr[p].saddtag), upd1sadd(mc(p), tr[p].saddtag);
                tr[p].saddtag = 0;
            }
        }
    }
    inline bool isroot(int x) {return lc(fa(x)) ^ x && rc(fa(x)) ^ x;}
    inline bool direct(int x) {return rc(fa(x)) == x;}
    inline void setfa(int x, int f, int typ) {if(x) fa(x) = f; if(f) tr[f].ch[typ] = x, pushup(f);}
    void pushall(int p) {if(!isroot(p)) pushall(fa(p)); pushdown(p);}
    void rotate(int p) {
        int x = p, y = fa(x), z = fa(y), dx = direct(x), w = tr[x].ch[dx ^ 1], dy = isroot(y) ? 2 : direct(y);
        setfa(w, y, dx), setfa(y, x, dx ^ 1), setfa(x, z, dy);
    }
    void splay(int p, int aim = 0) {
        pushall(p);
        for(; !isroot(p) && fa(p) ^ aim; rotate(p))
            if(!isroot(fa(p)) && fa(fa(p)) ^ aim)
                direct(fa(p)) == direct(p) ? rotate(fa(p)) : rotate(p);
    }
    void destruct(int p) {
        if(lc(p)) {
            int u = lc(p);
            while(rc(u)) pushdown(u), u = rc(u);
            splay(u, p);
            setfa(rc(p), u, 1);
            setfa(u, fa(p), 2);
        } else setfa(rc(p), fa(p), 2);
        delnode(p);
    }
    void splice(int p) {
        int f;
        splay(p), splay(f = fa(p)/*!!*/), pushdown(p);
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
            setfa(0, p, 1); // !
            setfa(u, p, 2);
        }
        for(; fa(p); p = fa(p)) splice(fa(p));
    }
    void makeroot(int p) {
        access(p), splay(p);
        upd1rev(p);
    }
    int findroot(int p) {
        access(p), splay(p);
        while(lc(p)) pushdown(p), p = lc(p);
        return splay(p), p;
    }
    void expose(int x, int y) {
        makeroot(x);
        access(y), splay(y);
    }
    int findfa(int p) {
        expose(rt, p); // !
        if(!(p = lc(p))) return 0;
        while(rc(p)) pushdown(p), p = rc(p);
        return splay(p), p;
    }
    void link(int x, int y) {
        if(findroot(x) == findroot(y)) return;
        access(x), splay(x), makeroot(y);
        setfa(y, x, 1);
    }
    void cut(int x, int y) {
        expose(x, y);
        if(lc(y) ^ x || rc(x)) return;
        setfa(x, 0, 0), setfa(0, y, 0);
    }
    void change_root(int x) {rt = x;}
    void change_father(int x, int y) {
        if(x == rt) return;
        int f = findfa(x); cut(f, x);
        findroot(x) == findroot(y) ? link(f, x) : link(x, y);
    }
    void update_path_cover(int x, int y, int v) {
        expose(x, y);
        upd1ccov(y, v);
    }
    void update_path_add(int x, int y, int v) {
        expose(x, y);
        upd1cadd(y, v);
    }
    void update_subtree_cover(int x, int v) {
        expose(rt, x);
        tr[x].val = v, upd1scov(mc(x), v), pushup(x);
    }
    void update_subtree_add(int x, int v) {
        expose(rt, x);
        tr[x].val += v, upd1sadd(mc(x), v), pushup(x);
    }
    int query_path_summary(int x, int y) {
        expose(x, y);
        return tr[y].chnsum;
    }
    int query_path_minimum(int x, int y) {
        expose(x, y);
        return tr[y].chnmin;
    }
    int query_path_maximum(int x, int y) {
        expose(x, y);
        return tr[y].chnmax;
    }
    int query_subtree_summary(int x) {
        expose(rt, x);
        return tr[x].val + tr[mc(x)].subsum;
    }
    int query_subtree_minimum(int x) {
        expose(rt, x);
        return min(tr[x].val, tr[mc(x)].submin);
    }
    int query_subtree_maximum(int x) {
        expose(rt, x);
        return max(tr[x].val, tr[mc(x)].submax);
    }
    #undef fa
    #undef lc
    #undef rc
    #undef mc
}
int n, q;
void Hutao() {
    n = read(), q = read();
    satt::build(n);
    for(int i = 1, u, v; i < n; i ++) {
        u = read(), v = read();
        satt::link(u, v);
    }
    for(int i = 1, v; i <= n; i ++) {
        v = read();
        satt::update_path_cover(i, i, v);
    }
    satt::change_root(read());
    for(int i = 1, op, x, y, z; i <= q; i ++) {
        switch(op = read()) {
            case 0 : x = read(), y = read(); satt::update_subtree_cover(x, y); break;
            case 1 : x = read(); satt::change_root(x); break;
            case 2 : x = read(), y = read(), z = read(); satt::update_path_cover(x, y, z); break;
            case 3 : x = read(); printf("%d\n", satt::query_subtree_minimum(x)); break;
            case 4 : x = read(); printf("%d\n", satt::query_subtree_maximum(x)); break;
            case 5 : x = read(), y = read(); satt::update_subtree_add(x, y); break;
            case 6 : x = read(), y = read(), z = read(); satt::update_path_add(x, y, z); break;
            case 7 : x = read(), y = read(); printf("%d\n", satt::query_path_minimum(x, y)); break;
            case 8 : x = read(), y = read(); printf("%d\n", satt::query_path_maximum(x, y)); break;
            case 9 : x = read(), y = read(); satt::change_father(x, y); break;
            case 10 : x = read(), y = read(); printf("%d\n", satt::query_path_summary(x, y)); break;
            case 11 : x = read(); printf("%d\n", satt::query_subtree_summary(x)); break;
        }
    }
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}