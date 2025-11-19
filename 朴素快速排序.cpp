#include <bits/stdc++.h>
using namespace std;
mt19937 rng(random_device{}());
vector<int> arr;
int partition(int l, int r)
{
    int x = arr[l];
    int i = l, j = r + 1;
    while (i < j)
    {
        while (++i <= r && arr[i] <= x)
            ;
        while (--j >= l && arr[j] >= x)
            ;
        if (i < j)
            swap(arr[i], arr[j]);
    }
    swap(arr[i], arr[l]);
    return i;
}
void quick_sort(int l, int r)
{
    if (l >= r)
        return;
    int mid = partition(l, r);
    quick_sort(l, mid - 1);
    quick_sort(mid + 1, r);
}