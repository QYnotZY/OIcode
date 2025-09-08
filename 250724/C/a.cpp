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
const int N = 3e5 + 10;
int n, b1, w[N];
vector<pair<int, int> > qry[N];
ll sum[N], ans[N];
int q;
void Hutao() {
    n = read(); b1 = sqrt(n);
    for(int i = 1; i <= n; i ++) w[i] = read();
    q = read();
    for(int i = 1; i <= q; i ++) {
        int x = read(), y = read();
        if(y <= b1) {
            qry[y].push_back(make_pair(x, i));
        } else {
            ll res = 0;
            for(int i = x; i <= n; i += y)
                res += w[i];
            ans[i] = res;
        }
    }
    for(int i = 1; i <= b1; i ++) {
        if(!qry[i].size()) continue;
        sort(qry[i].begin(), qry[i].end());
        for(int j = n, k = qry[i].size() - 1;; j --) {
            sum[j] = j + i > n ? w[j] : sum[j + i] + w[j];
            while(qry[i][k].first == j) {
                ans[qry[i][k --].second] = sum[j];
                if(!~k) break;
            }
            if(!~k) break;
        }
    }
    for(int i = 1; i <= q; i ++)
        printf("%lld\n", ans[i]);
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}