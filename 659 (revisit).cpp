/*
 * 659. Split Array into Consecutive Subsequences
 * https://leetcode.com/problems/split-array-into-consecutive-subsequences/
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>

#include "helpers/Operators.hpp"


#pragma mark - 1. Min heap (revisit)
// I took the "min heap" hint from LeetCode and devised the solution by myself.
// Runtime: 56 ms, faster than 99.43% of C++ online submissions for Split Array into Consecutive Subsequences.
// Memory Usage: 54.4 MB, less than 97.91% of C++ online submissions for Split Array into Consecutive Subsequences.
class Solution {
public:
    bool isPossible(std::vector<int>& nums) {
        if (nums.size() < 3) {
            return false;
        }

        auto cmp = [](const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
            if (lhs.first == rhs.first) {
                // Return the one with a shorter length.
                return lhs.second > rhs.second;
            } else {
                return lhs.first > rhs.first;
            }
        };
        auto heap = std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)>(cmp);

        for (const auto& num: nums) {
            if (heap.empty()) {
                heap.push(std::make_pair(num, 1));
            } else {
                // Remove the small/complete sequences (our `nums` array is sorted in ascending order).
                auto delta = num - heap.top().first;
                while ((delta > 1) && (!heap.empty())) {
                    if (heap.top().second < 3) {
                        return false;
                    } else {
                        heap.pop();
                        delta = num - heap.top().first;
                    }
                }

                if (heap.empty()) {
                    heap.push(std::make_pair(num, 1));
                } else {
                    if (delta == 1) {
                        const int newCount = heap.top().second + 1;
                        heap.pop();
                        heap.push(std::make_pair(num, newCount));
                    } else {
                        heap.push(std::make_pair(num, 1));
                    }
                }
            }

//            std::cout << heap << std::endl;
        }

        while (!heap.empty()) {
            if (heap.top().second < 3) {
                return false;
            }

            heap.pop();
        }

        return true;
    }
};



void test(const std::vector<int>& nums, const bool expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.isPossible(numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3,3,4,5}, true);
    test({1,2,3,3,4,4,5,5}, true);
    test({1,2,3,4,4,5}, false);
    test({1,1,1}, false);
    test({1,3,4}, false);
    test({1,3,4,5}, false);

    return 0;
}
