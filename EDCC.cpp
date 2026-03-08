#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> g, edccs;
vector<int> dfn, low;
vector<bool> instk;
stack<int> stk;
int tot;
// tarjan算法求边双连通分量(eDCCs)
void tarjan(int u, int fa)
{
    dfn[u] = low[u] = tot++;
    stk.push(u);
    instk[u] = true;
    // 是否访问到反边
    bool fa_edge = false;
    for (auto v : g[u])
    {
        if (dfn[v] == -1)
        {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            // 找到割边
            // if (low[v] > dfn[v]);
        }
        else if (instk[v] && (v != fa || fa_edge))
            low[u] = min(low[u], dfn[v]);
        else
            fa_edge = true;
    }
    if (dfn[u] != low[u])
        return;
    edccs.push_back({});
    int v;
    do
    {
        v = stk.top();
        stk.pop();
        edccs
            .back()
            .push_back(v);
        instk[v] = false;
    } while (v != u);
}
/**
 * @brief 使用示例
 * 
 * @note 测试链接: https://www.luogu.com.cn/problem/P8436
 */
int main()
{
    int n, m;
    cin >> n >> m;
    g.resize(n);
    dfn.resize(n, -1);
    low.resize(n, -1);
    instk.resize(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < n; ++i)
        if (dfn[i] == -1)
            tarjan(i, -1);
    cout << edccs.size() << "\n";
    for (auto &edcc : edccs)
    {
        cout << edcc.size() << " ";
        for (auto u : edcc)
            cout << u + 1 << " ";
        cout << "\n";
    }
    return 0;
}