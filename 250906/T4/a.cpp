#include "bits/stdc++.h"
using namespace std;
namespace FastIO {
    template <typename T = int> T read() {
        char ch = '\0'; bool f = 0; T res = 0;
        for(; !('0' <= ch && ch <= '9'); ch = getchar()) if(ch == '-') f = !f;
        for(; '0' <= ch && ch <= '9'; ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ '0');
        return f ? ~res + 1 : res;
    }
    char readch(const int acsp = 0) {
        char ch = '\0';
        for(; !(33 - acsp <= ch && ch < 127); ch = getchar()) ;
        return ch;
    }
} using FastIO::read; using FastIO::readch;
typedef long long ll;
namespace Qiuyu3600 {
const int N = 505, inf = 1e4;
const int mod = 998244353;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
int n0, m;
int n[2];
struct edge {
    int x1, y1, x2, y2;
    bool operator <(const edge& obj) const {
        return x2 < obj.x2 || x2 == obj.x2 && y2 < obj.y2;
    }
    bool operator >(const edge& obj) const {
        return x2 <= obj.x1 && y2 <= obj.y1;
    }
    bool operator >=(const edge& obj) const {
        return x2 <= obj.x2 && y2 <= obj.y2 || x1 <= obj.x1 && y1 <= obj.y1;
    }
} ed[2][N];
int vx[N << 1], vxsz, vy[N << 1], vysz;
vector<int> py[2][N << 1];
int f[N][N], g[N];
int minn[N], lstx[N], res[N];
int ans;
void Hutao() {
    m = read(), n0 = read();
    for(int i = 1, x1, y1, x2, y2; i <= m; i ++) {
        x1 = read(), y1 = read(), x2 = read(), y2 = read();
        if(x1 > x2) swap(x1, x2), swap(y1, y2);
        if(y1 < y2) ed[0][++ n[0]] = {x1, y1, x2, y2};
        else ed[1][++ n[1]] = {x1, n0 - y1 + 1, x2, n0 - y2 + 1};
    }
    for(int tp = 0; tp < 2; tp ++) {
        vxsz = vysz = 2 * n[tp];
        for(int i = 1; i <= n[tp]; i ++)
            tie(vx[i], vy[i], vx[n[tp] + i], vy[n[tp] + i]) = tie(ed[tp][i].x1, ed[tp][i].y1, ed[tp][i].x2, ed[tp][i].y2);
        sort(vx + 1, vx + vxsz + 1); vxsz = unique(vx + 1, vx + vxsz + 1) - vx - 1;
        sort(vy + 1, vy + vysz + 1); vysz = unique(vy + 1, vy + vysz + 1) - vy - 1;
        #define lwb(a, b, c) int(lower_bound(a + 1, a + b + 1, c) - a)
        for(int i = 1; i <= n[tp]; i ++)
            ed[tp][i] = {lwb(vx, vxsz, ed[tp][i].x1), lwb(vy, vysz, ed[tp][i].y1), lwb(vx, vxsz, ed[tp][i].x2), lwb(vy, vysz, ed[tp][i].y2)};
        #undef lwb
        sort(ed[tp] + 1, ed[tp] + n[tp] + 1);
        for(int i = 1; i <= n[tp]; i ++) {
            py[tp][ed[tp][i].y1].push_back(i);
            for(int j = 1; j <= n[tp]; j ++)
                f[i][j] = i == j ? 0 : (ed[tp][i] > ed[tp][j] ? 1 : -inf);
        }
        for(int k = 1; k <= n[tp]; k ++)
            for(int i = 1; i <= n[tp]; i ++)
                for(int j = 1; j <= n[tp]; j ++)
                    if(i ^ j && i ^ k && j ^ k)
                        f[i][j] = max(f[i][j], f[i][k] + f[k][j]);
        for(int i = 1; i <= n[tp]; i ++)
            for(int j = 1; j <= n[tp]; j ++) 
                (f[i][j] = max(f[i][j], 0)) += ed[tp][i] >= ed[tp][j];
        for(int x = 1; x <= vxsz; x ++) {
            for(int i = 1; i <= n[tp]; i ++) g[i] = 0;
            for(int y = vysz; y; y --) {
                for(auto i : py[tp][y])
                    if(ed[tp][i].x1 >= x)
                        for(int j = 1; j <= n[tp]; j ++)
                            g[j] = max(g[j], f[i][j]);
                for(int i = 1; i <= n[tp]; i ++) minn[i] = n0 + 1, lstx[i] = 0, res[i] = 0;
                for(int i = 1; i <= n[tp]; i ++) {
                    if(!g[i]) continue;
                    res[g[i]] = Add(res[g[i]], Mult(vx[ed[tp][i].x2] - lstx[g[i]], n0 - minn[g[i]] + 1));
                    lstx[g[i]] = vx[ed[tp][i].x2]; minn[g[i]] = min(minn[g[i]], vy[ed[tp][i].y2]);
                }
                for(int i = 1; i <= n[tp]; i ++)
                    res[i] = Add(res[i], Mult(n0 + 1 - lstx[i], n0 - minn[i] + 1));
                res[0] = 0; for(int i = 1; i <= n[tp]; i ++) res[0] = Add(res[0], res[i]);
                res[0] = Mult(res[0], Mult(vx[x] - vx[x - 1], vy[y] - vy[y - 1]));
                ans = Add(ans, res[0]);
            }
        }
    }
    ans = Minus(Add(Mult(332748118, Pow(n0, 5)), Mult(665496235, Pow(n0, 3))), ans);
    printf("%d", ans);
}
}
int main() {
    #ifndef db
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);
    #endif
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}