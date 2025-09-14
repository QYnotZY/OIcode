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
const int N = 2e5 + 10;
auto fate = []{return 0;};
namespace fhqt {
    struct node {
        int key, lc, rc;
        int l, r, id, val, tag;
    } tr[N * 3];
    int tot, rt, rcyc[N * 3];
    int newnode(int l, int r, int id) {
        int p = rcyc[0] ? rcyc[rcyc[0] --] : ++ tot;
        tr[p].key = fate();
        tr[p].l = l, tr[p].r = r, tr[p].id = id;
        tr[p].lc = tr[p].rc = tr[p].val = tr[p].tag = 0;
        return p;
    }
    void delnode(int p) {rcyc[++ rcyc[0]] = p;}
    void pushup(int p) {
        int &lc = tr[p].lc, &rc = tr[p].rc;
    }
    void add1(int p, int v) {
        if(!p) return;
        tr[p].val += v;
        tr[p].tag += v;
    }
    void pushdn(int p) {
        int &lc = tr[p].lc, &rc = tr[p].rc;
        add1(lc, tr[p].tag);
        add1(rc, tr[p].tag);
        tr[p].tag = 0;
    }
    void split(int p, int k, int &x, int &y) {
        if(!p) return void(x = y = 0);
        pushdn(p);
        int &lc = tr[p].lc, &rc = tr[p].rc;
        if(k <= tr[p].r) y = p, split(lc, k, x, lc);
        else x = p, split(rc, p, rc, y);
        pushup(p);
    }
    int merge(int x, int y) {
        if(!x || !y) return x | y;
        int p;
        if(tr[x].key > tr[y].key) pushdn(p = x), tr[p].rc = merge(tr[p].rc, y);
        else pushdn(p = y), tr[p].lc = merge(x, tr[p].lc);
        return pushup(p), p;
    }
}
void Hutao() {
    
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}