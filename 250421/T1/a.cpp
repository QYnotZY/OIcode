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
T read() {return readnum<T>();}
}
using FastIO::read;
typedef long long ll;

const int N = 2e5 + 505, sqrtN = 505;
int n, q, bs;
int a[N];
int l[N], r[N], k[N], p[N];
int ans[N];
int lst[N], cntb[sqrtN], cnt[N], sum;
vector<int> _[N];
void small(int L, int R, int K){
    for(int i = L; i <= R; i ++)
        _[r[p[i]]].emplace_back(p[i]);
    for(int ri = 1; ri <= n; ri ++){
        if(a[ri] < K) goto qqqq;
        if(lst[a[ri] / K]){
            cnt[lst[a[ri] / K]] --;
            cntb[lst[a[ri] / K] / bs] --;
            sum --;
        }
        lst[a[ri] / K] = ri;
            cnt[ri] ++;
            cntb[ri/ bs] ++;
            sum ++;
        qqqq:
        for(auto i : _[ri]){
            int li = l[i] - 1, bli = li / bs;
            int suml = 0;
            for(int j = 0; j < bli; j ++)
                suml += cntb[j];
            for(int j = bli * bs; j <= li; j ++)
                suml += cnt[j];
            ans[i] = sum - suml;
        }
    }
    sum = 0;
    for(int i = 1; i <= n; i ++)
        cnt[i] = 0, lst[i] = 0;
    for(int i = 0; i <= n / bs; i ++)
        cntb[i] = 0;
    for(int i = 1; i <= n; i ++)
        vector<int>().swap(_[i]);
}
int lstsum[N];
vector<int> vpos[N];
void big(int L, int R){
    for(int i = L; i <= R; i ++)
        _[k[p[i]] - 1].emplace_back(p[i]);
    for(int i = 1; i <= n; i ++)
        vpos[a[i]].emplace_back(i);
    for(int ri = 0; ri <= n; ri ++){
        for(auto pos : vpos[ri]){
            for(int j = pos; j <= pos / bs * bs + bs - 1; j ++)
                cnt[j] ++;
            for(int j = pos / bs + 1; j <= n / bs; j ++)
                cntb[j] ++;
        }
        for(auto i : _[ri]){
            _[min(ri + k[i], n + 1)].emplace_back(i);
            int sum = cntb[r[i] / bs] + cnt[r[i]] - cntb[(l[i] - 1) / bs] - cnt[l[i] - 1];
            if(ri >= k[i]) ans[i] += sum != lstsum[i];
            lstsum[i] = sum;
        }
        vector<int>().swap(_[ri]);
    }
    for(auto i : _[n + 1]){
        int sum = cntb[r[i] / bs] + cnt[r[i]] - cntb[(l[i] - 1) / bs] - cnt[l[i] - 1];
        ans[i] += sum != lstsum[i];
        lstsum[i] = sum;
    }
}
bool cmp(int x, int y){
    return k[x] < k[y];
}
int main(){
    #ifndef db
    freopen("div.in", "r", stdin);
    freopen("div.out", "w", stdout);
    #endif
    n = read(), q = read();
    bs = pow(n, 0.5);
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    for(int i = 1; i <= q; i ++)
        l[i] = read(), r[i] = read(), k[i] = read(), p[i] = i;
    sort(p + 1, p + q + 1, cmp);
    for(int i = 1, j = 1; i <= q; i = j){
        if(k[p[i]] > bs){
            big(i, q);
            break;
        }
        while(k[p[j]] == k[p[i]]) j ++;
        small(i, j - 1, k[p[i]]);
    }
    for(int i = 1; i <= q; i ++)
        printf("%d\n", ans[i]);
    return 0;
}