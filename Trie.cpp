// https://www.luogu.com.cn/problem/P8306
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define rep(i, j, k) for (int i = (j); i <= (k); ++i)
#define rrep(i, j, k) for (int i = (j); i >= (k); --i)
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int N = 3e6 + 5;
int tot;
int nex[N][63];
int cnt[N], chi[128];
void insert(const string &s)
{
    int p = 1;
    cnt[p]++;
    for (char c : s)
    {
        if (!nex[p][chi[c]])
        {
            nex[p][chi[c]] = ++tot;
            memset(nex[tot], 0, sizeof(nex[tot]));
            cnt[tot] = 0;
        }
        p = nex[p][chi[c]];
        cnt[p]++;
    }
}
int query(const string &s)
{
    int p = 1;
    for (char c : s)
    {
        if (!nex[p][chi[c]])
        {
            return 0;
        }
        p = nex[p][chi[c]];
    }
    return cnt[p];
}
void solve()
{
    tot = 1;
    memset(nex[1], 0, sizeof(nex[1]));
    cnt[1] = 0;
    int n, q;
    cin >> n >> q;
    string s;
    rep(i, 1, n)
    {
        cin >> s;
        insert(s);
    }
    rep(i, 1, q)
    {
        cin >> s;
        cout << query(s) << "\n";
    }
}
void init()
{
    rep(i, 1, 26) chi[i - 1 + 'a'] = i;
    rep(i, 27, 52) chi[i - 27 + 'A'] = i;
    rep(i, 53, 62) chi[i - 53 + '0'] = i;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    init();
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}