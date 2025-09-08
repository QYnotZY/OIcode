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

const int N = 1e6 + 10, eof = -1;
int n, a[N];
int cnt[N], minn, maxx;
int ans;
int main(){
    n = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    for(int i = 1; i <= n; i ++){
        minn = eof, maxx = eof;
        for(int i = 1; i <= n; i ++)
            cnt[i] = 0;
        for(int j = i; j <= n; j ++){
            if(minn == eof || a[j] < minn) minn = a[j];
            if(maxx == eof || a[j] > maxx) maxx = a[j];
            cnt[a[j]] ++;
            if(1ll * (j - i + 1) != 1ll * (minn + maxx) * (maxx - minn + 1) / 2)
                continue;
            int f = 1;
            for(int k = minn; k <= maxx; k ++)
                if(cnt[k] != k){
                    f = 0;
                    break;
                }
            ans += f;
        }
    }
    printf("%d", ans);
    return 0;
}