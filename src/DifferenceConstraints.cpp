// 与 Bellman-Ford 和 SPFA 的算法完全等价
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, int>> e;
    vector<int> dis(n + 1, 1e9);
    dis[0] = 0;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        e.push_back({v, u, w});
    }
    for (int i = 1; i < n + 1; i++)
        e.push_back({0, i, 0});
    // bellman-ford
    for (int i = 0; i < n; i++)
    {
        for (auto [u, v, w] : e)
        {
            if (dis[v] > dis[u] + w)
                dis[v] = dis[u] + w;
        }
    }
    for (auto [u, v, w] : e)
    {
        if (dis[v] > dis[u] + w)
        {
            // 存在负环，方程无解
            cout << "NO\n";
            return 0;
        }
    }
    // 差分不等式的一个解集
    for (int i = 1; i < n + 1; i++)
        cout << dis[i] << " ";
    cout << "\n";
    return 0;
}