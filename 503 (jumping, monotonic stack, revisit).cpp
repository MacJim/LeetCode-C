/*
 * 503. Next Greater Element II
 * https://leetcode.com/problems/next-greater-element-ii/
 */

#include <iostream>
#include <vector>
#include <climits>
#include <stack>

#include "helpers/Operators.hpp"


#pragma mark - 1. Cache next larger indices and use them to accelerate ("jump" to existing better solutions) (like problem 84)
/*
 * The thought behind this is very similar to my solution 2 of problem 84.
 *
 * I didn't solve problem 84 and referred to a discussion on May 18th, 2021.
 *
 * I then devised this solution on my own on May 21st, 2021.
 *
 * I'm pretty sure this is not the intended/official solution.
 * But it's damn fast!
 */
// Runtime: 24 ms, faster than 95.59% of C++ online submissions for Next Greater Element II.
// Memory Usage: 23.3 MB, less than 98.85% of C++ online submissions for Next Greater Element II.
class Solution1 {
public:
    std::vector<int> nextGreaterElements(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return {-1};
        }

        int maxNum = INT_MIN;
        for (const auto& num: nums) {
            maxNum = std::max(maxNum, num);
        }

        /*
         * -2: Uninitialized
         * -1: Largest number
         * Non-negative number: indices to the next larger element
         */
        auto returnValue = std::vector<int>(nums.size(), -2);

        // Back to front.
        for (int i = (nums.size() - 1); i >= 0; i -= 1) {
            if (nums[i] == maxNum) {
                returnValue[i] = -1;
                continue;
            }

            int j = i + 1;
            while (j != i) {
                if (j == nums.size()) {
                    j = 0;
                    continue;
                }

                if (nums[j] > nums[i]) {
                    returnValue[i] = j;
                    break;
                } else {
                    if (returnValue[j] >= 0) {
                        // Use cached "next larger" value.
                        j = returnValue[j];
                    } else {
                        // Use O(n) search.
                        j += 1;
                    }
                }
            }
        }

        /*
         * For the moment `returnValue` is storing indices to the next larger element.
         *
         * Convert indices to values.
         */
        for (auto& val: returnValue) {
            if (val != -1) {
                val = nums[val];
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Official solution: Use a monotonic stack 单调栈 (revisit)
/*
 * Monotonic stacks are only used to solve "next greater element" questions.
 * The official solution of problem 84 also uses a monotonic stack.
 *
 * To deal with circular arrays, duplicate the `nums` array once, and use the mod operator `%`.
 *
 * Each element is pushed and popped at most once.
 * Thus, this algorithm is O(n).
 *
 * This runs slightly slower than my solution 1 but has a more consistent worst-case O(n) complexity.
 */
// Runtime: 28 ms, faster than 86.66% of C++ online submissions for Next Greater Element II.
// Memory Usage: 24 MB, less than 51.41% of C++ online submissions for Next Greater Element II.
class Solution {
public:
    std::vector<int> nextGreaterElements(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return {-1};
        }

        auto s = std::stack<int>();
        auto returnValue = std::vector<int>(nums.size());    // Default-construction is sufficient in this solution.

        // Duplicate the `nums` array once.
        for (int i = (nums.size() * 2 - 1); i >= 0; i -= 1) {
            const auto realIndex = (i >= nums.size())? (i - nums.size()): i;
            const auto& num = nums[realIndex];

            while ((!s.empty()) && (s.top() <= num)) {
                // Pop the values between the current num and its larger num.
                s.pop();
            }

            if (s.empty()) {
                // This is the largest number.
                returnValue[realIndex] = -1;
            } else {
                // The top of the stack is larger than the current number.
                returnValue[realIndex] = s.top();
            }

            s.push(num);
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.nextGreaterElements(numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,1}, {2,-1,2});
    test({1,2,3,4,3}, {2,3,4,-1,4});
    test({4,5,4,5,4,5}, {5,-1,5,-1,5,-1});
    test({3,4,3,2,1}, {4,-1,4,3,3});
    test({2,4,3,2,1}, {4,-1,4,4,2});

    return 0;
}
