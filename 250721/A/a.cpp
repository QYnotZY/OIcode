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
const int N = 1 << 20;
int n, q;
int a[N], pre[N], suf[N];
char qry[22]; int cnt0, cnt1, cnt_;
int res;
int Furina(int d) {
    if(d == n) {
        return a[res];
    }
    int ans = 0;
    if(qry[d] == '0') {
        ans += Furina(d + 1);
    } else if(qry[d] == '1') {
        res ^= 1 << d;
        ans = Furina(d + 1);
        res ^= 1 << d;
    } else {
        ans = Furina(d + 1);
        res ^= 1 << d;
        ans += Furina(d + 1);
        res ^= 1 << d;
    }
    return ans;
}
int Citlali(int d) {
    if(d == n) {
        return suf[res];
    }
    int ans = 0;
    if(qry[d] == '1') {
        res ^= 1 << d;
        ans += Citlali(d + 1);
        res ^= 1 << d;
    } else if(qry[d] == '?') {
        ans += Citlali(d + 1);
    } else {
        ans += Citlali(d + 1);
        res ^= 1 << d;
        ans -= Citlali(d + 1);
        res ^= 1 << d;
    }
    return ans;
}
int Layla(int d) {
    if(d == n) {
        return pre[res];
    }
    int ans = 0;
    if(qry[d] == '0') {
        ans += Layla(d + 1);
    } else if(qry[d] == '?') {
        res ^= 1 << d;
        ans += Layla(d + 1);
        res ^= 1 << d;
    } else {
        ans -= Layla(d + 1);
        res ^= 1 << d;
        ans += Layla(d + 1);
        res ^= 1 << d;
    }
    return ans;
}
void Skirk() {
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < 1 << n; j ++)
            if(j >> i & 1) pre[j] += pre[j ^ 1 << i];
    for(int i = 0; i < n; i ++)
        for(int j = (1 << n) - 1; ~j; j --)
            if(!(j >> i & 1)) suf[j] += suf[j ^ 1 << i];
}
void Hutao() {
    n = read(), q = read();
    for(int i = 0; i < 1 << n; i ++)
        pre[i] = suf[i] = a[i] = readch() - '0';
    Skirk();
    for(; q --;) {
        cnt0 = cnt1 = cnt_ = 0;
        for(int i = n - 1; ~i; i --) {
            qry[i] = readch();
            if(qry[i] == '0') cnt0 ++;
            if(qry[i] == '1') cnt1 ++;
            if(qry[i] == '?') cnt_ ++;
        }
        if(cnt_ <= cnt0 && cnt_ <= cnt1) {
            printf("%d\n", Furina(0));
        } else if(cnt0 <= cnt_ && cnt0 <= cnt1) {
            printf("%d\n", Citlali(0));
        } else {
            printf("%d\n", Layla(0));
        }
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}