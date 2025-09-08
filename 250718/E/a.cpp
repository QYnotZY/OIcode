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
const int N = 4e5 + 10;
char s[N];
namespace SA {
    int sa[N], sa0[N], rk[N], rk0[N << 1], ad[N];
    int buc[N];
    void sort(int n) {
        int m = 127, cnt = 0;
        for(int i = 1; i <= n; i ++) buc[rk[i] = s[i]] ++;
        for(int i = 1; i <= m; i ++) buc[i] += buc[i - 1];
        for(int i = n; i; i --) sa[buc[s[i]] --] = i;

        for(int w = 1; ; w <<= 1, m = cnt, cnt = 0) {
            for(int i = n; i + w > n; i --) sa0[++ cnt] = i;
            for(int i = 1; i <= n; i ++) if(sa[i] - w > 0) sa0[++ cnt] = sa[i] - w;

            for(int i = 1; i <= m; i ++) buc[i] = 0;
            for(int i = 1; i <= n; i ++) ++ buc[ad[i] = rk[sa0[i]]];
            for(int i = 1; i <= m; i ++) buc[i] += buc[i - 1];
            for(int i = n; i; i --) sa[buc[ad[i]] --] = sa0[i];

            cnt = 0; for(int i = 1; i <= n; i ++) rk0[i] = rk[i];
            for(int i = 1; i <= n; i ++)
                rk[sa[i]] = rk0[sa[i]] == rk0[sa[i - 1]] && rk0[sa[i] + w] == rk0[sa[i - 1] + w] ? cnt : ++ cnt;
            if(cnt == n) return;
        }
    }
    int ht[N];
    void get_height(int n) {
        for(int i = 1, j = 0; i <= n; i ++) {
            j = max(j - 1, 0);
            while(s[i + j] == s[sa[rk[i] - 1] + j]) j ++;
            ht[rk[i]] = j;
        }
    }
}
namespace ST {
    int minn[N][21];
    void build(int n) {
        for(int i = 1; i <= n; i ++)
            minn[i][0] = SA::ht[i];
        for(int i = 1; i <= 20; i ++)
            for(int j = 1; j <= n + 1 - (1 << i); j ++)
                minn[j][i] = min(minn[j][i - 1], minn[j + (1 << i - 1)][i - 1]);
    }
    inline int log2(int n) {
        int res = 0;
        while(n >>= 1) res ++;
        return res;
    }
    int query(int l, int r) {
        int log2n = log2(r - l + 1);
        return min(minn[l][log2n], minn[r + 1 - (1 << log2n)][log2n]);
    }
}
int lcp(int pos1, int pos2) {
    if(SA::rk[pos1] > SA::rk[pos2]) swap(pos1, pos2);
    return ST::query(SA::rk[pos1] + 1, SA::rk[pos2]);
}
int n, m;
int qaq[N];
namespace STqaq {
    int minn[N][21];
    void build(int n) {
        for(int i = 1; i <= n; i ++)
            minn[i][0] = qaq[i];
        for(int i = 1; i <= 20; i ++)
            for(int j = 1; j <= n + 1 - (1 << i); j ++)
                minn[j][i] = max(minn[j][i - 1], minn[j + (1 << i - 1)][i - 1]);
    }
    inline int log2(int n) {
        int res = 0;
        while(n >>= 1) res ++;
        return res;
    }
    int query(int l, int r) {
        int log2n = log2(r - l + 1);
        return max(minn[l][log2n], minn[r + 1 - (1 << log2n)][log2n]);
    }
}
void Furina() {
    for(int i = 1, j = 0; i <= n + 1 + m; i ++) {
        if(SA::sa[i] > n + 1)
            for(j ++; j ^ i; j ++)
                qaq[SA::sa[j]] = max(qaq[SA::sa[j]], lcp(SA::sa[j], SA::sa[i]));
        else if(SA::sa[i] <= n)
            if(j) qaq[SA::sa[i]] = max(qaq[SA::sa[i]], lcp(SA::sa[j], SA::sa[i]));
    }
}
int Skirk(int left, int right) {
    int l = -1, r = right - left + 2, mid;
    while(l + 1 < r) {
        mid = l + r >> 1;
        if(STqaq::query(left, right - mid + 1) >= mid) l = mid;
        else r = mid;
    }
    return l;
}
int q;
void Hutao() {
    #ifdef db
    printf("2");
    #endif
    scanf("%s", s + 1); n = strlen(s + 1);
    s[n + 1] = '|';
    scanf("%s", s + n + 2); m = strlen(s + n + 2);
    #ifdef db
    printf("2");
    #endif
    SA::sort(n + 1 + m);
    #ifdef db
    printf("1");
    #endif
    SA::get_height(n + 1 + m);
    #ifdef db
    printf("1");
    #endif
    ST::build(n + 1 + m);
    #ifdef db
    printf("1");
    #endif
    Furina();
    #ifdef db
    printf("1");
    #endif
    STqaq::build(n);
    #ifdef db
    printf("1");
    #endif
    scanf("%d", &q);
    for(int l, r; q --;) {
        scanf("%d%d", &l, &r);
        printf("%d\n", Skirk(l, r));
    }
}
}
int main() {
    #ifdef db
    freopen("P6640_2.in", "r", stdin);
    #endif
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}