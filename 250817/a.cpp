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
constexpr int N = 5e5 + 10, D = 20;
namespace LinearBase {
    int v[D], t[D];
    void init() {memset(v, 0, sizeof v), memset(t, 0, sizeof t);}
    void insert(int x, int tim) {
        for(int i = D - 1; ~i; -- i) {
            if(!(x >> i & 1)) continue;
            if(!v[i]) {v[i] = x, t[i] = tim; return;}
            if(t[i] < tim) swap(v[i], x), swap(t[i], tim); x ^= v[i];
        }
    }
    int query(int tim) {
        int res = 0;
        for(int i = D - 1; ~i; -- i) {
            if(t[i] < tim || res >> i & 1) continue;
            res ^= v[i];
        }
        return res;
    }
}
int n, a[N], q, ans[N];
struct QRY {int l, r, id; bool operator < (const QRY& obj) {return r < obj.r;}} qry[N];
void Hutao() {
    n = read();
    for(int i = 1; i <= n; i ++) a[i] = read();
    q = read();
    for(int i = 1; i <= q; i ++) qry[i] = QRY{read(), read(), i};
    LinearBase::init();
    sort(qry + 1, qry + q + 1);
    for(int i = 1, qi = 1; i <= n; i ++) {
        LinearBase::insert(a[i], i);
        for(; qry[qi].r == i; ++ qi) ans[qry[qi].id] = LinearBase::query(qry[qi].l);
    }
    for(int i = 1; i <= q; i ++) printf("%d\n", ans[i]);
}
}
int main() {
    Qiuyu3600::Hutao();
    return 0;
}