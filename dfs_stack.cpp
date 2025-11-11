#include <bits/stdc++.h>
using namespace std;
#define rep(i, j, k) for (int i = j; i <= k; ++i)
const int N = 1e5 + 5;
vector<int> g[N];
stack<int> st;
bool vis[N];
void dfs(int p)
{
    st.push(p);
    while (st.size())
    {
        int x = st.top();
        st.pop();
        if (!vis[x])
            printf("%d ", x);
        vis[x] = 1;
        for (auto y : g[x])
        {
            if (!vis[y])
                st.push(y);
        }
    }
}
void solve()
{
    int n, m;
    scanf("%d%d", &n, &m);
    rep(i, 1, m)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        g[x].push_back(y);
    }
    dfs(1);
    printf("\n");
}
void init()
{
}
int main()
{
    init();
    int t = 1;
    scanf("%d", &t);
    while (t--)
    {
        solve();
    }
    return 0;
}