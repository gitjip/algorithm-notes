#include <bits/stdc++.h>
using namespace std;
mt19937 rng(random_device{}());
vector<int> arr;
pair<int, int> part(int l, int r, int x)
{
    int i = l, j = l, k = r;
    while (i <= k)
    {
        if (arr[i] == x)
            i++;
        else if (arr[i] < x)
            swap(arr[i++], arr[j++]);
        else if (arr[i] > x)
            swap(arr[i], arr[k--]);
    }
    return {j, k};
}
void quick_sort(int l, int r)
{
    if (l >= r)
        return;
    auto [L, R] = part(l, r, arr[l + rng() % (r - l + 1)]);
    quick_sort(l, L - 1);
    quick_sort(R + 1, r);
}