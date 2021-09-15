/*
 * 1423. Maximum Points You Can Obtain from Cards
 * https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Sliding window
// Runtime: 86 ms, faster than 16.58% of C++ online submissions for Maximum Points You Can Obtain from Cards.
// Memory Usage: 42.4 MB, less than 80.72% of C++ online submissions for Maximum Points You Can Obtain from Cards.
class Solution {
public:
    int maxScore(const std::vector<int>& cardPoints, const int k) {
        // Front k elements sum.
        int sum = 0;
        for (int i = 0; i < k; i += 1) {
            sum += cardPoints[i];
        }

        int returnValue = sum;

        for (int backLength = 1; backLength <= k; backLength += 1) {
            const int frontLength = k - backLength;

            // Remove front card, insert back card.
            sum -= cardPoints[frontLength];
            sum += cardPoints[cardPoints.size() - backLength];

            returnValue = std::max(returnValue, sum);
        }

        return returnValue;
    }
};


void test(const std::vector<int>& cardPoints, const int k, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.maxScore(cardPoints, k);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << cardPoints << ", " << k << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << cardPoints << ", " << k << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3,4,5,6,1}, 3, 12);
    test({2,2,2}, 2, 4);
    test({9,7,7,9,7,7,9}, 7, 55);
    test({1,1000,1}, 1, 1);
    test({1,1000,1}, 2, 1001);
    test({1,79,80,1,1,1,200,1}, 3, 202);

    return 0;
}
