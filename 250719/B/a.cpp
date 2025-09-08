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
const int N = 1.5e5 + 10, aN = 4.5e6 + 10, mod = 998244353;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int G(int a) {return Minus(Pow(2, a), 1);}
namespace trie {
    struct node {
        int trans[2];
        int sz;
    } tr[aN];
    int rt, tot;
    void init() {
        rt = tot = 1;
    }
    void insert(int x) {
        int cur = rt;
        for(int i = 29, j; ~i; -- i) {
            tr[cur].sz ++;
            j = x >> i & 1;
            if(!tr[cur].trans[j]) tr[cur].trans[j] = ++ tot;
            cur = tr[cur].trans[j];
        }
        tr[cur].sz ++;
    }
    int solve(int x, int p, int q, int b) {
        if(!p && !q) return 0;
        if(b == -1) return p == q ? G(tr[p].sz) : Mult(G(tr[p].sz), G(tr[q].sz));
        int x1 = x & (1 << b) - 1, res = 0;
        if(x >> b & 1) {
            if(p == q) return Add(solve(x, tr[p].trans[0], tr[p].trans[1], b - 1), Add(G(tr[tr[p].trans[0]].sz), G(tr[tr[p].trans[1]].sz)));
            int p0q1 = solve(x, tr[p].trans[0], tr[q].trans[1], b - 1), p1q0 = solve(x, tr[p].trans[1], tr[q].trans[0], b - 1);
            res = Add(res, Mult(p0q1, p1q0));
            res = Add(res, Add(Mult(p0q1, Add(G(tr[tr[p].trans[1]].sz), G(tr[tr[q].trans[0]].sz))), Mult(p1q0, Add(G(tr[tr[p].trans[0]].sz), G(tr[tr[q].trans[1]].sz)))));
            res = Add(res, Add(Add(p0q1, p1q0), Add(Mult(G(tr[tr[p].trans[0]].sz), G(tr[tr[q].trans[0]].sz)), Mult(G(tr[tr[p].trans[1]].sz), G(tr[tr[q].trans[1]].sz)))));
        } else {
            res = Add(solve(x, tr[p].trans[0], tr[q].trans[0], b - 1), solve(x, tr[p].trans[1], tr[q].trans[1], b - 1));
        }
        return res;
    }
}
int n, x;
int a;
void Hutao() {
    n = read(), x = read();
    trie::init();
    for(int i = 1; i <= n; i ++) {
        a = read();
        trie::insert(a);
    }
    printf("%d", trie::solve(x, 1, 1, 29));
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}