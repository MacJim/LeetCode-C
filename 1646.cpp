/*
 * 1646. Get Maximum in Generated Array
 * https://leetcode.com/problems/get-maximum-in-generated-array/
 */

#include <iostream>
#include <vector>

// #include "helpers/Operators.hpp"


#pragma mark - 1. Brute force
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Get Maximum in Generated Array.
// Memory Usage: 6.3 MB, less than 34.16% of C++ online submissions for Get Maximum in Generated Array.
class Solution {
public:
    int getMaximumGenerated(int n) {
        if (n <= 1) {
            return n;
        }

        auto nums = std::vector<int>(n + 1, 0);
        nums[1] = 1;
        int returnValue = 1;

        for (int i = 2; i <= n; i += 1) {
            if (i % 2 == 0) {
                nums[i] = nums[i / 2];
            } else {
                nums[i] = nums[i / 2] + nums[i / 2 + 1];
                if (nums[i] > returnValue) {
                    returnValue = nums[i];
                }
            }
        }

        return returnValue;
    }
};


void test(const int n, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.getMaximumGenerated(n);

    if (result == expectedResult) {
        std::cout << "[Correct] " << n << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << n << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(0, 0);
    test(2, 1);
    test(3, 2);
    test(7, 3);

    return 0;
}
