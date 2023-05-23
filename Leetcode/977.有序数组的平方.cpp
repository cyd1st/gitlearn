/*
 * @lc app=leetcode.cn id=977 lang=cpp
 *
 * [977] 有序数组的平方
 */

// @lc code=start
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        
        int len = nums.size();
        vector<int> result(len);

        int i = 0, j = len -1, k = j;

        while (i <= j) {
            if (abs(nums[i]) < abs(nums[j])) {
                result[k] = nums[j] * nums[j];
                j--;
            } else {
                result[k] = nums[i] * nums[i];
                i++;
            }
            k--;
        }

        return result;
    }
};
// @lc code=end

