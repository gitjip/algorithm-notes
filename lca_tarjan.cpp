// https://www.luogu.com.cn/problem/P3379
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define rep(i, j, k) for (int i = (j); i <= (k); ++i)
#define rrep(i, j, k) for (int i = (j); i >= (k); --i)
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
vector<vector<int>> g;
vector<vector<pair<int, int>>> query;
vector<int> vis, ans, pre;
int fin(int u)
{
    return pre[u] = pre[u] == u ? u : fin(pre[u]);
}
void uni(int u, int v)
{
    u = fin(u);
    v = fin(v);
    pre[u] = v;
}
void tarjan(int u)
{
    vis[u] = 1;
    for (auto v : g[u])
    {
        if (!vis[v])
        {
            tarjan(v);
            pre[v] = u;
        }
    }
    for (auto [v, i] : query[u])
    {
        if (vis[v])
        {
            ans[i] = fin(v);
        }
    }
}
void solve()
{
    int n, m, s;
    cin >> n >> m >> s;
    g.resize(n + 1);
    query.resize(n + 1);
    vis.resize(n + 1);
    pre.resize(n + 1);
    ans.resize(n + 1);
    for (int i = 1; i <= n; ++i)
        pre[i] = i;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        cin >> u >> v;
        query[u].push_back({v, i});
        query[v].push_back({u, i});
    }
    tarjan(s);
    for (int i = 1; i <= m; ++i)
        cout << ans[i] << "\n";
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}