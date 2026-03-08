#include <bits/stdc++.h>
using namespace std;
/**
 * @brief 堆元素上升
 * 
 * @param arr 源堆
 * @param i 待上升元素
 */
void heap_up(vector<int> &arr, int i)
{
    while (i > 0)
    {
        int f = (i - 1) / 2;
        if (arr[i] > arr[f])
        {
            swap(arr[i], arr[f]);
            i = f;
        }
        else
            break;
    }
}
/**
 * @brief 堆元素下沉
 * 
 * @param arr 源堆
 * @param i 待下沉元素
 * @param n 堆大小
 */
void heap_down(vector<int> &arr, int i, int n)
{
    while (i * 2 + 1 < n)
    {
        int l = i * 2 + 1;
        int r = i * 2 + 2;
        // 从i,l,r三者选最优者(即arr[x]最大)
        // 采用两两比较取最大
        int best = arr[l] > arr[i] ? l : i;
        best = r < n && arr[r] > arr[best] ? r : best;
        if (best != i)
        {
            swap(arr[best], arr[i]);
            i = best;
        }
        else
            break;
    }
}
/**
 * @brief 堆排序(大根堆)
 * 
 * @param arr 待排序数组
 */
void heap_sort(vector<int> &arr)
{
    int n = arr.size();
    // 首先建堆
    for (int i = 0; i < n; i++)
        heap_up(arr, i);
    // 将堆顶元素arr[0]与末尾元素arr[i]交换, 此时堆顶成为末尾最大
    for (int i = n - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        heap_down(arr, 0, i);
    }
}