#include <bits/stdc++.h>
using namespace std;
vector<vector<pair<int,int>>> g; // 图的邻接表
vector<int> vis, // 是否访问，非必需
            son, // 深儿子，深度最大的点在以它为根的子树中
            dis; // 深度
/// @brief 求以 u 为根的树的最大深度
/// @param u 树根
/// @param f 父亲
/// @return 深度最大的点
int dfs(int u, int f)
{
    int ans = u;
    vis[u] = true;
    son[u] = 0;
    for (auto [v, w] : g[u])
    {
        if (v == f)
            continue;
        if (!vis[v])
        {
            dis[v] = dis[u] + w;
            int b = dfs(v, u);
            if (dis[ans] < dis[b])
            {
                son[u] = v;
                ans = b;
            }
        }
    }
    return ans;
}