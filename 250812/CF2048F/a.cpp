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
const int N = 2e5 + 10, ub = 63;
int n;
ll a[N], b[N];
namespace st {
    struct node{
        int pos; ll val;
        bool operator < (const node& obj) const {
            return val < obj.val;
        }
    } minn[20][N];
    void init() {
        for(int i = 1; i <= n; i ++) minn[0][i] = node{i, b[i]};
        for(int i = 1; i < 20; i ++)
            for(int j = 1; j <= n + 1 - (1 << i); j ++)
                minn[i][j] = min(minn[i - 1][j], minn[i - 1][j + (1 << i - 1)]);
    }
    inline int log2(int x) {register int res = 0; while(x >>= 1) ++ res; return res;}
    int query(int l, int r) {
        int lg = log2(r - l + 1);
        return min(minn[lg][l], minn[lg][r + 1 - (1 << lg)]).pos;
    }
}
inline ll cdiv(ll a, ll b) {return (a + b - 1) / b;}
ll f[N][64];
int solve(int l, int r) {
    if(l > r) return 0;
    int mid = st::query(l, r);
    int lc = solve(l, mid - 1), rc = solve(mid + 1, r);
    if(lc && rc) {
        for(int i = 0; i <= ub; i ++) {
            f[mid][i] = 1e18;
            for(int j = 0; j <= i; j ++)
                f[mid][i] = min(f[mid][i], max(f[lc][j], f[rc][i - j]));
            f[mid][i] = max(f[mid][i], a[mid]);
        }
    } else if(lc) {
        for(int i = 0; i <= ub; i ++) f[mid][i] = max(a[mid], f[lc][i]);
    } else if(rc) {
        for(int i = 0; i <= ub; i ++) f[mid][i] = max(a[mid], f[rc][i]);
    } else {
        for(int i = 0; i <= ub; i ++) f[mid][i] = a[mid];
    }
    for(int i = 1; i <= ub; i ++) f[mid][i] = min(f[mid][i], cdiv(f[mid][i - 1], b[mid]));
    return mid;
}
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++) a[i] = read<ll>();
    for(int i = 1; i <= n; i ++) b[i] = read<ll>();
    st::init();
    int res = solve(1, n);
    for(int i = 0; i <= ub; i ++)
        if(f[res][i] == 1) {
            printf("%d\n", i);
            return;
        }
}
}
int main() {
    int t = read();
    while(t --) work::Hutao();
    return 0;
}