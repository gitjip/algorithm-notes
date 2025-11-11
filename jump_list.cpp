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
const int maxn = 1e5, N = maxn + 5;
const int maxl = 20, L = maxl + 5;
int tn;
int key[N];
int hei[N];
int cnt[N];
int nex[N][L];
int len[N][L];
mt19937 rd(random_device{}());
int rdhei()
{
    int ans = 1;
    while (ans <= maxl && rd() % 2 == 0)
    {
        ++ans;
    }
    return ans;
}
int fnd(int i, int h, int x)
{
    while (nex[i][h] && key[nex[i][h]] < x)
    {
        i = nex[i][h];
    }
    if (h == 1)
    {
        if (nex[i][h] && key[nex[i][h]] == x)
        {
            return nex[i][h];
        }
        else
        {
            return 0;
        }
    }
    return fnd(i, h - 1, x);
}
void add_cnt(int i, int h, int x)
{
    while (nex[i][h] && key[nex[i][h]] < x)
    {
        i = nex[i][h];
    }
    if (h == 1)
    {
        ++cnt[nex[i][h]];
    }
    else
    {
        add_cnt(i, h - 1, x);
    }
    ++len[i][h];
}
int add_node(int i, int h, int j)
{
    int rcnt = 0;
    while (nex[i][h] && key[nex[i][h]] < key[j])
    {
        rcnt += len[i][h];
        i = nex[i][h];
    }
    if (h == 1)
    {
        nex[j][h] = nex[i][h];
        nex[i][h] = j;
        len[j][h] = cnt[nex[j][h]];
        len[i][h] = 1;
        return rcnt;
    }
    else
    {
        int dcnt = add_node(i, h - 1, j);
        if (h > hei[j])
        {
            ++len[i][h];
        }
        else
        {
            nex[j][h] = nex[i][h];
            nex[i][h] = j;
            len[j][h] = len[i][h] + 1 - dcnt - cnt[j];
            len[i][h] = dcnt + cnt[j];
        }
        return rcnt + dcnt;
    }
}
void add(int x)
{
    if (fnd(1, maxl, x))
    {
        add_cnt(1, maxl, x);
    }
    else
    {
        key[++tn] = x;
        cnt[tn] = 1;
        hei[tn] = rdhei();
        add_node(1, maxl, tn);
    }
}
void del_cnt(int i, int h, int x)
{
    while (nex[i][h] && key[nex[i][h]] < x)
    {
        i = nex[i][h];
    }
    if (h == 1)
    {
        --cnt[nex[i][h]];
    }
    else
    {
        del_cnt(i, h - 1, x);
    }
    --len[i][h];
}
void del_node(int i, int h, int j)
{
    if (h < 1)
    {
        return;
    }
    while (nex[i][h] && key[nex[i][h]] < key[j])
    {
        i = nex[i][h];
    }
    if (h > hei[j])
    {
        --len[i][h];
    }
    else
    {
        nex[i][h] = nex[j][h];
        len[i][h] += len[j][h] - 1;
    }
    del_node(i, h - 1, j);
}
void del(int x)
{
    int j = fnd(1, maxl, x);
    if (j)
    {
        if (cnt[j] > 1)
        {
            del_cnt(1, maxl, x);
        }
        else
        {
            del_node(1, maxl, j);
        }
    }
}
int get_rank(int i, int h, int x)
{
    int rcnt = 0;
    while (nex[i][h] && key[nex[i][h]] < x)
    {
        rcnt += len[i][h];
        i = nex[i][h];
    }
    if (h == 1)
    {
        return rcnt + 1;
    }
    else
    {
        return rcnt + get_rank(i, h - 1, x);
    }
}
int get_key(int i, int h, int x)
{
    int c = 0;
    while (nex[i][h] && c + len[i][h] < x)
    {
        c += len[i][h];
        i = nex[i][h];
    }
    if (h == 1)
    {
        return key[nex[i][h]];
    }
    else
    {
        return get_key(i, h - 1, x - c);
    }
}
int get_pre(int i, int h, int x)
{
    while (nex[i][h] && key[nex[i][h]] < x)
    {
        i = nex[i][h];
    }
    if (h == 1)
    {
        return i == 1 ? INT_MIN : key[i];
    }
    else
    {
        return get_pre(i, h - 1, x);
    }
}
int get_post(int i, int h, int x)
{
    while (nex[i][h] && key[nex[i][h]] < x)
    {
        i = nex[i][h];
    }
    if (h == 1)
    {
        if (!nex[i][h])
        {
            return INT_MAX;
        }
        if (key[nex[i][h]] > x)
        {
            return key[nex[i][h]];
        }
        i = nex[i][h];
        if (!nex[i][h])
        {
            return INT_MAX;
        }
        else
        {
            return key[nex[i][h]];
        }
    }
    else
    {
        return get_post(i, h - 1, x);
    }
}
inline void solve()
{
    clr(key, 0);
    clr(hei, 0);
    clr(cnt, 0);
    clr(nex, 0);
    clr(len, 0);
    tn = 1;
    key[1] = INT_MIN;
    hei[1] = maxl;
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
            printf("%d\n", get_rank(1, maxl, x));
        }
        else if (op == 4)
        {
            printf("%d\n", get_key(1, maxl, x));
        }
        else if (op == 5)
        {
            printf("%d\n", get_pre(1, maxl, x));
        }
        else
        {
            printf("%d\n", get_post(1, maxl, x));
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