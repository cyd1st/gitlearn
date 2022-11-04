/*
 * @lc app=leetcode.cn id=367 lang=cpp
 *
 * [367] 有效的完全平方数
 */

// @lc code=start
class Solution {
public:
    bool isPerfectSquare(int num) {
        int left = 0;
        int right = num;
        long temp, mid;
        while (left <= right) {
            mid = (left + right) >> 1;
            temp = mid * mid;
            if (temp > num) {
                right = mid - 1;
            } else if (temp < num) {
                left = mid + 1;
            } else {
                return true;
            }
        }
        return false;
    }
};
// @lc code=end

