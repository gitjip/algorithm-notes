#include <bits/stdc++.h>
using namespace std;
vector<int> pre;
vector<vector<int>> g;
vector<vector<pair<int, int>>> query;
vector<bool> vis;
vector<int> ans;
void dsu_init(int n)
{
    pre.resize(n);
    for (int i = 0; i < n; i++)
        pre[i] = i;
}
int dsu_find(int u)
{
    return pre[u] = pre[u] == u ? u : dsu_find(pre[u]);
}
/**
 * @brief Tarjan求LCA
 * @param u 子树根节点
 */
void tarjan(int u)
{
    vis[u] = true;
    for (int v : g[u])
        if (!vis[v])
        {
            // 先求子树再连边, 隔离环境求最近
            tarjan(v);
            pre[v] = u;
        }
    // 离线查询
    for (auto [v, i] : query[u])
        if (vis[v])
            // 已经访问过的在同一个子树, 可图解
            ans[i] = dsu_find(v);
}
/**
 * @brief 测试链接: https://www.luogu.com.cn/problem/P3379
 */
int main()
{
    int n, m, s;
    cin >> n >> m >> s;
    s--;
    dsu_init(n);
    g.resize(n);
    query.resize(m);
    vis.resize(n);
    ans.resize(m);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        query[u].push_back({v, i});
        query[v].push_back({u, i});
    }
    tarjan(s);
    for (int i = 0; i < m; i++)
        cout << ans[i] + 1 << "\n";
    return 0;
}