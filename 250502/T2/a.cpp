#include "bits/stdc++.h"
using namespace std;
int size();
int test(vector<int> x);
void Reverse(int l, int r);
void answer(int x);
int n, ans;
int B, bcnt;
inline int bl(int i) {return (i - 1) * B + 1;}
inline int br(int i) {return min(i * B , n);}
inline int bid(int i) {return i / B + 1;}
vector<int> x;
void init() {
    n = size();
    B = pow(n, 0.5) * 3;
    bcnt = bid(n);
}
void solve() {
    init();
    for(int i = bl(1); i <= br(1); i ++) {
        x.emplace_back(i);
        int a = test(x);
        if(a == 1) ans ++;
        else Reverse(i, i);
        x.pop_back();
    }
    for(int i = 2; i <= bcnt; i ++) {
        int bsz = br(i) - bl(i) + 1;
        vector<int>().swap(x);
        for(int j = bl(i); j <= br(i); j ++)
            x.emplace_back(j);
        int a = test(x), f = 1;
        if(!a) {
            ans += bsz >> 1;
            continue;
        }
        if(a ^ -1)
            Reverse(bl(i), br(i)), f = -f;
        int left = 0, right = bsz + 1;
        while(left + 1 < right) {
            int mid = left + right >> 1;
            for(int i = 1; i <= mid; i ++) x.emplace_back(i);
            if(test(x) <= 0) left = mid;
            else right = mid;
            for(int i = 1; i <= mid; i ++) x.pop_back();
        }
        ans += (bsz - f * left) >> 1;
    }
    answer(ans);
}