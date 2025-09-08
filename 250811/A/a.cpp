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
const int N = 5e5 + 10;
const int mod = 1000000000;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int halfMult(int a, int b) {return 1ll * a * b / 2 % mod;}
int a[N]; int minn[N], maxx[N], Smin[N], Swmin[N], Smax[N], Swmax[N], Smm[N], Swmm[N];
int ans;
void solve(int l, int r) {
    if(l == r) return void(ans = Add(ans, Mult(a[l], a[r])));
    int mid = l + r >> 1, i, j, k;
    solve(l, mid), solve(mid + 1, r);
    minn[mid] = mod, maxx[mid] = Smin[mid] = Swmin[mid] = Smax[mid] = Swmax[mid] = Smm[mid] = Swmm[mid] = 0;
    for(i = mid + 1; i <= r; i ++) {
        minn[i] = min(minn[i - 1], a[i]), maxx[i] = max(maxx[i - 1], a[i]);
        Smin[i] = Add(Smin[i - 1], minn[i]), Swmin[i] = Add(Swmin[i - 1], Mult(i - mid, minn[i]));
        Smax[i] = Add(Smax[i - 1], maxx[i]), Swmax[i] = Add(Swmax[i - 1], Mult(i - mid, maxx[i]));
        Smm[i] = Add(Smm[i - 1], Mult(minn[i], maxx[i])), Swmm[i] = Add(Swmm[i - 1], Mult(i - mid, Mult(minn[i], maxx[i])));
    }
    int mn = mod, mx = 0, szl;
    for(i = mid, j = mid + 1, k = mid + 1; i >= l; i --) {
        mn = min(mn, a[i]), mx = max(mx, a[i]);
        for(; j <= r && minn[j] >= mn; j ++) ;
        for(; k <= r && maxx[k] <= mx; k ++) ;
        if(j < k) {
            szl = mid - i + 1;
            ans = Add(ans, Mult(Mult(mn, mx), halfMult(Add(2 * szl, j - mid), j - mid - 1)));
            ans = Add(ans, Mult(mx, Add(Minus(Swmin[k - 1], Swmin[j - 1]), Mult(szl, Minus(Smin[k - 1], Smin[j - 1])))));
            ans = Add(ans, Add(Minus(Swmm[r], Swmm[k - 1]), Mult(szl, Minus(Smm[r], Smm[k - 1]))));
        } else {
            szl = mid - i + 1;
            ans = Add(ans, Mult(Mult(mn, mx), halfMult(Add(2 * szl, k - mid), k - mid - 1)));
            ans = Add(ans, Mult(mn, Add(Minus(Swmax[j - 1], Swmax[k - 1]), Mult(szl, Minus(Smax[j - 1], Smax[k - 1])))));
            ans = Add(ans, Add(Minus(Swmm[r], Swmm[j - 1]), Mult(szl, Minus(Smm[r], Smm[j - 1]))));
        }
    }
}
int n;
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    solve(1, n);
    printf("%d", ans);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}