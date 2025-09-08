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
int n, m1, m2;
vector<pair<int, int> > to[45][2];
int vis1, rq1, vis2, rq2, st;
ll a[1 << 21], pre[1 << 21], suf[1 << 21];
void dfs1(int d) {
    if(d == 0) {
        ++ a[st];
        return;
    }
    int tmpv1 = vis1, tmp1 = rq1, tmpst = st;
    if(!(vis1 >> d - 1 & 1) || !(rq1 >> d - 1 & 1)) {
        for(auto ele : to[d][0]) {
            int &v = ele.first, &w = ele.second;
            if((vis1 >> v - 1 & 1) && (rq1 >> v - 1 & 1) ^ w) {
                vis1 = tmpv1, rq1 = tmp1, st = tmpst;
                goto mk1;
            }
            vis1 |= 1 << v - 1, rq1 |= w << v - 1;
        }
        dfs1(d - 1);
        vis1 = tmpv1, rq1 = tmp1, st = tmpst;
    }mk1:;
    if(!(vis1 >> d - 1 & 1) || (rq1 >> d - 1 & 1)) {
        for(auto ele : to[d][1]) {
            int &v = ele.first, &w = ele.second;
            if((vis1 >> v - 1 & 1) && (rq1 >> v - 1 & 1) ^ w) {
                vis1 = tmpv1, rq1 = tmp1, st = tmpst;
                goto mk2;
            }
            vis1 |= 1 << v - 1, rq1 |= w << v - 1;
        }
        st |= 1 << d - 1;
        dfs1(d - 1);
        vis1 = tmpv1, rq1 = tmp1, st = tmpst;
    }mk2:;
}
ll dfsq2(int d, int &vis1, int &rq1) {
    if(d == 0) return a[st];
    ll res = 0;
    if(!(vis1 >> d - 1 & 1) || !(rq1 >> d - 1 & 1)) {
        res += dfsq2(d - 1, vis1, rq1);
    }
    if(!(vis1 >> d - 1 & 1) || (rq1 >> d - 1 & 1)) {
        st ^= 1 << d - 1;
        res += dfsq2(d - 1, vis1, rq1);
        st ^= 1 << d - 1;
    }
    return res;
}
ll dfsq0(int d, int &vis1, int &rq1) {
    if(d == 0) return suf[st];
    ll res = 0;
    if(!(vis1 >> d - 1 & 1)) {
        res = dfsq0(d - 1, vis1, rq1);
    } else if(rq1 >> d - 1 & 1) {
        st ^= 1 << d - 1;
        res = dfsq0(d - 1, vis1, rq1);
        st ^= 1 << d - 1;
    } else {
        res = dfsq0(d - 1, vis1, rq1);
        st ^= 1 << d - 1;
        res -= dfsq0(d - 1, vis1, rq1);
        st ^= 1 << d - 1;
    }
    return res;
}
ll dfsq1(int d, int &vis1, int &rq1) {
    if(d == 0) return pre[st];
    ll res = 0;
    if((vis1 >> d - 1 & 1) && !(rq1 >> d - 1 & 1)) {
        res = dfsq1(d - 1, vis1, rq1);
    } else if(!(vis1 >> d - 1 & 1)) {
        st ^= 1 << d - 1;
        res = dfsq1(d - 1, vis1, rq1);
        st ^= 1 << d - 1;
    } else {
        res -= dfsq1(d - 1, vis1, rq1);
        st ^= 1 << d - 1;
        res += dfsq1(d - 1, vis1, rq1);
        st ^= 1 << d - 1;
    }
    return res;
}
ll query(int vis1, int rq1) {
    int c0 = 0, c1 = 0, c2 = 0;
    for(int i = 0; i < n >> 1; i ++) {
        if(!(vis1 >> i & 1)) c2 ++;
        else if(rq1 >> i & 1) c1 ++;
        else c0 ++;
    }
    if(c2 <= c0 && c2 <= c1) return dfsq2(n >> 1, vis1, rq1);
    else if(c0 <= c1 && c0 <= c2) return dfsq0(n >> 1, vis1, rq1);
    else return dfsq1(n >> 1, vis1, rq1);
}
ll dfs2(int d) {
    if(d == n >> 1) return query(vis1, rq1);
    int tmpv1 = vis1, tmp1 = rq1, tmpv2 = vis2, tmp2 = rq2; ll res = 0;
    if(!(vis2 >> d - (n >> 1) - 1 & 1) || !(rq2 >> d - (n >> 1) - 1 & 1)) {
        for(auto ele : to[d][0]) {
            int &v = ele.first, &w = ele.second;
            if(v <= (n >> 1)) {
                if((vis1 >> v - 1 & 1) && (rq1 >> v - 1 & 1) ^ w) {
                    vis1 = tmpv1, rq1 = tmp1, vis2 = tmpv2, rq2 = tmp2;
                    goto mk3;
                }
                vis1 |= 1 << v - 1, rq1 |= w << v - 1;
            } else {
                if((vis2 >> v - (n >> 1) - 1 & 1) && (rq2 >> v - (n >> 1) - 1 & 1) ^ w) {
                    vis1 = tmpv1, rq1 = tmp1, vis2 = tmpv2, rq2 = tmp2;
                    goto mk3;
                }
                vis2 |= 1 << v - (n >> 1) - 1, rq2 |= w << v - (n >> 1) - 1;
            }
        }
        res += dfs2(d - 1);
        vis1 = tmpv1, rq1 = tmp1, vis2 = tmpv2, rq2 = tmp2;
    }mk3:;
    if(!(vis2 >> d - (n >> 1) - 1 & 1) || (rq2 >> d - (n >> 1) - 1 & 1)) {
        for(auto ele : to[d][1]) {
            int &v = ele.first, &w = ele.second;
            if(v <= (n >> 1)) {
                if((vis1 >> v - 1 & 1) && (rq1 >> v - 1 & 1) ^ w) {
                    vis1 = tmpv1, rq1 = tmp1, vis2 = tmpv2, rq2 = tmp2;
                    goto mk4;
                }
                vis1 |= 1 << v - 1, rq1 |= w << v - 1;
            } else {
                if((vis2 >> v - (n >> 1) - 1 & 1) && (rq2 >> v - (n >> 1) - 1 & 1) ^ w) {
                    vis1 = tmpv1, rq1 = tmp1, vis2 = tmpv2, rq2 = tmp2;
                    goto mk4;
                }
                vis2 |= 1 << v - (n >> 1) - 1, rq2 |= w << v - (n >> 1) - 1;
            }
        }
        res += dfs2(d - 1);
        vis1 = tmpv1, rq1 = tmp1, vis2 = tmpv2, rq2 = tmp2;
    }mk4:;
    return res;
}
void prework(int n) {
    for(int j = 0; j < 1 << n; j ++) pre[j] = suf[j] = a[j];
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < 1 << n; j ++)
            if(j >> i & 1) pre[j] += pre[j ^ 1 << i];
    for(int i = 0; i < n; i ++)
        for(int j = (1 << n) - 1; ~j; j --)
            if(!(j >> i & 1)) suf[j] += suf[j ^ 1 << i];
}
void Hutao() {
    n = read(), m1 = read(), m2 = read();
    for(int i = 1; i <= m1; i ++){
        int a = read(), b = read();
        if(a > b)
            to[a][1].push_back(make_pair(b, 1));
        else
            to[b][0].push_back(make_pair(a, 0));
    }
    for(int i = 1; i <= m2; i ++){
        int a = read(), b = read();
        if(a > b)
            to[a][1].push_back(make_pair(b, 0));
        else
            to[b][1].push_back(make_pair(a, 0));
    }
    dfs1(n >> 1); prework(n >> 1);
    printf("%lld", dfs2(n));
}
}
int main() {
    freopen("treasure.in", "r", stdin);
    freopen("treasure.out", "w", stdout);
    int t = 1;
    while(t --) work::Hutao();
    return 0;
}