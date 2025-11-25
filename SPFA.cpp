#include <bits/stdc++.h>
using namespace std;
/**
 * @brief SPFA求单源最短路
 * 
 * @param g 存储节点编号和长度的图
 * @param dis 最短路
 * @param s 源点编号
 * 
 * @return 是否有负环
 * 
 * @note 要求 g.size() == dis.size()
 */
bool spfa(vector<vector<pair<int, int>>> &g, vector<int> &dis, int s)
{
    int n = g.size();
    // 存储节点编号和松弛次数
    queue<pair<int, int>> q;
    q.push({s, 0});
    while (q.size())
    {
        auto [u, c] = q.front();
        q.pop();
        if (c >= n)
        {
            return false;
        }
        for (auto [v, w] : g[u])
        {
            if (dis[v] < dis[u] + w)
            {
                dis[v] = dis[u] + w;
                q.push({v, c + 1});
            }
        }
    }
    return true;
}