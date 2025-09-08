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
int n;
string s[20];
int to[20][20];
queue<int> q;
vector<int> pre[(1 << 20) + 100];
int win[(1 << 20) + 100], sufsum[(1 << 20) + 100], sufcnt[(1 << 20) + 100];
void adde(int u, int v) {
    sufsum[u] ++;
    pre[v].push_back(u);
}
int bfs() {
    while(q.size()) {
        int u = q.front(); q.pop();
        if(win[u] < 0) {
            for(auto v : pre[u]) {
                if(win[v]) continue;
                win[v] = 1;
                q.push(v);
            }
        } else {
            for(auto v : pre[u]) {
                if(win[v]) continue;
                if(++ sufcnt[v] == sufsum[v]) {
                    win[v] = -1;
                    q.push(v);
                }
            }
        }
    }
    return win[0];
}
void Hutao() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i ++)
        cin >> s[i];
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++)
            to[i][j] = s[i][s[i].size() - 1] == s[j][0] ? 1 : 0;
    for(int i = 1; i <= n; i ++) adde(0, (1 << i - 1) * n + i);
    for(int S = 0; S < 1 << n; S ++)
        for(int i = 1; i <= n; i ++) {
            if(!(S >> i - 1 & 1)) continue;
            bool lose = 1;
            for(int j = 1; j <= n; j ++)
                if(to[i][j] && !(S >> j - 1 & 1)) {
                    lose = 0;
                    adde(S * n + i, (S | 1 << j - 1) * n + j);
                }
            if(lose) {
                win[S * n + i] = -1;
                q.push(S * n + i);
            }
        }
    printf(bfs() == 1 ? "First" : "Second");
}
}
int main() {
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}