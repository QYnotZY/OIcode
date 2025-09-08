#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
char gc() {return getchar();}
template<typename T = int>
inline T readnum(){
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
template<typename T = int>
T read() {return readnum<T>();}
}
using FastIO::read;
typedef long long ll;

const int N = 5e5 + 10, inf = 5e5;
int n, m;
namespace hjtt{
    int tot, head[N], totver;
    struct node{
        int c[2];
        int cnt; ll sum;
    } tr[N * 20];
    int newnode(){
        tr[++ tot] = {{0, 0}, 0, 0ll};
        return tot;
    }
    void pushup(int p){
        int lc = tr[p].c[0], rc = tr[p].c[1];
        tr[p].cnt = tr[lc].cnt + tr[rc].cnt;
        tr[p].sum = tr[lc].sum + tr[rc].sum;
    }
    void mkadd(int x, int p, int plst, int l = 1, int r = inf){
        tr[p] = tr[plst];
        if(l == r) return tr[p].cnt ++, tr[p].sum += l, void();
        int mid = l + (r - l >> 1);
        if(x <= mid) mkadd(x, tr[p].c[0] = newnode(), tr[plst].c[0], l, mid), pushup(p);
        else mkadd(x, tr[p].c[1] = newnode(), tr[plst].c[1], mid + 1, r), pushup(p);
    }
    void add(int x){
        head[++ totver] = newnode();
        mkadd(x, head[totver], head[totver - 1]);
    }
    ll getquery(int k, int pl, int pr, int ubl = N, int l = 1, int r = inf){
        if(l == r) return l * k;
        int mid = l + (r - l >> 1);
        bool er = 0;
        int llc = tr[pl].c[0], rlc = tr[pr].c[0], lrc = tr[pl].c[1], rrc = tr[pr].c[1];
        int lcnt = tr[rlc].cnt - (tr[llc].cnt <= ubl ? tr[llc].cnt : (er = 1, ubl));
        if(k <= lcnt) return getquery(k, llc, rlc, ubl, l, mid);
        ll lsum = tr[rlc].sum - (er ? getquery(ubl, 0, llc, N, l, mid) : tr[llc].sum);
        return lsum + getquery(k - lcnt, lrc, rrc, ubl - min(tr[llc].cnt, ubl), mid + 1, r);
    }
    ll query(int c, int l, int r, int k){
        return getquery(k, head[min(l - 1 + c, n)], head[min(r + c, n)], l - 1);
    }
}
int main(){
    #ifndef db
    freopen("florist.in", "r", stdin);
    freopen("florist.out", "w", stdout);
    #endif
    n = read(), m = read();
    for(int i = 1; i <= n; i ++){
        int a = read();
        hjtt::add(a);
    }
    for(int i = 1; i <= m; i ++){
        int c = read(), l = read(), r = read(), k = read();
        printf("%lld\n", hjtt::query(c, l, r, k));
    }
    return 0;
}
/*
6 10
3 6 5 2 1 3
1 3 5 3
1 3 5 3
3 1 6 2
3 2 4 3
3 2 5 3
0 2 4 1
1 2 6 1
2 5 5 1
1 2 5 4
1 3 5 3
*/