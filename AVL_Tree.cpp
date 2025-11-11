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
int hei[N];
int ls[N];
int rs[N];
int cnt[N];
int siz[N];
void upd(int x)
{
    siz[x] = siz[ls[x]] + siz[rs[x]] + cnt[x];
    hei[x] = max(hei[ls[x]], hei[rs[x]]) + 1;
}
int lrot(int x)
{
    int r = rs[x];
    rs[x] = ls[r];
    ls[r] = x;
    upd(x);
    upd(r);
    return r;
}
int rrot(int x)
{
    int l = ls[x];
    ls[x] = rs[l];
    rs[l] = x;
    upd(x);
    upd(l);
    return l;
}
int maintain(int x)
{
    int l = ls[x];
    int r = rs[x];
    int lh = hei[l];
    int rh = hei[r];
    if (lh - rh > 1)
    {
        if (hei[ls[l]] >= hei[rs[l]])
        {
            x = rrot(x);
        }
        else
        {
            ls[x] = lrot(l);
            x = rrot(x);
        }
    }
    else if (rh - lh > 1)
    {
        if (hei[rs[r]] >= hei[ls[r]])
        {
            x = lrot(x);
        }
        else
        {
            rs[x] = rrot(r);
            x = lrot(x);
        }
    }
    return x;
}
int add(int p, int x)
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
        rs[p] = add(rs[p], x);
    }
    else
    {
        ls[p] = add(ls[p], x);
    }
    upd(p);
    return maintain(p);
}
int del_mostlst(int p, int x)
{
    if (p == x)
    {
        return rs[p];
    }
    else
    {
        ls[p] = del_mostlst(ls[p], x);
    }
    upd(p);
    return maintain(p);
}
int del(int p, int x)
{
    if (!p)
    {
        return 0;
    }
    else if (key[p] == x)
    {
        if (cnt[p] > 1)
        {
            --cnt[p];
        }
        else
        {
            if (!ls[p] && !rs[p])
            {
                return 0;
            }
            else if (!ls[p] && rs[p])
            {
                p = rs[p];
            }
            else if (ls[p] && !rs[p])
            {
                p = ls[p];
            }
            else
            {
                int rl = rs[p];
                while (ls[rl])
                    rl = ls[rl];
                rs[rl] = del_mostlst(rs[p], rl);
                ls[rl] = ls[p];
                p = rl;
            }
        }
    }
    else if (key[p] < x)
    {
        rs[p] = del(rs[p], x);
    }
    else
    {
        ls[p] = del(ls[p], x);
    }
    upd(p);
    return maintain(p);
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
    if (!p)
        return INT_MIN;
    else if (key[p] >= x)
        return get_pre(ls[p], x);
    else
        return max(key[p], get_pre(rs[p], x));
}
int get_post(int p, int x)
{
    if (!p)
        return INT_MAX;
    else if (key[p] <= x)
        return get_post(rs[p], x);
    else
        return min(key[p], get_post(ls[p], x));
}
inline void solve()
{
    tn = 0;
    root = 0;
    clr(key, 0);
    clr(hei, 0);
    clr(ls, 0);
    clr(rs, 0);
    clr(cnt, 0);
    clr(siz, 0);
    int m;
    scanf("%d", &m);
    int op, x;
    while (m--)
    {
        scanf("%d%d", &op, &x);
        if (op == 1)
        {
            root = add(root, x);
        }
        else if (op == 2)
        {
            root = del(root, x);
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