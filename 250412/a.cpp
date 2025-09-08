#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
const int maxn = 5e3+14;
const int maxk = 13;
const int warma = 12;
const int inf = 1e9;
namespace IO{
    const int SIZE=1<<21;
    static char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=oS+SIZE-1;
    int qr;
    char qu[55],c;
    bool f;
    #define getchar() (IO::iS==IO::iT?(IO::iT=(IO::iS=IO::ibuf)+fread(IO::ibuf,1,IO::SIZE,stdin),(IO::iS==IO::iT?EOF:*IO::iS++)):*IO::iS++)
    #define putchar(x) *IO::oS++=x,IO::oS==IO::oT?flush():0
    #define flush() fwrite(IO::obuf,1,IO::oS-IO::obuf,stdout),IO::oS=IO::obuf
    #define puts(x) IO::Puts(x)
    template<typename T>
    inline void read(T&x){
        for(f=1,c=getchar();c<48||c>57;c=getchar())f^=c=='-';
        for(x=0;c<=57&&c>=48;c=getchar()) x=(x<<1)+(x<<3)+(c&15); 
        x=f?x:-x;
    }
    template<typename T>
    inline void write(T x){
        if(!x) putchar(48); if(x<0) putchar('-'),x=-x;
        while(x) qu[++qr]=x%10^48,x/=10;
        while(qr) putchar(qu[qr--]);
    }
    inline void Puts(const char*s){
        for(int i=0;s[i];++i)
            putchar(s[i]);
        putchar('\n');
    }
    struct Flusher_{~Flusher_(){flush();}}io_flusher_;
}
using IO::read;
using IO::write;
struct my_hash{
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
        chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }

  size_t operator()(pair<uint64_t, uint64_t> x) const {
    static const uint64_t FIXED_RANDOM =
        chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x.first + FIXED_RANDOM) ^
           (splitmix64(x.second + FIXED_RANDOM) >> 1);
  }
};
unordered_set<int,my_hash> E[maxn][maxk];//(u.v) level-i
mt19937 rd(time(0));
__gnu_pbds::gp_hash_table<int,int,my_hash> lev[maxn];
int n,m;
class ETT{
    private:
        int k;
        int rk[maxn*3],ls[maxn*3],rs[maxn*3],fa[maxn*3],sz[maxn*3],siz[maxn*3];
        int minpos[maxn*3];
        pair<int,pair<int,int> > minedge[maxn*3],w[maxn*3];
        int tot;
        __gnu_pbds::gp_hash_table<int,int,my_hash> id;
        vector<int> vec;
        void pushup(int cur);//FHQtreap
        int merge(int u,int v);//FHQtreap
        void split(int cur,int K,int &l,int &r);//FHQtreap
        int clone();
        int rank(int u);//ETT
        void makeroot(int u);//tree
        int del_left(int u);
    public:
        //tree
        void init(int level);
        bool link(int u,int v);
        void cut(int u,int v);
        void upd(int u);
        int asksz(int u);
        int find(int u);
        int findroot(int u);//ETT
        void update(int u,int v);
        pair<int,pair<int,int> > findedge(int u);
}tr[maxk];
int ETT::del_left(int u){
    if(ls[u]==0){
        u=rs[u];
        pushup(u);
        return u;
    }else{
        ls[u]=del_left(ls[u]);
        if(ls[u]!=0) fa[ls[u]]=u;
        pushup(u);
        return u;
    }
}
void ETT::pushup(int cur){
    if(cur==0) return ;
    sz[cur]=sz[ls[cur]]+sz[rs[cur]]+(cur<=n);
    siz[cur]=siz[ls[cur]]+siz[rs[cur]]+1;
    minpos[cur]=min(minpos[ls[cur]],minpos[rs[cur]]);
    minedge[cur]=min(w[cur],min(minedge[ls[cur]],minedge[rs[cur]]));
    if(cur<=n&&E[cur][k].size()>0) minpos[cur]=min(minpos[cur],cur);
}
int ETT::merge(int u,int v){
    if(u==0||v==0) return u+v;
    if(rk[u]>rk[v]){
        rs[u]=merge(rs[u],v);
        pushup(u);
        if(rs[u]!=0) fa[rs[u]]=u;
        return u;
    }else{
        ls[v]=merge(u,ls[v]);
        pushup(v);
        if(ls[v]!=0) fa[ls[v]]=v;
        return v;
    }
}
void ETT::split(int cur,int K,int &l,int &r){
    if(cur==0){
        l=r=0;
        return ;
    }
    if(K>=siz[ls[cur]]+1){
        l=cur;
        split(rs[l],K-(siz[ls[cur]]+1),rs[l],r);
        if(rs[l]!=0) fa[rs[l]]=l;
        pushup(l);
        return ;
    }else{
        r=cur;
        split(ls[r],K,l,ls[r]);
        if(ls[r]!=0) fa[ls[r]]=r;
        pushup(r);
        return ;
    }
}
int ETT::clone(){
    if(vec.size()==0){
        tot++;
        minpos[tot]=inf;
        siz[tot]=1;
        sz[tot]=0;
        rk[tot]=rd();
        ls[tot]=rs[tot]=fa[tot]=0;
        w[tot]=minedge[tot]=make_pair(inf,make_pair(inf,inf));
        return tot;
    }
    else{
        int u=vec.back();
        vec.pop_back();
        minpos[u]=inf;
        siz[u]=1;
        rk[u]=rd();
        sz[u]=0;
        ls[u]=rs[u]=fa[u]=0;
        w[u]=minedge[u]=make_pair(inf,make_pair(inf,inf));
        return u;
    }
}
int ETT::rank(int u){
    int res=siz[ls[u]];
    while(fa[u]!=0){
        if(u==rs[fa[u]]) res+=siz[ls[fa[u]]]+1;
        u=fa[u];
    }
    return res;
}
void ETT::makeroot(int u){
    int rt=findroot(u);
    int K=rank(u);
    int x=0,y=0;
    split(rt,K,x,y);
    fa[x]=fa[y]=0;
    rt=merge(y,x);
}
void ETT::init(int level){
    k=level;
    tot=n;
    minpos[0]=inf;
    minedge[0]=w[0]=make_pair(inf,make_pair(inf,inf));
    ls[0]=rs[0]=fa[0]=0;
    for(int i=1;i<=n;i++){
        sz[i]=1;
        siz[i]=1;
        ls[i]=rs[i]=fa[i]=0;
        minpos[i]=inf;
        rk[i]=rd();
        minedge[i]=w[i]=make_pair(inf,make_pair(inf,inf));
    }
}
bool ETT::link(int u,int v){
    if(u>v) swap(u,v);
    if(findroot(u)==findroot(v)) return false;
    makeroot(u);
    makeroot(v);
    int e1=id[u*(maxn*3)+v]=clone();
    int e2=id[v*(maxn*3)+u]=clone();
    minedge[e1]=w[e1]=make_pair(lev[u][v],make_pair(u,v));
    int x=findroot(u),y=findroot(v);
    int rt=merge(x,merge(e1,merge(y,e2)));
    return true;
}
void ETT::cut(int u,int v){
    int e1=id[u*(maxn*3)+v],e2=id[v*(maxn*3)+u];
    int l=rank(e1),r=rank(e2);
    if(l>r) swap(l,r);
    int x=0,y=0,z=0;
    int rt=findroot(u);
    split(rt,l,x,y);
    fa[x]=fa[y]=0;
    r-=l;
    y=del_left(y);
    fa[y]=0;
    r--;
    split(y,r,y,z);
    fa[y]=fa[z]=0;
    z=del_left(z);
    fa[z]=0;
    //x y z
    vec.push_back(e1);
    vec.push_back(e2);
    id.erase(e1);
    id.erase(e2);
    rt=merge(x,z);
    return ;
}
void ETT::upd(int u){
    pushup(u);
    while(fa[u]!=0) u=fa[u],pushup(u);
}
int ETT::asksz(int u){
    return sz[findroot(u)];
}
int ETT::find(int u){
    return minpos[findroot(u)];
}
int ETT::findroot(int u){
    while(fa[u]!=0){
        u=fa[u];
    }
    return u;
}
void ETT::update(int u,int v){
    if(u>v) swap(u,v);
    int x=id[u*(maxn*3)+v];
    w[x]=make_pair(lev[u][v],make_pair(u,v));
    pushup(x);
    while(fa[x]!=0) x=fa[x],pushup(x);
}
pair<int,pair<int,int> > ETT::findedge(int u){
    return minedge[findroot(u)];
}
void link(int u,int v){
    if(tr[0].link(u,v)==false){
        E[u][0].insert(v);
        E[v][0].insert(u);
        tr[0].upd(u);
        tr[0].upd(v);
    }
    lev[u][v]=lev[v][u]=0;
}
void insert(int u,int v,int k){
    //insert (u,v) E_k
    if(tr[k].link(u,v)==false){
        E[u][k].insert(v);
        E[v][k].insert(u);
        tr[k].upd(u);
        tr[k].upd(v);
    }
}
void improve(int u,int v){
    E[u][lev[u][v]].erase(v);
    E[v][lev[u][v]].erase(u);
    tr[lev[u][v]].upd(u);
    tr[lev[u][v]].upd(v);
    lev[u][v]++,lev[v][u]++;
    insert(u,v,lev[u][v]);
}
void cut(int u,int v){
    int level=lev[u][v];
    if(E[u][level].find(v)==E[u][level].end()){
        //(u,v) is tree_edge
        for(int i=level;i>=0;i--){
            tr[i].cut(u,v);
        }
        for(int i=level;i>=0;i--){
            if(tr[i].asksz(u)>tr[i].asksz(v)) swap(u,v);
            pair<int,pair<int,int> > res;
            while((res=tr[i].findedge(u)).first==i){
                int x=res.second.first,y=res.second.second;
                lev[x][y]++;
                lev[y][x]++;
                tr[i].update(x,y);
                insert(x,y,lev[x][y]);
            }
            //|T(u)|<=|T(v)|
            int x;
            while((x=tr[i].find(u))!=inf){
                while(E[x][i].size()>0){
                    int y=(*E[x][i].begin());
                    if(tr[i].findroot(x)==tr[i].findroot(y)){
                        improve(x,y);
                    }else{
                        E[x][i].erase(y);
                        E[y][i].erase(x);
                        tr[i].upd(x);
                        tr[i].upd(y);
                        for(int j=i;j>=0;j--) tr[j].link(x,y);
                        lev[u].erase(v),lev[v].erase(u);
                        return ;
                    }
                }
            }
        }
    }else{
        E[u][level].erase(v);
        E[v][level].erase(u);
        tr[level].upd(u);
        tr[level].upd(v);
    }
    lev[u].erase(v),lev[v].erase(u);
}
int lst;
int main(){
    read(n);
    read(m);
    for(int i=0;i<=warma;i++) tr[i].init(i);
    while(m--){
        int op,x,y;
        read(op);
        read(x);
        read(y);
        x^=lst;
        y^=lst;
        if(op==0){
            link(x,y);
        }else if(op==1){
            cut(x,y);
        }else{
            if(tr[0].findroot(x)==tr[0].findroot(y)){
                lst=x;
                putchar('Y');
            }else{
                lst=y;
                putchar('N');
            }
            putchar('\n');
        }
    }    
    return 0;
}