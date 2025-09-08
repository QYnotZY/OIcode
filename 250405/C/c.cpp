#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
char gc() {return getchar();}
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
}
using FastIO::read;
typedef long long ll;

const ll b = 19890604, a = 998244353, mod[5] = {40009, 40013, 40031, 40037, 40039};
int n, k;
ll val[5][40100];
set<int> ans;
int main(){
    n = read(), k = read();
    for(int i = 1, x; i <= n; i ++){
        x = read();
        for(int j = 0; j < 5; j ++)
            val[j][x % mod[j]] ^= a * x + b;
    }
    for(int i = 0; i < 5; i ++){
        for(int j = 0; j < mod[i]; j ++){
            if(val[i][j] % a == b){
                int key = val[i][j] / a;
                if(ans.find(key) == ans.end()) ans.insert(key);
            }
        }
    }
    for(auto ele : ans){
        printf("%d\n", ele);
    }
    return 0;
}