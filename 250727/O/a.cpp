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
const int N = 5e4 + 10;
int mu[N], summu[N];
vector<int> pri; bitset<N> isnp;
void Euler(int n) {
    mu[1] = 1; summu[1] = 1;
    for(int i = 2; i <= n; i ++) {
        if(!isnp[i]) {
            pri.push_back(i);
            mu[i] = -1;
        }
        for(auto j : pri) {
            if(i * j > n) break;
            isnp.set(i * j);
            if(!(i % j)) {
                mu[i * j] = 0;
                break;
            }
            mu[i * j] = -mu[i];
        }
        summu[i] = summu[i - 1] + mu[i];
    }
}
ll s[N];
void get_s(int n) {
    for(int i = 1; i <= n; i ++)
        for(int l = 1, r; l <= i; l = r + 1) {
            r = i / (i / l);
            s[i] += (r - l + 1) * (i / l);
        }
}
void Hutao() {
    Euler(50000); get_s(50000);
    int t = read();
    while(t --) {
        int n = read(), m = read(); ll ans = 0;
        for(int l = 1, r; l <= min(n, m); l = r + 1) {
            r = min(n / (n / l), m / (m / l));
            ans += (summu[r] - summu[l - 1]) * s[n / l] * s[m / l];
        }
        printf("%lld\n", ans);
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}