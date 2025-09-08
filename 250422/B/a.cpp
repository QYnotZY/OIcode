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

const int N = 2e5 + 10, mod = 998244353;
int n, lst[N], tr[N];
inline int lowbit(int x) {return x & -x;}
void add(int x, int v){
    while(x <= n + 1){
        (tr[x] += v) %= mod;
        x += lowbit(x);
    }
}
int query(int x){
    int res = 0;
    while(x){
        (res += tr[x]) %= mod;
        x -= lowbit(x);
    }
    return res;
}
int main(){
    n = read();
    add(1, 1);
    for(int i = 1; i <= n; i ++){
        int a = read();
        add(i + 1, (query(i) - query(lst[a]) + mod) % mod);
        if(lst[a]) add(lst[a] + 1, (query(lst[a]) - query(lst[a] + 1) + mod) % mod);
        lst[a] = i;
    }
    printf("%d", (query(n + 1) - 1 + mod) % mod);
    return 0;
}