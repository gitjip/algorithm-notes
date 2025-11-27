#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> g, vdccs;
vector<int> dfn, low;
vector<bool> cut;
stack<int> stk;
int tot, rt;
// 求点双连通分量(vDCC)
void tarjan(int u)
{
    dfn[u] = low[u] = tot++;
    stk.push(u);
    // 特判一个点的vDCC
    if (u == rt && g[u].empty())
    {
        vdccs.push_back({u});
        return;
    }
    int son = 0;
    for (auto v : g[u])
    {
        if (dfn[v] == -1)
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            // 找到vDCC
            if (dfn[u] > low[v])
                continue;
            son++;
            // 找到割点
            if (u != rt || son > 1)
                cut[u] = true;
            vdccs.push_back({});
            int w;
            do
            {
                w = stk.top();
                stk.pop();
                vdccs.back().push_back(w);
            } while (w != v);
            vdccs.back().push_back(u);
        }
        else
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
/**
 * @brief 使用示例
 * 
 * @note 测试链接: https://www.luogu.com.cn/problem/P8435
 */
int main()
{
    int n, m;
    cin >> n >> m;
    g.resize(n);
    dfn.resize(n, -1);
    low.resize(n, -1);
    cut.resize(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        if (u == v)
            continue;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < n; ++i)
        if (dfn[i] == -1)
            tarjan(rt = i);
    cout << vdccs.size() << "\n";
    for (auto &vdcc : vdccs)
    {
        cout << vdcc.size() << " ";
        for (auto u : vdcc)
            cout << u + 1 << " ";
        cout << "\n";
    }
    return 0;
}