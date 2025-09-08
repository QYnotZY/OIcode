#include "bits/stdc++.h"
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// inline char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
// }
inline char gc() {return getchar();}
template<typename T>
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
inline T read() {return readnum<T>();}
char wc[50]; int top;
template<typename T>
inline void writenum(T x, char sp){
    if(!x) return putchar('0'), void(putchar(sp));
    if(x < 0) putchar('-'), x = ~x + 1;
    top = 0;
    for(; x; x /= 10) wc[top ++] = x % 10 ^ 48;
    while(top --) putchar(wc[top]);
    putchar(sp);
}
template<typename T = int>
inline void write(T x, char sp = '\n'){
    writenum(x, sp);
}
}
using FastIO::read;
using FastIO::readch;
using FastIO::write;
typedef long long ll;
const int N = 2e5 + 10;
namespace work {
int t, n, q;
int a[N];
set<int> sets[4];
char s[N];
int Main() {
    t = read();
    while(t --) {
        n = read(), q = read();
        scanf("%s", s + 1);
        for(int i = 0; i < 4; i ++)
            set<int>().swap(sets[i]);
        for(int i = 1; i <= q; i ++) {
            char x = readch(), y = readch();
            if(x == 'b' && y == 'a') sets[0].insert(i);
            if(x == 'b' && y == 'c') sets[1].insert(i);
            if(x == 'c' && y == 'a') sets[2].insert(i);
            if(x == 'c' && y == 'b') sets[3].insert(i);
        }
        for(int i = 1; i <= n; i ++) {
            set<int>::iterator x, y;
            if(s[i] == 'a') continue;
            if(s[i] == 'b') {
                x = sets[0].begin();
                if(x != sets[0].end()) {
                    sets[0].erase(x);
                    s[i] = 'a';
                    continue;
                }
                x = sets[1].begin();
                if(x != sets[1].end()) {
                    y = sets[2].lower_bound(*x);
                    if(y != sets[2].end()) {
                        sets[1].erase(x);
                        sets[2].erase(y);
                        s[i] = 'a';
                        continue;
                    }
                }
            }
            if(s[i] == 'c') {
                x = sets[2].begin();
                if(x != sets[2].end()) {
                    sets[2].erase(x);
                    s[i] = 'a';
                    continue;
                }
                x = sets[3].begin();
                if(x != sets[3].end()) {
                    y = sets[0].lower_bound(*x);
                    if(y != sets[0].end()) {
                        sets[3].erase(x);
                        sets[0].erase(y);
                        s[i] = 'a';
                        continue;
                    } else {
                        sets[3].erase(x);
                        s[i] = 'b';
                        continue;
                    }
                }
            }
        }
        printf("%s\n", s + 1);
    }
    return 0;
}
}
int main() {
    return work::Main();
}