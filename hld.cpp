// 树链剖分
#include <bits/stdc++.h>
using namespace std;
struct hld
{
    vector<vector<int>> g;
    vector<int> fa, dep, son, sz, top;
    hld(int n) : g(n), fa(n), dep(n), son(n), sz(n), top(n) {};
    void dfs1(int u, int f)
    {
        fa[u] = f;
        dep[u] = dep[f] + 1;
        sz[u] = 1;
        for (auto v : g[u])
        {
            if (v == f)
                continue;
            dfs1(v, u);
            sz[u] += sz[v];
            if (sz[son[u]] < sz[v])
                son[u] = v;
        }
    }
    void dfs2(int u, int t)
    {
        top[u] = t;
        if (!son[u])
            return;
        dfs2(son[u], t);
        for (auto v : g[u])
        {
            if (v == fa[u] || v == son[u])
                continue;
            dfs2(v, v);
        }
    }
    int lca(int u, int v)
    {
        while (top[u] != top[v])
        {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
};