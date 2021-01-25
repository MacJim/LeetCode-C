/*
 * 918. Maximum Sum Circular Subarray
 * https://leetcode.com/problems/maximum-sum-circular-subarray
 */

/*
 * This problem is very similar to "560. Subarray Sum Equals K".
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>

#include "helpers/Operators.hpp"


#pragma mark - 1
/*
 * We either find the max middle subarray, or the min middle subarray.
 *
 * In the later case, we actually use the sides of the array.
 */
// WRONG ANSWER because I didn't consider using the entire array.
class Solution1 {
public:
    int maxSubarraySumCircular(std::vector<int>& arr) {
        if (arr.size() == 1) {
            // We know that the min length is 1.
            return arr[0];
        }

        int minSubArraySum = INT_MAX;
        int maxSubArraySum = INT_MIN;

        /// Min sum of [0, n];
        auto minSum = arr[0];
        /// Max sum of [0, n];
        auto maxSum = arr[0];
        int currentSum = arr[0];

        for (auto it = (arr.begin() + 1); it < arr.end(); it += 1) {
            currentSum += *it;

            maxSubArraySum = std::max(currentSum - minSum, maxSubArraySum);
            minSubArraySum = std::min(currentSum - maxSum, minSubArraySum);

            minSum = std::min(currentSum, minSum);
            maxSum = std::max(currentSum, maxSum);
        }

        const int arrSum = std::accumulate(arr.begin(), arr.end(), 0);    // Yes. A 32 bit signed int is enough.
        minSubArraySum = arrSum - minSubArraySum;

        return std::max(minSubArraySum, maxSubArraySum);
    }
};


#pragma mark - 2. Fixed 1
// Actually I just changed the last line to `return std::max(minSubArraySum, std::max(maxSubArraySum, arrSum));` to include the case of using the entire array.
// Runtime: 64 ms, faster than 89.94% of C++ online submissions for Maximum Sum Circular Subarray.
// Memory Usage: 39.8 MB, less than 96.95% of C++ online submissions for Maximum Sum Circular Subarray.
class Solution {
public:
    int maxSubarraySumCircular(std::vector<int>& arr) {
        if (arr.size() == 1) {
            // We know that the min length is 1.
            return arr[0];
        }

        int minSubArraySum = INT_MAX;
        int maxSubArraySum = INT_MIN;

        /// Min sum of [0, n];
        auto minSum = arr[0];
        /// Max sum of [0, n];
        auto maxSum = arr[0];
        int currentSum = arr[0];

        for (auto it = (arr.begin() + 1); it < arr.end(); it += 1) {
            currentSum += *it;

            maxSubArraySum = std::max(currentSum - minSum, maxSubArraySum);
            minSubArraySum = std::min(currentSum - maxSum, minSubArraySum);

            minSum = std::min(currentSum, minSum);
            maxSum = std::max(currentSum, maxSum);
        }

        const int arrSum = std::accumulate(arr.begin(), arr.end(), 0);    // Yes. A 32 bit signed int is enough.
        minSubArraySum = arrSum - minSubArraySum;

        return std::max(minSubArraySum, std::max(maxSubArraySum, arrSum));
    }
};


void test(const std::vector<int>& A, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto aCopy = A;
    auto result = solutionInstance.maxSubarraySumCircular(aCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << A << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << A << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({3,1,3,2,6}, 15);
    test({-2,-3,-1}, -1);
    test({1,-2,3,-2}, 3);
    test({5,-3,5}, 10);
    test({3,-1,2,-1}, 4);
    test({3,-2,2,-3}, 3);

    return 0;
}
