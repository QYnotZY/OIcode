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
namespace lct {
    struct node {
        int fa, ch[2], sz;
        int val, chn;
        int rev_tag;
    } tr[N];
    int rt;
    inline bool isroot(const int& p) {
        return tr[tr[p].fa].ch[0] ^ p && tr[tr[p].fa].ch[1] ^ p;
    }
    inline int direct(const int& p) {  // p isn't a root
        return tr[tr[p].fa].ch[0] ^ p ? 1 : 0;
    }
    inline void pushup(int p) {
        int &lc = tr[p].ch[0], &rc = tr[p].ch[1];
        tr[p].sz = tr[lc].sz + 1 + tr[rc].sz;
        tr[p].chn = tr[lc].chn ^ tr[p].val ^ tr[rc].chn;
    }
    inline void upd1_rev(int p) {
        swap(tr[p].ch[0], tr[p].ch[1]);
        tr[p].rev_tag ^= 1;
    }
    inline void pushdown(int p) {
        if(tr[p].rev_tag) {
            if(tr[p].ch[0]) upd1_rev(tr[p].ch[0]);
            if(tr[p].ch[1]) upd1_rev(tr[p].ch[1]);
            tr[p].rev_tag = 0;
        }
    }
    inline void pushall(int p) {
        if(!isroot(p)) pushall(tr[p].fa); pushdown(p);
    }
    inline void rotate(int p) {  // p isn't a root
        int x = p, y = tr[x].fa, z = tr[y].fa, dir = direct(x);
        tr[x].fa = z; if(!isroot(y)) tr[z].ch[direct(y)] = x;
        tr[tr[x].ch[dir ^ 1]].fa = y; tr[y].ch[dir] = tr[x].ch[dir ^ 1];
        tr[y].fa = x; tr[x].ch[dir ^ 1] = y;
        pushup(y), pushup(x);
    }
    void splay(int p) {
        pushall(p);
        for(; !isroot(p); rotate(p))
            if(!isroot(tr[p].fa))
                direct(p) ^ direct(tr[p].fa) ? rotate(p) : rotate(tr[p].fa);
    }
    int access(int p) {
        int lst = 0;
        for(; p; lst = p, p = tr[p].fa)
            splay(p), tr[p].ch[1] = lst, pushup(p);
        return lst;
    }
    void makeroot(int p) {
        upd1_rev(access(p));
    }
    int findroot(int p) {
        access(p), splay(p);
        while(tr[p].ch[0]) pushdown(p = tr[p].ch[0]);
        splay(p);
        return p;
    }
    bool split(int x, int y) {
        makeroot(x), access(y);
        return findroot(y) == x;
    }
    bool link(int x, int y) {
        makeroot(y), splay(y);
        if(findroot(x) == y) return false;
        tr[y].fa = x; return true;
    }
    bool cut(int x, int y) {
        if(!split(x, y)) return false;
        splay(y);
        if(tr[y].ch[0] ^ x || tr[x].ch[1]) return false;
        tr[x].fa = tr[y].ch[0] = 0;
        return true;
    }
    void update(int p, int val) {
        splay(p);
        tr[p].val = val;
    }
    int query(int x, int y) {
        split(x, y);
        splay(x);
        return tr[x].chn;
    }
}
int n, m;
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= n; i ++) lct::tr[i].val = read();
    for(int i = 1, op, x, y; i <= m; i ++) {
        op = read(), x = read(), y = read();
        if(op == 0) printf("%d\n", lct::query(x, y));
        if(op == 1) lct::link(x, y);
        if(op == 2) lct::cut(x, y);
        if(op == 3) lct::update(x, y);
    }
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}