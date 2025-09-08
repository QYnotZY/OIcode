#include "bits/stdc++.h"
using namespace std;
namespace FastIO {
    template <typename T = int> T read() {
        char ch = '\0'; bool f = 0; T res = 0;
        for(; !('0' <= ch && ch <= '9'); ch = getchar()) if(ch == '-') f = !f;
        for(; '0' <= ch && ch <= '9'; ch = getchar()) res = (res << 3) + (res << 1) + (ch ^ '0');
        return f ? ~res + 1 : res;
    }
    char readch(const int acsp = 0) {
        char ch = '\0';
        for(; !(33 - acsp <= ch && ch < 127); ch = getchar()) ;
        return ch;
    }
} using FastIO::read; using FastIO::readch;
typedef long long ll;
namespace Qiuyu3600 {
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
inline int Add(int a, int b) {return a + b < mod ? a + b : a + b - mod;}
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
int n, m, v, ans;
map<int, int> mp;
void Hutao() {
    n = read(), m = read(), v = read(), ans = 1;
    mp = map<int, int>();
    for(int i = 1, a, b; i <= m; i ++) {
        a = read(), b = read();
        if(mp.find(a) != mp.end() && mp[a] ^ b)
            return void(printf("0\n"));
        mp[a] = b;
    }
    int lst = 0, cur, res;
    for(auto ele : mp) {
        cur = ele.first;
        if(!lst) res = Pow(v, 2 * (cur - 1));
        else res = Minus(Pow(v, 2 * (cur - lst)), Mult(Pow(v, cur - lst - 1), v - 1));
        ans = Mult(ans, res);
        lst = cur;
    }
    res = Pow(v, 2 * (n - lst));
    ans = Mult(ans, res);
    printf("%d\n", ans);
}
}
int main() {
    int t = read(); while(t --) Qiuyu3600::Hutao();
    return 0;
}