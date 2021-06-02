/*
 * 239. Sliding Window Maximum
 * https://leetcode.com/problems/sliding-window-maximum/
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Naive solution: find max for every window


#pragma mark - 2. Optimized 1: Remove smaller previous elements
// Time Limit Exceeded
class Solution2 {
public:
    std::vector<int> maxSlidingWindow(std::vector<int>& nums, int length) {
        if ((nums.size() == 1) || (length == 1)) {
            return nums;
        }

        auto returnValue = std::vector<int>(nums.size() - length + 1);

        /// Elements in [left, mid) are all smaller than `nums[mid]`.
        size_t mid = 0;
        int currentMax = INT_MIN;

        for (size_t left = 0; left < returnValue.size(); left += 1) {
            mid = std::max(mid, left);

            for (size_t i = mid; i <= (left + length - 1); i += 1) {
                if (nums[i] >= currentMax) {
                    currentMax = nums[i];
                    mid = i;
                }
            }

            returnValue[left] = currentMax;

            // Check if `currentMax` is removed.
            if (left == mid) {
                // `currentMax` is the left-most element, and will be removed in the next iteration.
                currentMax = INT_MIN;
            }
        }

        return returnValue;
    }
};


#pragma mark - 3. Red black tree
// Runtime: 808 ms, faster than 5.33% of C++ online submissions for Sliding Window Maximum.
// Memory Usage: 172.7 MB, less than 20.33% of C++ online submissions for Sliding Window Maximum.
class Solution3 {
public:
    std::vector<int> maxSlidingWindow(const std::vector<int>& nums, const int length) {
        if ((nums.size() == 1) || (length == 1)) {
            return nums;
        }

        auto returnValue = std::vector<int>(nums.size() - length + 1);

        auto occurrences = std::map<int, int, std::greater<>>();    // Greater: biggest element first.
        for (size_t i = 0; i < length; i += 1) {
            occurrences[nums[i]] += 1;
        }
        returnValue[0] = occurrences.begin()->first;

        for (size_t previous = 0; previous < (nums.size() - length); previous += 1) {
            const auto& previousNum = nums[previous];
            if (occurrences[previousNum] == 1) {
                occurrences.erase(previousNum);
            } else {
                occurrences[previousNum] -= 1;
            }

            const size_t current = previous + length;
            const auto& currentNum = nums[current];
            occurrences[currentNum] += 1;

            returnValue[previous + 1] = occurrences.begin()->first;
        }

        return returnValue;
    }
};


#pragma mark - 4. Official solution: Double-ended queue (revisit)
/*
 * This is somewhat similar to solution 2, but goes much further.
 *
 * We only keep potential answers in the deque.
 */
// Runtime: 580 ms, faster than 13.12% of C++ online submissions for Sliding Window Maximum.
// Memory Usage: 129.1 MB, less than 96.30% of C++ online submissions for Sliding Window Maximum.
class Solution {
public:
    std::vector<int> maxSlidingWindow(const std::vector<int>& nums, const int length) {
        if ((nums.size() == 1) || (length == 1)) {
            return nums;
        }

        auto returnValue = std::vector<int>(nums.size() - length + 1);

        /**
         * Stores indices of large numbers (potential answers).
         *
         * Numbers represented by front indices are always larger or equal to numbers represented by back indices.
         *
         * The front index always represents the largest number.
         */
        auto largeIndices = std::deque<size_t>();

        // First `length` elements.
        for (size_t i = 0; i < length; i += 1) {
            const auto& currentNum = nums[i];

            // Remove previous deque numbers that are smaller than the current number.
            while ((!largeIndices.empty()) && (nums[largeIndices.back()] < currentNum)) {
                largeIndices.pop_back();
            }

            largeIndices.push_back(i);

            // The front of the deque is the largest.
            returnValue[0] = nums[largeIndices.front()];
        }

        // Upcoming elements.
        for (size_t previous = 0; previous < (nums.size() - length); previous += 1) {
            // Remove the queue front if it expired.
            if (largeIndices.front() == previous) {
                largeIndices.pop_front();
            }

            // Remove previous deque numbers that are smaller than the current number.
            const size_t current = previous + length;
            const auto& currentNum = nums[current];
            while ((!largeIndices.empty()) && (nums[largeIndices.back()] < currentNum)) {
                largeIndices.pop_back();
            }

            largeIndices.push_back(current);

            // The front of the deque is the largest.
            returnValue[previous + 1] = nums[largeIndices.front()];
        }

        return returnValue;
    }
};



void test(const std::vector<int>& nums, const int k, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.maxSlidingWindow(numsCopy, k);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({7,2,4}, 2, {7,4});
    test({1,3,-1,-3,5,3,6,7}, 3, {3,3,5,5,6,7});
    test({1}, 1, {1});
    test({1,-1}, 1, {1, -1});
    test({1,-1}, 2, {1});

    return 0;
}
