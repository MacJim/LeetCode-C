/*
 * 605. Can Place Flowers
 * https://leetcode.com/problems/can-place-flowers/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Find 000 streak
// Runtime: 32 ms, faster than 77.64% of C++ online submissions for Can Place Flowers.
// Memory Usage: 20.6 MB, less than 25.76% of C++ online submissions for Can Place Flowers.
class Solution {
public:
    bool canPlaceFlowers(std::vector<int>& flowerbed, int n) {
        if (n == 0) {
            // Too few flowers.
            return true;
        } else if (n > ((flowerbed.size() + 1) / 2)) {
            // Too many flowers.
            return false;
        }

        // Find 000
        int currentZeros = 1;    // The first streak can be 00.
        for (size_t i = 0; i < flowerbed.size(); i += 1) {
            const auto& availability = flowerbed[i];
            if (availability == 0) {
                currentZeros += 1;
                if (currentZeros == 3) {
                    n -= 1;    // TODO: Maybe check the value of n after this line's executed, and stop early.
                    currentZeros = 1;    // The last 0 can be used in the next 000 streak.
                }
            } else {
                currentZeros = 0;
            }
        }

        if (currentZeros == 2) {
            // The final streak can also be 00 instead of 000.
            n -= 1;
        }

        return (n <= 0);
    }
};


void test(const std::vector<int>& flowerbed, const int n, const bool expectedResult) {
    static auto solutionInstance = Solution();

    auto flowerbedCopy = flowerbed;
    auto result = solutionInstance.canPlaceFlowers(flowerbedCopy, n);

    if (result == expectedResult) {
        std::cout << "[Correct] " << flowerbed << " " << n << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << flowerbed << " " << n << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({0,0,1,0,1}, 1, true);
    test({1,0,1,0,0}, 1, true);
    test({1,0,0,0,1}, 1, true);
    test({1,0,0,0,1}, 2, false);
    test({1,0,0,0,0,0,1}, 2, true);
    return 0;
}
