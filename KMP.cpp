// KMP
#include <bits/stdc++.h>
using namespace std;
int main()
{
    string s, t;
    cin >> s >> t;
    int n = s.size();
    int m = t.size();
    vector<int> nex(m + 1);
    // 求next数组
    for (int i = 1, j = 0; i < m; i++)
    {
        while (j && t[i] != t[j])
            j = nex[j];
        if (t[i] == t[j])
            j++;
        nex[i + 1] = j;
    }
    // 输出匹配位置(下标从1开始)
    for (int i = 0, j = 0; i < n; i++)
    {
        while (j && s[i] != t[j])
            j = nex[j];
        if (s[i] == t[j])
            j++;
        if (j == m)
            cout << i - m + 2 << "\n";
    }
    for (int i = 1; i <= m; i++)
        cout << nex[i] << " ";
    cout << "\n";
    return 0;
}