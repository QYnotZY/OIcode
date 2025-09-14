#include "bits/stdc++.h"
using namespace std;
namespace FastIO {
    template<typename T = int> T read() {
        char ch = getchar(); bool neg = 0; T res = 0;
        for(; !('0' <= ch && ch <= '9'); ch = getchar()) if(ch == '-') neg = !neg;
        for(; ('0' <= ch && ch <= '9'); ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ 48);
        return neg ? ~res + 1 : res;
    }
    char readch(bool acsp = 0) {
        char ch = getchar(); for(; !(33 - acsp <= ch && ch < 127); ch = getchar()); return ch;
    }
} using namespace FastIO;
typedef long long ll;
namespace Qiuyu3600 {
const int N = 2e5 + 10, logn = 20, loga = 30;
int n, a[N], s[N];
namespace trie {
    struct node {
        int ch[2];
    } tr[N * 4 * loga];
    int rt[N], tot, rcyc[N * 4 * loga];
    void init() {memset(rt, 0, n + 1 << 2); tot = rcyc[0] = 0;}
    int newnode() {int p = rcyc[0] ? rcyc[rcyc[0] --] : ++ tot; tr[p].ch[0] = tr[p].ch[1] = 0; return p;}
    void delnode(int p) {rcyc[++ rcyc[0]] = p;}
    void insert(int pos, int val) {
        if(!rt[pos]) rt[pos] = newnode();
        int u = rt[pos];
        for(int i = loga - 1, dir; ~i; -- i) {
            dir = val >> i & 1;
            if(!tr[u].ch[dir]) tr[u].ch[dir] = newnode();
            u = tr[u].ch[dir];
        }
    }
    int query(int pos, int val) {
        int u = rt[pos], res = 0;
        for(int i = loga - 1, dir; ~i; -- i) {
            dir = 1 ^ (val >> i & 1);
            if(tr[u].ch[dir]) {
                res |= 1 << i;
                u = tr[u].ch[dir];
            } else u = tr[u].ch[dir ^ 1];
        }
        return res;
    }
    int merge_(int p, int q) {
        if(!p || !q) return p | q;
        tr[p].ch[0] = merge_(tr[p].ch[0], tr[q].ch[0]);
        tr[p].ch[1] = merge_(tr[p].ch[1], tr[q].ch[1]);
        return delnode(q), p;
    }
    void merge(int x, int y) {
        rt[x] = merge_(rt[x], rt[y]);
    }
}
namespace st {
    struct node {
        int pos, val;
        bool operator < (const node &obj) const {
            return val < obj.val;
        }
    } maxx[logn][N];
    void init() {
        for(int i = 1; i <= n; i ++) maxx[0][i] = {i, a[i]};
        for(int i = 1; i < logn; i ++)
            for(int j = 1; j + (i << 1) - 1 <= n; j ++)
                maxx[i][j] = max(maxx[i - 1][j], maxx[i - 1][j + (1 << i - 1)]);
    }
    int query(int l, int r) {
        int tmp = __lg(r - l + 1);
        return max(maxx[tmp][l], maxx[tmp][r + 1 - (1 << tmp)]).pos;
    }
}
int ans;
int solve(int l, int r) {
    if(l > r) return 0;
    else if(l == r) return l;
    int p = st::query(l, r);
    int lc = solve(l, p - 1), rc = solve(p + 1, r);
    if(p - l <= r - p)
        for(int i = l - 1; i < p; i ++)
            ans = max(ans, trie::query(rc, a[p] ^ s[i]));
    else
        for(int i = r; i >= p; i --)
            ans = max(ans, trie::query(lc, a[p] ^ s[i]));
    trie::merge(p, lc), trie::merge(p, rc);
    return p;
}
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read(), s[i] = s[i - 1] ^ a[i];
    trie::init();
    for(int i = 1; i <= n; i ++)
        trie::insert(i, s[i - 1]), trie::insert(i, s[i]);
    st::init();
    ans = 0; solve(1, n);
    printf("%d\n", ans);
}
}
int main() {
    int t = read(); while(t --) Qiuyu3600::Hutao();
    return 0;
}