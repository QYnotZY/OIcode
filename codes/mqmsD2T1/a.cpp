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
const int N = 2e5 + 10;
int n, m, a[N], ans[N];
pair<int, int> mdf[N]; int tot;
int bound;
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    for(int i = 1, r, t; i <= m; i ++) {
        t = read(), r = read();
        while(tot && mdf[tot].first <= r) -- tot;
        mdf[++ tot] = make_pair(r, t);
    } mdf[tot + 1] = make_pair(0, 0);
    bound = mdf[1].first;
    for(int i = bound + 1; i <= n; i ++) ans[i] = a[i];
    sort(a + 1, a + bound + 1);
    for(int i = 1, l = 1, r = bound; i <= tot; i ++)
        for(int j = mdf[i].first; j ^ mdf[i + 1].first; -- j)
            ans[j] = mdf[i].second == 1 ? a[r --] : a[l ++];
    for(int i = 1; i <= n; i ++)
        printf("%d ", ans[i]);
}
}
int main() {
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}