// https://acm.hdu.edu.cn/showproblem.php?pid=2602
#include <bits/stdc++.h>
#define ONLINE_JUDGE
#define rep(i, j, k) for (int i = j; i <= k; ++i)
typedef long long ll;
typedef unsigned long long ull;
int v[1005], w[1005];
int dp[1005][1005];
bool path[1005][1005];
void clear()
{
    memset(dp, 0, sizeof(dp));
}
void solve()
{
    clear();
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &v[i]);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &w[i]);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j] = dp[i - 1][j];
            path[i][j] = 0;
            if (j >= w[i] && dp[i][j] < dp[i - 1][j - w[i]] + v[i]) {
                dp[i][j] = dp[i - 1][j - w[i]] + v[i];
                path[i][j] = 1;
            }
        }
    }
    printf("%d\n", dp[n][m]);
    // 输出01背包方案
    for (int i = n, j = m; i && j; --i) {
        if (path[i][j]) {
            printf("%d ", i);
            j -= w[i];
        }
    }
    printf("\n");
}
void IOS()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
}
int main()
{
    int t = 1;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}