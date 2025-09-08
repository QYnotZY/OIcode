#include "bits/stdc++.h"
#pragma pack(1)
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// inline char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
inline char gc() {return getchar();}
template<typename T>
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
inline T read() {return readnum<T>();}
char wc[50]; int top;
template<typename T>
inline void writenum(T x, char sp){
    if(!x) return putchar('0'), void(putchar(sp));
    if(x < 0) putchar('-'), x = ~x + 1;
    top = 0;
    for(; x; x /= 10) wc[top ++] = x % 10 ^ 48;
    while(top --) putchar(wc[top]);
    putchar(sp);
}
template<typename T = int>
inline void write(T x, char sp = '\n'){
    writenum(x, sp);
}
}
using FastIO::read;
using FastIO::write;
typedef long long ll;
const int N = 3e5 + 10, M = 6e5 + 10;
namespace work {
int n, m;
int a[N];
struct Ans {
    ll sum, pre, suf, ans;
} ans[M];
struct Qry {
    int l, r; ll k;
    int id;
} qry[M];
vector<int> curq;
bool cmpqry(Qry a, Qry b) {
    return a.k > b.k;
}
struct Vec {
    int x; ll y;
    Vec operator + (Vec obj) {
        return {x + obj.x, y + obj.y};
    }
    Vec operator - (Vec obj) {
        return {x - obj.x, y - obj.y};
    }
    ll operator * (Vec obj) {
        return x * obj.x + y * obj.y;
    }
    ll operator ^ (Vec obj) {
        return x * obj.y - y * obj.x;
    }
    bool operator < (Vec obj) {
        if(x == obj.x)
            return y < obj.y;
        return x < obj.x;
    }
    ll calc(ll k){
        return y - k * x;
    }
} ;
struct PointSet {
    vector<Vec> pts;
    void relief(){
        vector<Vec>().swap(pts);
    }
    void insert(Vec a) {
        pts.emplace_back(a);
    }
    void getConv() {
        vector<Vec> tmp; tmp.swap(pts);
        int sz;
        for(auto x3 : tmp) {
            for(sz = pts.size(); sz >= 2; -- sz) {
                Vec x1 = pts[sz - 2], x2 = pts[sz - 1];
                if(((x3 - x2) ^ (x2 - x1)) > 0) break;
                pts.pop_back();
            }
            pts.emplace_back(x3);
        }
    }
    void Minkowski(PointSet &a, PointSet &b) {
        vector<Vec>().swap(pts);
        Vec lst = {0, 0};
        pts.emplace_back(lst);
        int posa = 1, posb = 1, sza = a.pts.size(), szb = b.pts.size();
        while(posa < sza && posb < szb) {
            if(((a.pts[posa] - a.pts[posa - 1]) ^ (b.pts[posb] - b.pts[posb - 1])) < 0) {
                lst = lst + a.pts[posa] - a.pts[posa - 1];
                pts.emplace_back(lst);
                posa ++;
            } else {
                lst = lst + b.pts[posb] - b.pts[posb - 1];
                pts.emplace_back(lst);
                posb ++;
            }
        }
        while(posa < sza) {
            lst = lst + a.pts[posa] - a.pts[posa - 1];
            pts.emplace_back(lst);
            posa ++;
        }
        while(posb < szb) {
            lst = lst + b.pts[posb] - b.pts[posb - 1];
            pts.emplace_back(lst);
            posb ++;
        }
    }
} ;
struct SMTnode {
    ll sum;
    PointSet pre, suf, ans;
    void init(ll a) {
        sum += a;
        pre.insert({0, 0});
        pre.insert({1, a});
        suf.insert({0, 0});
        suf.insert({1, a});
        ans.insert({0, 0});
        ans.insert({1, a});
    }
    void relief() {
        sum = 0;
        pre.relief();
        suf.relief();
        ans.relief();
    }
} tr[N];
int stk[N], top, cnt;
int newnode(){
    if(top) return stk[top --];
    return ++ cnt;
}
void relief(int p){
    tr[p].relief();
    stk[++ top] = p;
}
void build(int l = 1, int r = n) {
    if(l == r)
        return void(tr[newnode()].init(a[l]));
    int mid = l + r >> 1;
    build(l, mid);
    build(mid + 1, r);
}
void pushup(int p, int lc, int rc, int l, int r){
    int mid = l + r >> 1;
    tr[p].sum = tr[lc].sum + tr[rc].sum;
    tr[p].ans.Minkowski(tr[lc].suf, tr[rc].pre);
    vector<Vec> dick;
    dick.resize(tr[p].ans.pts.size() + tr[lc].ans.pts.size());
    merge(tr[p].ans.pts.begin(), tr[p].ans.pts.end(), tr[lc].ans.pts.begin(), tr[lc].ans.pts.end(), dick.begin());
    tr[p].ans.pts.resize(dick.size() + tr[rc].ans.pts.size());
    merge(dick.begin(), dick.end(), tr[rc].ans.pts.begin(), tr[rc].ans.pts.end(), tr[p].ans.pts.begin());
    vector<Vec>().swap(dick);
    tr[p].ans.getConv();
    ll x = 0;
    tr[p].pre.pts = tr[lc].pre.pts;
    int tx = mid - l + 1; ll ty = tr[lc].sum;
    for(auto ele : tr[rc].pre.pts)
        tr[p].pre.insert({ele.x + tx, ele.y + ty});
    tr[p].pre.getConv();
    x = 0;
    tr[p].suf.pts = tr[rc].suf.pts;
    tx = r - mid, ty = tr[rc].sum;
    for(auto ele : tr[lc].suf.pts)
        tr[p].suf.insert({ele.x + tx, ele.y + ty});
    tr[p].suf.getConv();
    relief(lc);
    relief(rc);
}
int solve(int l = 1, int r = n) {
    int p, lc, rc, mid = l + r >> 1;
    vector<int> loc, tmp;
    int ql, qr;
    for(auto ele : curq) {
        ql = qry[ele].l, qr = qry[ele].r;
        if(ql <= l && r <= qr)
            loc.emplace_back(ele);
        else if(!(qr < l) && !(r < ql))
            tmp.emplace_back(ele);
    }
    if(l == r){
        p = l;
        goto local_solve;
    }
    curq.swap(tmp);
    lc = solve(l, mid);
    rc = solve(mid + 1, r);
    curq.swap(tmp);
    pushup(p = newnode(), lc, rc, l, r);
    local_solve:
    int posans = 0, szans = tr[p].ans.pts.size();
    int pospre = 0, szpre = tr[p].pre.pts.size();
    int possuf = 0, szsuf = tr[p].suf.pts.size();
    Ans tmpans;
    ll k; int id;
    for(auto ele : loc) {
        k = qry[ele].k, id = qry[ele].id;
        tmpans.sum = tr[p].sum + (-k) * (r - l + 1);
        while(posans < szans - 1 && tr[p].ans.pts[posans].calc(k) <= tr[p].ans.pts[posans + 1].calc(k)) posans ++;
        tmpans.ans = tr[p].ans.pts[posans].calc(k);
        while(pospre < szpre - 1 && tr[p].pre.pts[pospre].calc(k) <= tr[p].pre.pts[pospre + 1].calc(k)) pospre ++;
        tmpans.pre = tr[p].pre.pts[pospre].calc(k);
        while(possuf < szsuf - 1 && tr[p].suf.pts[possuf].calc(k) <= tr[p].suf.pts[possuf + 1].calc(k)) possuf ++;
        tmpans.suf = tr[p].suf.pts[possuf].calc(k);
        ans[id].ans = max(max(ans[id].ans, tmpans.ans), ans[id].suf + tmpans.pre);
        ans[id].pre = max(ans[id].pre, ans[id].sum + tmpans.pre);
        ans[id].suf = max(tmpans.suf, tmpans.sum + ans[id].suf);
        ans[id].sum += tmpans.sum;
    }
    return p;
}
void init() {
    n = read(); int m0 = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    int op, l, r; ll x = 0;
    for(; m0 --;) {
        op = read();
        if(op == 1)
            x += read<ll>();
        else {
            l = read(), r = read();
            qry[++ m] = {l, r, -x, m};
        }
    }
    sort(qry + 1, qry + m + 1, cmpqry);
    for(int i = 1; i <= m; i ++)
        curq.emplace_back(i);
    build();
}
void print() {
    for(int i = 1; i <= m; i ++)
        write<ll>(ans[i].ans);
}
int Main() {
    init();
    solve();
    print();
    return 0;
}
}
int main() {
    return work::Main();
}