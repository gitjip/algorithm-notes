#include <bits/stdc++.h>
using namespace std;
const int N = 2e5;
vector<string> pat;         // 模式串
string str;                 // 源串
vector<vector<int>> trie;   // Trie
vector<int> fail;           // 失配指针, 指向最长后缀的头
vector<int> en;             // 每个模式串的结束位置
vector<int> cnt;            // 词频
int tot = 1;                // Trie节点总数, 0为根节点
vector<vector<int>> g;
/**
 * @brief Trie插入串
 *
 * @param idx 串编号
 * @param s 待插入的串
 */
void insert(int idx, string s)
{
    int u = 0;
    for (char c : s)
    {
        int i = c - 'a';
        if (trie[u][i] == 0)
        {
            // 新建节点
            trie.push_back(vector<int>(26));
            trie[u][i] = tot++;
        }
        u = trie[u][i];
    }
    en[idx] = u;
}
/**
 * @brief 设置fail指针
 */
void set_fail()
{
    // BFS设置fail指针
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (trie[0][i] != 0)
            q.push(trie[0][i]);
    while (q.size())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++)
        {
            if (trie[u][i] == 0)
            // AC自动机优化: 设置直通表, 压缩fail指针跳转长度
                trie[u][i] = trie[fail[u]][i];
            else
            {
                // 为子节点设置fail指针
                fail[trie[u][i]] = trie[fail[u]][i];
                // 压入队列
                q.push(trie[u][i]);
            }
        }
    }
}
/**
 * @brief 统计词频
 */
void set_cnt()
{
    int u = 0;
    for (char c : str)
    {
        int i = c - 'a';
        u = trie[u][i];
        cnt[u]++;
    }
}
/**
 * @brief 统计答案, 直接在词频上做
 */
void set_ans()
{
    // 栈优化, 也可用递归做
    vector<bool> vis(tot);
    stack<int> st;
    st.push(0);
    while (st.size())
    {
        int u = st.top();
        if (!vis[u])
        {
            // 儿子未处理
            vis[u] = true;
            for (int v : g[u])
                st.push(v);
        }
        else
        {
            // 儿子已处理, 轮到自己
            st.pop();
            for (int v : g[u])
                cnt[u] += cnt[v];
        }
    }
}
/**
 * @brief 使用示例
 * 
 * @note 测试链接: https://www.luogu.com.cn/problem/P5357
 */
int main()
{
    int n;
    cin >> n;
    pat.resize(n);
    en.resize(n);
    // 0为根节点
    trie.push_back(vector<int>(26));
    for (int i = 0; i < n; i++)
    {
        cin >> pat[i];
        insert(i, pat[i]);
    }
    fail.resize(tot);
    cnt.resize(tot);
    g.resize(tot);
    set_fail();
    cin >> str;
    set_cnt();
    // 根据fail建反图
    for (int i = 1; i < tot; i++)
        g[fail[i]].push_back(i);
    set_ans();
    for (int i = 0; i < n; i++)
        cout << cnt[en[i]] << "\n";
    return 0;
}