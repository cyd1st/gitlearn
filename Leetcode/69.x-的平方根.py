#
# @lc app=leetcode.cn id=69 lang=python3
#
# [69] x 的平方根 
#

# @lc code=start
class Solution:
    def mySqrt(self, x: int) -> int:
        if x == 1:
            return 1

        l = 0
        r = x
        while (r - l > 1):
            mid = (l + r) >> 1
            temp = mid * mid
            if temp > x:
                r = mid
            elif temp < x:
                l = mid
            else:
                return mid
        return l

# @lc code=end

