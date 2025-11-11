#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        for (int i = nums.size() - 1; i >= 0; --i) {
            heapify(nums, i, nums.size());
        }
        for (int i = nums.size() - 1; i >= 1; --i) {
            swap(nums[0], nums[i]);
            heapify(nums, 0, i);
        }
        return nums;
    }
    void heapInsert(vector<int>& nums, int i) {
        while (nums[i] > nums[(i - 1) / 2]) {
            swap(nums[i], nums[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
    void heapify(vector<int>& nums, int i, int n) {
        int best;
        while (i * 2 + 1 < n) {
            best = (i * 2 + 2 < n && nums[i * 2 + 2] > nums[i * 2 + 1])
                       ? i * 2 + 2
                       : i * 2 + 1;
            best = nums[best] > nums[i] ? best : i;
            if (best == i) {
                break;
            }
            swap(nums[i], nums[best]);
            i = best;
        }
    }
};