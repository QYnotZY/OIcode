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
typedef unsigned long long ull;
namespace Mker{
	unsigned long long SA,SB,SC;
	void init(){scanf("%llu%llu%llu",&SA,&SB,&SC);}
	unsigned long long rand()
	{
	    SA^=SA<<32,SA^=SA>>13,SA^=SA<<1;
	    unsigned long long t=SA;
		SA=SB,SB=SC,SC^=t^SA;return SC;
	}
}
namespace work {
const int x1 = 823062778, x2 = 176316517, mod = 1e9 + 7;
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
inline int Pow_pr(int a, int b) {return b ? Mult(Pow_pr(Mult(a, a), b >> 1), b & 1 ? a : 1) : 1;}
inline int Inv(int a) {return Pow_pr(a, mod - 2);}
inline int Pow(int a, ull b) {return Pow_pr(a, b % (mod - 1));}
ull n;
int ans;
void Hutao() {
    printf("%d\n", Inv(Minus(427786560, 303444676)));
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}
/*
56953
188305837
811694170
303444676
427786560
812312318
*/