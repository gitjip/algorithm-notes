#include <bits/stdc++.h>
using namespace std;
vector<int> pre;
void dsu_init(int n)
{
    pre.resize(n);
    for (int i = 0; i < n; i++)
        pre[i] = i;
}
int dsu_find(int u)
{
    // 路径压缩优化: pre[u] = ...
    return pre[u] = pre[u] == u ? u : dsu_find(pre[u]);
}
void dsu_union(int u, int v)
{
    u = dsu_find(u);
    v = dsu_find(v);
    pre[u] = v;
}