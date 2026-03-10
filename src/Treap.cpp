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
int prior[N];
int ls[N];
int rs[N];
int cnt[N];
int siz[N];
mt19937 rd(random_device{}());
void upd(int p)
{
    siz[p] = siz[ls[p]] + siz[rs[p]] + cnt[p];
}
int lrot(int p)
{
    int r = rs[p];
    rs[p] = ls[r];
    ls[r] = p;
    upd(p);
    upd(r);
    return r;
}
int rrot(int p)
{
    int l = ls[p];
    ls[p] = rs[l];
    rs[l] = p;
    upd(p);
    upd(l);
    return l;
}
int add(int p, int x, int pr)
{
    if (!p)
    {
        key[++tn] = x;
        prior[tn] = pr;
        cnt[tn] = 1;
        siz[tn] = 1;
        return tn;
    }
    if (x == key[p])
    {
        ++cnt[p];
    }
    else if (x < key[p])
    {
        ls[p] = add(ls[p], x, pr);
        if (prior[ls[p]] > prior[p])
        {
            p = rrot(p);
        }
    }
    else
    {
        rs[p] = add(rs[p], x, pr);
        if (prior[rs[p]] > prior[p])
        {
            p = lrot(p);
        }
    }
    upd(p);
    return p;
}
int del(int p, int x)
{
    if (!p)
        return 0;
    if (x == key[p])
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
                return rs[p];
            }
            else if (ls[p] && !rs[p])
            {
                return ls[p];
            }
            else
            {
                if (prior[ls[p]] > prior[rs[p]])
                {
                    p = rrot(p);
                    rs[p] = del(rs[p], x);
                }
                else
                {
                    p = lrot(p);
                    ls[p] = del(ls[p], x);
                }
            }
        }
    }
    else if (x < key[p])
    {
        ls[p] = del(ls[p], x);
    }
    else
    {
        rs[p] = del(rs[p], x);
    }
    upd(p);
    return p;
}
int get_rank(int p, int x)
{
    if (!p)
        return 1;
    if (key[p] >= x)
        return get_rank(ls[p], x);
    if (key[p] < x)
        return siz[ls[p]] + cnt[p] + get_rank(rs[p], x);
}
int get_key(int p, int x)
{
    if (siz[ls[p]] >= x)
        return get_key(ls[p], x);
    if (siz[ls[p]] + cnt[p] < x)
        return get_key(rs[p], x - siz[ls[p]] - cnt[p]);
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
    clr(prior, 0);
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
            root = add(root, x, rd());
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