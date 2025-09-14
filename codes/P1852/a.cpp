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
struct node {
    int a, b, c;
    node() {a = b = c = 0;}
    bool operator==(const node &obj) const {
        return a == obj.a && b == obj.b && c == obj.c;
    }
    bool operator!=(const node &obj) const {
        return !(*this == obj);
    }
    void sort() {
        if(b > c) swap(b, c);
        if(a > b) swap(a, b);
        if(b > c) swap(b, c);
    }
} x, y, resx, resy;
int dx, dy;
pair<node, int> trans(node x, int d) {
    int x1 = x.b - x.a, x2 = x.c - x.b;
    if(d == 0 || x1 == x2) return make_pair(x, 0);
    pair<node, int> res;
    if(x1 > x2) {
        int dd = min(d, (x1 - 1) / x2);
        x.b -= dd * x2;
        x.c -= dd * x2;
        res = trans(x, d - dd);
        return make_pair(res.first, res.second + dd);
    } else {
        int dd = min(d, (x2 - 1) / x1);
        x.a += dd * x1;
        x.b += dd * x1;
        res = trans(x, d - dd);
        return make_pair(res.first, res.second + dd);
    }
}
void Hutao() {
    x.a = read(), x.b = read(), x.c = read();
    y.a = read(), y.b = read(), y.c = read();
    x.sort(), y.sort();
    tie(resx, dx) = trans(x, (int)2e9), tie(resy, dy) = trans(y, (int)2e9);
    if(resx != resy) return void(printf("NO\n"));
    printf("YES\n");
    int le = -1, ri = min(dx, dy) + 1;
    while(le + 1 < ri) (trans(x, dx - (le + ri >> 1)).first == trans(y, dy - (le + ri >> 1)).first ? le : ri) = le + ri >> 1;
    int dlca = le;
    printf("%lld\n", dx + dy - dlca - dlca);
}
}
signed main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}