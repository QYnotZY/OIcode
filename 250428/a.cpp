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
T read() {return readnum<T>();}
}
using FastIO::read;
typedef long long ll;

const int V = 1e6 + 10, N = 2e3 + 10;
int vis[V];
int n;
int main(){
    int t = read();
    while(t --){
        memset(vis, 0, sizeof vis);
        n = read();
        int ans = 0;
        for(int round = 1; round = n; round ++){
            int a = read(), b = read();
            if(b < a) b += 1000000;
            for(int i = a, j = i; i <= b; i ++, j = (i - 1) % 1000000 + 1)
                ans = max(ans, ++ vis[j]);
        }
        printf("%d\n", ans);
    }
    return 0;
}