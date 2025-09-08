#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
template<typename T=int> 
T readnum(){
    T res=0; bool f=0;
    char ch=getchar();
    while(!('0'<=ch&&ch<='9')){
        if(ch=='-') f=!f;
        ch=getchar();
    }
    while('0'<=ch&&ch<='9'){
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    return f?~res+1:res;
}
template<typename T=int>
T read() {return readnum<T>();}

const int N = 6e5;
const ll mod = 1e9 + 7;
inline ll ADD(ll a, ll b) {return (a + b) % mod;}
inline ll MINUS(ll a, ll b) {return (a - b + mod) % mod;}
inline ll MULT(ll a, ll b) {return a * b % mod;}
inline ll SQ(ll a) {return MULT(a, a);}
int m;
int a, b, u;
ll ans;
ll fac[N + 10], ifac[N + 10], pow2[N + 10];
ll power(ll a, int b){
    ll res = 1;
    for(; b; a = MULT(a, a), b >>= 1)
        if(b & 1) res = MULT(res, a);
    return res;
}
ll inv(ll a) {return power(a, 1e9 + 5);}
void init(){
    fac[0] = 1;
    for(int i = 1; i <= N; i ++)
        fac[i] = MULT(fac[i - 1], i);
    ifac[N] = inv(fac[N]);
    for(int i = N - 1; i >= 0; i --)
        ifac[i] = MULT(ifac[i + 1], i + 1);
    pow2[0] = 1;
    for(int i = 1; i <= N; i ++)
        pow2[i] = MULT(pow2[i - 1], 2ll);
}
ll C(int n, int m){
    if(n < m) return 0;
    if(n == m) return 1;
    return MULT(fac[n], MULT(ifac[m], ifac[n - m]));
}
int gcd(int a, int b){
    if(a < b) swap(a, b);
    if(b == 0) return a;
    return gcd(b, a % b);
}
int main(){
  freopen("name.in", "r", stdin);
  freopen("name.out", "w", stdout);
    init();
    string s;
    cin >> s;
    for(auto ele : s){
        if(ele == 'D') a ++;
        if(ele == 'R') b --;
        if(ele == 'U') a ++, u ++;
    }
    string t;
    cin >> t;
    for(auto ele : t){
        if(ele == 'D') a --;
        if(ele == 'R') b ++;
        if(ele == 'U') b ++, u ++;
    }
    cin >> m;
    if(s.size() == t.size()){
        ll cases = 1;
        for(int i = 0; i < s.size(); i ++){
            if(s[i] == 'D' && t[i] == 'R' || s[i] == 'R' && t[i] == 'D'){
                cases = 0;
                break;
            }
            if(s[i] == 'U' && t[i] == 'U') cases <<= 1;
        }
        ans = ADD(ans, MULT(SQ(MINUS(pow2[m + 1], 2ll)), cases));
        ans = MINUS(ans, MULT(MINUS(pow2[m + 1], 2ll), cases));
    }
    int cura, curb, curg; ll cases;
    for(int i = 0; i <= u; i ++){
        cura = a + i, curb = b + i;
        cases = C(u, i);
        if(cura == 0 && curb == 0){
            ans = ADD(ans, MULT(MINUS(pow2[m + 1], 2ll), cases));
            #ifdef db
            printf("%d %lld\n", i, ans);
            #endif
            continue;
        }
        if(cura == 0 || curb == 0 || 1ll * cura * curb < 0ll)
            continue;
        if(cura < 0) cura = -cura, curb = -curb;
        curg = gcd(cura, curb);
        ans = ADD(ans, MULT(MINUS(pow2[m / max(cura/curg, curb/curg) + 1], 2ll), cases));
        #ifdef db
        printf("%d %lld\n", i, ans);
        #endif
    }
    printf("%lld", ans);
    return 0;
}