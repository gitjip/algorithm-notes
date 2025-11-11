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
int tn;
int root;
int key[N];
int pri[N];
int ls[N];
int rs[N];
int siz[N];
mt19937 rd(random_device{}());
void upd(int p)
{
    siz[p] = siz[ls[p]] + siz[rs[p]] + 1;
}
void split(int l, int r, int p, int x)
{
    if (!p)
    {
        rs[l] = ls[r] = 0;
        return;
    }
    if (key[p] <= x)
    {
        rs[l] = p;
        split(p, r, rs[p], x);
    }
    else
    {
        ls[r] = p;
        split(l, p, ls[p], x);
    }
    upd(p);
}
int merge(int l, int r)
{
    if (!l)
        return r;
    if (!r)
        return l;
    if (pri[l] >= pri[r])
    {
        rs[l] = merge(rs[l], r);
        upd(l);
        return l;
    }
    else
    {
        ls[r] = merge(l, ls[r]);
        upd(r);
        return r;
    }
}
void add(int x)
{
    split(0, 0, root, x);
    key[++tn] = x;
    siz[tn] = 1;
    pri[tn] = rd();
    root = merge(merge(rs[0], tn), ls[0]);
}
void del(int x)
{
    split(0, 0, root, x);
    int lm = rs[0];
    int r = ls[0];
    split(0, 0, lm, x - 1);
    int l = rs[0];
    int m = ls[0];
    root = merge(merge(l, merge(ls[m], rs[m])), r);
}
int get_rank(int x)
{
    split(0, 0, root, x - 1);
    int res = siz[rs[0]] + 1;
    root = merge(rs[0], ls[0]);
    return res;
}
int get_key(int p, int x)
{
    if (siz[ls[p]] >= x)
        return get_key(ls[p], x);
    if (siz[ls[p]] + 1 < x)
        return get_key(rs[p], x - siz[ls[p]] - 1);
    return key[p];
}
int get_pre(int p, int x)
{
    if (!p)
        return INT_MIN;
    if (key[p] >= x)
        return get_pre(ls[p], x);
    return max(key[p], get_pre(rs[p], x));
}
int get_post(int p, int x)
{
    if (!p)
        return INT_MAX;
    if (key[p] <= x)
        return get_post(rs[p], x);
    return min(key[p], get_post(ls[p], x));
}
inline void solve()
{
    tn = 0;
    root = 0;
    clr(key, 0);
    clr(pri, 0);
    clr(ls, 0);
    clr(rs, 0);
    clr(siz, 0);
    int m;
    scanf("%d", &m);
    int op, x;
    while (m--)
    {
        scanf("%d%d", &op, &x);
        if (op == 1)
        {
            add(x);
        }
        else if (op == 2)
        {
            del(x);
        }
        else if (op == 3)
        {
            printf("%d\n", get_rank(x));
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