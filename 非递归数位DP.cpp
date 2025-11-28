#include <bits/stdc++.h>
using namespace std;
using ll = long long;
/**
 * @brief 非递归数位DP
 * @param num 上界
 * @return 满足题意的数的个数
 */
ll f(ll num)
{
    vector<int> arr(19);
    for (int i = 0; i < 19; i++)
    {
        arr[i] = num % 10;
        num /= 10;
    }
    // dp[位置][末尾的数][是否遇到非零][是否限制]
    ll dp[20][10][2][2]{};
    dp[19][0][0][1] = 1;
    for (int p = 18; p >= 0; p--)
        for (int x = 0; x < 10; x++)
            for (int s = 0; s < 2; s++)
                for (int l = 0; l < 2; l++)
                {
                    int up = l ? arr[p] : 9;
                    for (int y = 0; y <= up; y++)
                    {
                        if (!s || abs(y - x) >= 2)
                            dp[p][y][s || y][l && y == up] += dp[p + 1][x][s][l];
                    }
                }
    ll ans = 0;
    for (int x = 0; x < 10; x++)
        for (int s = 0; s < 2; s++)
            for (int l = 0; l < 2; l++)
                ans += dp[0][x][s][l];
    return ans;
}
/**
 * @brief 使用示例
 * @note 测试链接: https://www.luogu.com.cn/problem/P13085
 */
int main()
{
    ll a, b;
    cin >> a >> b;
    ll ans1 = f(a - 1);
    ll ans2 = f(b);
    cout << ans2 - ans1 << "\n";
    return 0;
}