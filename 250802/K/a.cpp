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
const int N = 2e5 + 10;
int n;
namespace smts {
    int rt[N], tot;
    struct node {
        int val, lc, rc;
    } tr[N * 20];
    void pushup(int p) {
        tr[p].val = tr[tr[p].lc].val + tr[tr[p].rc].val;
    }
    int create(int x, int l = 1, int r = n) {
        int cur = ++ tot;
        if(l == r) {
            tr[cur].val = 1;
            return cur;
        }
        int mid = l + r >> 1;
        if(x <= mid) tr[cur].lc = create(x, l, mid);
        else tr[cur].rc = create(x, mid + 1, r);
        pushup(cur);
        return cur;
    }
    ll res0, res1;
    int merge(int p, int q, int l = 1, int r = n) {
        if(l == 1 && r == n) res0 = res1 = 0;
        if(!p || !q) return p ^ q;
        res0 += 1ll * tr[tr[p].rc].val * tr[tr[q].lc].val;
        res1 += 1ll * tr[tr[q].rc].val * tr[tr[p].lc].val;
        int mid = l + r >> 1;
        int lc = merge(tr[p].lc, tr[q].lc, l, mid);
        int rc = merge(tr[p].rc, tr[q].rc, mid + 1, r);
        int cur = p;
        tr[cur].lc = lc, tr[cur].rc = rc;
        pushup(cur);
        return cur;
    }
} using smts::rt;
ll ans;
int dfs() {
    int x = read();
    if(x) {
        rt[x] = smts::create(x);
        return rt[x];
    }
    int lc = dfs(), rc = dfs();
    x = smts::merge(lc, rc);
    ans += min(smts::res0, smts::res1);
    return x;
}
void Hutao() {
    n = read();
    dfs();
    printf("%lld\n", ans);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}