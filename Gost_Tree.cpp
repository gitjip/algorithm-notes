// https://www.luogu.com.cn/problem/P3369
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
#define IOS                  \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0)
#define rep(i, j, k) for (int i = j; i <= k; ++i)
#define rrep(i, j, k) for (int i = j; i >= k; --i)
#define clr(a, b) memset(a, b, sizeof(a))
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const double EPS = 1e-8;
const int N = 1e5 + 5;
const double ALPHA = 0.7;
int tn;
int root;
int key[N];
int ls[N];
int rs[N];
int cnt[N];
int dif[N];
int siz[N];
int in[N];
int inn;
int top;
int father;
bool isbal(int p)
{
    return max(dif[ls[p]], dif[rs[p]]) <= dif[p] * ALPHA;
}
void upd(int x)
{
    siz[x] = siz[ls[x]] + siz[rs[x]] + cnt[x];
    dif[x] = dif[ls[x]] + dif[rs[x]] + (cnt[x] ? 1 : 0);
}
void inorder(int p)
{
    if (!p)
        return;
    inorder(ls[p]);
    if (cnt[p])
        in[++inn] = p;
    inorder(rs[p]);
}
int build(int l, int r)
{
    if (l > r)
        return 0;
    int mid = l + r >> 1;
    ls[in[mid]] = build(l, mid - 1);
    rs[in[mid]] = build(mid + 1, r);
    upd(in[mid]);
    return in[mid];
}
void rebuild()
{
    if (top)
    {
        inn = 0;
        inorder(top);
        if (!father)
            root = build(1, inn);
        else if (ls[father] == top)
            ls[father] = build(1, inn);
        else
            rs[father] = build(1, inn);
    }
    top = 0;
    father = 0;
}
int add(int p, int x, int f)
{
    if (!p)
    {
        p = ++tn;
        key[tn] = x;
        cnt[tn] = 1;
    }
    else if (key[p] == x)
    {
        ++cnt[p];
    }
    else if (key[p] < x)
    {
        rs[p] = add(rs[p], x, p);
    }
    else
    {
        ls[p] = add(ls[p], x, p);
    }
    upd(p);
    if (!isbal(p))
    {
        top = p;
        father = f;
    }
    return p;
}
int del(int p, int x, int f)
{
    if (!p)
    {
        return 0;
    }
    else if (key[p] == x)
    {
        if (cnt[p] > 0)
            --cnt[p];
    }
    else if (key[p] < x)
    {
        rs[p] = del(rs[p], x, p);
    }
    else
    {
        ls[p] = del(ls[p], x, p);
    }
    upd(p);
    if (!isbal(p))
    {
        top = p;
        father = f;
    }
    return p;
}
int get_rank(int p, int x)
{
    if (!p)
        return 1;
    else if (key[p] >= x)
        return get_rank(ls[p], x);
    else
        return siz[ls[p]] + cnt[p] + get_rank(rs[p], x);
}
int get_key(int p, int x)
{
    if (siz[ls[p]] >= x)
        return get_key(ls[p], x);
    else if (siz[ls[p]] + cnt[p] < x)
        return get_key(rs[p], x - siz[ls[p]] - cnt[p]);
    else
        return key[p];
}
int get_pre(int p, int x)
{
    return get_key(root, get_rank(root, x) - 1);
}
int get_post(int p, int x)
{
    return get_key(root, get_rank(root, x + 1));
}
inline void solve()
{
    tn = 0;
    root = 0;
    clr(key, 0);
    clr(ls, 0);
    clr(rs, 0);
    clr(cnt, 0);
    clr(dif, 0);
    clr(siz, 0);
    clr(in, 0);
    inn = 0;
    top = 0;
    father = 0;
    int m;
    scanf("%d", &m);
    int op, x;
    while (m--)
    {
        scanf("%d%d", &op, &x);
        if (op == 1)
        {
            root = add(root, x, 0);
            rebuild();
        }
        else if (op == 2)
        {
            root = del(root, x, 0);
            rebuild();
        }
        else if (op == 3)
        {
            printf("%d\n", get_rank(root, x));
        }
        else if (op == 4)
        {
            printf("%d\n", get_key(root, x));
        }
        else if (op == 5)
        {
            printf("%d\n", get_pre(root, x));
        }
        else
        {
            printf("%d\n", get_post(root, x));
        }
    }
}
inline void init()
{
}
int main()
{
    IOS;
    init();
    int t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}