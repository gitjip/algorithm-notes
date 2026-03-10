#include <bits/stdc++.h>
using namespace std;
// 图的邻接表
vector<vector<int>> g;
vector<int> dfn, low;
// 是否是割点
vector<bool> cut;
int tot, rt;
// tarjan算法求割点
void tarjan(int u)
{
    dfn[u] = low[u] = tot++;
    int son = 0;
    for (int v : g[u])
    {
        if (dfn[v] == -1)
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            // 邻居要满足下面条件
            if (low[v] >= dfn[u])
            {
                son++;
                // 当节点不是根或满足条件的邻居多于1个
                // 则该节点是割点
                if (u != rt || son > 1)
                    cut[u] = true;
            }
        }
        else
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
}