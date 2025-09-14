#include <cstring>
#include <string>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>
#include <limits.h>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <bitset>
#include <random>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f3f3f3f3fll
#define IINF 0x3f3f3f3f
#define DINF 10000000
#define ll long long
#define sc scanf
#define pr printf
#define v1 first
#define v2 second
#define lowbit(x) ((x)&(-x))
const int N=1e5+5;
ll dis[N];
bool b[N];
vector<pair<int,ll>> v[N];
void dijk(){
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> q;
    memset(b,0,sizeof(b));
    memset(dis,0x3f,sizeof(dis));
    dis[0]=0;
    q.push({0,0});
    while(q.size()){
        int x=q.top().v2;
        q.pop();
        if(b[x])
            continue;
        b[x]=1;
        for(auto y:v[x]){
            if(dis[x]+y.v2<dis[y.v1]){
                dis[y.v1]=dis[x]+y.v2;
                q.push({dis[y.v1],y.v1});
            }
        }
    }
}
ll h,x,y,z;
signed main(){
    sc("%lld%lld%lld%lld",&h,&x,&y,&z);
    h--;
    for(int i=0; i < x; i++){
        v[i].push_back({(i+y)%x,y});
        v[i].push_back({(i+z)%x,z});
    }
    dijk();
    ll ans=0;
    for(int i=0; i < x; i++){
        if(h>=dis[i])
            ans+=(h-dis[i])/x+1ll;
    }
    cout << ans;
    return 0;
}
