#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> trie;
vector<int> cnt;
/**
 * @brief 建Trie树, 插入串
 */
void insert(string s)
{
    int u = 0;
    for (char c : s)
    {
        cnt[u]++;
        if (trie[u][c] == 0)
        {
            trie[u][c] = trie.size();
            trie.push_back(vector<int>(128));
            cnt.push_back(0);
        }
        u = trie[u][c];
    }
    cnt[u]++;
}
/**
 * @brief 查询以s为前缀的串的个数
 */
int query(string s)
{
    int u = 0;
    for (char c : s)
    {
        if (trie[u][c] == 0)
            return 0;
        u = trie[u][c];
    }
    return cnt[u];
}
void solve()
{
    trie.clear();
    cnt.clear();
    trie.resize(1, vector<int>(128));
    cnt.resize(1);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        insert(s);
    }
    for (int i = 0; i < q; i++)
    {
        string s;
        cin >> s;
        cout << query(s) << "\n";
    }
}
int main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}