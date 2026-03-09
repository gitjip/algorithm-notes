#include <bits/stdc++.h>
using namespace std;
mt19937 rng(random_device{}());
vector<int> arr;
int partition(int l, int r)
{
    int i = l + 1, j = r;
    while (i <= j)
    {
        if (arr[i] <= arr[l])
            i++;
        else
            swap(arr[i], arr[j--]);
    }
    return j;
}
void quick_sort(int l, int r)
{
    if (l >= r)
        return;
    int mid = partition(l, r);
    quick_sort(l, mid - 1);
    quick_sort(mid + 1, r);
}