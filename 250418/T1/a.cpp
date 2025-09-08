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

const int N = 5e3 + 10;
int n, m;
int a[N], b[N];
void input(){
    n = read(), m = read();
    for(int i = 1; i <= m; i ++)
        a[i] = read(), b[i] = read();
}
int c[N];
ll cnt[N][N];
void solve(){
    for(int i = 1; i <= n; i ++)
        cnt[i][i] = m * (m - 1) >> 1;
    for(int i = 1; i <= m; i ++){
        for(int i = 1; i <= n; i ++) c[i] = i;
        for(int j = i; j <= m; j ++){
            cnt[a[j]][c[a[j]]] -= m - j + 1, cnt[b[j]][c[b[j]]] -= m - j + 1;
            swap(c[a[j]], c[b[j]]);
            cnt[a[j]][c[a[j]]] += m - j + 1, cnt[b[j]][c[b[j]]] += m - j + 1;
        }
    }
}
void print(){
    for(int i = 1; i <= n; i ++){
        ll res = 0;
        for(int j = 1; j <= n; j ++)
            res += j * cnt[i][j];
        printf("%lld ", res);
    }
}
int main(){
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    input();
    solve();
    print();
    return 0;
}