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
const int N = 1e3 + 10, inf = 1e9 + 7;
int n, a[N], f[2][N][N];
bool check(int val) {
    int cnt0 = 0, cnt1 = 0, sum = 0, cnts0 = 0;
    for(int i = 1; i <= n; i ++) {
        if(a[i] < val) ++ cnt0, -- sum;
        else ++ cnt1, ++ sum;
        if(sum == 0) ++ cnts0;
    }
    if(cnt0 > cnt1) return 0;
    if(cnt1 > cnt0) return 1;
    return cnts0 & 1 ? 0 : 1;
}
void dfs(int d) {
    if(d > n) {
        for(int i = 1; i <= n; i ++) printf("%d ", a[i]);
        printf(": %d\n", check(1));
        return;
    }
    a[d] = 0;
    dfs(d + 1);
    a[d] = 1;
    dfs(d + 1);
}
void Hutao() {
    n = read();
    dfs(1);
}
}
int main() {
    #ifndef db
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    #endif
    int t = 1; while(t --) Qiuyu3600::Hutao();
    return 0;
}
