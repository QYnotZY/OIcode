#include "bits/stdc++.h"
using namespace std;
namespace fastIO{static char BUF[2000000],*P1=BUF,*P2=BUF,OBUF[2000000],*P3=OBUF;inline char gc(){return P1==P2&&(P2=(P1=BUF)+fread(BUF,1,1000000,stdin),P1==P2)?EOF:*P1++;}inline void pc(register char x){(P3-OBUF<1000000)?(*P3++=x):(fwrite(OBUF,P3-OBUF,1,stdout),P3=OBUF,*P3++=x);}template<typename item>inline void uread(register item&x){register char c;for(;c=gc(),c<48||c>57;);for(x=c^48;c=gc(),c>=48&&c<=57;)x=(x<<3)+(x<<1)+(c^48);}template<typename item>inline void read(register item&x){register char c;register bool f=0;for(;c=gc(),c<48||c>57;)if(c==45)f=1;for(x=c^48;c=gc(),c>=48&&c<=57;)x=(x<<3)+(x<<1)+(c^48);f&&(x=-x);}static char STACK[40];template<typename item>inline void uwrite(register item x){if(!x)return pc('0');register unsigned short len=0;for(;x;x/=10)STACK[len++]=x%10|48;for(;len--;)pc(STACK[len]);}template<typename item>inline void write(register item x){if(!x)return pc('0');if(x<0)pc('-'),x=-x;register unsigned short len=0;for(;x;x/=10)STACK[len++]=x%10;for(;len--;)pc(STACK[len]|48);}inline void close(){fwrite(OBUF,P3-OBUF,1,stdout);}}
using namespace fastIO;
#define space() pc(' ')
#define endl() pc('\n')
#define rint register int
typedef long long ll;
namespace work {
const int N = 1e5 + 10, B = 330;
int n, m, a[N];
inline const int Block(int i) {return (i + B - 1) / B;}
inline const int Left(int i) {return i * B - B + 1;}
inline const int Right(int i) {return min(i * B, n);}
struct ANSnode {
    ll sum, premax, sufmax, ans;
    ANSnode() {sum = premax = sufmax = ans = 0;}
    ANSnode(ll a, ll b, ll c, ll d) {sum = a; premax = b; sufmax = c; ans = d;}
    friend ANSnode operator + (const ANSnode &a, const ANSnode &b) {
        ANSnode res;
        res.sum = a.sum + b.sum;
        res.premax = max(a.premax, a.sum + b.premax);
        res.sufmax = max(b.sufmax, b.sum + a.sufmax);
        res.ans = max(max(a.ans, b.ans), a.sufmax + b.premax);
        return res;
    }
} ans[N];
struct Point {
    int x; ll y;
    Point() {x = 0; y = 0;}
    Point(int x0, ll y0) {x = x0; y = y0;}
    bool operator < (const Point &obj) const {
        return x < obj.x || x == obj.x && y < obj.y;
    }
    friend Point operator + (const Point &a, const Point &b) {
        return Point(a.x + b.x, a.y + b.y);
    }
    friend Point operator - (const Point &a, const Point &b) {
        return Point(a.x - b.x, a.y - b.y);
    }
    friend ll operator * (const Point &a, const Point &b) {
        return a.x * b.x + a.y * b.y;
    }
    friend ll operator ^ (const Point &a, const Point &b) {
        return a.x * b.y - a.y * b.x;
    }
} ;
Point pool[25 * B], pooll[25 * B], poolr[25 * B], tmp1[B + 5 << 1], tmp2[B + 5 << 1]; int lent;
inline void toConvex(Point *a, int &len) {
    int n = 0;
    for(rint i = 0; i < len; i ++) {
        while(n >= 2 && ((a[n - 1] - a[n - 2]) ^ (a[i] - a[n - 2])) >= 0) -- n;
        a[n ++] = a[i];
    }
    len = n;
}
#define tsa(sth) (sth + Point(0, sth.x * Da))
#define tsb(sth) (sth + Point(0, sth.x * Db))
inline void Minkowski(Point *c, int &lenc, Point *a, int &lena, ll &Da, Point *b, int &lenb, ll &Db) {
    int i = 1, j = 1; lenc = 1;
    c[0] = Point(0, 0);
    while(i < lena && j < lenb) {
        if(((tsa(a[i]) - tsa(a[i - 1])) ^ (tsb(b[j]) - tsb(b[j - 1]))) <= 0) {
            c[lenc] = c[lenc - 1] + tsa(a[i]) - tsa(a[i - 1]);
            lenc ++; i ++;
        } else {
            c[lenc] = c[lenc - 1] + tsb(b[j]) - tsb(b[j - 1]);
            lenc ++; j ++;
        }
    }
    while(i < lena) {
        c[lenc] = c[lenc - 1] + tsa(a[i]) - tsa(a[i - 1]);
        lenc ++; i ++;
    }
    while(j < lenb) {
        c[lenc] = c[lenc - 1] + tsb(b[j]) - tsb(b[j - 1]);
        lenc ++; j ++;
    }
}
inline void Merge(Point *c, int &lenc, Point *a, int &lena, Point *b, int &lenb, ll &Db) {
    int i = 0, j = 0; lenc = 0;
    while(i < lena && j < lenb) {
        if(a[i] < tsb(b[j])) {
            c[lenc] = a[i];
            lenc ++; i ++;
        } else {
            c[lenc] = tsb(b[j]);
            lenc ++; j ++;
        }
    }
    while(i < lena) {
        c[lenc] = a[i];
        lenc ++; i ++;
    }
    while(j < lenb) {
        c[lenc] = tsb(b[j]);
        lenc ++; j ++;
    }
}
#undef tsa
#undef tsb
struct CHnode {
    int sz;
    ll tag, delta, sum;
    int lenl, lenr, len;
    Point *lmax, *rmax, *maxx;
    void init1(ll val) {
        sz = 1; tag = 0; delta = 0; sum = val;
        lenl = lenr = len = 2;
        lmax[0] = Point(0, 0); lmax[1] = Point(1, val);
        rmax[0] = Point(0, 0); rmax[1] = Point(1, val);
        maxx[0] = Point(0, 0); maxx[1] = Point(1, val);
    }
    void update(ll d) {
        delta += d;
        tag += d;
        sum += d * sz;
    }
    void update(CHnode &a, CHnode &b) {
        sz = a.sz + b.sz;
        tag = 0;
        delta = 0;
        sum = a.sum + b.sum;

        lenl = a.lenl + b.lenl;
        for(rint i = 0; i < a.lenl; i ++) lmax[i] = Point(a.lmax[i].x, a.lmax[i].y + a.delta * a.lmax[i].x);
        for(rint i = 0; i < b.lenl; i ++) lmax[a.lenl + i] = Point(a.sz + b.lmax[i].x, a.sum + b.lmax[i].y + b.delta * b.lmax[i].x);
        toConvex(lmax, lenl);

        lenr = a.lenr + b.lenr;
        for(rint i = 0; i < b.lenr; i ++) rmax[i] = Point(b.rmax[i].x, b.rmax[i].y + b.delta * b.rmax[i].x);
        for(rint i = 0; i < a.lenr; i ++) rmax[b.lenr + i] = Point(b.sz + a.rmax[i].x, b.sum + a.rmax[i].y + a.delta * a.rmax[i].x);
        toConvex(rmax, lenr);

        Minkowski(maxx, len, a.rmax, a.lenr, a.delta, b.lmax, b.lenl, b.delta);
        Merge(tmp1, lent, maxx, len, a.maxx, a.len, a.delta);
        Merge(tmp2, len, tmp1, lent, b.maxx, b.len, b.delta);
        toConvex(tmp2, len);
        memcpy(maxx, tmp2, len << 4);
    }
    ANSnode query_1(ll d, int &curl, int &curr, int &cur) {
        while(curl + 1 < lenl && lmax[curl].y + d * lmax[curl].x < lmax[curl + 1].y + d * lmax[curl + 1].x) curl ++;
        while(curr + 1 < lenr && rmax[curr].y + d * rmax[curr].x < rmax[curr + 1].y + d * rmax[curr + 1].x) curr ++;
        while(cur + 1 < len && maxx[cur].y + d * maxx[cur].x < maxx[cur + 1].y + d * maxx[cur + 1].x) cur ++;
        return ANSnode(sum + sz * d, lmax[curl].y + d * lmax[curl].x, rmax[curr].y + d * rmax[curr].x, maxx[cur].y + d * maxx[cur].x);
    }
} ;
namespace smt {
    int malloc_ptr;
    CHnode tr[B + 5 << 2];
    void pushdown(int p) {
        tr[p << 1].update(tr[p].tag);
        tr[p << 1 | 1].update(tr[p].tag);
        tr[p].tag = 0;
    }
    void build(bool be_malloc, int p, int l, int r) {
        if(p == 1) malloc_ptr = 0;
        if(be_malloc) {
            tr[p].maxx = pool + malloc_ptr;
            tr[p].lmax = pooll + malloc_ptr;
            tr[p].rmax = poolr + malloc_ptr;
            malloc_ptr += r - l + 3;
        }
        if(l == r)
            return tr[p].init1(a[l]);
        int mid = l + r >> 1;
        build(be_malloc, p << 1, l, mid);
        build(be_malloc, p << 1 | 1, mid + 1, r);
        tr[p].update(tr[p << 1], tr[p << 1 | 1]);
    }
    void update(int ql, int qr, ll d, int p, int l, int r) {
        if(ql <= l && r <= qr) return tr[p].update(d);
        int mid = l + r >> 1;
        pushdown(p);
        if(ql <= mid) update(ql, qr, d, p << 1, l, mid);
        if(qr > mid) update(ql, qr, d, p << 1 | 1, mid + 1, r);
        tr[p].update(tr[p << 1], tr[p << 1 | 1]);
    }
}
struct QRY {
    int typ, l, r, v;
} qry0[N];
struct QRY1 {
    int v, id;
}qry[N];
int buc[256], p[N], p0[N], id[N], ad[N];
bool cmp1(int x, int y) {
    return qry[x].v < qry[y].v;
}
void base_sort(int l, int r) {
    if(r - l + 1 <= 116) {
        for(int i = l; i <= r; i ++) p[i] = i;
        sort(p + l, p + r + 1, cmp1);
        return;
    }
    memset(buc, 0, sizeof buc); buc[0] = l - 1;
    for(rint i = l; i <= r; i ++) ++ buc[qry[i].v & 255];
    for(rint i = 1; i <= 255; i ++) buc[i] += buc[i - 1];
    for(rint i = r; i >= l; i --) p0[buc[qry[i].v & 255] --] = i;
    memset(buc, 0, sizeof buc); buc[0] = l - 1;
    for(rint i = l; i <= r; i ++) ++ buc[ad[i] = qry[p0[i]].v >> 8 & 255];
    for(rint i = 1; i <= 255; i ++) buc[i] += buc[i - 1];
    for(rint i = r; i >= l; i --) p[buc[ad[i]] --] = p0[i];
    memset(buc, 0, sizeof buc); buc[0] = l - 1;
    for(rint i = l; i <= r; i ++) ++ buc[ad[i] = qry[p[i]].v >> 16 & 255];
    for(rint i = 1; i <= 255; i ++) buc[i] += buc[i - 1];
    for(rint i = r; i >= l; i --) p0[buc[ad[i]] --] = p[i];
    memset(buc, 0, sizeof buc); buc[0] = l - 1;
    for(rint i = l; i <= r; i ++) ++ buc[ad[i] = (qry[p0[i]].v >> 24 & 255) ^ 128];
    for(rint i = 1; i <= 255; i ++) buc[i] += buc[i - 1];
    for(rint i = r; i >= l; i --) p[buc[ad[i]] --] = p0[i];
}
void Hutao() {
    read<int>(n), read<int>(m);
    for(rint i = 1; i <= n; i ++) read<int>(a[i]);
    for(rint i = 1; i <= m; i ++)
        read<int>(qry0[i].typ), read<int>(qry0[i].l), read<int>(qry0[i].r), (qry0[i].typ == 1 ? read<int>(qry0[i].v) : void());
    int lst, cur, CHptrl, CHptrr, CHptr; ll tag;
    int bcnt = Block(n), bl, br; int tag1 = 0; ll sum1, res1;
    ANSnode res2;
    for(rint j = 1; j <= m; j ++) {
        if(qry0[j].l <= B) {
            if(qry0[j].typ == 1) {
                if(qry0[j].l == 1 && B <= qry0[j].r)
                    tag1 += qry0[j].v;
                else 
                    for(rint k = qry0[j].l; k <= min(B, qry0[j].r); k ++)
                        a[k] += qry0[j].v;
            } else {
                res1 = sum1 = 0;
                for(rint i = qry0[j].l; i <= min(B, qry0[j].r); i ++) {
                    sum1 += a[i] + tag1;
                    if(sum1 < 0) sum1 = 0;
                    res1 = max(res1, sum1);
                }
                res2.ans = res1;
                res1 = sum1 = 0;
                for(rint i = qry0[j].l; i <= min(B, qry0[j].r); i ++) {
                    sum1 += a[i] + tag1;
                    res1 = max(res1, sum1);
                }
                res2.premax = res1;
                res2.sum = sum1;
                res1 = sum1 = 0;
                for(rint i = min(B, qry0[j].r); i >= qry0[j].l; i --) {
                    sum1 += a[i] + tag1;
                    res1 = max(res1, sum1);
                }
                res2.sufmax = res1;
                ans[j] = ans[j] + res2;
            }
        }
    }
    for(rint i = 2; i <= bcnt; i ++) {
        bl = Left(i), br = Right(i);
        smt::build(i == 2 || i == bcnt, 1, bl, br);
        lst = cur = CHptrl = CHptrr = CHptr = 0; tag = 0;
        tag1 = 0;
        for(rint j = 1; j <= m; j ++)
            if(max(qry0[j].l, bl) <= min(qry0[j].r, br)) {
                if(qry0[j].typ == 1) {
                    if(qry0[j].l <= bl && br <= qry0[j].r)
                        tag += qry0[j].v, tag1 += qry0[j].v;
                    else {
                        if(lst ^ cur) {
                            base_sort(lst + 1, cur);
                            for(rint k = lst + 1; k <= cur; k ++)
                                ans[qry[p[k]].id] = ans[qry[p[k]].id] + smt::tr[1].query_1(qry[p[k]].v, CHptrl, CHptrr, CHptr);
                        }
                        smt::tr[1].update(tag);
                        smt::update(max(bl, qry0[j].l), min(br, qry0[j].r), qry0[j].v, 1, bl, br);
                        tag = 0; lst = cur; CHptrl = CHptrr = CHptr = 0;
                        for(rint k = max(bl, qry0[j].l); k <= min(br, qry0[j].r); k ++)
                            a[k] += qry0[j].v;
                    }
                } else {
                    if(qry0[j].l <= bl && br <= qry0[j].r)
                        qry[++ cur] = QRY1{int(tag), j};
                    else {
                        res1 = sum1 = 0;
                        for(rint i = max(bl, qry0[j].l); i <= min(br, qry0[j].r); i ++) {
                            sum1 += a[i] + tag1;
                            if(sum1 < 0) sum1 = 0;
                            res1 = max(res1, sum1);
                        }
                        res2.ans = res1;
                        res1 = sum1 = 0;
                        for(rint i = max(bl, qry0[j].l); i <= min(br, qry0[j].r); i ++) {
                            sum1 += a[i] + tag1;
                            res1 = max(res1, sum1);
                        }
                        res2.premax = res1;
                        res2.sum = sum1;
                        res1 = sum1 = 0;
                        for(rint i = min(br, qry0[j].r); i >= max(bl, qry0[j].l); i --) {
                            sum1 += a[i] + tag1;
                            res1 = max(res1, sum1);
                        }
                        res2.sufmax = res1;
                        ans[j] = ans[j] + res2;
                    }
                }
            }
        if(lst ^ cur) {
            base_sort(lst + 1, cur);
            for(rint k = lst + 1; k <= cur; k ++)
                ans[qry[p[k]].id] = ans[qry[p[k]].id] + smt::tr[1].query_1(qry[p[k]].v, CHptrl, CHptrr, CHptr);
        }
    }
    for(rint i = 1; i <= m; i ++) if(qry0[i].typ == 2) write<ll>(ans[i].ans), endl();
    fastIO::close();
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}