/*
 * 1143. Longest Common Subsequence
 * https://leetcode.com/problems/longest-common-subsequence/
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


// Runtime: 16 ms, faster than 86.45% of C++ online submissions for Longest Common Subsequence.
// Memory Usage: 6.6 MB, less than 100.00% of C++ online submissions for Longest Common Subsequence.
class Solution {
public:
    int longestCommonSubsequence(std::string text1, std::string text2) {
        const auto len1 = text1.size();
        const auto len2 = text2.size();

        if ((len1 == 0) || (len2 == 0)) {
            return 0;
        }

        auto currentRow = std::vector<int>(len1, 0);

        // First row.
        for (int i = 0; i < len1; i += 1) {
            if (text1.at(i) == text2.at(0)) {
                currentRow.at(i) = 1;
            }
        }

        // Upcoming rows.
        for (int j = 1; j < len2; j += 1) {
            int previousLargestValue = currentRow.at(0);

            // First element.
            if (text1.at(0) == text2.at(j)) {
                currentRow.at(0) = std::max(1, currentRow.at(0));
            }

            // Upcoming elements.
            for (int i = 1; i < len1; i += 1) {
                const int previousValue = currentRow.at(i);

                if (text1.at(i) == text2.at(j)) {
                    currentRow.at(i) = std::max(previousLargestValue + 1, currentRow.at(i));
                }

                if (previousValue > previousLargestValue) {
                    previousLargestValue = previousValue;
                }
            }
        }

        return *std::max_element(currentRow.begin(), currentRow.end());
    }
};


int main() {
    auto solutionInstance = Solution();
    std::cout << solutionInstance.longestCommonSubsequence("abcde", "ace") << std::endl;    // 3
    std::cout << solutionInstance.longestCommonSubsequence("abcb", "acb") << std::endl;    // 3
    std::cout << solutionInstance.longestCommonSubsequence("abcb", "acbabcb") << std::endl;    // 4
    std::cout << solutionInstance.longestCommonSubsequence("abcb", "abcbc") << std::endl;    // 4
    std::cout << solutionInstance.longestCommonSubsequence("abc", "def") << std::endl;    // 0

    return 0;
}
