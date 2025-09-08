#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// inline char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
char gc() {return getchar();}
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
const int mod = 1e9 + 7, bas = sqrt(mod) + 1, x1 = 303444676, x2 = 427786560, inv666 = 812312318, invx2_x1 = 668350896, invx1x2 = 999999341;
inline int Minus(int a, int b) {return a < b ? a - b + mod : a - b;}
inline int Mult(int a, int b) {return 1ll * a * b % mod;}
int p1[3][35010], p2[3][35010];
void Layla() {
    p1[0][0] = 1; p1[0][1] = x1; for(int i = 2; i <= bas; i ++) p1[0][i] = Mult(p1[0][i - 1], p1[0][1]);
    p2[0][0] = 1; p2[0][1] = p1[0][bas]; for(int i = 2; i <= mod / bas; i ++) p2[0][i] = Mult(p2[0][i - 1], p2[0][1]);
    p1[1][0] = 1; p1[1][1] = x2; for(int i = 2; i <= bas; i ++) p1[1][i] = Mult(p1[1][i - 1], p1[1][1]);
    p2[1][0] = 1; p2[1][1] = p1[1][bas]; for(int i = 2; i <= mod / bas; i ++) p2[1][i] = Mult(p2[1][i - 1], p2[1][1]);
    p1[2][0] = 1; p1[2][1] = invx1x2; for(int i = 2; i <= bas; i ++) p1[2][i] = Mult(p1[2][i - 1], p1[2][1]);
    p2[2][0] = 1; p2[2][1] = p1[2][bas]; for(int i = 2; i <= mod / bas; i ++) p2[2][i] = Mult(p2[2][i - 1], p2[2][1]);
}
inline int Pow(int a, int b) {return Mult(p2[a][b / bas], p1[a][b % bas]);}
ull n;
int ans;
void Hutao() {
    n = Mker::rand();
    n %= mod - 1;
    int x1n = Pow(0, n), x2n = Pow(1, n), invx1x2n = Pow(2, n);
    ans ^= Mult(Mult(Mult(inv666, invx2_x1), invx1x2n), Minus(x1n, x2n));
}
}
int main() {
    work::Layla();
    int t = read(); Mker::init();
    while(t --) work::Hutao();
    printf("%d", work::ans);
    return 0;
}