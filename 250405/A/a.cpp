#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
char buf[1 << 20], *p1, *p2;
char gc(){
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
}
// char gc() {return getchar();}
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
typedef unsigned long long ull;

const int N = 1e5 + 10, bas = 1e5 + 1;
string s, t; int lens, lent;

int spre[N], ssuf[N], tpre[N], tsuf[N];
ull powbas[N];
void presolve(){
    int lst[128];
    for(int i = 'a'; i <= 'z'; i ++)
        lst[i] = -1;
    for(int i = 0; i < lens; i ++){
        spre[i] = ssuf[i] = -1;
        if(~lst[s[i]]) spre[i] = lst[s[i]], ssuf[lst[s[i]]] = i;
        lst[s[i]] = i;
    }
    for(int i = 'a'; i <= 'z'; i ++)
        lst[i] = -1;
    for(int i = 0; i < lent; i ++){
        tpre[i] = tsuf[i] = -1;
        if(~lst[t[i]]) tpre[i] = lst[t[i]], tsuf[lst[t[i]]] = i;
        lst[t[i]] = i;
    }
    powbas[0] = 1;
    for(int i = 1; i <= max(lens, lent); i ++)
        powbas[i] = powbas[i - 1] * bas;
}
bool check(int);
int solve(int lb, int ub){
    int left = lb - 1, right = ub + 1;
    while(left + 1 < right){
        int mid = left + (right - left >> 1);
        if(check(mid)) left = mid;
        else right = mid;
    }
    return left;
}
struct Hash{
    ull hs;
    void push_back(int x){
        hs = hs * bas + x;
    }
    void modify(int pos, int x0, int x){
        hs += (x - x0) * powbas[pos];
    }
    void clear(){
        hs = 0;
    }
}hs;
map<ull, int> mp;
int calcs(int pos, int len){
    return ~spre[pos] && spre[pos] >= pos - len + 1 ? pos - spre[pos] : 0;
}
int calct(int pos, int len){
    return ~tpre[pos] && tpre[pos] >= pos - len + 1 ? pos - tpre[pos] : 0;
}
bool check(int len){
    map<ull, int>().swap(mp);
    hs.clear();
    for(int i = 0; i < len; i ++){
        hs.push_back(calcs(i, len));
    }
    mp[hs.hs] = 1;
    for(int i = len; i < lens; i ++){
        if(~ssuf[i - len] && ssuf[i - len] < i) hs.modify(i - ssuf[i - len] - 1, ssuf[i - len] - i + len, 0);
        hs.push_back(calcs(i, len));
        mp[hs.hs] = 1;
    }
    hs.clear();
    for(int i = 0; i < len; i ++){
        hs.push_back(calct(i, len));
    }
    if(mp[hs.hs] == 1) return true;
    for(int i = len; i < lent; i ++){
        if(~tsuf[i - len] && tsuf[i - len] < i) hs.modify(i - tsuf[i - len] - 1, tsuf[i - len] - i + len, 0);
        hs.push_back(calct(i, len));
        if(mp[hs.hs] == 1) return true;
    }
    return false;
}
int main(){
    cin >> s >> t;
    lens = s.size(), lent = t.size();
    presolve();
    printf("%d", solve(1, min(lens, lent)));
    return 0;
}