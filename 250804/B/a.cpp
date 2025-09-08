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
const int N = 2e5 + 10, K = 210, inf = 1e9;
int n, m, k;
char op[K];
int mp[N];
int round[N];
int ind[N]; queue<int> q;
bool vis[N], nvis[N];
int tm[N], maxtm, ntm[N];
int tot;
vector<int> ans;
inline int cd(int i, int j) {return (i - 1) * m + j;}
inline int mv(int st, char op) {
    int i = (st - 1) / m + 1, j = (st - 1) % m + 1;
    if(op == 'U') {
        if(i == 1) return st;
        if(!mp[cd(i - 1, j)]) return st;
        return cd(i - 1, j);
    } else if(op == 'D') {
        if(i == n) return st;
        if(!mp[cd(i + 1, j)]) return st;
        return cd(i + 1, j);
    } else if(op == 'L') {
        if(j == 1) return st;
        if(!mp[cd(i, j - 1)]) return st;
        return cd(i, j - 1);
    } else if(op == 'R') {
        if(j == m) return st;
        if(!mp[cd(i, j + 1)]) return st;
        return cd(i, j + 1);
    }
}
void Hutao() {
    n = read(), m = read(), k = read();
    scanf("%s", op + 1);
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= m; j ++)
            tot += mp[cd(i, j)] = readch() - '0', round[cd(i, j)] = cd(i, j), vis[cd(i, j)] = mp[cd(i, j)];
    for(int i = 1; i <= k; i ++) {
        char curop = op[i];
        for(int j = 1; j <= n * m; j ++)
            if(mp[j]) round[j] = mv(round[j], curop);
    }
    for(int i = 1; i <= n * m; i ++) ind[round[i]] ++;
    for(int i = 1; i <= n * m; i ++) if(!ind[i]) tm[i] = 1, q.push(i);
    while(q.size()) {
        int i = q.front(); q.pop();
        maxtm = max(maxtm, tm[i]);
        if(!(-- ind[round[i]])) tm[round[i]] = tm[i] + 1, q.push(round[i]);
    }
    for(int i = 1; i <= n * m; i ++) if(!tm[i]) tm[i] = inf;
    for(int i = 1; i <= k; i ++) {
        char curop = op[i];
        memset(nvis, 0, sizeof nvis);
        memset(ntm, 0, sizeof ntm);
        for(int j = 1, j1; j <= n * m; j ++)
            if(vis[j]) {
                j1 = mv(j, curop);
                if(nvis[j1]) {
                    if(ntm[j1] < tm[j]) swap(ntm[j1], tm[j]);
                    for(int t = 0; t < min(maxtm, tm[j]); t ++)
                        ans.push_back(t * k + i);
                }
                else nvis[j1] = 1, ntm[j1] = tm[j];
            }
        swap(vis, nvis);
        swap(tm, ntm);
    }
    for(int i = 1; i <= tot - 1 - ans.size(); i ++) printf("-1\n");
    sort(ans.begin(), ans.end(), greater<int>());
    for(auto ele : ans) printf("%d\n", ele);
    for(int i = tot; i <= n * m; i ++) printf("0\n");
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}