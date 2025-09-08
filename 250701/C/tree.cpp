#include "bits/stdc++.h"
using namespace std;
int ask(int, vector<int>);
void answer(int, int);
const int N = 1005;
mt19937_64 rnd(1145141);
vector<int> fl[N];
int fa[N][11];
int dep[N];
int lca(int u, int v) {
    if(dep[u] > dep[v]) swap(u, v);
    for(int i = 10; i >= 0; i --)
        if(dep[fa[v][i]] >= dep[u])
            v = fa[v][i];
    if(u == v) return u;
    for(int i = 10; i >= 0; i --)
        if(fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}
int ask1(int u, vector<int> v) {
    int res = 0;
    for(auto ele : v) {
        res += dep[u] + dep[ele] - (dep[lca(u, ele)] << 1);
    }
    return res;
}
void solve(vector<int> a, vector<int> b) {
    if(a.size() == 1) {
        for(auto ele : b) {
            answer(a[0], ele);
            fa[ele][0] = a[0];
            for(int i = 1; i <= 10; i ++)
                fa[ele][i] = fa[fa[ele][i - 1]][i - 1];
        }
        return;
    }
    vector<int> al, ar;
    int liml = a.size() >> 1, szl = liml, limr = a.size() - liml;
    for(auto elea : a) {
        if(!limr) al.emplace_back(elea);
        else if(!liml) ar.emplace_back(elea);
        else if(rnd() & 1ll) al.emplace_back(elea), liml --;
        else ar.emplace_back(elea), limr --;
    }
    map<int, vector<int> > ma, mb;
    for(auto ele : a) {
        ma[ask1(ele, al)].emplace_back(ele);
    }
    for(auto ele : b) {
        mb[ask(ele, al)].emplace_back(ele);
    }
    for(auto ele : ma) {
        solve(ele.second, mb[ele.first + szl]);
    }
}
void solver(int n, int A, int B) {
    int rt = rnd() % n + 1;
    vector<int> ele;
    ele.emplace_back(rt);
    for(int u = 1; u <= n; u ++) {
        dep[u] = ask(u, ele);
        fl[dep[u]].emplace_back(u);
    }
    for(int i = 1; fl[i].size(); i ++) {
        solve(fl[i - 1], fl[i]);
    }
}