#include <bits/stdc++.h>
using namespace std;
int t, n, ans = 2, a[200005], f;
int main() {
    cin >> t;
    while(t --) {
        ans = 2;
        f = 0;
        cin >> n;
        for(int i = 1; i <= n; i ++)
            cin >> a[i];
        sort(a + 2, a + n);
        if(n == 2) {
            if(a[1] * 2 < a[2]) {
                cout << "-1" << endl;
                continue;
            }
        }
        for(int i = 1; i < n;) {
            if(a[i] * 2 < a[i + 1]) {
                cout << "-1" << endl;
                f = 1;
                break;
            }
            if(a[i] * 2 >= a[n])
                break;
            // x 为第一个>2*a[i]的元素的下标,这里用了指针运算
            int x = upper_bound(a + 2, a + n, a[i] * 2) - a;
            i = x - 1;
            ans ++;
        }
        if(!f) cout << ans << endl;
    }
    return 0;
}