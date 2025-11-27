#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long h;
    int x, y, z;
    cin >> h >> x >> y >> z;
    vector<vector<pair<int, int>>> g(x);
    for (int i = 0; i < x; i++)
    {
        g[i].push_back({(i + y) % x, y});
        g[i].push_back({(i + z) % x, z});
    }
    vector<long long> dis(x, h);
    dis[0] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> q;
    q.push({dis[0], 0});
    while (q.size())
    {
        auto [d, u] = q.top();
        q.pop();
        for (auto [v, w] : g[u])
        {
            if (dis[v] > d + w)
            {
                dis[v] = d + w;
                q.push({dis[v], v});
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < x; i++)
        if (h - 1 >= dis[i])
            ans += (h - 1 - dis[i]) / x + 1;
    cout << ans << "\n";
    return 0;
}