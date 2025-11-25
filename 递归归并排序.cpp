#include <bits/stdc++.h>
using namespace std;
vector<int> arr, tmp;
void merge_sort(int l, int r)
{
    int mid = (l + r) / 2;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);
    for (int i = l, j = l, k = mid + 1; i <= r; i++)
    {
        if (j <= mid && (k > r || arr[j] <= arr[k]))
            tmp[i] = arr[j++];
        else
            tmp[i] = arr[k++];
    }
    for (int i = l; i <= r; i++)
        arr[i] = tmp[i];
}