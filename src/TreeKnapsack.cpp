// https://www.luogu.com.cn/problem/P1064
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
const int N = 3205;
const int M = 105;
int n, m;
int v[M], p[M], q[M];
vector<int> g[M];
int dp[M][N];
void dfs(int x)
{
    rep(i, v[x], n) dp[x][i] = v[x] * p[x];
    for (auto y : g[x])
    {
        dfs(y);
        rrep(i, n, v[x])
        {
            rep(j, v[x], i)
            {
                dp[x][i] = max(dp[x][i], dp[x][j] + dp[y][i - j]);
            }
        }
    }
}
inline void solve()
{
    scanf("%d%d", &n, &m);
    n /= 10;
    rep(i, 1, m) scanf("%d%d%d", &v[i], &p[i], &q[i]);
    rep(i, 1, m)
    {
        v[i] /= 10;
        g[q[i]].push_back(i);
    }
    dfs(0);
    printf("%d\n", dp[0][n] * 10);
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