/*
 * 344. Reverse String
 * https://leetcode.com/problems/reverse-string/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Swap
// Runtime: 20 ms, faster than 72.61% of C++ online submissions for Reverse String.
// Memory Usage: 23.2 MB, less than 67.68% of C++ online submissions for Reverse String.
class Solution {
public:
    void reverseString(std::vector<char>& s) {
        if (s.size() == 1) {
            return;
        }

        int left = 0;
        int right = s.size() - 1;
        while (left < right) {    // Terminates when left == right
            std::swap(s[left], s[right]);
            left += 1;
            right -= 1;
        }
    }
};


//void test(const std::vector<int>& s, const int expectedResult) {
//    static auto solutionInstance = Solution();
//
//    auto sCopy = s;
//    solutionInstance.reverseString(sCopy);
//
//    if (result == expectedResult) {
//        std::cout << "[Correct] " << nums << ": " << result << std::endl;
//    } else {
//        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
//    }
//}


int main() {
    return 0;
}
