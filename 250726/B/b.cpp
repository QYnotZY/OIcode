#include<bits/stdc++.h>
const int N = 2e5 + 10, mod = 1e9 + 7;
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow(int a, int b) {return b ? Mult(Pow(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return a;}
int main() {
    printf("%d\n", Mult(188305837 - 233, Inv(1332)));
    printf("%d\n", Mult(811694170 - 233, Inv(1332)));
    return 0;
}