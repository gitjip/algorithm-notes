#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<int> num(19);
vector<vector<vector<ll>>> dp;
/**
 * @brief 记忆化搜索
 * @param n 当前位置
 * @param la 上一个数
 * @param st 是否已经遇到非零
 * @param lim 是否受到约束
 */
ll dfs(int n, int la, bool st, bool lim)
{
    if (n < 0)
    // 返回 1 也可以
        return st;
    // 返回未约束且已记录的值
    if (!lim && dp[n][la][st] != -1)
        return dp[n][la][st];
    ll res = 0;
    // 选上界
    int up = lim ? num[n] : 9;
    for (int i = 0; i <= up; i++)
        // 满足题中条件
        if (!st || abs(i - la) >= 2)
            res += dfs(n - 1, i, st || i, lim && i == up);
    // 只记录未约束的值
    if (!lim)
        dp[n][la][st] = res;
    return res;
}
/**
 * @brief 返回小等于x且满足题意的数的个数
 * @param x 上界
 */
ll f(ll x)
{
    dp.clear();
    dp.resize(20, vector<vector<ll>>(10, vector<ll>(2, -1)));
    for (int i = 0; i < 19; i++)
    {
        num[i] = x % 10;
        x /= 10;
    }
    ll res = dfs(18, 0, false, true);
    return res;
}
/**
 * @brief 示例
 * @note 链接: https://www.luogu.com.cn/problem/P13085
 */
int main()
{
    ll a, b;
    cin >> a >> b;
    ll f2 = f(b);
    ll f1 = f(a - 1);
    cout << f2 - f1 << "\n";
    return 0;
}