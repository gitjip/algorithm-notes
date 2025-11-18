#include <bits/stdc++.h>
using namespace std;
// 希尔排序
void shell_sort(vector<int> &arr)
{
    int n = arr.size();
    // 枚举步长并分组
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        // 对每组插入排序
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}