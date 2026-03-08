/**
 * 伸展树
 * 节点编号从1开始
 */
#include <bits/stdc++.h>
using namespace std;

vector<int> key, cnt, ls, rs, sz;
int tot = 1;

/**
 * @brief 更新节点大小
 */
void upd(int u)
{
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
 * @brief 单旋操作（用于最后一步调整）
 */
int splay(int u)
{
    if (ls[ls[u]])
    { // 左左情况
        u = rrot(u);
    }
    else if (rs[rs[u]])
    { // 右右情况
        u = lrot(u);
    }
    return u;
}

/**
 * @brief 伸展操作：将包含x的节点旋转到根
 */
int splay(int u, int x)
{
    if (u == 0)
        return 0;

    if (x < key[u])
    {
        if (ls[u] == 0)
            return u;

        if (x < key[ls[u]])
        { // 左左情况
            ls[ls[u]] = splay(ls[ls[u]], x);
            u = rrot(u); // 第一次旋转
            if (ls[u])
                u = rrot(u); // 第二次旋转
        }
        else if (x > key[ls[u]])
        { // 左右情况
            rs[ls[u]] = splay(rs[ls[u]], x);
            if (rs[ls[u]])
                ls[u] = lrot(ls[u]);
        }

        if (ls[u] == 0)
            return u;
        else
            return rrot(u); // 最后一次旋转
    }
    else if (x > key[u])
    {
        if (rs[u] == 0)
            return u;

        if (x > key[rs[u]])
        { // 右右情况
            rs[rs[u]] = splay(rs[rs[u]], x);
            u = lrot(u); // 第一次旋转
            if (rs[u])
                u = lrot(u); // 第二次旋转
        }
        else if (x < key[rs[u]])
        { // 右左情况
            ls[rs[u]] = splay(ls[rs[u]], x);
            if (ls[rs[u]])
                rs[u] = rrot(rs[u]);
        }

        if (rs[u] == 0)
            return u;
        else
            return lrot(u); // 最后一次旋转
    }
    // x == key[u]时，执行最后一次单旋调整
    return splay(u);
}

/**
 * @brief 插入新节点
 */
int insert(int u, int x)
{
    if (u == 0)
    {
        u = tot++;
        key[u] = x;
        cnt[u] = 1;
        sz[u] = 1;
        return u;
    }

    if (x < key[u])
    {
        ls[u] = insert(ls[u], x);
    }
    else if (x > key[u])
    {
        rs[u] = insert(rs[u], x);
    }
    else
    {
        cnt[u]++;
    }

    upd(u);
    return splay(u, x); // 插入后伸展到根
}

/**
 * @brief 查找最小值节点（用于删除操作）
 */
int find_min(int u)
{
    while (ls[u])
        u = ls[u];
    return u;
}

/**
 * @brief 删除节点
 */
int remove(int u, int x)
{
    if (u == 0)
        return 0;

    u = splay(u, x); // 先将待删除节点伸展到根

    if (key[u] != x)
        return u; // 未找到节点

    if (cnt[u] > 1)
    {
        cnt[u]--;
        upd(u);
        return u;
    }

    // 处理子树情况
    int new_root;
    if (ls[u] == 0)
    {
        new_root = rs[u];
    }
    else if (rs[u] == 0)
    {
        new_root = ls[u];
    }
    else
    {
        new_root = find_min(rs[u]);
        rs[new_root] = splay(rs[u], key[new_root]); // 伸展右子树最小值到根
        ls[new_root] = ls[u];
    }

    if (new_root != 0)
        upd(new_root);
    return new_root;
}

/**
 * @brief 获取节点排名(从0开始)
 */
int get_rank(int u, int x)
{
    if (u == 0)
        return 0;
    if (x > key[u])
    {
        return sz[ls[u]] + cnt[u] + get_rank(rs[u], x);
    }
    else
    {
        return get_rank(ls[u], x);
    }
}

/**
 * @brief 获取指定排名的节点键
 */
int get_key(int u, int rk)
{
    if (sz[ls[u]] > rk)
    {
        return get_key(ls[u], rk);
    }
    else if (sz[ls[u]] + cnt[u] <= rk)
    {
        return get_key(rs[u], rk - sz[ls[u]] - cnt[u]);
    }
    else
    {
        return key[u];
    }
}

/**
 * @brief 获取节点前驱
 */
int get_pre(int u, int x)
{
    if (u == 0)
        return -1e9;
    if (key[u] < x)
    {
        return max(key[u], get_pre(rs[u], x));
    }
    else
    {
        return get_pre(ls[u], x);
    }
}

/**
 * @brief 获取节点后继
 */
int get_post(int u, int x)
{
    if (u == 0)
        return 1e9;
    if (key[u] > x)
    {
        return min(key[u], get_post(ls[u], x));
    }
    else
    {
        return get_post(rs[u], x);
    }
}

/**
 * @brief 测试链接: https://www.luogu.com.cn/problem/P3369
 */
int main()
{
    int n;
    cin >> n;
    // 预留足够空间
    key.resize(n + 2);
    cnt.resize(n + 2);
    ls.resize(n + 2);
    rs.resize(n + 2);
    sz.resize(n + 2);

    int root = 0;
    for (int i = 0; i < n; i++)
    {
        int op, x;
        cin >> op >> x;
        if (op == 1)
        {
            root = insert(root, x);
        }
        else if (op == 2)
        {
            root = remove(root, x);
        }
        else if (op == 3)
        {
            // 查询排名前先伸展，确保树结构优化
            if (root != 0)
                root = splay(root, x);
            cout << get_rank(root, x) + 1 << "\n";
        }
        else if (op == 4)
        {
            cout << get_key(root, x - 1) << "\n";
            // 查询后伸展该节点
            if (root != 0)
                root = splay(root, get_key(root, x - 1));
        }
        else if (op == 5)
        {
            int pre = get_pre(root, x);
            cout << pre << "\n";
            // 伸展前驱节点
            if (root != 0 && pre != -1e9)
                root = splay(root, pre);
        }
        else if (op == 6)
        {
            int post = get_post(root, x);
            cout << post << "\n";
            // 伸展后继节点
            if (root != 0 && post != 1e9)
                root = splay(root, post);
        }
    }
    return 0;
}