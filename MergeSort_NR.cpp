#include <bits/stdc++.h>
using namespace std;
void merge_sort(vector<int> &arr)
{
    int n = arr.size();
    vector<int> tmp(n);
    for (int step = 1; step < n; step *= 2)
    {
        for (int i = 0; i * step < n; i++)
        {
            int l = i * 2 * step;
            int mid = min((i * 2 + 1) * step, n);
            int r = min((i * 2 + 2) * step, n);
            if (mid == r)
                continue;
            for (int i = l, j = l, k = mid; i < r; i++)
            {
                if (j < mid && (k >= r || arr[j] <= arr[k]))
                    tmp[i] = arr[j++];
                else
                    tmp[i] = arr[k++];
            }
            for (int i = l; i < r; i++)
                arr[i] = tmp[i];
        }
    }
}