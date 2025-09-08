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
const int N = 2e5 + 10;
char s[N];
int n, k, a[N], b[N];
struct ANS {
    int l, r, p;
    ANS operator + (const int& obj) const {
        return ANS{l + obj, r + obj, ~p ? p + obj : -1};
    }
    ANS operator | (const ANS& obj) const {
        ANS res;
        res.l = min(l, obj.l), res.r = max(r, obj.r);
        if(r + 1 < obj.l) res.p = r + 1;
        else if(obj.r < l - 1) res.p = l - 1;
        else if(~p && ~obj.p) {
            if(p == obj.p) res.p = p;
            else if(p < obj.l || p > obj.r) res.p = p;
            else if(obj.p < l || obj.p > r) res.p = obj.p;
            else res.p = -1;
        } else if(~p) {
            if(p < obj.l || p > obj.r) res.p = p;
            else res.p = -1;
        } else if(~obj.p) {
            if(obj.p < l || obj.p > r) res.p = obj.p;
            else res.p = -1;
        } else res.p = -1;
        return res;
    }
    bool operator > (const int& obj) const {
        return l <= obj && obj <= r && obj != p;
    }
} f[N][2];
void Hutao() {
    scanf("%d%d", &n, &k);
    scanf("%s", s + 1);
    for(int i = 1; i <= n; i ++) {
        a[i] = (s[i] == 'B') ? 1 : 0;
        if(i > 1 && a[i] != a[i - 1]) -- k;
    }
    f[1][a[1]] = {0, 0, -1}, f[1][1 ^ a[1]] = {1, 1, -1};
    for(int i = 2; i <= n; i ++) {
        f[i][1 ^ a[i]] = (f[i - 1][a[i]] + 2) | (f[i - 1][1 ^ a[i]] + 1);
        f[i][a[i]] = (f[i - 1][1 ^ a[i]] + 1) | (f[i - 1][a[i]]);
    }
    if(f[n][0] > k) b[n] = 0;
    else if(f[n][1] > k) b[n] = 1;
    else return void(printf("NO\n"));
    printf("YES\n");
    for(int i = n - 1; i; i --) {
        if(b[i + 1] != a[i + 1]) -- k;
        if(f[i][b[i + 1]] > k) b[i] = b[i + 1];
        else b[i] = 1 ^ b[i + 1], -- k;
    }
    for(int i = 1; i <= n; i ++) putchar(b[i] ? 'B' : 'A');
    printf("\n");
}
}
int main() {
    int t = read();
    while(t --) work::Hutao();
    return 0;
}