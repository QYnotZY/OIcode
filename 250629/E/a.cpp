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
const int inf = 3e5 + 10;
namespace work {
int n, a[N], lst[N], lst1[N], lst2[N];
struct SMTnode {
    int val, tag;
    int l, r;
};
struct SMT {
    SMTnode sn[N << 2];
    void pushup(int p) {
        sn[p].val = min(sn[p << 1].val, sn[p << 1 | 1].val);
    }
    void u1(int p, int add) {
        sn[p].val += add;
        sn[p].tag += add;
    }
    void pushdown(int p) {
        u1(p << 1, sn[p].tag);
        u1(p << 1 | 1, sn[p].tag);
        sn[p].tag = 0;
    }
    void create(int p = 1, int l = 1, int r = n) {
        sn[p].l = l, sn[p].r = r, sn[p].val = sn[p].tag = 0;
        if(l == r) return;
        int mid = l + r >> 1;
        create(p << 1, l, mid);
        create(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int ql, int qr, int add, int p = 1) {
        int &l = sn[p].l, &r = sn[p].r;
        if(ql <= l && r <= qr)
            return u1(p, add);
        int mid = l + r >> 1;
        pushdown(p);
        if(ql <= mid) update(ql, qr, add, p << 1);
        if(qr > mid) update(ql, qr, add, p << 1 | 1);
        pushup(p);
    }
    int query(int ql, int qr, int p = 1) {
        int &l = sn[p].l, &r = sn[p].r;
        if(ql <= l && r <= qr)
            return sn[p].val;
        int mid = l + r >> 1, res = inf;
        pushdown(p);
        if(ql <= mid) res = min(res, query(ql, qr, p << 1));
        if(qr > mid) res = min(res, query(ql, qr, p << 1 | 1));
        return res;
    }
} tr;
int ans;
int Main() {
    int t = read();
    while(t --) {
        n = read();
        for(int i = 1; i <= n; i ++) {
            lst[i] = 0;
        }
        for(int i = 1; i <= n; i ++) {
            a[i] = read();
            lst2[i] = lst1[lst[a[i]]];
            lst1[i] = lst[a[i]];
            lst[a[i]] = i;
        }
        tr.create();
        ans = 0;
        for(int i = 1, cur = 1; i <= n; i ++) {
            if(lst1[i]) {
                if(lst2[i]) {
                    tr.update(lst1[i] + 1, i, 1);
                    tr.update(lst2[i] + 1, lst1[i], -1);
                } else {
                    tr.update(lst1[i] + 1, i, 1);
                    tr.update(1, lst1[i], -1);
                }
            } else {
                tr.update(1, i, 1);
            }
            if(!tr.query(cur, i)) {
                cur = i + 1;
                ans ++;
            }
        }
        write(ans);
    }
    return 0;
}
}
int main() {
    return work::Main();
}