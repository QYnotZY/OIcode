#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
using namespace std;
namespace FastIO{
char buf[1 << 20], *p1, *p2;
char gc(){
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
}
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
T read(bool ch = 0, bool sp = 0) {return ch ? readch(sp) : readnum<T>();}
int stk[15], top;
inline void write(int x){
    top = 0;
    if(x == 0) {putchar('0'); return;}
    if(x < 0) putchar('-'), x = -x;
    for(; x; x /= 10) stk[++ top] = x % 10;
    for(int i = top; i > 0; i --) putchar(stk[i] ^ 48);
    return;
}
}
using FastIO::read;
using FastIO::write;
typedef long long ll;

const int N = 12;
const ll mod = 998244353;
inline int ADD(int a, int b) {return a + b >= mod ? a + b - mod : a + b;}
inline int MINUS(int a, int b) {return a >= b ? a - b : a + mod - b;}
int n, m;
ll k;
char s[N], t[N];
ll f[N][N], get1;
int g[N][N];
void UPD(){
    f[1][1] = k, g[1][1] = k & 1ll;
    for(int i = 1; i <= n; i ++){
        for(int j = 1 + (i == 1); j <= m; j ++){
            f[i][j] = (f[i - 1][j] >> 1) + (f[i][j - 1] >> 1);
            g[i][j] = f[i][j] & 1ll;
        }
    }
    for(int i = 1; i <= n; i ++)
        get1 += (s[i] == '1') * (f[i][m] >> 1);
    for(int i = 1; i <= m; i ++)
        get1 += (t[i] == '1') * (f[n][i] >> 1);
}
map<array<int, 11>, int> dp[2];
int ans[N * N], suma[N * N];
void DP(){
    array<int, 11> sets;
    for(int i = 0; i < 11; i ++) sets[i] = 0;
    for(int i = 1; i <= m; i ++) sets[i] = g[1][i];
    dp[0][sets] = 1;
    int tg = 0;
    for(int i = 2; i <= n + 1; i ++){ 
        for(int j = 1; j <= m; j ++){
            for(auto state : dp[tg]){
                auto key = state.first; auto val = state.second;
                if(key[j] & 1ll){
                    auto a = key, b = key;
                    a[j] = g[i][j] + (key[j] >> 1) + 1; j == m ? (a[0] += (s[i - 1] == '1') * (key[j] >> 1)) : (a[j + 1] += key[j] >> 1);
                    b[j] = g[i][j] + (key[j] >> 1); j == m ? (b[0] += (s[i - 1] == '1') * ((key[j] >> 1) + 1)) : (b[j + 1] += (key[j] >> 1) + 1);
                    dp[tg ^ 1][a] = ADD(dp[tg ^ 1][a], val);
                    dp[tg ^ 1][b] = ADD(dp[tg ^ 1][b], val);
                } else{
                    auto a = key;
                    a[j] = g[i][j] + (key[j] >> 1); j == m ? (a[0] += (s[i - 1] == '1') * (key[j] >> 1)) : (a[j + 1] += key[j] >> 1);
                    dp[tg ^ 1][a] = ADD(dp[tg ^ 1][a], ADD(val, val));
                }
            }
            tg ^= 1;
            map<array<int, 11>, int>().swap(dp[tg ^ 1]);
        }
    }
    for(auto state : dp[tg]){
        auto key = state.first; auto val = state.second;
        ll tmp = key[0];
        for(int i = 1; i <= m; i ++)
            tmp += (t[i] == '1') * key[i];
        ans[tmp] = ADD(ans[tmp], val);
    }
    for(int i = 0; i <= 100; i ++){
        if(!i) suma[i] = ans[i];
        else suma[i] = ADD(suma[i - 1], ans[i]);
    }
}
int query(ll l, ll r){
    l -= get1, r -= get1;
    r = min(r, 100ll);
    if(l > r) return 0;
    if(r < 0ll) return 0;
    if(l <= 0ll) return suma[r];
    return MINUS(suma[r], suma[l - 1]);
}
int main(){
    n = read(), m = read(), k = read<ll>();
    for(int i = 1; i <= n; i ++) s[i] = read(1);
    for(int i = 1; i <= m; i ++) t[i] = read(1);
    UPD();
    DP();
    int q = read();
    while(q --){
        ll l = read<ll>(), r = read<ll>();
        write(query(l, r)); putchar('\n');
    }
    return 0;
}