/*
 * @lc app=leetcode.cn id=704 lang=cpp
 *
 * [704] 二分查找
 */

// @lc code=start
class Solution {
public:
/* 左闭右闭 */
    int search1(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int mid = 0;
        while (left <= right) {
            mid = left + (right - left) / 2;
            if (nums[mid] > target) {
                right = mid - 1;
            } else if (nums[mid] == target) {
                return mid;
            } else {
                left = mid + 1;
            }
        }
        return -1;
    }
    /* 左闭右开 */
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size();
        int mid = 0;
        while (left < right) {
            mid = left + ((right - left) >> 1);
            if (nums[mid] > target) {
                right = mid;
            } else if (nums[mid] == target) {
                return mid;
            } else {
                left = mid + 1;
            }
        }
        return -1;
    }
};
// @lc code=end

