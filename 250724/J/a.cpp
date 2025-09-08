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
const int N = 1e6 + 10;
int n, q, qr; int b1;
int a[N], mdf[N][4];
struct Qry {
    int l, r, t, id;
    bool operator < (Qry obj) {
        if(l / b1 == obj.l / b1) {
            if(r / b1 == obj.r / b1)
                return t < obj.t;
            return r / b1 < obj.r / b1;
        }
        return l / b1 < obj.l / b1;
    }
} qry[N];
int cnt[N], res;
void move(int pos, int typ) {
    res -= int(cnt[a[pos]] >= 1);
    cnt[a[pos]] += typ;
    res += int(cnt[a[pos]] >= 1);
}
int ans[N];
void Hutao() {
    n = read(), q = read();
    for(int i = 1; i <= n; i ++) a[i] = read();
    for(int i = 1; i <= q; i ++) {
        char op = readch(); int x = read(), y = read();
        if(op == 'R') {
            mdf[++ qr][0] = x; mdf[qr][1] = y;
            mdf[qr][2] = x; mdf[qr][3] = a[x];
            a[x] = y;
        } else {
            qry[i - qr].l = x, qry[i - qr].r = y, qry[i - qr].t = qr, qry[i - qr].id = i - qr;
        }
    }
    q -= qr;
    b1 = int(1.0 * n / pow(q, 1.0 / 3) + 1e-6) + 1;
    sort(qry + 1, qry + q + 1);
    int l = 1, r = 1, t = qr; move(1, 1);
    for(int i = 1; i <= q; i ++) {
        while(qry[i].l < l) move(-- l, 1);
        while(r < qry[i].r) move(++ r, 1);
        while(qry[i].l > l) move(l ++, -1);
        while(r > qry[i].r) move(r --, -1);
        while(t < qry[i].t) {
            ++ t;
            int &x = mdf[t][0], &y = mdf[t][1];
            if(l <= x && x <= r) {
                res -= int(cnt[a[x]] >= 1) + int(cnt[y] >= 1);
                -- cnt[a[x]], ++ cnt[y];
                res += int(cnt[a[x]] >= 1) + int(cnt[y] >= 1);
            }
            a[x] = y;
        }
        while(t > qry[i].t) {
            int &x = mdf[t][2], &y = mdf[t][3];
            if(l <= x && x <= r) {
                res -= int(cnt[a[x]] >= 1) + int(cnt[y] >= 1);
                -- cnt[a[x]], ++ cnt[y];
                res += int(cnt[a[x]] >= 1) + int(cnt[y] >= 1);
            }
            a[x] = y;
            -- t;
        }
        ans[qry[i].id] = res;
    }
    for(int i = 1; i <= q; i ++) printf("%d\n", ans[i]);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}