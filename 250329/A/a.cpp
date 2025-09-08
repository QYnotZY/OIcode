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

const int N = 4e5 + 10;
const ll mod = 998244353, G = 3, invG = 332748118;
int n, lim, loglim;
char s[N];
ll f[N], g[N];
inline ll Add(ll a, ll b) {return (a + b) % mod;}
inline ll Minus(ll a, ll b) {return (a - b + mod) % mod;}
inline ll Mult(ll a, ll b) {return (a * b) % mod;}
inline ll Mod(ll a, ll b) {return (a % b + b) % b;}
ll power(ll a, int b){
    ll res = 1;
    for(; b; a = Mult(a, a), b >>= 1)
        if(b & 1) res = Mult(res, a);
    return res;
}
int tax[N];
void getTax(int loglim){
    int lim = 1 << loglim;
    tax[0] = 0;
    for(int i = 1; i < lim; i ++){
        tax[i] = tax[i >> 1] >> 1 | (i & 1) << loglim - 1;
    }
}
void Rev(ll* A, int loglim){
    int lim = 1 << loglim;
    getTax(loglim);
    for(int i = 0; i < lim; i ++)
        if(i < tax[i]) swap(A[i], A[tax[i]]);
}
void NTT(ll* A, int loglim, int typ){
    int lim = 1 << loglim;
    Rev(A, loglim);
    for(int mid = 1; mid < lim; mid <<= 1){
        ll wn = power(~typ ? G : invG, (mod - 1) / (mid << 1));
        for(int j = 0; j < lim; j += mid << 1){
            ll w = 1ll;
            for(int k = 0; k < mid; k ++, w = Mult(w, wn)){
                ll x = A[j + k], y = Mult(w, A[j + k + mid]);
                A[j + k] = Add(x, y);
                A[j + k + mid] = Minus(x, y);
            }
        }
    }
    if(!~typ){
        ll invlim = power(lim, mod - 2);
        for(int i = 0; i < lim; i ++)
            A[i] = Mult(A[i], invlim);
    }
}
void polymult(ll *C, ll *A, ll *B, int loglim){
    int lim = 1 << loglim;
    NTT(A, loglim, 1); NTT(B, loglim, 1);
    for(int i = 0; i < lim; i ++) C[i] = Mult(A[i], B[i]);
    NTT(C, loglim, -1);
}
ll a[N], b[N], c[N];
void DAC(int l, int r, int loglim){
    if(!loglim) return;
    int lim = 1 << loglim, mid = r - l >> 1;
    DAC(l, l + mid, loglim - 1);
    for(int i = 0; i < mid; i ++){
        a[i] = f[i + l] * (s[i + l] != '<');
        b[i] = g[i];
    }
    for(int i = mid; i < r - l; i ++){
        a[i] = 0;
        b[i] = g[i];
    }
    polymult(c, a, b, loglim);
    for(int i = mid; i < r - l; i ++){
        f[i + l] = Add(f[i + l], c[i]);
    }
    DAC(l + mid, r, loglim - 1);
}
int main(){
    scanf("%s", s + 1);
    n = strlen(s + 1);
    int sgn = n & 1 ? 1 : -1;
    for(int i = 1; i <= n; i ++){
        if(s[i] == '<') sgn = -sgn;
    }
    while((1 << loglim) < n + 2) loglim ++;
    ll facn1 = 1;
    for(int i = 1; i <= n + 1; i ++)
        facn1 = Mult(facn1, i);
    g[n + 1] = Mult(power(facn1, mod - 2), mod - 1);
    for(int i = n; i >= 0; i --){
        g[i] = Mult(g[i + 1], i + 1);
    }
    f[0] = 1;
    DAC(0, 1 << loglim, loglim);
    printf("%lld", Mult(Mod(sgn, mod), Mult(facn1, f[n + 1])));
    return 0;
}