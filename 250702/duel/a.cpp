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
const int N = 2e5 + 10;
namespace work {
int n, k, s, t;
int c[N], v[N], p[N];
int sta[N];
bool cmp(int a, int b) {
    return v[a] < v[b];
}
bool check(int i) {
    int tmp, res = 0;
    for(int j = 1; j <= k + 1; j ++) {
        if(v[i] < sta[j] - sta[j - 1]) return false;
        if(v[i] >= 2 * (sta[j] - sta[j - 1])) {
            res += sta[j] - sta[j - 1];
            continue;
        }
        tmp = v[i] - sta[j] + sta[j - 1];
        res += 2 * (sta[j] - sta[j - 1]) - tmp;
    }
    return res <= t;
}
int bs(int lb, int ub) {
    int l = lb - 1, r = ub + 1;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(check(p[mid])) r = mid;
        else l = mid;
    }
    return r;
}

int Main() {
    n = read(), k = read(), s = read(), t = read();
    for(int i = 1; i <= n; i ++) 
        c[i] = read(), v[i] = read(), p[i] = i;
    sort(p + 1, p + n + 1, cmp);
    for(int i = 1; i <= k; i ++)
        sta[i] = read();
    sort(sta + 1, sta + k + 1);
    sta[k + 1] = s;
    int ans = 2e9;
    for(int i = bs(1, n); i <= n; i ++) {
        ans = min(ans, c[p[i]]);
    }
    if(ans == 2e9) write(-1);
    else write(ans);
    return 0;
}
}
int main() {
    return work::Main();
}