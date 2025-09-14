#include "bits/stdc++.h"
using namespace std;
namespace FastIO {
    template<typename T = int> T read() {
        char ch = getchar(); bool neg = 0; T res = 0;
        for(; !('0' <= ch && ch <= '9'); ch = getchar()) if(ch == '-') neg = !neg;
        for(; ('0' <= ch && ch <= '9'); ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ 48);
        return neg ? ~res + 1 : res;
    }
    char readch(bool acsp = 0) {
        char ch = getchar(); for(; !(33 - acsp <= ch && ch < 127); ch = getchar()); return ch;
    }
} using namespace FastIO;
typedef long long ll;
namespace Qiuyu3600 {
const int N = 1e5 + 10, M = 1e6 + 10, T = 4e4;
const ll inf = 1e15;
int n, m; ll A, B, C;
struct point {
    ll x, y;
    point() {x = y = 0;};
    point(ll x0, ll y0) {x = x0, y = y0;}
    point operator-(const point &obj) const {return {x - obj.x, y - obj.y};}
    ll operator^(const point &obj) const {return x * obj.y - y * obj.x;}
    ll calc(ll k) {return y - k * x;}
};
vector<point> pts[N];
#define lst1(x) pts[x][pts[x].size() - 1]
#define lst2(x) pts[x][pts[x].size() - 2]
void insert(int pos, point npt) {
    for(; pts[pos].size() >= 2 && (lst1(pos) - lst2(pos) ^ npt - lst1(pos)) <= 0; pts[pos].pop_back()) ;
    pts[pos].push_back(npt);
}
bool queriable(int pos) {
    return pts[pos].size();
}
ll query(int pos, ll k) {
    int l = -1, r = pts[pos].size() - 1;
    while(l + 1 < r) (pts[pos][l + r >> 1].calc(k) > pts[pos][l + r + 2 >> 1].calc(k) ? l : r) = l + r >> 1;
    return pts[pos][r].calc(k);
}
struct edge {
    int x, y, p, q;
    ll ans;
} ed[M];
int sp[M], sq[M];
bool cmpp(int x, int y) {return ed[x].p < ed[y].p;}
bool cmpq(int x, int y) {return ed[x].q < ed[y].q;}
void Hutao() {
    n = read(), m = read(), A = read(), B = read(), C = read();
    for(int i = 1; i <= m; i ++) ed[i] = {read(), read(), read(), read(), 0ll};
    for(int i = 1; i <= m; i ++) sp[i] = i; sort(sp + 1, sp + m + 1, cmpp);
    for(int i = 1; i <= m; i ++) sq[i] = i; sort(sq + 1, sq + m + 1, cmpq);
    insert(1, point(0, C));
    for(int t = 0, pi = 1, qi = 1; t <= T; t ++) {
        for(ll qq; qi <= m && ed[sq[qi]].q <= t; qi ++) {
            if(ed[sq[qi]].ans == inf) continue;
            qq = ed[sq[qi]].q;
            insert(ed[sq[qi]].y, point(qq, A * qq * qq - B * qq + C + ed[sq[qi]].ans));
        }
        for(ll pp; pi <= m && ed[sp[pi]].p <= t; pi ++) {
            if(!queriable(ed[sp[pi]].x)) {ed[sp[pi]].ans = inf; continue;}
            pp = ed[sp[pi]].p;
            ed[sp[pi]].ans = query(ed[sp[pi]].x, 2 * A * pp) + A * pp * pp + B * pp;
        }
    }
    ll ans = inf;
    for(int i = 1; i <= m; i ++)
        if(ed[i].y == n) ans = min(ans, ed[i].ans + ed[i].q);
    printf("%lld", ans);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}