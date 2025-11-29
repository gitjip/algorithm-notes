#include <bits/stdc++.h>
using namespace std;
const int DEP = 17;
vector<tuple<int, int, int>> e;
vector<int> pre;
vector<vector<pair<int, int>>> g;
vector<vector<int>> f;
vector<vector<int>> st;
vector<int> dep;
vector<bool> vis, sel;
bool cmp(tuple<int, int, int> a, tuple<int, int, int> b)
{
    return get<2>(a) < get<2>(b);
}
void dsu_init(int n)
{
    pre.resize(n);
    for (int i = 0; i < n; i++)
        pre[i] = i;
}
int dsu_find(int u)
{
    return pre[u] = pre[u] == u ? u : dsu_find(pre[u]);
}
void build(int u, int fa)
{
    vis[u] = true;
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    for (int i = 1; i < DEP; i++)
    {
        f[u][i] = f[f[u][i - 1]][i - 1];
        st[u][i] = max(st[u][i - 1], st[f[u][i - 1]][i - 1]);
    }
    for (auto [v, w] : g[u])
        if (v != fa)
        {
            st[v][0] = w;
            build(v, u);
        }
}
/**
 * @brief 求两点路径中最大权值(但小于上界), 采用倍增
 * @param u, v 两点
 * @param w 权值上界
 */
int get_ans(int u, int v, int w)
{
    if (dep[u] < dep[v])
        swap(u, v);
    int ans = -1e9;
    for (int i = DEP - 1; i >= 0; i--)
        if (dep[f[u][i]] >= dep[v])
        {
            if (st[u][i] < w)
                ans = max(ans, st[u][i]);
            u = f[u][i];
        }
    if (u == v)
        return ans;
    for (int i = DEP - 1; i >= 0; i--)
        if (f[u][i] != f[v][i])
        {
            if (st[u][i] < w)
                ans = max(ans, st[u][i]);
            if (st[v][i] < w)
                ans = max(ans, st[v][i]);
            u = f[u][i];
            v = f[v][i];
        }
    if (st[u][0] < w)
        ans = max(ans, st[u][0]);
    if (st[v][0] < w)
        ans = max(ans, st[v][0]);
    return ans;
}
/**
 * @brief 测试链接: https://www.luogu.com.cn/problem/P4180
 */
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    n++;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        e.push_back({u, v, w});
    }
    sort(e.begin(), e.end(), cmp);
    dsu_init(n);
    g.resize(n);
    f.resize(n, vector<int>(DEP));
    st.resize(n, vector<int>(DEP));
    dep.resize(n);
    vis.resize(n);
    sel.resize(m);
    long long sum = 0;
    for (int i = 0; i < m; i++)
    {
        auto [u, v, w] = e[i];
        int fu = dsu_find(u);
        int fv = dsu_find(v);
        if (fu == fv)
            continue;
        pre[fu] = fv;
        sum += w;
        sel[i] = true;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    for (int i = 1; i < n; i++)
        if (!vis[i])
            build(i, 0);
    int diff = 1e9;
    for (int i = 0; i < m; i++)
    {
        if (sel[i])
            continue;
        auto [u, v, w] = e[i];
        int td = w - get_ans(u, v, w);
        if (td > 0)
            diff = min(diff, td);
    }
    cout << sum + diff << "\n";
    return 0;
}