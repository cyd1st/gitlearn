/*
 * @lc app=leetcode.cn id=69 lang=cpp
 *
 * [69] x 的平方根 
 */

// @lc code=start
class Solution {
public:
    int mySqrt(int x) {
        if (x == 1) return 1;
        int l = 0;
        int r = x;
        long mid, temp;
        while (r - l > 1) {
            mid = (l + r) >> 1;
            temp = mid * mid;
            if (temp > x) {
                r = mid;
            } else {
                l = mid;
            }
        }
        return l;
    }
};
// @lc code=end

