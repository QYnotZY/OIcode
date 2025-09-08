#include "bits/stdc++.h"
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
const int N = 3e5 + 10;
namespace work {
int n, q;
int a[N], a1[N];
vector<int> nw[N], dl[N];
struct QRY {
    int x, t, pos, stt;
    bool operator < (QRY obj) {
        return x < obj.x || x == obj.x && t < obj.t || x == obj.x && t == obj.t && stt < obj.stt;
    }
} qry[N << 1];
struct SMT1node {
    int sum, lmax, rmax, maxx;
    SMT1node operator + (SMT1node obj) {
        SMT1node res;
        res.sum = sum + obj.sum;
        res.lmax = max(lmax, sum + obj.lmax);
        res.rmax = max(obj.rmax, rmax + obj.sum);
        res.maxx = max(max(maxx, obj.maxx), rmax + obj.lmax);
        return res;
    }
} ;
struct SMT1 {
    SMT1node sn[N << 2];
    void pushup(int p) {
        sn[p] = sn[p << 1] + sn[p << 1 | 1];
    }
    void u1(int p, int stt) {
        sn[p].sum = stt;
        sn[p].lmax = sn[p].rmax = sn[p].maxx = max(stt, 0);
    }
    void create(int p = 1, int l = 1, int r = n) {
        if(l == r)
            return u1(p, -1);
        int mid = l + r >> 1;
        create(p << 1, l, mid);
        create(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int x, int stt, int p = 1, int l = 1, int r = n) {
        if(l == r)
            return u1(p, stt);
        int mid = l + r >> 1;
        if(x <= mid) update(x, stt, p << 1, l, mid);
        else update(x, stt, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    int query() {
        return sn[1].maxx;
    }
} smt;
struct SMT2 {
    int sn[N << 2];
    void u1(int p, int val) {
        sn[p] = max(sn[p], val);
    }
    void create(int p = 1, int l = 1, int r = q) {
        sn[p] = 0;
        if(l == r) return;
        int mid = l + r >> 1;
        create(p << 1, l, mid);
        create(p << 1 | 1, mid + 1, r);
    }
    void update(int ql, int qr, int val, int p = 1, int l = 1, int r = q) {
        if(ql > qr) return;
        if(ql <= l && r <= qr)
            return u1(p, val);
        int mid = l + r >> 1;
        if(ql <= mid) update(ql, qr, val, p << 1, l, mid);
        if(qr > mid) update(ql, qr, val, p << 1 | 1, mid + 1, r);
    }
    int query(int x, int p = 1, int l = 1, int r = q) {
        if(l == r)
            return sn[p];
        int mid = l + r >> 1;
        if(x <= mid) return max(sn[p], query(x, p << 1, l, mid));
        else return max(sn[p], query(x, p << 1 | 1, mid + 1, r));
    }
} ans;
void solve() {
    n = read(), q = read();
    for(int i = 1; i <= n; i ++) {
        a1[i] = a[i] = read();
        vector<int>().swap(nw[i]);
        vector<int>().swap(dl[i]);
    }
    for(int i = 1; i <= q; i ++) {
        int pos = read(), val = read();
        qry[2 * i - 1] = {a1[pos], i, pos, -1};
        qry[2 * i] = {val, i, pos, 1};
        a1[pos] = val;
    }
    for(int i = 1; i <= n; i ++) {
        nw[a[i]].emplace_back(i);
        dl[a1[i]].emplace_back(i);
    }
    sort(qry + 1, qry + 2 * q + 1);
    smt.create();
    ans.create();
    for(int x = 1, i = 1, cur; x <= n; x ++) {
        for(auto ele : nw[x]) {
            smt.update(ele, 1);
        }
        for(cur = 1; i <= 2 * q && qry[i].x == x; i ++) {
            ans.update(cur, qry[i].t - 1, smt.query() >> 1);
            cur = qry[i].t;
            smt.update(qry[i].pos, qry[i].stt);
        }
        ans.update(cur, q, smt.query() >> 1);
        for(auto ele : dl[x]) {
            smt.update(ele, -1);
        }
    }
    for(int i = 1; i <= q; i ++)
        write(ans.query(i), ' ');
    putchar('\n');
}
int Main() {
    int t = read();
    while(t --) {
        solve();
    }
    return 0;
}
}
int main() {
    return work::Main();
}