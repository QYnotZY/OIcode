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

const int N = 45, SIZE = 6e6 + 10;
namespace work{
int n;
ll p, a[N];
pair<ll, ll> s1[SIZE], s2[SIZE]; int cnts1, cnts2;
void dfs1(int d, ll val, ll S){
    if(d > n / 2){
        s1[++ cnts1] = make_pair(val, S);
        return;
    }
    dfs1(d + 1, val, S);
    dfs1(d + 1, (val + a[d]) % p, S | 1ll << d - 1);
}
void dfs2(int d, ll val, ll S){
    if(d <= n / 2){
        s2[++ cnts2] = make_pair(val, S);
        return;
    }
    dfs2(d - 1, val, S);
    dfs2(d - 1, (val + a[d]) % p, S | 1ll << d - 1);
}
bool check(ll l, ll r){
    int ans = 0;
    for(int i = 1, j = cnts1, k = cnts1; i <= cnts2; i ++){
        while(j > 0 && l <= s2[i].first + s1[j].first) j --;
        while(k > j && s2[i].first + s1[k].first > r) k --;
        ans += k - j;
    }
    return ans > r - l + 1;
}
ll bsans(ll lb, ll ub){
    ll l = lb, r = ub + 1;
    while(l < r){
        ll mid = l + r - 1 >> 1;
        if(check(l, mid)) r = mid;
        else l = mid + 1;
    }
    return l;
}
int b[N];
void print(ll v){
    int cnt = 0;
    for(int i = 1, j = cnts1, k = cnts1; i <= cnts2; i ++){
        while(j > 0 && s1[j].first + s2[i].first >= v) j --;
        while(k > j && s1[k].first + s2[i].first > v) k --;
        for(int l = j + 1; l <= k; l ++){
            ll S = s1[l].second | s2[i].second;
            if(!cnt){
                cnt ++;
                for(int i = 1; i <= n; i ++)
                    b[i] += bool(S & 1ll << i - 1);
            } else if(!(cnt ^ 1)){
                cnt ++;
                for(int i = 1; i <= n; i ++)
                    b[i] -= bool(S & 1ll << i - 1);
            } else{
                goto Answer;
            }
        }
        if(cnt >= 2) goto Answer;
    }
    Answer:
    for(int i = 1; i <= n; i ++)
        printf("%d ", b[i]);
}
int Main(){
    n = read(), p = read<ll>();
    for(int i = 1; i <= n; i ++)
        a[i] = read<ll>();
    dfs1(1, 0, 0), dfs2(n, 0, 0);
    for(int i = 1; i <= cnts1; i ++) s1[cnts1 + i] = make_pair(s1[i].first - p, s1[i].second);
    // for(int i = 1; i <= cnts1; i ++) s1[cnts1 * 2 + i] = make_pair(s1[i].first + p, s1[i].second);
    cnts1 *= 2;
    s1[++ cnts1].first = 1ll << 50;
    sort(s1 + 1, s1 + cnts1 + 1), sort(s2 + 1, s2 + cnts2 + 1);
    ll v = bsans(0, p - 1);
    print(v);
    return 0;
}
}
int main(){
    return work::Main();
}