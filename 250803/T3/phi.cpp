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
const int N = 2e5 + 10, inf = 1e6, B = 10000;
const int mod = 998244353;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow(a, mod - 2);}
int pw0[200][B + 10], pw1[200][B + 10];
inline int Pw(int a, int b) {int x1 = b / B, x0 = b % B; return Mult(pw0[a][x0], pw1[a][x1]);}
bool isnp[inf + 10];
int pri[200], prisz;
void Euler(int ub) {
    for(int i = 2; i <= ub; i ++) {
        if(!isnp[i]) {
            pri[++ prisz] = i;
        }
        for(int j = 1; j <= prisz && i * pri[j] <= ub; j ++) {
            isnp[i * pri[j]] = 1;
            if(i % pri[j] == 0) {
                break;
            }
        }
    }
    for(int i = 1; i <= prisz; i ++) {
        pw0[i][0] = 1; for(int j = 1; j <= B; j ++) pw0[i][j] = Mult(pw0[i][j - 1], pri[i]);
        pw1[i][0] = 1; for(int j = 1; j <= B; j ++) pw1[i][j] = Mult(pw1[i][j - 1], pw0[i][B]);
    }
}
int n, q, a[N], inva[N], inva_[N];
int cnt[N][200];
int b, left, right;
struct QRY {
    int l, r, id;
    bool operator < (QRY obj) {
        return l / b < obj.l / b || l / b == obj.l / b && (l / b & 1 ? r > obj.r : r < obj.r);
    }
} qry[N]; int qrysz;
int res = 1;
int buc[inf + 10];
void move(int pos, int typ) {
    if(a[pos] == 1) return;
    if(typ == 1) {
        if(!buc[a[pos]]) {
            res = Mult(res, a[pos] - 1);
        } else res = Mult(res, a[pos]);
        ++ buc[a[pos]];
    } else {
        -- buc[a[pos]];
        if(!buc[a[pos]]) {
            res = Mult(res, inva_[pos]);
        } else res = Mult(res, inva[pos]);
    }
}
int ans[N];
void Hutao() {
    Euler(1000);
    n = read();
    for(int i = 1; i <= n; i ++) {
        a[i] = read();
        for(int j = 1; j <= prisz && pri[j] <= a[i]; j ++)
            while(!(a[i] % pri[j])) {
                a[i] /= pri[j];
                ++ cnt[i][j];
            }
        if(a[i] != 1) {
            cnt[i][0] = 1;
            inva[i] = Inv(a[i]);
            inva_[i] = Inv(a[i] - 1);
        }
    }
    for(int i = 0; i <= prisz; i ++)
        for(int j = 2; j <= n; j ++)
            cnt[j][i] += cnt[j - 1][i];
    q = read();
    for(int i = 1, l, r; i <= q; i ++) {
        ans[i] = 1;
        l = read(), r = read();
        for(int j = 1, tmp; j <= prisz; j ++) {
            tmp = cnt[r][j] - cnt[l - 1][j];
            if(tmp) ans[i] = Mult(ans[i], Mult(pri[j] - 1, Pw(j, tmp - 1)));
        }
        if(cnt[r][0] - cnt[l - 1][0])
            qry[++ qrysz].l = l, qry[qrysz].r = r, qry[qrysz].id = i;
    }
    if(!qrysz) goto PRINTING;
    b = sqrt(qrysz) + 1;
    sort(qry + 1, qry + qrysz + 1);
    left = 1, right = 1; move(1, 1);
    for(int i = 1; i <= qrysz; i ++) {
        while(qry[i].l < left) move(-- left, 1);
        while(right < qry[i].r) move(++ right, 1);
        while(left < qry[i].l) move(left ++, -1);
        while(qry[i].r < right) move(right --, -1);
        ans[qry[i].id] = Mult(ans[qry[i].id], res);
    }
    PRINTING:;
    for(int i = 1; i <= q; i ++)
        printf("%d\n", ans[i]);
}
}
int main() {
    freopen("phi.in", "r", stdin);
    freopen("phi.out", "w", stdout);
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}