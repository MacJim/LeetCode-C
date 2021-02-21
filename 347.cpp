/*
 * 347. Top K Frequent Elements
 * https://leetcode.com/problems/top-k-frequent-elements/
 */

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

#include "helpers/Operators.hpp"


#pragma mark - 1. Heap
// Runtime: 20 ms, faster than 64.06% of C++ online submissions for Top K Frequent Elements.
// Memory Usage: 13.4 MB, less than 99.79% of C++ online submissions for Top K Frequent Elements.
class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        if (nums.empty()) {
            return {};
        }

        // In fact I should have used a hash map to store the occurrences (rather than sort and iterate).
        std::sort(nums.begin(), nums.end());

        auto cmp = [] (std::pair<int, int>& left, std::pair<int, int>& right) {
            return (left.second > right.second);    // Greater: min heap.
        };
        auto heap = std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)>(cmp);

        int current = nums[0];
        int currentCount = 0;
        for (const auto& n: nums) {
            if (n == current) {
                currentCount += 1;
            } else {
                if (currentCount) {
                    if (heap.size() < k) {
                        heap.emplace(current, currentCount);
                    } else {
                        if (currentCount > heap.top().second) {
                            heap.pop();
                            heap.emplace(current, currentCount);
                        }
                    }
                }

                current = n;
                currentCount = 1;
            }
        }

        if (currentCount) {
            if (heap.size() < k) {
                heap.emplace(current, currentCount);
            } else {
                if (currentCount > heap.top().second) {
                    heap.pop();
                    heap.emplace(current, currentCount);
                }
            }
        }

        auto returnValue = std::vector<int>();
        while (!heap.empty()) {
            returnValue.push_back(heap.top().first);
            heap.pop();
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums, const int k, const std::set<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto numCopy = nums;
    auto result = solutionInstance.topKFrequent(numCopy, k);
    auto resultSet = std::set<int>(result.begin(), result.end());

    if (resultSet == expectedResult) {
        std::cout << "[Correct] " << nums << " " << k << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums << " " << k << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,1,1,1,2}, 2, {1,2});
    test({1,1,1,2,2,2}, 2, {1,2});
    test({1,2,2,2}, 1, {2});
    test({1,2,2,2,3,3,3,4,4,4}, 3, {2,3,4});
    test({4,2,4,3,3,1,2,4,2,3}, 3, {2,3,4});

    return 0;
}
