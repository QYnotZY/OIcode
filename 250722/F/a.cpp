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
const int N = 3010;
int n, m, e[N][N];
bool del[N];
void Hutao() {
    n = read(), m = read();
    for(int i = 1; i <= m; i ++) {
        int u = read(), v = read();
        e[u][v] = e[v][u] = 1;
    }
    int cnt = 0;
    for(int i = 1; i <= n; i ++) {
        if(del[i]) continue;
        for(int j = i + 1; j <= n; j ++)
            if(!del[j] && !e[i][j]) {
                cnt ++;
                del[i] = del[j] = 1;
                break;
            }
        if(cnt == n / 3) break;
    }
    cnt = 0;
    for(int i = 1; i <= n; i ++)
        if(!del[i] && cnt < n / 3) ++ cnt, printf("%d ", i);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}