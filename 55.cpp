/*
 * 55. Jump Game
 * https://leetcode.com/problems/jump-game/
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include "helpers/Operators.hpp"


#pragma mark - 1. Greedy?
// Runtime: 8 ms, faster than 93.24% of C++ online submissions for Jump Game.
// Memory Usage: 12.8 MB, less than 85.74% of C++ online submissions for Jump Game.
class Solution {
public:
    bool canJump(std::vector<int>& nums) {
        const auto len = nums.size();
        if (len == 1) {
            return true;
        }

        size_t current = 0;
        size_t maxDestination = nums[0];
        size_t maxNext = 0;

        while (true) {
            const int maxStep = nums[current];
            if (maxStep == 0) {
                return false;
            }

            bool nextUpdated = false;

            for (size_t step = 1; step <= maxStep; step += 1) {
                const size_t next = current + step;

                const int nextStep = nums[next];
                const size_t destination = next + nextStep;
                if (destination >= (len - 1)) {
                    return true;
                }

                if (destination > maxDestination) {
                    maxDestination = destination;
                    maxNext = next;
                    nextUpdated = true;
                }
            }

            if (!nextUpdated) {
                return false;
            }

            current = maxNext;
        }

        return (current == (nums.size() - 1));
    }
};


void test(const std::vector<int>& nums, const bool expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.canJump(numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({3,2,1,0,4}, false);
    test({2,3,1,1,4}, true);
    test({1,1,1,1,1,1,1,1,1,1}, true);
    test({3,2,1,0}, true);
    test({1, 0}, true);
    test({6, 0}, true);
    test({3,3,3,1,0,0,100}, false);

    return 0;
}
