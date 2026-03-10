#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> g, f;
vector<int> dep;
void build(int u, int fa)
{
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    for (int i = 1; i < 20; i++)
    // 建立多级父子关系, 优化到O(n*logn)
        f[u][i] = f[f[u][i - 1]][i - 1];
    for (int v : g[u])
        if (v != fa)
            build(v, u);
}
int get_lca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    // 先一个跳
    for (int i = 19; i >= 0; --i)
        if (dep[f[u][i]] >= dep[v])
            u = f[u][i];
    if (u == v)
        return u;
    // 再两个跳
    for (int i = 19; i >= 0; --i)
        if (f[u][i] != f[v][i])
        {
            u = f[u][i];
            v = f[v][i];
        }
    return f[u][0];
}
/**
 * @brief 测试链接: https://www.luogu.com.cn/problem/P3379
 */
int main()
{
    // 本题卡常, 故关闭同步流
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s;
    cin >> n >> m >> s;
    n++;
    g.resize(n);
    f.resize(n, vector<int>(20));
    dep.resize(n);
    for (int i = 0; i < n - 2; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    build(s, 0);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        cout << get_lca(u, v) << "\n";
    }
    return 0;
}