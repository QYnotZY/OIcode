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
const int N = 1010;
int n, id[N], b[7];
ll q[13];
vector<int> qry[13];
void Hutao() {
    scanf("%d", &n);
    for(int j = 0; j < 6; j ++) b[j] = j;
    for(int i = 1; i <= n; i ++) {
        for(int j = 5; ~j; j --) {
            id[i] |= 1 << b[j];
            qry[b[j]].push_back(i);
        }
        for(int j = 5; ~j; j --)
            if(b[j] - b[0] == j) {
                b[j] ++;
                for(int k = j - 1; ~k; k --)
                    b[k] = k;
                break;
            }
    }
    for(int i = 0; i < 13; i ++) {
        if(!qry[i].size()) continue;
        printf("? %d ", qry[i].size());
        for(auto ele : qry[i]) printf("%d ", ele);
        printf("\n"); fflush(stdout);
        scanf("%lld", q + i);
    }
    printf("! ");
    for(int i = 1; i <= n; i ++) {
        ll ans = 0;
        for(int j = 0; j < 13; j ++) {
            if(!(id[i] >> j & 1)) ans |= q[j];
        }
        printf("%lld ", ans);
    }
    printf("\n"); fflush(stdout);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}