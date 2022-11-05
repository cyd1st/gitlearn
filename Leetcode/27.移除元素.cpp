/*
 * @lc app=leetcode.cn id=27 lang=cpp
 *
 * [27] 移除元素
 */

// @lc code=start
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int len = nums.size();
        // if (len <= 0 || (val > 50)) return len;
        
        int i = 0, j = len - 1, ret = len;
        while (j >= i) {
            while (nums[i] != val && i < j) i++;
            if (nums[i] == val) ret--;
            else break;

            while (nums[j] == val && j > i) {j--; ret--;}; 
            if (j <= i) break;
            
            nums[i] = nums[j];
            if (j - i > 1) {
                i++;
                j--;
            } else {
                break;
            }
        }

        return ret;
    }
};
// @lc code=end

