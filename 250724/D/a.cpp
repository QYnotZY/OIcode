#include <bits/stdc++.h>
using namespace std;
namespace FastIO{
// char buf[1 << 20], *p1, *p2;
// inline char gc(){
//     return p1 == p2 && (p2 = (p1 = buf) + (buf, 1, sizeof(buf), stdin), p1 == p2) ? 0 : *p1 ++;
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
typedef long long ll;
namespace work {
const int N = 5e4 + 10;
int n, a[N], b1;
int pre[N]; map<int, int> lst;
int nxt[N], head; bool elm[N];
ll f[N];
void Hutao() {
    while(~scanf("%d", &n)) {
        map<int, int> ().swap(lst);
        memset(elm, 0, (n + 1) * sizeof(int));
        b1 = sqrt(n);
        for(int i = 1; i <= n; i ++) {
            scanf("%d", a + i);
            pre[i] = lst[a[i]];
            lst[a[i]] = i;
        }
        nxt[0] = -1; head = 0;
        f[0] = 0;
        for(int i = 1; i <= n; i ++) {
            f[i] = ll(1e14);
            if(pre[i]) elm[pre[i]] = 1;
            nxt[i] = head; head = i;
            for(int j = nxt[i], lst = head, cnt = 1; ~j; lst = j, j = nxt[j]) {
                if(elm[j]) {
                    nxt[lst] = nxt[j];
                    continue;
                }
                f[i] = min(f[i], f[j] + 1ll * cnt * cnt);
                ++ cnt;
                if(cnt > b1) break;
            }
        }
        printf("%lld\n", f[n]);
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}