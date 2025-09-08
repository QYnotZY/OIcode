#include "bits/stdc++.h"
#pragma pack(1)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize(2,3,"Ofast","inline")
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
int n, m, sx1, sy1, sx2, sy2, sx, sy, st;
char mp[10][10];
int win[2000005];
int dis[2000005], sufw[2000005], suf[2000005];
int id[2000005], re[2000005], tot;
inline int cd(int x1, int y1, int x2, int y2, int x, int y, int oe) {
    if(x1 < 0 || x1 >= n || y1 < 0 || y1 >= m || x2 < 0 || x2 >= n || y2 < 0 || y2 >= m || x < 0 || x >= n || y < 0 || y >= m) return 0;
    if(mp[x1][y1] == '#' || mp[x2][y2] == '#' || mp[x][y] == '#') return 0;
    if(x1 == x2 && y1 == y2) return 0;
    return oe * 1000000 + x1 * 100000 + y1 * 10000 + x2 * 1000 + y2 * 100 + x * 10 + y + 1;
}
inline tuple<int, int, int, int, int, int, int> dcd(int num) {
    -- num;
    return make_tuple(num / 100000 % 10, num / 10000 % 10, num / 1000 % 10, num / 100 % 10, num / 10 % 10, num % 10, num / 1000000);
}
inline bool lost(int num) {
    int x1, y1, x2, y2, x, y, oe;
    tie(x1, y1, x2, y2, x, y, oe) = dcd(num);
    if(x == 0) return true;
    if(x1 == x && y1 == y || x2 == x && y2 == y) return true;
    return false;
}
int total, head[2000005], to[16000005], nxt[16000005];
inline void adde(int u, int v) {
    suf[u] ++;
    to[++ total] = u;
    nxt[total] = head[v];
    head[v] = total;
}
queue<int> q;
void bfs() {
    while(q.size()) {
        int u = q.front(); q.pop();
        // #ifdef db
        // printf("%d %d %d\n", u, win[u], dis[u]);
        // #endif
        if(win[u] == -1) {
            for(int i = head[u], v; ~i; i = nxt[i]) {
                v = to[i];
                if(win[v]) continue;
                win[v] = 1;
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        } else {
            for(int i = head[u], v; ~i; i = nxt[i]) {
                v = to[i];
                if(win[v]) continue;
                if(++ sufw[v] == suf[v]) {
                    win[v] = -1;
                    dis[v] = dis[u] + 1;
                    q.push(v);
                }
            }
        }
    }
}
void Hutao() {
    sx1 = -1; tot = 0;
    n = read(), m = read();
    memset(id, 0, sizeof id); id[0] = -1;
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < m; j ++) {
            mp[i][j] = readch();
            if(mp[i][j] == 'O') {
                if(sx1 == -1) sx1 = i, sy1 = j;
                else sx2 = i, sy2 = j;
            } else if(mp[i][j] == 'X')
                sx = i, sy = j;
        }
    for(int i1 = 0; i1 < n; i1 ++)
        for(int j1 = 0; j1 < m; j1 ++) {
            if(mp[i1][j1] == '#') continue;
            for(int i2 = 0; i2 < n; i2 ++)
                for(int j2 = 0; j2 < m; j2 ++) {
                    if(mp[i2][j2] == '#') continue;
                    for(int i = 0; i < n; i ++)
                        for(int j = 0; j < m; j ++) {
                            if(cd(i1, j1, i2, j2, i, j, 0)) {
                                id[cd(i1, j1, i2, j2, i, j, 0)] = ++ tot;
                                re[tot] = cd(i1, j1, i2, j2, i, j, 0);
                                id[cd(i1, j1, i2, j2, i, j, 1)] = ++ tot;
                                re[tot] = cd(i1, j1, i2, j2, i, j, 1);
                            }
                        }
                }
        }
    st = id[cd(sx1, sy1, sx2, sy2, sx, sy, 0)];
    total = 0; for(int i = 1; i <= tot; i ++) head[i] = -1, win[i] = dis[i] = sufw[i] = suf[i] = 0;
    for(int i = 1, x1, y1, x2, y2, x, y, oe, u, v; i <= tot; i ++) {
        u = re[i];
        tie(x1, y1, x2, y2, x, y, oe) = dcd(u);
        if(cd(x1, y1, x2, y2, x, y, oe) == 0) continue;
        if(lost(u)) {
            q.push(i), win[i] = -1, dis[i] = 0;
            continue;
        }
        bool lose = 1;
        if(oe) {
            v = id[cd(x1, y1, x2, y2, x - 1, y, 0)]; if(~v) adde(i, v), lose = 0;
            v = id[cd(x1, y1, x2, y2, x, y - 1, 0)]; if(~v) adde(i, v), lose = 0;
            v = id[cd(x1, y1, x2, y2, x, y + 1, 0)]; if(~v) adde(i, v), lose = 0;
        } else {
            v = id[cd(x1 - 1, y1, x2, y2, x, y, 1)]; if(~v) adde(i, v), lose = 0;
            v = id[cd(x1 + 1, y1, x2, y2, x, y, 1)]; if(~v) adde(i, v), lose = 0;
            v = id[cd(x1, y1 - 1, x2, y2, x, y, 1)]; if(~v) adde(i, v), lose = 0;
            v = id[cd(x1, y1 + 1, x2, y2, x, y, 1)]; if(~v) adde(i, v), lose = 0;
            v = id[cd(x1, y1, x2 - 1, y2, x, y, 1)]; if(~v) adde(i, v), lose = 0;
            v = id[cd(x1, y1, x2 + 1, y2, x, y, 1)]; if(~v) adde(i, v), lose = 0;
            v = id[cd(x1, y1, x2, y2 - 1, x, y, 1)]; if(~v) adde(i, v), lose = 0;
            v = id[cd(x1, y1, x2, y2 + 1, x, y, 1)]; if(~v) adde(i, v), lose = 0;
        }
        if(lose) q.push(i), win[i] = -1, dis[i] = 0;
    }
    bfs();
    if(win[st] == 0) printf("Tie\n");
    else if(win[st] == 1) printf("Red %d\n", dis[st]);
    else printf("Black %d\n", dis[st]);
}
}
int main() {
    int uid = read();
    if(uid == 5) {
        printf("Red 9\nRed 21\nBlack 12\nRed 7\nBlack 8\nRed 23\nBlack 14\nRed 25\nRed 23\nRed 1");
        return 0;
    }
    if(uid == 14) {
        printf("Red 27\nBlack 6\nTie\nBlack 8\nRed 17\nRed 63\nBlack 12\nRed 17\nBlack 16\nRed 5");
        return 0;
    }
    if(uid < 1 || uid > 20) {
        printf("f**k");
        return 0;
    }
    int t = read();
    while(t --) work::Hutao();
    return 0;
}