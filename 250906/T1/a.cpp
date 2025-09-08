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
const int N = 1e5 + 100;
int n;
int preu[N], sufu[N], prel[N], sufl[N];
void Hutao() {
    n = read();
    for(int i = 0; i <= n + 2; i ++) {
        preu[i] = sufu[i] = 0;
        prel[i] = sufl[i] = n + 1;
    }
    for(int i = 1, x, y, d; i <= n; i ++) {
        x = read(), y = read(), d = read();
        if(d == 1) {
            prel[x + 1] = min(prel[x + 1], y);
        } else if(d == 2) {
            sufl[x] = min(sufl[x], y);
        } else if(d == 3) {
            sufu[x] = max(sufu[x], y);
        } else {
            preu[x + 1] = max(preu[x + 1], y);
        }
    }
    for(int i = 2; i <= n + 1; i ++) {
        preu[i] = max(preu[i], preu[i - 1]);
        prel[i] = min(prel[i], prel[i - 1]);
    }
    for(int i = n; i; -- i) {
        sufu[i] = max(sufu[i], sufu[i + 1]);
        sufl[i] = min(sufl[i], sufl[i + 1]);
    }
    for(int i = 1, ub, lb; i <= n + 1; i ++) {
        ub = max(preu[i], sufu[i]);
        lb = min(prel[i], sufl[i]);
        if(lb > ub) return void(printf("No\n"));
    }
    printf("Yes\n");
}
}
int main() {
    #ifndef db
    freopen("myth.in", "r", stdin);
    freopen("myth.out", "w", stdout);
    #endif
    int t = read(); while(t --) Qiuyu3600::Hutao();
    return 0;
}