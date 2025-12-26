#include <bits/stdc++.h>
using namespace std;
vector<int> arr,  // 需要保留原始数组并操作
            len,  // 线段树中该点的最长区间
            llen, // 该点的从左端点开始的最长区间
            rlen; // 该点的从右端点开始的最长区间
/// @brief 线段树合并，求满足条件的连续最长区间长度
/// @param l 
/// @param r 
/// @param u 
void up(int l, int r, int u)
{
    int mid = (l + r) / 2;
    int ls = u * 2 + 1;
    int rs = u * 2 + 2;
    len[u] = max(len[ls], len[rs]);
    llen[u] = llen[ls];
    rlen[u] = rlen[rs];
    if (arr[mid - 1] != arr[mid])
    {
        len[u] = max(len[u], rlen[ls] + llen[rs]);
        if (llen[ls] == mid - l)
            llen[u] = mid - l + llen[rs];
        if (rlen[rs] == r - mid)
            rlen[u] = r - mid + rlen[ls];
    }
}
void build(int l, int r, int u)
{
    if (l + 1 == r)
    {
        len[u] = llen[u] = rlen[u] = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, u * 2 + 1);
    build(mid, r, u * 2 + 2);
    up(l, r, u);
}
void upd(int p, int l, int r, int u)
{
    if (r <= p || p < l)
        return;
    if (l + 1 == r)
    {
        arr[p] ^= 1;
        return;
    }
    int mid = (l + r) / 2;
    upd(p, l, mid, u * 2 + 1);
    upd(p, mid, r, u * 2 + 2);
    up(l, r, u);
}
/// @brief 调试，输出线段树每点的值
/// @param l 
/// @param r 
/// @param u 
void out(int l, int r, int u)
{
    cout << l << " " << r - 1 << ":" << len[u] << " " << llen[u] << " " << rlen[u] << "\n";
    if (l + 1 == r)
        return;
    int mid = (l + r) / 2;
    out(l, mid, u * 2 + 1);
    out(mid, r, u * 2 + 2);
}
/// @brief 测试链接：https://www.luogu.com.cn/problem/P6492
/// @return 
int main()
{
    int n, q;
    cin >> n >> q;
    arr.resize(n);
    len.resize(n * 4);
    llen.resize(n * 4);
    rlen.resize(n * 4);
    build(0, n, 0);
    while (q--)
    {
        int x;
        cin >> x;
        x--;
        upd(x, 0, n, 0);
        cout << len[0] << "\n";
        // out(0, n, 0);
    }
    return 0;
}