/*
 * @lc app=leetcode.cn id=209 lang=cpp
 *
 * [209] 长度最小的子数组
 */

// @lc code=start
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int len = nums.size();
        int win_size = 0;
        int min_size = INT_MAX;
        for (int i = 0, j = 0, sum = 0; j < len; j++) {
            if (nums[j] >= target) return 1;
            sum += nums[j];
            win_size++;
            if (sum < target) continue;
            // 收缩窗口
            while (sum - nums[i] >= target) {
                win_size--;
                sum -= nums[i++];
            }
            min_size = min_size > win_size ? win_size : min_size;
        }
        if (min_size > len) return 0;
        return min_size;
    }
}
// @lc code=end

