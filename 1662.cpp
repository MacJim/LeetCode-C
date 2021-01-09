/*
 * 1662. Check If Two String Arrays are Equivalent
 * https://leetcode.com/problems/check-if-two-string-arrays-are-equivalent/
 */

#include <iostream>
#include <vector>
#include <string>

#include "helpers/Operators.hpp"


// Runtime: 8 ms, faster than 42.56% of C++ online submissions for Check If Two String Arrays are Equivalent.
// Memory Usage: 11.5 MB, less than 96.06% of C++ online submissions for Check If Two String Arrays are Equivalent.
class Solution {
public:
    bool arrayStringsAreEqual(std::vector<std::string>& words1, std::vector<std::string>& words2) {
        size_t outer1 = 0;
        size_t inner1 = 0;
        size_t outer2 = 0;
        size_t inner2 = 0;

        while ((outer1 < words1.size()) && (outer2 < words2.size())) {
            const auto& s1 = words1[outer1];
            const auto& s2 = words2[outer2];
            const char& c1 = s1[inner1];
            const char& c2 = s2[inner2];

            if (c1 != c2) {
                return false;
            }

            inner1 += 1;
            inner2 += 1;

            if (inner1 >= s1.size()) {
                outer1 += 1;
                inner1 = 0;
            }
            if (inner2 >= s2.size()) {
                outer2 += 1;
                inner2 = 0;
            }
        }

        if ((outer1 < words1.size()) || (outer2 < words2.size())) {
            // One array/word is unfinished.
            return false;
        }

        return true;
    }
};


void test(const std::vector<std::string>& words1, const std::vector<std::string>& words2, const bool expectedResult) {
    static auto solutionInstance = Solution();

    auto words1Copy = words1;
    auto words2Copy = words2;
    auto result = solutionInstance.arrayStringsAreEqual(words1Copy, words2Copy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << words1Copy << words2Copy << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << words1Copy << words2Copy << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({"ab", "c"}, {"a", "bc"}, true);
    test({"a", "cb"}, {"ab", "c"}, false);
    test({"abc", "d", "defg"}, {"abcddefg"}, true);

    return 0;
}
