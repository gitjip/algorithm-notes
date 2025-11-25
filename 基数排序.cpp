#include <bits/stdc++.h>
using namespace std;
/**
 * @brief 基数排序
 * 
 * @param arr 源数组
 * @param base 底数(几进制)
 * @param power 幂(几位)
 * 
 */
void radix_sort(vector<int> &arr, int base, int power)
{
    int n = arr.size();
    // 基数计数(例如十进制下468的第1,2,3基数分别是4,6,8), 临时数组
    vector<int> cnt(base), tmp(n);
    for (int offset = 1; power > 0; power--, offset *= base)
    {
        fill(cnt.begin(), cnt.end(), 0);
        // 统计不同基数的数的个数
        for (int i = 0; i < n; i++)
            cnt[arr[i] / offset % base]++;
        // 计算后的是每组的右边界
        for (int i = 1; i < base; i++)
            cnt[i] += cnt[i - 1];
        // 每次读入临时数组的对应区域, 不同基数互不干扰
        for (int i = n - 1; i >= 0; i--)
            tmp[--cnt[arr[i] / offset % base]] = arr[i];
        // 写回原数组
        for (int i = 0; i < n; i++)
            arr[i] = tmp[i];
    }
}