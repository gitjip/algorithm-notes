#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> g;
vector<int> c, fa, sz, son, ans, cnt;
int cur;
/**
 * @brief 树链剖分
 * 
 * @param u 根节点
 * @param f 父亲
 */
void build(int u, int f)
{
    fa[u] = f;
    sz[u] = 1;
    for (int v : g[u])
    {
        if (v == f)
            continue;
        build(v, u);
        sz[u] += sz[v];
        // 求重儿子
        if (son[u] == -1 || sz[son[u]] < sz[v])
            son[u] = v;
    }
}
/**
 * @brief 添加信息
 * 
 * @param u 根节点
 */
void add(int u)
{
    // 更新种类数
    if (cnt[c[u]]++ == 0)
        cur++;
    for (int v : g[u])
    {
        if (v == fa[u])
            continue;
        add(v);
    }
}
/**
 * @brief 删除信息
 * 
 * @param u 根节点
 */
void del(int u)
{
    // 更新种类数
    if (cnt[c[u]]-- == 1)
        cur--;
    for (int v : g[u])
    {
        if (v == fa[u])
            continue;
        del(v);
    }
}
/**
 * @brief 求答案
 * 
 * @param u 起始根节点
 * @param keep 是否保留cnt中的信息
 */
void setans(int u, bool keep)
{
    // 先对轻儿子求答案, 不保留信息, 互不干扰
    for (int v : g[u])
    {
        if (v == fa[u] || v == son[u])
            continue;
        setans(v, 0);
    }
    // 对重儿子求答案
    if (son[u] != -1)
        setans(son[u], 1);
    // 对自己求答案
    if (cnt[c[u]]++ == 0)
        cur++;
    // 再次对轻儿子求答案, 保留信息, 即合并
    for (int v : g[u])
    {
        if (v == fa[u] || v == son[u])
            continue;
        add(v);
    }
    // 最终答案
    ans[u] = cur;
    // 响应keep命令
    if (!keep)
        del(u);
}
/**
 * @brief 使用示例
 * 
 * @note 测试链接: https://www.luogu.com.cn/problem/U41492
 */
int main()
{
    int n;
    cin >> n;
    g.resize(n);
    c.resize(n);
    fa.resize(n, -1);
    sz.resize(n);
    son.resize(n, -1);
    ans.resize(n);
    cnt.resize(1e5);
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < n; ++i)
    {
        cin >> c[i];
        c[i]--;
    }
    build(0, -1);
    setans(0, 0);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int u;
        cin >> u;
        --u;
        cout << ans[u] << "\n";
    }
    return 0;
}