#include <bits/stdc++.h>
using namespace std;
// 邻接表, 强连通分量集合
vector<vector<int>> g, sccs;
vector<int> dfn, low;
// 是否在栈中, 即是否在搜索路径中
vector<bool> instk;
// 路径上的点压栈
stack<int> stk;
// 当前访问时间戳
int tot;
// tarjan算法求强连通分量
void tarjan(int u)
{
    dfn[u] = low[u] = tot++;
    stk.push(u);
    instk[u] = true;
    for (auto v : g[u])
    {
        if (dfn[v] == -1)
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (instk[v])
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] != low[u])
        return;
    // 该点是强连通分量的根
    sccs.push_back({});
    int v;
    do
    {
        v = stk.top();
        stk.pop();
        instk[v] = false;
        sccs.back().push_back(v);
    } while (v != u);
}