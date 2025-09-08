#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
char gc() {return getchar();}
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
T read(bool ch = 0, bool sp = 0) {return ch ? readch(sp) : readnum<T>();}
}
using FastIO::read;
typedef long long ll;

const int maxS = 1 << 20;
int n, l, m, S, ful;
int dp[120][maxS];
int count(int S){
    int res = 0;
    for(; S; S -= S & -S) res ++;
    return res;
}
int dfs(int dep){
    int res = 0;
    if(count(S) == l / 2) return 0;
    if(dep == n + 1) return 1;
    int s0 = S;
    S = (S & ful) << 1 | 0;
    res += dfs(dep + 1);
    S = s0;
    S = (S & ful) << 1 | 1;
    res += dfs(dep + 1);
    S = s0;
    return res;
}
int main(){
    n = read(), l = read(), m = read();
    ful = (1 << l - 1) - 1;
    for(int i = 1; i <= m; i ++){
        char a = getchar();
        while(33 > a || a >= 127) a = getchar();
        if(i < l){
            S = S << 1 | (a ^ 48);
        } else{
            S = (S & ful) << 1 | (a ^ 48);
            if(count(S) == l / 2){
                printf("0");
                exit(0);
            }
        }
    }
    printf("%d", dfs(m + 1));
    return 0;
}