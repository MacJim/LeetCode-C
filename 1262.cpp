/*
 * 1262. Greatest Sum Divisible by Three
 * https://leetcode.com/problems/greatest-sum-divisible-by-three/
 */

#include <iostream>
#include <vector>
#include <array>
#include <queue>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1
// WRONG ANSWER because it supports up to 3 numbers.
class Solution1 {
public:
    int maxSumDivThree(const std::vector<int>& nums) {
        auto largest0 = std::array<int, 3>({-1, -1, -1});
        auto largest1 = std::array<int, 3>({-1, -1, -1});
        auto largest2 = -1;

        for (const auto& num: nums) {
            switch (num % 3) {
                case 0:
                    for (int i = 0; i < 3; i += 1) {
                        if (num > largest0[i]) {
                            for (int j = 2; j > i; j -= 1) {
                                largest0[j] = largest0[j - 1];
                            }

                            largest0[i] = num;

                            break;
                        }
                    }
                    break;

                case 1:
                    for (int i = 0; i < 3; i += 1) {
                        if (num > largest1[i]) {
                            for (int j = 2; j > i; j -= 1) {
                                largest0[j] = largest1[j - 1];
                            }

                            largest1[i] = num;

                            break;
                        }
                    }
                    break;

                default:
                    largest2 = std::max(largest2, num);
            }
        }

        // 0 0 0
        int returnValue000 = 0;
        for (int i = 0; i < 3; i += 1) {
            if (largest0[i] > 0) {
                returnValue000 += largest0[i];
            } else {
                break;
            }
        }

        // 0 1 2
        int returnValue012 = 0;
        if ((largest1[0] > 0) && (largest2 > 0)) {
            returnValue012 = largest1[0] + largest2;
            if (largest0[0] > 0) {
                returnValue012 += largest0[0];
            }
        }

        // 1 1 1
        int returnValue111 = 0;
        if (largest1[2] > 0) {
            returnValue111 = largest1[0] + largest1[1] + largest1[2];
        }

        return std::max(returnValue000, std::max(returnValue012, returnValue111));
    }
};


#pragma mark - 2. Fixed 1
// WRONG ANSWER because I didn't judge (1, 2) vs (1, 1, 1).
class Solution2 {
public:
    int maxSumDivThree(const std::vector<int>& nums) {
        auto nums1 = std::priority_queue<int>();
        auto nums2 = std::priority_queue<int>();

        int returnValue = 0;

        for (const auto& num: nums) {
            switch (num % 3) {
                case 0:
                    returnValue += num;
                    break;

                case 1:
                    nums1.push(num);
                    break;

                default:
                    nums2.push(num);
            }
        }

        // This part only judges (1, 2)
        while ((!nums1.empty()) && (!nums2.empty())) {
            returnValue += nums1.top();
            nums1.pop();
            returnValue += nums2.top();
            nums2.pop();
        }

        return returnValue;
    }
};


#pragma mark - 3. Sum and subtract
// Runtime: 36 ms, faster than 85.65% of C++ online submissions for Greatest Sum Divisible by Three.
// Memory Usage: 25 MB, less than 90.46% of C++ online submissions for Greatest Sum Divisible by Three.
class Solution3 {
public:
    int maxSumDivThree(const std::vector<int>& nums) {
        // Smallest numbers with remainder 1 and 2.
        auto nums1 = std::array<int, 2>({INT_MAX, INT_MAX});
        auto nums2 = std::array<int, 2>({INT_MAX, INT_MAX});;

        int returnValue = 0;

        for (const auto& num: nums) {
            returnValue += num;

            switch (num % 3) {
                case 1:
                    if (num < nums1[0]) {
                        nums1[1] = nums1[0];
                        nums1[0] = num;
                    } else {
                        nums1[1] = std::min(nums1[1], num);
                    }
                    break;

                case 2:
                    if (num < nums2[0]) {
                        nums2[1] = nums2[0];
                        nums2[0] = num;
                    } else {
                        nums2[1] = std::min(nums2[1], num);
                    }
                    break;
            }
        }

        switch (returnValue % 3) {
            case 1: {    // Must place in curly braces.
                // Guaranteed to have either a 1 or (2, 2).
                int sum2 = INT_MAX;
                if (nums2[1] != INT_MAX) {
                    sum2 = nums2[0] + nums2[1];
                }
                returnValue -= std::min(nums1[0], sum2);
                break;
            }

            case 2:
                // Guaranteed to have either (1, 1) or a 2.
                int sum1 = INT_MAX;
                if (nums1[1] != INT_MAX) {
                    sum1 = nums1[0] + nums1[1];
                }
                returnValue -= std::min(sum1, nums2[0]);
                break;
        }

        return returnValue;
    }
};


#pragma mark - 4. State machine/DP
/*
 * This solution is too complex: too many edge cases to consider.
 * Maybe I should change the initial values of `sum1` and `sum2`?
 *
 * And to optimize for performance, I could have used a `sums` array that is indexed by `num % 3`.
 */
// Runtime: 38 ms, faster than 72.33% of C++ online submissions for Greatest Sum Divisible by Three.
// Memory Usage: 25 MB, less than 90.46% of C++ online submissions for Greatest Sum Divisible by Three.
class Solution {
public:
    int maxSumDivThree(const std::vector<int>& nums) {
        // Remainder 0, 1, 2.
        int sum0 = 0;
        int sum1 = 0;
        int sum2 = 0;


        for (const auto& num: nums) {
            switch (num % 3) {
                case 0:
                    sum0 += num;
                    if (sum1 > 0) {
                        sum1 += num;
                    }
                    if (sum2 > 0) {
                        sum2 += num;
                    }
                    break;

                case 1: {
                    int newSum0 = (sum2 == 0) ? sum0 : std::max(sum0, sum2 + num);
                    int newSum1 = (sum0 == 0) ? std::max(sum1, num) : std::max(sum1, sum0 + num);
                    int newSum2 = (sum1 == 0) ? sum2 : std::max(sum2, sum1 + num);

                    sum0 = newSum0;
                    sum1 = newSum1;
                    sum2 = newSum2;

                    break;
                }

                default: {
                    int newSum0 = (sum1 == 0) ? sum0 : std::max(sum0, sum1 + num);
                    int newSum1 = (sum2 == 0) ? sum1 : std::max(sum1, sum2 + num);
                    int newSum2 = (sum0 == 0) ? std::max(sum2, num) : std::max(sum2, sum0 + num);

                    sum0 = newSum0;
                    sum1 = newSum1;
                    sum2 = newSum2;

                    break;
                }
            }
        }

        return sum0;
    }
};


void test(const std::vector<int>& nums, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.maxSumDivThree(nums);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << nums << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3,4,4}, 12);
    test({2,6,2,2,7}, 15);
    test({3,6,5,1,8}, 18);
    test({4}, 0);
    test({5}, 0);
    test({5,4}, 9);
    test({5,4,3,2}, 12);
    test({8,7,2,8}, 18);

    return 0;
}
