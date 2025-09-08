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
const int N = 5e5 + 10;
namespace work {
inline int log2(int n) {
    int res = 0;
    while(n) n >>= 1, res ++;
    return res - 1;
}
struct ST {
    int minn[N][21], maxx[N][21];
    void init(int n, int *a) {
        for(int i = 1; i <= n; i ++) {
            minn[i][0] = maxx[i][0] = a[i];
        }
        for(int i = 1; i <= 20; i ++) {
            for(int j = 1; j <= n - (1 << i) + 1; j ++) {
                minn[j][i] = min(minn[j][i - 1], minn[j + (1 << i - 1)][i - 1]);
                maxx[j][i] = max(maxx[j][i - 1], maxx[j + (1 << i - 1)][i - 1]);
            }
        }
    }
    int query(int typ, int l, int r) {
        int logn = log2(r - l + 1);
        #ifdef db
        printf("%d %d\n", r - l + 1, logn);
        #endif
        if(typ) return max(maxx[l][logn], maxx[r + 1 - (1 << logn)][logn]);
        return min(minn[l][logn], minn[r + 1 - (1 << logn)][logn]);
    }
} st;
struct BIT {
    int n, tr[N];
    inline int lowbit(int x) {return x & -x;}
    void init(int n) {
        this -> n = n;
        for(int i = 1; i <= n; i ++) {
            tr[i] = 0;
        }
    }
    void update(int x, int val) {
        while(x <= n) {
            tr[x] = max(tr[x], val);
            x += lowbit(x);
        }
    }
    int query(int x) {
        int res = 0;
        while(x) {
            res = max(res, tr[x]);
            x -= lowbit(x);
        }
        return res;
    }
} bit;
int n, a[N], ans[N];
void solve() {
    n = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    #ifdef db
    printf("1");
    #endif
    st.init(n, a);
    bit.init(n);
    #ifdef db
    printf("2");
    #endif
    for(int i(n); i; i --) {
        ans[i] = st.query(1, 1, i);
        #ifdef db
        printf("%d ", ans[i]);
        #endif
        ans[i] = max(ans[i], bit.query(ans[i] - 1));
        #ifdef db
        printf("%d\n", ans[i]);
        #endif
        bit.update(a[i], ans[i]);
    }
    #ifdef db
    printf("3\n");
    #endif
    for(int i = 1; i <= n; i ++) {
        write(ans[i], ' ');
    }
    printf("\n");
}
int Main() {
    int t = read();
    while(t --) solve();
    return 0;
}
}
int main() {
    return work::Main();
}