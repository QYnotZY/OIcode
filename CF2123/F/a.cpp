#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// inline char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
inline char gc() {return getchar();}
template<typename T>
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
inline T read() {return readnum<T>();}
char wc[50]; int top;
template<typename T>
inline void writenum(T x, char sp){
    if(!x) return putchar('0'), void(putchar(sp));
    if(x < 0) putchar('-'), x = ~x + 1;
    top = 0;
    for(; x; x /= 10) wc[top ++] = x % 10 ^ 48;
    while(top --) putchar(wc[top]);
    putchar(sp);
}
template<typename T = int>
inline void write(T x, char sp = '\n'){
    writenum(x, sp);
}
}
using FastIO::read;
using FastIO::write;
typedef long long ll;
const int N = 1e5 + 10;
namespace work {
bitset<N> isp;
int p[N];
void Init(){
	for(int i = 2; i <= N; i ++) {
		if(!isp[i])
			p[++p[0]] = i;
		for(int j = 1; j <= p[0] && p[j] * i <= N; j ++) {
			isp[i * p[j]] = true;
			if(i % p[j] == 0) break;
		}
	}
}
int n;
bitset<N> vis;
int cir[N];
int ans[N];
int Main() {
    Init();
    int t = read();
    while(t --) {
        n = read();
        for(int i = 1; i <= n; i ++) vis[i] = 0;
        int cur = lower_bound(p + 1, p + p[0] + 1, n) - p;
        ans[1] = 1;
        for(; cur >= 1; cur --) {
            if(p[cur] > n) continue;
            cir[0] = 0;
            for(int i = p[cur]; i <= n; i += p[cur]) {
                if(vis[i]) continue;
                vis[i] = 1;
                cir[++ cir[0]] = i;
            }
            for(int i = 1; i < cir[0]; i ++)
                ans[cir[i]] = cir[i + 1];
            ans[cir[cir[0]]] = cir[1];
        }
        for(int i = 1; i <= n; i ++)
            write(ans[i], ' ');
        printf("\n");
    }
    return 0;
}
}
int main() {
    return work::Main();
}