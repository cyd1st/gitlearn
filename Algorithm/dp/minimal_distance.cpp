#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// basic 
int minDistance(string word1, string word2) {
    int m = word1.size();
    int n = word2.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i;
    }

    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
            }
        }
    }

    return dp[m][n];
}

// Damerau-Levenshtein
int damerauLevenshteinDistance(string word1, string word2) {
    int m = word1.size();
    int n = word2.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i;
    }

    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min({ dp[i - 1][j] + 1,  // 删除
                                dp[i][j - 1] + 1,  // 插入
                                dp[i - 1][j - 1] + 1 });  // 替换

                // 考虑字符对换操作
                if (i > 1 && j > 1 && word1[i - 1] == word2[j - 2] && word1[i - 2] == word2[j - 1]) {
                    dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + 1);  // 对换
                }
            }
        }
    }

    return dp[m][n];
}

int main() {
    string word1 = "sitting";
    string word2 = "kitten";

    cout << "Damerau-Levenshtein distance between '" << word1 << "' and '" << word2 << "' is: " << damerauLevenshteinDistance(word1, word2) << endl;
    cout << "min distance between '" << word1 << "' and '" << word2 << "' is: " << minDistance(word1, word2) << endl;

    return 0;
}