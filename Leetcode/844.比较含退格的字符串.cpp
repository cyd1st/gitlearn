/*
 * @lc app=leetcode.cn id=844 lang=cpp
 *
 * [844] 比较含退格的字符串
 */

// @lc code=start
class Solution {
public:
    bool backspaceCompare(string s, string t) {
        int i = s.size() - 1;
        int j = t.size() - 1;
        int s_skip = 0, t_skip = 0;

        while (i >= 0 || j >= 0) {
            while (i >= 0) {
                if (s[i] == '#') {
                    i--; s_skip++;
                } else if (s_skip > 0) {
                    i--; s_skip--;
                } else break;
            }
            
            while (j >= 0) {
                if (t[j] == '#') {
                    j--; t_skip++;
                } else if (t_skip > 0 ) {
                    j--; t_skip--;
                } else break;
            }

            if (i >= 0 && j >= 0) {
                printf("%d %d\n", i, j);
                if (s[i--] != t[j--]) return false;
            } else if (i >= 0 || j >= 0) {
                return false;
            }
        }
        return true;
    }
};
// @lc code=end

