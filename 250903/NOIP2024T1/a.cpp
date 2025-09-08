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
const int N = 1e5 + 10;
int n;
int s1[N], s2[N], t1[N], t2[N];
int bl1[N], bl2[N], sum1[N][2], sum2[N][2];
int ans;
void Hutao() {
    memset(sum1, 0, sizeof(sum1));
    memset(sum2, 0, sizeof(sum2));
    ans = 0;
    n = read();
    for(int i = 1; i <= n; i ++)
        s1[i] = readch() - '0';
    for(int i = 1; i <= n; i ++)
        s2[i] = readch() - '0';
    for(int i = 1, lst = 0; i <= n; i ++) {
        t1[i] = readch() - '0';
        if(t1[i]) {
            if(!lst) lst = i;
            bl1[i] = lst;
            ++ sum1[lst][s1[i]];
        } else bl1[i] = lst = 0;
    }
    for(int i = 1, lst = 0; i <= n; i ++) {
        t2[i] = readch() - '0';
        if(t2[i]) {
            if(!lst) lst = i;
            bl2[i] = lst;
            ++ sum2[lst][s2[i]];
        } else bl2[i] = lst = 0;
    }
    for(int i = 1; i <= n; i ++) {
        if(!t1[i] && !t2[i]) {
            ans += (s1[i] == s2[i]);
        } else if(t1[i] ^ t2[i]) {
            if(!t1[i] && sum2[bl2[i]][s1[i]]) -- sum2[bl2[i]][s1[i]], ++ ans;
            else if(!t1[i] && !sum2[bl2[i]][s1[i]]) -- sum2[bl2[i]][s1[i] ^ 1];
            if(!t2[i] && sum1[bl1[i]][s2[i]]) -- sum1[bl1[i]][s2[i]], ++ ans;
            else if(!t2[i] && !sum1[bl1[i]][s2[i]]) -- sum1[bl1[i]][s2[i] ^ 1];
        }
    }
    for(int i = 1; i <= n; i ++) {
        if(t1[i] && t2[i]) {
            if(sum1[bl1[i]][0] && sum2[bl2[i]][0]) {
                -- sum1[bl1[i]][0], -- sum2[bl2[i]][0], ++ ans;
            } else if(sum1[bl1[i]][1] && sum2[bl2[i]][1]) {
                -- sum1[bl1[i]][1], -- sum2[bl2[i]][1], ++ ans;
            } else if(sum1[bl1[i]][0] && sum2[bl2[i]][1]) {
                -- sum1[bl1[i]][0], -- sum2[bl2[i]][1];
            } else {
                -- sum1[bl1[i]][1], -- sum2[bl2[i]][0];
            }
        }
    }
    printf("%d\n", ans);
}
}
int main() {
    int t = read(); while(t --) Qiuyu3600::Hutao();
    return 0;
}