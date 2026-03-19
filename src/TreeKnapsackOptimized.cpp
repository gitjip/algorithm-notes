// https://loj.ac/p/160
#include <bits/stdc++.h>
using namespace std;
const int N = 50003;
const int M = 60003;
int n, m, tot;
int w[N], v[N], s[N], dfn[N], rdfn[N];
vector<vector<int>> g, f;
void dfs(int u)
{
    s[u] = 1;
    for (int v : g[u]) {
        dfs(v);
        s[u] += s[v];
    }
    dfn[u] = ++tot; // 求后序遍历序
    rdfn[tot] = u;
}
/// @brief 树上背包后序遍历优化版，时间复杂度O(nm)
/// @return 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    g.resize(n + 3);
    f.resize(n + 3, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i) {
        int d;
        cin >> d;
        g[d].push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
    }
    dfs(0);
    for (int i = 1; i <= n + 1; ++i) {
        for (int j = 0; j <= m; ++j) {
            f[i][j] = f[i - s[rdfn[i]]][j]; // 不取当前节点，则其子树不能取
            if (j >= w[rdfn[i]]) { // 取当前节点
                f[i][j] = max(f[i][j], f[i - 1][j - w[rdfn[i]]] + v[rdfn[i]]);
            }
        }
    }
    cout << f[n + 1][m] << "\n";
    return 0;
}