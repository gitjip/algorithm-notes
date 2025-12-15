#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<ll> tr, tg;
void up(int u)
{
    int ls = u * 2 + 1;
    int rs = u * 2 + 2;
    tr[u] = tr[ls] + tr[rs];
}
void down(int l, int r, int u)
{
    if (!tg[u])
        return;
    int mid = (l + r) / 2;
    int ls = u * 2 + 1;
    int rs = u * 2 + 2;
    tr[ls] += tg[u] * (mid - l);
    tr[rs] += tg[u] * (r - mid);
    tg[ls] += tg[u];
    tg[rs] += tg[u];
    tg[u] = 0;
}
void upd(int L, int R, ll x, int l, int r, int u)
{
    if (R <= l || r <= L)
        return;
    if (L <= l && r <= R)
    {
        tr[u] += x * (r - l);
        tg[u] += x;
        return;
    }
    down(l, r, u);
    int mid = (l + r) / 2;
    upd(L, R, x, l, mid, u * 2 + 1);
    upd(L, R, x, mid, r, u * 2 + 2);
    up(u);
}
ll qry(int L, int R, int l, int r, int u)
{
    if (R <= l || r <= L)
        return 0;
    if (L <= l && r <= R)
        return tr[u];
    down(l, r, u);
    int mid = (l + r) / 2;
    ll ans = 0;
    ans += qry(L, R, l, mid, u * 2 + 1);
    ans += qry(L, R, mid, r, u * 2 + 2);
    return ans;
}
/**
 * @brief 链接: https://www.luogu.com.cn/problem/P3372
 */
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    tr.resize(n * 4);
    tg.resize(n * 4);
    for (int i = 0; i < n; i++)
    {
        ll x;
        cin >> x;
        upd(i, i + 1, x, 0, n, 0);
    }
    for (int i = 0; i < m; i++)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            l--;
            upd(l, r, x, 0, n, 0);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            l--;
            cout << qry(l, r, 0, n, 0) << "\n";
        }
    }
    return 0;
}