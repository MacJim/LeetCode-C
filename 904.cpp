/*
 * 904. Fruit Into Baskets
 * https://leetcode.com/problems/fruit-into-baskets/
 *
 * This problem is the same as 159.
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Same as question 159: 2 pointers
// Runtime: 84 ms, faster than 94.39% of C++ online submissions for Fruit Into Baskets.
// Memory Usage: 56.2 MB, less than 98.77% of C++ online submissions for Fruit Into Baskets.
class Solution {
public:
    int totalFruit(std::vector<int>& nums) {
        if (nums.size() <= 2) {
            return nums.size();
        }

        int returnValue = 0;

        // Log the 2 most recent numbers and their last appearances.
        int num1 = -1;
        int num2 = -1;
        int lastNum1Index = -1;
        int lastNum2Index = -1;

        int left = 0;
        int right = 0;

        while (right < nums.size()) {
            const auto& rightNum = nums[right];

            if (num1 == -1) {
                // No numbers yet.
                num1 = rightNum;
                lastNum1Index = right;
            } else if (num1 == rightNum) {
                lastNum1Index = right;
            } else if (num2 == -1) {
                num2 = rightNum;
                lastNum2Index = right;
            } else if (num2 == rightNum) {
                lastNum2Index = right;
            } else {
                // This is a new number and needs to replace one of the previous 2.
                const int previousLength = right - left;
                returnValue = std::max(returnValue, previousLength);

                if (lastNum1Index < lastNum2Index) {
                    left = lastNum1Index + 1;

                    num1 = rightNum;
                    lastNum1Index = right;
                } else {
                    left = lastNum2Index + 1;

                    num2 = rightNum;
                    lastNum2Index = right;
                }
            }

            right += 1;
        }

        const int lastLength = right - left;
        returnValue = std::max(returnValue, lastLength);

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.totalFruit(numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,1}, 3);
    test({0,1,2,2}, 3);
    test({1,2,3,2,2}, 4);
    test({3,3,3,1,2,1,1,2,3,3,4}, 5);

    return 0;
}
