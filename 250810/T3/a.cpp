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
const int N = 510, M = 1e6 + 10;
const int mod = 998244353;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
namespace scl {
    struct MDF {
        ll x, y1, y2, v;
        bool operator < (const MDF& obj) const {
            return x < obj.x || x == obj.x && v > obj.v;
        }
    } m[N]; int msz;
    ll num[N];
    int dx[N], dy[N], nx, ny;
    void disc() {
        for(int i = 1; i <= msz; i ++) num[i] = m[i].x;
        sort(num + 1, num + msz + 1);
        nx = unique(num + 1, num + msz + 1) - num - 1;
        for(int i = 1; i < nx; i ++) dx[i] = (num[i + 1] - num[i]) % mod;
        for(int i = 1; i <= msz; i ++) m[i].x = lower_bound(num + 1, num + nx + 1, m[i].x) - num;
        for(int i = 1; i <= msz; i ++) num[2 * i - 1] = m[i].y1, num[2 * i] = m[i].y2;
        sort(num + 1, num + 2 * msz + 1);
        ny = unique(num + 1, num + 2 * msz + 1) - num - 1;
        for(int i = 1; i < ny; i ++) dy[i] = (num[i + 1] - num[i]) % mod;
        for(int i = 1; i <= msz; i ++) m[i].y1 = lower_bound(num + 1, num + ny + 1, m[i].y1) - num, m[i].y2 = lower_bound(num + 1, num + ny + 1, m[i].y2) - num;
    }
    namespace smt {
        int n;
        struct node {
            int w, tag, ans;
        } tr[N << 2];
        void pushup(int p) {
            if(tr[p].tag) tr[p].ans = tr[p].w;
            else tr[p].ans = Add(tr[p << 1].ans, tr[p << 1 | 1].ans);
        }
        void build(int p = 1, int l = 1, int r = n) {
            tr[p].ans = tr[p].tag = 0;
            if(l == r) return void(tr[p].w = dy[l]);
            int mid = l + r >> 1;
            build(p << 1, l, mid);
            build(p << 1 | 1, mid + 1, r);
            tr[p].w = Add(tr[p << 1].w, tr[p << 1 | 1].w);
        }
        void init(int n0) {
            n = n0; build();
        }
        void update(int ql, int qr, int v, int p = 1, int l = 1, int r = n) {
            if(ql > qr) return;
            if(ql <= l && r <= qr) {
                tr[p].tag += v;
                return pushup(p);
            }
            int mid = l + r >> 1;
            if(ql <= mid) update(ql, qr, v, p << 1, l, mid);
            if(qr > mid) update(ql, qr, v, p << 1 | 1, mid + 1, r);
            pushup(p);
        }
        int query() {
            return tr[1].ans;
        }
    }
    void clear() {msz = 0;}
    void insert(ll x0, ll x1, ll y0, ll y1) {
        m[++ msz] = {x0, y0, y1, 1};
        m[++ msz] = {x1, y0, y1, -1};
    }
    int ans;
    int work() {
        if(!msz) return 0;
        disc();
        sort(m + 1, m + msz + 1);
        smt::init(ny - 1);
        ans = 0;
        for(int x = 1, mi = 1; x < nx; x ++) {
            for(; mi <= msz && m[mi].x <= x; mi ++)
                smt::update(m[mi].y1, m[mi].y2 - 1, m[mi].v);
            ans = Add(ans, Mult(dx[x], smt::query()));
        }
        return ans;
    }
}
int x_1, x_2, x_3, y_1, y_2, y_3, a_0, a_1, a_2, a_3;
void Lagrange() {
    int inv = Inv(Mult(Minus(x_2, x_1), Mult(Minus(x_3, x_1), Minus(x_3, x_2))));
    int c3 = Mult(y_3, Mult(inv, Minus(x_2, x_1))), c2 = Mult(y_2, Mult(mod - inv, Minus(x_3, x_1))), c1 = Mult(y_1, Mult(inv, Minus(x_3, x_2)));
    a_2 = Add(c3, Add(c2, c1));
    a_1 = Minus(0, Add(Mult(c3, Add(x_1, x_2)), Add(Mult(c2, Add(x_1, x_3)), Mult(c1, Add(x_2, x_3)))));
    a_0 = Add(Mult(c3, Mult(x_1, x_2)), Add(Mult(c2, Mult(x_1, x_3)), Mult(c1, Mult(x_2, x_3))));
}
void itergral() {
    int tmp3, tmp2, tmp1, tmp0 = 0;
    tmp3 = Mult(a_2, Inv(3));
    tmp2 = Add(Mult(a_2, Inv(2)), Mult(a_1, Inv(2)));
    tmp1 = Add(Mult(a_2, Inv(6)), Add(a_0, Mult(a_1, Inv(2))));
    tie(a_3, a_2, a_1, a_0) = tie(tmp3, tmp2, tmp1, tmp0);
}
int fx(tuple<int, int, int, int> f, int x) {
    int a, b, c, d; tie(a, b, c, d) = f;
    return Add(Mult(Add(Mult(Add(Mult(a, x), b), x), c), x), d);
}
int n[3], x[2][N], y[2][N];
int q, qry[M], ans[M];
set<int> tim;
int tot;
int div[N * N];
int sum[N * N];
tuple<int, int, int, int> func[N * N];
void getf(int dir, int t) {
    x_1 = 1;
    scl::clear();
    for(int i = 1; i <= n[dir]; i ++)
        scl::insert(x[dir][i] - (t + 1 >> 1), x[dir][i] + (t + 2 >> 1), y[dir][i] - (t + 1 >> 1), y[dir][i] + (t + 2 >> 1));
    y_1 = scl::work();
    ++ t;
    x_2 = 2;
    scl::clear();
    for(int i = 1; i <= n[dir]; i ++)
        scl::insert(x[dir][i] - (t + 1 >> 1), x[dir][i] + (t + 2 >> 1), y[dir][i] - (t + 1 >> 1), y[dir][i] + (t + 2 >> 1));
    y_2 = scl::work();
    ++ t;
    x_3 = 3;
    scl::clear();
    for(int i = 1; i <= n[dir]; i ++)
        scl::insert(x[dir][i] - (t + 1 >> 1), x[dir][i] + (t + 2 >> 1), y[dir][i] - (t + 1 >> 1), y[dir][i] + (t + 2 >> 1));
    y_3 = scl::work();
    Lagrange(), itergral();
}
void add(int dir, int t) {
    div[tot] = t;
    if(tot) sum[tot] = Add(sum[tot - 1], fx(func[tot - 1], t - div[tot - 1]));
    getf(dir, t); func[tot ++] = make_tuple(a_3, a_2, a_1, a_0);
}
void solve(int dir) {
    tim = set<int>(); tot = 0;
    for(int i = 1; i <= n[dir]; i ++)
        for(int j = i + 1; j <= n[dir]; j ++)
            tim.insert(max(abs(x[dir][j] - x[dir][i]), abs(y[dir][j] - y[dir][i])));
    add(dir, 0);
    if(tim.size()) for(auto ele : tim)
        add(dir, ele);
    for(int i = 1; i <= q; i ++) {
        int key = upper_bound(div + 1, div + tot, qry[i]) - div - 1;
        ans[i] = Add(ans[i], Add(sum[key], fx(func[key], qry[i] - div[key] + 1)));
    }
}
void Hutao() {
    n[2] = read(), q = read();
    for(int i = 1, tx, ty; i <= n[2]; i ++) {
        tx = read(), ty = read();
        if(tx + ty & 1) {
            x[1][++ n[1]] = tx - ty + 1 >> 1;
            y[1][n[1]] = tx + ty + 1 >> 1;
        } else {
            x[0][++ n[0]] = tx - ty >> 1;
            y[0][n[0]] = tx + ty >> 1;
        }
    }
    for(int i = 1; i <= q; i ++) {
        qry[i] = read();
    }
    solve(0), solve(1);
    for(int i = 1; i <= q; i ++) {
        printf("%d\n", ans[i]);
    }
}
}
signed main() {
    freopen("lifegame.in", "r", stdin);
    freopen("lifegame.out", "w", stdout);
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}