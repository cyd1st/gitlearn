#
# @lc app=leetcode.cn id=27 lang=python
#
# [27] 移除元素
#

# @lc code=start
class Solution(object):
    def removeElement(self, nums, val):
        """
        :type nums: List[int]
        :type val: int
        :rtype: int
        """
        length = len(nums)
        l = 0
        r = length - 1
        ret = length

        while r >= l:
            # get left position
            while nums[l] != val and l < r:
                l += 1
            if nums[l] == val: ret -= 1
            else: return ret

            # get right position
            while nums[r] == val and r > l:
                ret -= 1
                r -= 1
            if r <= l: break

            # change left by right
            nums[l] = nums[r]
            
            # move point
            if r - l > 1:
                l += 1
                r -= 1
            else: break

        return ret

# @lc code=end

