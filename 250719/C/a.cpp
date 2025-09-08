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
const int N = 2010, Sgm = 26;
int n;
char s[1000010], t[155][75];
int ans[155];
namespace ACAM {
    int rt, tot;
    struct node {
        int trans[Sgm], fail;
        int end;
    } tr[N];
    void init() {
        for(; tot; -- tot) {
            memset(tr[tot].trans, 0, sizeof tr[tot].trans);
            tr[tot].fail = 0;
        }
        rt = tot = 1;
        tr[rt].fail = rt;
        int u;
        for(int i = 1; i <= n; i ++) {
            int cur = rt, lenti = strlen(t[i] + 1);
            for(int j = 1; j <= lenti; j ++) {
                if(!tr[cur].trans[t[i][j] - 'a']) {
                    tr[cur].trans[t[i][j] - 'a'] = ++ tot;
                    for(u = tr[cur].fail; u ^ rt && !tr[u].trans[t[i][j] - 'a']; u = tr[u].fail) ;
                    if(tr[u].trans[t[i][j] - 'a'] != tot && tr[u].trans[t[i][j] - 'a']) tr[tot].fail = tr[u].trans[t[i][j] - 'a'];
                    else tr[tot].fail = rt;
                }
                cur = tr[cur].trans[t[i][j] - 'a'];
            }
            tr[cur].end = i;
        }
    }
    void query() {
        int cur = rt, len = strlen(s + 1);
        for(int i = 1; i <= len; i ++) {
            while(cur ^ rt && !tr[cur].trans[s[i] - 'a']) cur = tr[cur].fail;
            if(tr[cur].trans[s[i] - 'a']) cur = tr[cur].trans[s[i] - 'a'];
            #ifdef db
            printf("%d %d\n", i, cur);
            #endif
            for(int u = cur; u ^ rt; u = tr[u].fail) {
                if(tr[u].end) ans[tr[u].end] ++;
            }
        }
    }
}
int maxx;
vector<int> tgt;
void Hutao() {
    while(scanf("%d", &n), n) {
        for(int i = 1; i <= n; i ++)
            scanf("%s", t[i] + 1);
        ACAM::init();
        scanf("%s", s + 1);
        maxx = 0;
        for(int i = 1; i <= n; i ++) ans[i] = 0;
        ACAM::query();
        for(int i = 1; i <= n; i ++) {
            if(maxx < ans[i]) {maxx = ans[i]; vector<int> ().swap(tgt);}
            if(maxx == ans[i]) tgt.push_back(i);
        }
        printf("%d\n", maxx);
        for(auto ele : tgt)
            printf("%s\n", t[ele] + 1);
    }
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}