#include"bits/stdc++.h"
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
template<typename T=int>
T read() {return readnum<T>();}

ll n, k;
int main(){
    freopen("kasane.in", "r", stdin);
    freopen("kasane.out", "w", stdout);
    int t; cin >> t;
    while(t --){
        cin >> n >> k;
        string s; cin >> s;
        cout << n * (n - 1) / 2 + n;
    }
    return 0;
}