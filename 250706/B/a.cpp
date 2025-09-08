#include <bits/stdc++.h>
using namespace std;
int f0, f1;
int ans, b0, b1, b[30], n;
int main() {
    for(int i = 0; i < 30; i ++) {
        if(i & 1) f1 |= 1 << i;
        else f0 |= 1 << i;
    }
    int t;
    scanf("%d", &t);
    while(t --) {
        ans = 0;
        printf("%d\n", f0);
        fflush(stdout);
        scanf("%d", &b1);
        b1 -= f0 << 1;
        printf("%d\n", f1);
        fflush(stdout);
        scanf("%d", &b0);
        b0 -= f1 << 1;
        for(int i = 0; i < 30; i ++) {
            if(i & 1) b[i] = 3 << i & b1;
            else b[i] = 3 << i & b0;
        }
        printf("!\n");
        fflush(stdout);
        scanf("%d", &n);
        ans = 0;
        for(int i = 0; i < 30; i ++) {
            if(n & 1 << i) ans += 1 << i + 1;
            else ans += b[i];
        }
        printf("%d\n", ans);
        fflush(stdout);
    }
    return 0;
}