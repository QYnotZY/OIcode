#include<iostream>
#include<cstdio>
#include<set>
#include<stack>
#include<algorithm>
using namespace std;
typedef long long ll;
template<typename T=int> 
T readnum(){
    T res=0; bool f=0;
    char ch=getchar();
    while(!('0'<=ch&&ch<='9')){
        if(ch=='-') f=!f;
        ch=getchar();
    }
    while('0'<=ch&&ch<='9'){
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    return f?~res+1:res;
}
char readchar(){
    char ch=getchar();
    while(!(32<ch&&ch<127)) ch=getchar();
    return ch;
}
template<typename T=int> T read() {return readnum<T>();}
const int N=5e4+10;
int n,m;
set<int> tr;
stack<int> st;
int main(){
    while(~scanf("%d%d",&n,&m)){
    tr.clear();
    while(st.size()) st.pop();
    tr.insert(0);
    tr.insert(n+1);
    for(int i=1,x;i<=m;i++){
        char op=readchar();
        if(op=='D'){
            scanf("%d",&x);
            tr.insert(x);
            st.push(x);
        }
        if(op=='Q'){
            scanf("%d",&x);
            set<int>::iterator it=lower_bound(tr.begin(),tr.end(),x);
            if(*it==x) printf("0\n");
            else printf("%d\n",*it-*(--it)-1);
        }
        if(op=='R'){
            tr.erase(st.top());
            st.pop();
        }
    }
    }
    return 0;
}