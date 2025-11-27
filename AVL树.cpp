/**
 * @brief AVL树
 * 
 * @note 节点编号从1开始
 */
#include <bits/stdc++.h>
using namespace std;
vector<int> key, cnt, ls, rs, ht, sz;
int tot = 1;
/**
 * @brief 更新高度和结点数
 */
void upd(int u)
{
    ht[u] = max(ht[ls[u]], ht[rs[u]]) + 1;
    sz[u] = sz[ls[u]] + sz[rs[u]] + cnt[u];
}
/**
 * @brief 左旋
 */
int lrot(int u)
{
    int r = rs[u];
    rs[u] = ls[r];
    ls[r] = u;
    upd(u);
    upd(r);
    return r;
}
/**
 * @brief 右旋
 */
int rrot(int u)
{
    int l = ls[u];
    ls[u] = rs[l];
    rs[l] = u;
    upd(u);
    upd(l);
    return l;
}
/**
 * @brief 根据平衡因子通过旋转调整树高
 */
int balance(int u)
{
    int lh = ht[ls[u]];
    int rh = ht[rs[u]];
    if (lh - rh > 1)
    {
        if (ht[rs[ls[u]]] > ht[ls[ls[u]]])
        {
            ls[u] = lrot(ls[u]);
            return rrot(u);
        }
        return rrot(u);
    }
    if (rh - lh > 1)
    {
        if (ht[ls[rs[u]]] > ht[rs[rs[u]]])
        {
            rs[u] = rrot(rs[u]);
            return lrot(u);
        }
        return lrot(u);
    }
    return u;
}
/**
 * @brief 插入新节点
 * 
 * @param u 起始根节点
 * @param x 节点的键
 */
int insert(int u, int x)
{
    if (u == 0)
    {
        u = tot++;
        key[u] = x;
        cnt[u] = 1;
    }
    else if (key[u] == x)
    {
        cnt[u]++;
    }
    else if (key[u] < x)
        rs[u] = insert(rs[u], x);
    else if (key[u] > x)
        ls[u] = insert(ls[u], x);
    upd(u);
    return balance(u);
}
/**
 * @brief 摘取最右端的节点, 服务于remove函数
 * 
 * @param u 起始根节点
 */
pair<int, int> pick_mostright(int u)
{
    if (rs[u] == 0)
        return {ls[u], u};
    auto [r, v] = pick_mostright(rs[u]);
    rs[u] = r;
    upd(u);
    return {balance(u), v};
}
/**
 * @brief 删除节点
 * 
 * @param x 待删节点的键
 */
int remove(int u, int x)
{
    if (u == 0)
        return 0;
    if (key[u] != x)
    {
        if (key[u] < x)
            rs[u] = remove(rs[u], x);
        else if (key[u] > x)
            ls[u] = remove(ls[u], x);
        upd(u);
        return balance(u);
    }
    if (cnt[u] > 1)
    {
        cnt[u]--;
        upd(u);
        return u;
    }
    if (ls[u] == 0 && rs[u] == 0)
        return 0;
    if (ls[u] == 0)
        return rs[u];
    if (rs[u] == 0)
        return ls[u];
    auto [v, w] = pick_mostright(ls[u]);
    ls[w] = v;
    rs[w] = rs[u];
    upd(w);
    return balance(w);
}
/**
 * @brief 获取节点排名(从0开始)
 * 
 * @param x 节点的键
 */
int get_rank(int u, int x)
{
    if (u == 0)
        return 0;
    if (key[u] < x)
        return sz[ls[u]] + cnt[u] + get_rank(rs[u], x);
    return get_rank(ls[u], x);
}
/**
 * @brief 获取指定排名的节点键
 * 
 * @param rk 节点排名
 */
int get_key(int u, int rk)
{
    if (sz[ls[u]] + cnt[u] <= rk)
        return get_key(rs[u], rk - sz[ls[u]] - cnt[u]);
    if (sz[ls[u]] > rk)
        return get_key(ls[u], rk);
    return key[u];
}
/**
 * @brief 获取节点前驱
 * 
 * @param x 节点的键
 */
int get_pre(int u, int x)
{
    if (u == 0)
        return -1e9;
    if (key[u] < x)
        return max(get_pre(rs[u], x), key[u]);
    return get_pre(ls[u], x);
}
/**
 * @brief 获取节点后继
 * 
 * @param x 节点的键
 */
int get_post(int u, int x)
{
    if (u == 0)
        return 1e9;
    if (key[u] > x)
        return min(get_post(ls[u], x), key[u]);
    return get_post(rs[u], x);
}
/**
 * @brief 使用示例
 * 
 * @note 测试链接: https://www.luogu.com.cn/problem/P3369
 */
int main()
{
    int n;
    cin >> n;
    key.resize(n + 1);
    cnt.resize(n + 1);
    ls.resize(n + 1);
    rs.resize(n + 1);
    ht.resize(n + 1);
    sz.resize(n + 1);
    int root = 0;
    for (int i = 0; i < n; i++)
    {
        int op, x;
        cin >> op >> x;
        if (op == 1)
            root = insert(root, x);
        else if (op == 2)
            root = remove(root, x);
        else if (op == 3)
            cout << get_rank(root, x) + 1 << "\n";
        else if (op == 4)
            cout << get_key(root, x - 1) << "\n";
        else if (op == 5)
            cout << get_pre(root, x) << "\n";
        else
            cout << get_post(root, x) << "\n";
    }
    return 0;
}