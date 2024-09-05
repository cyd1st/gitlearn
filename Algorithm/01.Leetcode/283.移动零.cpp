/*
 * @lc app=leetcode.cn id=283 lang=cpp
 *
 * [283] 移动零
 */

// @lc code=start
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int len = nums.size();
        int i = 0, j = 1;

        while (j < len) {
            if (nums[i] != 0) i++;
            else if (nums[j] != 0) {
                nums[i++] = nums[j];
                nums[j] = 0;
            }
            j++;
        }
    }
};
// @lc code=end

