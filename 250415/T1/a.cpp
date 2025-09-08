#include "bits/stdc++.h"
#pragma GCC optimize("Ofast,unroll-loops")
using namespace std;
namespace FastIO{
char buf[1 << 20], *p1, *p2;
char gc(){
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
}
// char gc() {return getchar();}
template<typename T = int>
inline T readnum(){
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
template<typename T = int>
T read() {return readnum<T>();}
}
using FastIO::read;
typedef long long ll;

const int N = 1e6 + 10, mod = 1e9 + 7;
inline int Add(int a, int b) {return a + b >= mod ? a + b - mod : a + b;}
int n, m;
int a[N], b[17];
int sta[N], dp[2][1 << 17];
int main(){
    freopen("bard.in", "r", stdin);
    freopen("bard.out", "w", stdout);
    n = read(), m = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    for(int i = 0; i < m; i ++)
        b[i] = read();
    dp[0][0] = dp[1][0] = 1;
    int tmp = 0;
    for(int i = 1; i <= n; i ++){
        for(int st = 0; st < 1 << m; st ++)
            dp[tmp ^ 1][st] = dp[tmp][st];
        for(int lg = 0; lg < m; lg ++){
            if(a[i] % b[lg]) continue;
            for(int st = 0; st < 1 << m; st ++){
                if(!(st & 1 << lg))
                    dp[tmp ^ 1][st | 1 << lg] = Add(dp[tmp ^ 1][st | 1 << lg], dp[tmp][st]);
            }
        }
        tmp ^= 1;
    }
    printf("%d", dp[tmp][(1 << m) - 1]);
    return 0;
}