#include <bits/stdc++.h>
using namespace std;
int n, k;
int a[305], b[305], ned[305], f[305][305][128], sum[128], L[305], R[305];
bool pd[305];
vector<int> ng;
int main()
{
    scanf("%d%d", &n, &k);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), ans += 2 * a[i];
    a[0] = 1e6;
    a[n + 1] = 1e6;
    ans += 2e6;
    for (int i = 2; i <= k + 1; i++)
        scanf("%d", &b[i]), pd[b[i]] = true;
    b[1] = 0;
    b[k + 2] = n + 1;
    for (int i = 1; i <= n; i++)
        if (!pd[i])
        ng.push_back(a[i]);
    int K = 0;
    for (int i = 1; i <= k + 1; i++)
    {
        if (b[i] == b[i + 1] - 1)
        {
            ans += abs(a[b[i + 1]] - a[b[i]]);
            continue;
        }
        ned[++K] = b[i + 1] - b[i] - 1;
        L[K] = a[b[i]];
        R[K] = a[b[i + 1]];
        if (L[K] > R[K])
            swap(L[K], R[K]);
    }
    ng.push_back(-1);
    sort(ng.begin(), ng.end());
    int m = ng.size() - 1;
    for (int j = 0; j < (1 << K); j++)
        for (int i = 1; i <= K; i++)
            if (j & (1 << i - 1))
                sum[j] += ned[i];
    for (int l = 0; l <= m + 1; l++)
        for (int r = 0; r <= m + 1; r++)
            for (int j = 0; j < (1 << K); j++)
                f[l][r][j] = (j == 0 ? 0 : 1e9);
    for (int i = 1; i <= m; i++)
    {
        for (int l = 1; l + i - 1 <= m; l++)
        {
            int r = l + i - 1;
            for (int j = 0; j < (1 << K); j++)
            {
                f[l][r][j] = min(f[l + 1][r][j], f[l][r - 1][j]);
                if (sum[j] > i)
                    continue;
                if (sum[j] == i)
                {
                    for (int x = 1; x <= K; x++)
                        if (j & (1 << x - 1))
                        {
                            if (ned[x] == 1 && i == 1)
                                f[l][r][j] = min(f[l][r][j], abs(L[x] -ng[l]) + abs(R[x] - ng[l]));
                            else if (ned[x] > 1)
                                f[l][r][j] = min(f[l][r][j], f[l + 1][r - 1][j ^ (1 << x - 1)] + abs(L[x] - ng[l]) + abs(R[x] - ng[r]) + ng[r] - ng[l]);
                        }
                }
                for (int s = (j - 1) & j; s; s = (s - 1) & j)
                    f[l][r][j] = min(f[l][r][j], f[l][l + sum[s] - 1][s] + f[l + sum[s]][r][j ^ s]);
            }
        }
    }
    ans += f[1][m][(1 << K) - 1];
    ans >>= 1;
    ans -= 2e6;
    printf("%d\n", ans);
    return 0;
}