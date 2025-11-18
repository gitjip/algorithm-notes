#include <bits/stdc++.h>
using namespace std;
// 图的邻接表
vector<vector<int>> g;
// 存储割边
vector<pair<int, int>> e;
vector<int> dfn, low;
int tot;
// tarjan算法求割边(桥)
void tarjan(int u, int fa)
{
    dfn[u] = low[u] = tot++;
    // 是否访问过连向父亲的边
    bool fa_edge = false;
    for (auto v : g[u])
    {
        if (dfn[v] == -1)
        {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u])
            // 发现割边
                e.push_back({min(u, v), max(u, v)});
        }
        // 若目标节点不是父亲或访问到连向父亲的重边
        else if (v != fa || fa_edge)
            low[u] = min(low[u], dfn[v]);
        else
            fa_edge = true;
    }
}