#include <bits/stdc++.h>
using namespace std;
// 最小堆
struct heap
{
    vector<int> a;
    void push(int x)
    {
        a.push_back(x);
        up(a.size() - 1);
    }
    int top()
    {
        return a.front();
    }
    void pop()
    {
        swap(a.front(), a.back());
        a.pop_back();
        down(0);
    }
    int fa(int i)
    {
        return (i - 1) / 2;
    }
    int ls(int i)
    {
        return i * 2 + 1;
    }
    int rs(int i)
    {
        return i * 2 + 2;
    }
    void up(int i)
    {
        while (i && a[i] < a[fa(i)])
        {
            swap(a[i], a[fa(i)]);
            i = fa(i);
        }
    }
    void down(int i)
    {
        while (ls(i) < a.size() && (a[i] > a[ls(i)] || rs(i) < a.size() && a[i] > a[rs(i)]))
        {
            int j = rs(i) < a.size() && a[rs(i)] < a[ls(i)] ? rs(i) : ls(i);
            swap(a[i], a[j]);
            i = j;
        }
    }
};