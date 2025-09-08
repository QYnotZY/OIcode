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

const int N = 2e5 + 10;
int n, k, cnt;
int a[N], ans[N], vis[N];
int main(){
    n = read(), k = read();
    for(int i = 1, num = 1; i < k; i ++){
        a[i] = read();
        ans[++ cnt] = a[i], vis[a[i]] = 1;
        if(num < a[i]) ans[++ cnt] = num, vis[num] = 1;
        while(vis[num]) ++ num;
    }
    a[k] = read();
    for(int num = n; cnt <= n; num --){
        if(!vis[num]) ans[++ cnt] = num;
    }
    for(int i = 1; i <= n; i ++)
        printf("%d ", ans[i]);
    return 0;
}