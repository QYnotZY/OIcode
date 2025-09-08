#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
char gc() {return getchar();}
template<typename T = int>
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
T read() {return readnum<T>();}
}
using FastIO::read;
typedef long long ll;

const int N = 5e5 + 10;
const ll inf = 1e15;
namespace sol{
int n, m, c0;
int x[N]; ll c[N];
struct Mdf{
    int op, l, r, id;
    bool operator < (Mdf obj){
        if(x[id] == x[obj.id]){
            if(id == obj.id){
                if(l == obj.l)
                    return op < obj.op;
                return l < obj.l;
            }
            return id < obj.id;
        }
        return x[id] < x[obj.id];
    }
}mdf[N];
int cnt;
struct Mdf1{
    int l, r, x; ll y;
}mdf1[N];
vector<int> son[N];
int dfn[N], curdfn; int sz[N];
void dfs(int u){
    dfn[u] = ++ curdfn; sz[u] = 1;
    for(auto v : son[u]){
        dfs(v);
        sz[u] += sz[v];
    }
}
void init(){
    n = read(), m = read(), c[1] = read();
    mdf[1] = {0, 1, n, 1};
    for(int i = 2, fr, id; i <= n; i ++){
        mdf[i].op = read(); fr = read() + 1; mdf[i].id = read() + 1;
        son[fr].emplace_back(i);
        if(!mdf[i].op) x[mdf[i].id] = read(), read(), read(), c[mdf[i].id] = read<ll>();
    }
    dfs(1);
    for(int i = 1; i <= n; i ++)
        mdf[i].l = dfn[i], mdf[i].r = dfn[i] + sz[i] - 1;
    sort(mdf + 1, mdf + n + 1);
    for(int i = 1, j; i <= n; i = j){
        for(j = i + 1; mdf[j].op; j ++);
        for(int k = i + 1, lst = mdf[i].l; k <= j; k ++){
            if(k ^ j){
                mdf1[++ cnt].l = lst;
                mdf1[cnt].r = mdf[k].l - 1;
                mdf1[cnt].x = 2 * x[mdf[i].id];
                mdf1[cnt].y = 1ll * x[mdf[i].id] * x[mdf[i].id] + c[mdf[i].id];
                lst = mdf[k].r + 1;
            }
            else{
                mdf1[++ cnt].l = lst;
                mdf1[cnt].r = mdf[i].r;
                mdf1[cnt].x = 2 * x[mdf[i].id];
                mdf1[cnt].y = 1ll * x[mdf[i].id] * x[mdf[i].id] + c[mdf[i].id];
            }
        }
    }
    #ifdef db
    for(int i = 1; i <= n; i ++)
        printf("%d %d %d %d %d %lld\n", mdf[i].op, mdf[i].l, mdf[i].r, mdf[i].id, x[mdf[i].id], c[mdf[i].id]);
    for(int i = 1; i <= n; i ++)
        printf("%d %d %d %lld\n", mdf1[i].l, mdf1[i].r, mdf1[i].x, mdf1[i].y);
    #endif
}
namespace smt{
    vector<pair<int, ll> > conv[N << 2];
    void upd1(int p, int x, ll y){
        for(int sz = conv[p].size(); sz >= 2; sz = conv[p].size()){
            int x1 = conv[p][sz - 1].first; ll y1 = conv[p][sz - 1].second;
            int x2 = conv[p][sz - 2].first; ll y2 = conv[p][sz - 2].second;
            if((y1 - y2) * (x - x1) < (y - y1) * (x1 - x2)) break;
            conv[p].pop_back();
        }
        conv[p].push_back(make_pair(x, y));
    }
    void update(int ql, int qr, int x, ll y, int p = 1, int l = 1, int r = n){
        if(ql > qr) return;
        if(ql <= l && r <= qr)
            return upd1(p, x, y);
        int mid = l + (r - l >> 1);
        if(ql <= mid) update(ql, qr, x, y, p << 1, l, mid);
        if(qr > mid) update(ql, qr, x, y, p << 1 | 1, mid + 1, r);
    }
    ll qry1(int p, int k){
        if(!conv[p].size()) return inf;
        int l = 0, r = conv[p].size();
        while(l + 1 < r){
            int mid = l + (r - l >> 1);
            if(conv[p][mid - 1].second - 1ll * k * conv[p][mid - 1].first > conv[p][mid].second - 1ll * k * conv[p][mid].first)
                l = mid;
            else r = mid;
        }
        return conv[p][l].second - 1ll * k * conv[p][l].first;
    }
    ll query(int x, int k, int p = 1, int l = 1, int r = n){
        if(l == r) return qry1(p, k);
        int mid = l + (r - l >> 1);
        ll res = qry1(p, k);
        if(x <= mid) res = min(res, query(x, k, p << 1, l, mid));
        else res = min(res, query(x, k, p << 1 | 1, mid + 1, r));
        return res;
    }
}
int Main(){
    init();
    for(int i = 1; i <= cnt; i ++)
        smt::update(mdf1[i].l, mdf1[i].r, mdf1[i].x, mdf1[i].y);
    for(int i = 1; i <= m; i ++){
        int s = read() + 1, x0 = read();
        printf("%lld\n", smt::query(dfn[s], x0) + 1ll * x0 * x0);
    }
    return 0;
}
}
int main(){
    return sol::Main();
}