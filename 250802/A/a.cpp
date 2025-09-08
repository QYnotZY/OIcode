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
const int N = 1e5 + 10;
int n, m;
namespace smt {
    struct node {
        ll ans, ri, le, cnt;
        bool leaf;
    } tr[N << 2];
    ll get_cnt(int p, ll c) {
        if(tr[p].leaf) {
            ll v = tr[p].ans / tr[p].le;
            return max(tr[p].le - c, 0ll) * v;
        }
        if(tr[p << 1 | 1].le > c) {
            return tr[p].cnt + get_cnt(p << 1 | 1, c);
        } else {
            return get_cnt(p << 1, c - tr[p << 1 | 1].le + tr[p << 1 | 1].ri);
        }
    }
    void pushup(int p) {
        tr[p].cnt = get_cnt(p << 1, tr[p << 1 | 1].ri);
        tr[p].le = max(tr[p << 1].le - tr[p << 1 | 1].ri, 0ll) + tr[p << 1 | 1].le;
        tr[p].ri = max(tr[p << 1 | 1].ri - tr[p << 1].le, 0ll) + tr[p << 1].ri;
        tr[p].ans = tr[p << 1 | 1].ans + tr[p].cnt;
    }
    void build(int p = 1, int l = 1, int r = n) {
        if(l == r) {
            tr[p].leaf = 1;
            tr[p].cnt = tr[p].le = tr[p].ri = tr[p].ans = 0;
            return;
        }
        tr[p].cnt = tr[p].le = tr[p].ri = tr[p].ans = 0;
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
    }
    void update_add(ll x, ll y)
}
void Hutao() {

}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}