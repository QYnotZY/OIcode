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
using FastIO::readch;
using FastIO::write;
typedef long long ll;
namespace work {
const int N = 2e5 + 10;
int n, q, a[N];
char s[N];
struct ST {
    int minn[N][20], maxx[N][20];
    int log2(int n) {
        int res = 0;
        while(n) n >>= 1, res ++;
        return res - 1;
    }
    void init() {
        for(int i = 1; i <= n; i ++)
            minn[i][0] = maxx[i][0] = a[i];
        for(int j = 1; j < 20; j ++)
            for(int i = 1; i <= n + 1 - (1 << j); i ++)
                minn[i][j] = min(minn[i][j - 1], minn[i + (1 << j - 1)][j - 1]),
                maxx[i][j] = max(maxx[i][j - 1], maxx[i + (1 << j - 1)][j - 1]);
    }
    int qmin(int l, int r) {
        int lg = log2(r - l + 1);
        return min(minn[l][lg], minn[r + 1 - (1 << lg)][lg]);
    }
    int qmax(int l, int r) {
        int lg = log2(r - l + 1);
        return max(maxx[l][lg], maxx[r + 1 - (1 << lg)][lg]);
    }
} st;
struct SMT {
    int tr[N << 2];
    void pushup(int p) {
        tr[p] = 0;
    }
    void pushdown(int p) {
        if(!tr[p]) return;
        tr[p << 1] = tr[p];
        tr[p << 1 | 1] = tr[p];
        tr[p] = 0;
    }
    void build(int p = 1, int l = 1, int r = n) {
        tr[p] = 0;
        if(l == r) return;
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    void update(int ql, int qr, int col, int p = 1, int l = 1, int r = n) {
        if(ql > qr) return;
        if(ql <= l && r <= qr) return void(tr[p] = col);
        int mid = l + r >> 1;
        pushdown(p);
        if(ql <= mid) update(ql, qr, col, p << 1, l, mid);
        if(qr > mid) update(ql, qr, col, p << 1 | 1, mid + 1, r);
        pushup(p);
    }
    int query(int x, int p = 1, int l = 1, int r = n) {
        if(l == r) return tr[p];
        int mid = l + r >> 1;
        pushdown(p);
        if(x <= mid) return query(x, p << 1, l, mid);
        else return query(x, p << 1 | 1, mid + 1, r);
    }
} L, R;
int cnt;
void Hutao() {
    n = read(), q = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    for(int i = 1; i <= n; i ++)
        s[i] = readch();
    s[n + 1] = 'R';
    cnt = 0;
    st.init(), L.build(), R.build();
    #ifdef db
    for(int j = 0; j <= 4; j ++) {for(int i = 1; i <= n; i ++) printf("%d", st.minn[i][j]); printf("\n");}
    #endif
    for(int l = 1, r = 1; r <= n; r ++) {
        if(s[r] == 'L' && s[r + 1] == 'R') {
            L.update(l, r, l);
            R.update(l, r, r);
            if(st.qmin(l, r) != l || st.qmax(l, r) != r){
                cnt ++;
            }
            l = r + 1;
        }
    }
    for(int i = 1; i <= q; i ++) {
        int x = read();
        if(s[x - 1] == 'L' && s[x] == 'R') {
            int l1 = L.query(x - 1), r1 = R.query(x);
            if(st.qmin(l1, x - 1) != l1 || st.qmax(l1, x - 1) != x - 1) cnt --;
            if(st.qmin(x, r1) != x || st.qmax(x, r1) != r1) cnt --;
            L.update(l1, r1, l1);
            R.update(l1, r1, r1);
            if(st.qmin(l1, r1) != l1 || st.qmax(l1, r1) != r1) cnt ++;
        }
        if(s[x] == 'L' && s[x + 1] == 'R') {
            int l1 = L.query(x), r1 = R.query(x + 1);
            if(st.qmin(l1, x) != l1 || st.qmax(l1, x) != x) cnt --;
            if(st.qmin(x + 1, r1) != x + 1 || st.qmax(x + 1, r1) != r1) cnt --;
            L.update(l1, r1, l1);
            R.update(l1, r1, r1);
            if(st.qmin(l1, r1) != l1 || st.qmax(l1, r1) != r1) cnt ++;
        }
        s[x] = s[x] == 'R' ? 'L' : 'R';
        if(s[x - 1] == 'L' && s[x] == 'R') {
            int l1 = L.query(x - 1), r1 = R.query(x);
            if(st.qmin(l1, r1) != l1 || st.qmax(l1, r1) != r1) cnt --;
            L.update(l1, x - 1, l1);
            R.update(l1, x - 1, x - 1);
            L.update(x, r1, x);
            R.update(x, r1, r1);
            if(st.qmin(l1, x - 1) != l1 || st.qmax(l1, x - 1) != x - 1) cnt ++;
            if(st.qmin(x, r1) != x || st.qmax(x, r1) != r1) cnt ++;
        }
        if(s[x] == 'L' && s[x + 1] == 'R') {
            int l1 = L.query(x), r1 = R.query(x + 1);
            if(st.qmin(l1, r1) != l1 || st.qmax(l1, r1) != r1) cnt --;
            L.update(l1, x, l1);
            R.update(l1, x, x);
            L.update(x + 1, r1, x + 1);
            R.update(x + 1, r1, r1);
            if(st.qmin(l1, x) != l1 || st.qmax(l1, x) != x) cnt ++;
            if(st.qmin(x + 1, r1) != x + 1 || st.qmax(x + 1, r1) != r1) cnt ++;
        }
        printf(cnt ? "NO\n" : "YES\n");
    }
}
}
int main() {
    int t = read();
    while(t --) work::Hutao();
    return 0;
}