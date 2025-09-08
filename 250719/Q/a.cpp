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
const int N = 2e6 + 10;
int s[N];
namespace SA {
    int sa[N], rk[N], id[N], sa0[N], rk0[N << 1], ad[N];
    int buc[N];
    void sort(int n) {
        int m = 100130, cnt = 0;
        for(int i = 1; i <= n; i ++) buc[rk[i] = s[i]] ++;
        for(int i = 1; i <= m; i ++) buc[i] += buc[i - 1];
        for(int i = n; i; i --) sa[buc[s[i]] --] = i;

        for(int w = 1; ; w <<= 1, m = cnt, cnt = 0) {
            for(int i = n; i + w > n; i --) sa0[++ cnt] = i;
            for(int i = 1; i <= n; i ++) if(sa[i] - w > 0) sa0[++ cnt] = sa[i] - w;

            for(int i = 1; i <= m; i ++) buc[i] = 0;
            for(int i = 1; i <= n; i ++) ++ buc[ad[i] = rk[sa0[i]]];
            for(int i = 1; i <= m; i ++) buc[i] += buc[i - 1];
            for(int i = n; i; i --) sa[buc[ad[i]] --] = sa0[i];

            cnt = 0; for(int i = 1; i <= n; i ++) rk0[i] = rk[i];
            for(int i = 1; i <= n; i ++)
                rk[sa[i]] = rk0[sa[i]] == rk0[sa[i - 1]] && rk0[sa[i] + w] == rk0[sa[i - 1] + w] ? cnt : ++ cnt;
            if(cnt == n) return;
        }
    }
    int ht[N];
    void get_height(int n) {
        for(int i = 1, j = 0; i <= n; i ++) {
            j = max(j - 1, 0);
            while(s[i + j] == s[sa[rk[i] - 1] + j]) j ++;
            ht[rk[i]] = j;
        }
    }
}
namespace ST {
    int minn[21][N];
    void build(int n) {
        for(int i = 1; i <= n; i ++)
            minn[0][i] = SA::ht[i];
        for(int i = 1; i <= 20; i ++)
            for(int j = 1; j <= n + 1 - (1 << i); j ++)
                minn[i][j] = min(minn[i - 1][j], minn[i - 1][j + (1 << i - 1)]);
    }
    inline int log2(int n) {
        int res = 0;
        while(n >>= 1) res ++;
        return res;
    }
    int query(int l, int r) {
        int log2n = log2(r - l + 1);
        return min(minn[log2n][l], minn[log2n][r + 1 - (1 << log2n)]);
    }
}
int lcp(int pos1, int pos2) {
    return ST::query(SA::rk[pos1] + 1, SA::rk[pos2]);
}
int n0, n, q;
int pos[N], id[N];
char str[N];
int l[N], r[N];
int lst[N], cnt[N];
void Furina(int n) {
    for(int i = 1; i <= n; i ++) {
        if(lst[id[SA::sa[i]]]) cnt[SA::sa[i]] = lcp(lst[id[SA::sa[i]]], SA::sa[i]);
        lst[id[SA::sa[i]]] = SA::sa[i];
    }
}
struct node {
    int sum;
    int lc, rc;
};
namespace pt {
    node tr[N * 20];
    int tot, rt[N];
    void pushup(int p) {
        tr[p].sum = tr[tr[p].lc].sum + tr[tr[p].rc].sum;
    }
    void update(int x, int p, int p0, int l = 1, int r = n0) {
        tr[p] = tr[p0];
        if(l == r) return void(++ tr[p].sum);
        int mid = l + r >> 1;
        if(x <= mid) {
            tr[p].lc = ++ tot;
            update(x, tr[p].lc, tr[p0].lc, l, mid);
        } else {
            tr[p].rc = ++ tot;
            update(x, tr[p].rc, tr[p0].rc, mid + 1, r);
        }
        pushup(p);
    }
    int query(int ql, int qr, int p, int p0, int l = 1, int r = n0) {
        if(ql > qr) return 0;
        if(ql <= l && r <= qr) return tr[p].sum - tr[p0].sum;
        int mid = l + r >> 1, res = 0;
        if(ql <= mid) res += query(ql, qr, tr[p].lc, tr[p0].lc, l, mid);
        if(qr > mid) res += query(ql, qr, tr[p].rc, tr[p0].rc, mid + 1, r);
        return res;
    }
    void u(int x, int ver, int ver0) {
        if(x > n0) return void(rt[ver] = rt[ver0]);
        rt[ver] = ++ tot;
        update(x, rt[ver], rt[ver0]);
    }
    int q(int x1, int x2, int y1, int y2) {
        return query(y1, y2, rt[x2], rt[x1 - 1]);
    }
}
bool Skirk(int pos, int p, int tid) {
    int lb = SA::rk[pos], ub = SA::rk[pos];
    for(int i = 20; ~i; -- i) {
        if(1 << i >= lb) continue;
        if(ST::minn[i][lb - (1 << i) + 1] >= p) lb -= 1 << i;
    }
    for(int i = 20; ~i; -- i) {
        if(1 << i > n - ub) continue;
        if(ST::minn[i][ub + 1] >= p) ub += 1 << i;
    }
    return pt::q(lb, ub, l[tid], r[tid] + 1 - p) > 0;
}
void Hutao() {
    scanf("%s", str + 1); n0 = n = strlen(str + 1);
    for(int i = 1; i <= n; i ++) s[i] = str[i];
    s[++ n] = 128;
    scanf("%d", &q);
    for(int i = 1, len; i <= q; i ++) {
        scanf("%s%d%d", str + 1, l + i, r + i); len = strlen(str + 1);
        pos[i] = n + 1;
        for(int j = 1; j <= len; j ++)
            s[n + j] = str[j], id[n + j] = i;
        n += len;
        s[++ n] = 128 + i;
    }
    pos[q + 1] = n + 1;
    SA::sort(n);
    SA::get_height(n);
    ST::build(n);
    Furina(n);
    for(int i = 1; i <= n; i ++)
        pt::u(SA::sa[i], i, i - 1);
    for(int i = 1; i <= q; i ++) {
        ll ans = 1ll * (pos[i + 1] - pos[i] - 1) * (pos[i + 1] - pos[i]) >> 1;
        for(int j = pos[i], cur = 0; j < pos[i + 1] - 1; j ++) {
            for(cur = max(cur - 1, 0); Skirk(j, cur + 1, i); cur ++);
            ans -= max(cnt[j], cur);
        }
        printf("%lld\n", ans);
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}