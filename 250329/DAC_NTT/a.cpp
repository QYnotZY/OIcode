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
int n, m, len, lim, loglim;
ll f[N], g[N];
inline ll Add(ll a, ll b) {return (a + b) % mod;}
inline ll Minus(ll a, ll b) {return (a - b + mod) % mod;}
inline ll Mult(ll a, ll b) {return (a * b) % mod;}
inline ll Mod(ll a, ll b) {return (a % b + b) % b;}
ll power(ll a, int b){
    b = Mod(b, mod - 1);
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
        ll invlim = power(lim, -1);
        for(int i = 0; i < lim; i ++)
            A[i] = Mult(A[i], invlim);
    }
}
void polymult(ll *C, ll *A, ll *B, int loglim){
    int lim = 1 << loglim;
    NTT(A, loglim, 1); NTT(B, loglim, 1);
    for(int i = 0; i < lim; i ++) C[i] = Mult(A[i], B[i]);
    NTT(C, loglim, -1);
    #ifdef db
    for(int i = 0; i < lim; i ++)
        printf("%lld ", C[i]);
    printf("\n");
    #endif
}
ll a[N], b[N], c[N];
void DAC(int l, int r, int loglim){
    #ifdef db
    printf("%d %d %d:\n", l, r, loglim);
    #endif
    if(!loglim) return;
    int lim = 1 << loglim, mid = r - l >> 1;
    DAC(l, l + mid, loglim - 1);
    for(int i = 0; i < mid; i ++){
        a[i] = f[i + l];
        b[i] = g[i];
    }
    for(int i = mid; i < r - l; i ++){
        a[i] = 0;
        b[i] = g[i];
    }
    #ifdef db
    for(int i = 0; i < r - l; i ++)
        printf("%d ", a[i]);
    printf("  ");
    for(int i = 0; i < r - l; i ++)
        printf("%d ", b[i]);
    printf("\n");
    #endif
    polymult(c, a, b, loglim);
    for(int i = mid; i < r - l; i ++){
        f[i + l] = Add(f[i + l], c[i]);
    }
    DAC(l + mid, r, loglim - 1);
}
int main(){
    n = read();
    f[0] = 1, g[0] = 0;
    for(int i = 1; i < n; i ++){
        g[i] = read();
    }
    while((1 << loglim) < n) loglim ++;
    DAC(0, 1 << loglim, loglim);
    for(int i = 0; i < n; i ++)
        printf("%lld ", f[i]);
    return 0;
}