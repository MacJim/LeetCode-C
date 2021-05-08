/*
 * 209. Minimum Size Subarray Sum
 * https://leetcode.com/problems/minimum-size-subarray-sum/
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <exception>
#include <climits>

#include "helpers/Operators.hpp"


#pragma mark - 1. Cumulated sums delta
// Runtime: 424 ms, faster than 6.59% of C++ online submissions for Minimum Size Subarray Sum.
// Memory Usage: 10.6 MB, less than 59.17% of C++ online submissions for Minimum Size Subarray Sum.
class Solution1 {
public:
    int minSubArrayLen(const int target, std::vector<int>& nums) {
        // Impossible. Return 0.
        auto totalSum = std::accumulate(nums.begin(), nums.end(), 0);
        if (totalSum < target) {
            return 0;
        } else if (totalSum == target) {
            return nums.size();
        }

        // A single number.
        for (const auto& n: nums) {
            if (n >= target) {
                return 1;
            }
        }

        // Multiple numbers.
        /// sums[0] is always a dummy value of 0.
        auto sums = std::vector<int>(nums.size() + 1, 0);
        sums[1] = nums[0];
        for (size_t i = 1; i < nums.size(); i += 1) {
            sums[i + 1] = sums[i] + nums[i];
        }

        for (int distance = 2; distance < sums.size(); distance += 1) {
            for (size_t i = (sums.size() - 1); i >= distance; i -= 1) {
                const int currentSum = sums[i] - sums[i - distance];
                if (currentSum >= target) {
                    return distance;
                }
            }
        }

        throw std::runtime_error("Should never reach here.");
    }
};


#pragma mark - 2. 2 pointers
// WRONG ANSWER: Cannot simply select the end with a larger number (see 12, {9,1,1,1,1,1,1,1,4,4,4} test case)
class Solution2 {
public:
    int minSubArrayLen(int target, std::vector<int>& nums) {
        // Impossible. Return 0.
        auto totalSum = std::accumulate(nums.begin(), nums.end(), 0);
        if (totalSum < target) {
            return 0;
        } else if (totalSum == target) {
            return nums.size();
        }

        // A single number.
        for (const auto& n: nums) {
            if (n >= target) {
                return 1;
            }
        }

        // Multiple numbers.
        auto sums = std::vector<int>(nums.size() + 1, 0);
        sums[1] = nums[0];
        for (size_t i = 1; i < nums.size(); i += 1) {
            sums[i + 1] = sums[i] + nums[i];
        }

        auto start = 0;
        auto end = sums.size() - 1;

        int returnValue = nums.size();

        while (start < end) {
            const int currentSum = sums[end] - sums[start];
            if (currentSum >= target) {
                returnValue = end - start;

                if (nums[start] == nums[end - 1]) {
                    // The array is symmetric on the outer rim.
                    // Dig into the inner rim to determine with side to remove.
                    auto innerStart = start;
                    auto innerEnd = end;
                    while ((innerStart < innerEnd) && (nums[innerStart] == nums[innerEnd - 1])) {
                        innerStart += 1;
                        innerEnd -= 1;
                    }

                    if (innerStart >= innerEnd) {
                        // The array is fully symmetric.
                        // We can remove from either end.
                        start += 1;
                    } else if (nums[innerStart] > nums[innerEnd - 1]) {
                        end -= 1;
                    } else {
                        start += 1;
                    }
                } else if (nums[start] < nums[end - 1]) {
                    start += 1;
                } else {
                    end -= 1;
                }
            } else {
                break;
            }
        }

        return returnValue;
    }
};


#pragma mark - 3. Improves 1 using binary search, resulting in O(n logn) instead of O(n^2) (revisit)
/*
 * Keep start fixed, and search for end using binary search.
 *
 * Just keep in mind that binary search can also be used to search for upper/lower bounds.
 */
// Runtime: 8 ms, faster than 68.73% of C++ online submissions for Minimum Size Subarray Sum.
// Memory Usage: 10.7 MB, less than 16.25% of C++ online submissions for Minimum Size Subarray Sum.
class Solution3 {
private:
    /**
     * Find the end index lower bound for a given start index.
     *
     * @param target
     * @param sums
     * @param subtractionIndex
     * @return The lower bound's end index; -1 otherwise (if `target` is too big).
     */
    inline int searchForEnd(const int target, const std::vector<int>& sums, size_t subtractionIndex) {
        const int& subtractedValue = sums[subtractionIndex];

        if ((sums.back() - subtractedValue) < target) {
            return -1;
        }

        int start = subtractionIndex + 1;
        int end = sums.size() - 1;

        while (start < end) {
            const int mid = (start + end) / 2;
            const int currentValue = sums[mid] - subtractedValue;

            if (currentValue == target) {
                return mid;
            } else if (currentValue > target) {
                end = mid;
            } else {
                // Start must be `mid + 1` because the current value is smaller and should not be returned.
                start = mid + 1;
            }
        }

        return start;
    }

public:
    int minSubArrayLen(const int target, std::vector<int>& nums) {
        // Impossible. Return 0.
        auto totalSum = std::accumulate(nums.begin(), nums.end(), 0);
        if (totalSum < target) {
            return 0;
        } else if (totalSum == target) {
            return nums.size();
        }

        // A single number.
        for (const auto& n: nums) {
            if (n >= target) {
                return 1;
            }
        }

        // Multiple numbers.
        /// sums[0] is always a dummy value of 0.
        auto sums = std::vector<int>(nums.size() + 1, 0);
        sums[1] = nums[0];
        for (size_t i = 1; i < nums.size(); i += 1) {
            sums[i + 1] = sums[i] + nums[i];
        }

        auto returnValue = nums.size();
        for (size_t i = 0; i < (sums.size() - 1); i += 1) {
            int end = searchForEnd(target, sums, i);
            if (end == -1) {
                break;
            } else {
                returnValue = std::min(returnValue, end - i);
            }
        }

        return returnValue;
    }
};


#pragma mark - 4. 2 pointers: slow and fast pointers (revisit)
// Runtime: 4 ms, faster than 97.14% of C++ online submissions for Minimum Size Subarray Sum.
// Memory Usage: 10.5 MB, less than 92.53% of C++ online submissions for Minimum Size Subarray Sum.
class Solution {
public:
    int minSubArrayLen(int target, std::vector<int>& nums) {
        // Impossible. Return 0.
        auto totalSum = std::accumulate(nums.begin(), nums.end(), 0);
        if (totalSum < target) {
            return 0;
        } else if (totalSum == target) {
            return nums.size();
        }

        int returnValue = INT_MAX;

        // [start, end)
        int start = 0;
        int end = 1;
        int currentSum = nums[0];
        while (end <= nums.size()) {
            if (currentSum >= target) {
                returnValue = std::min(returnValue, end - start);

                currentSum -= nums[start];
                start += 1;
            } else {
                if (end == nums.size()) {
                    break;
                }

                currentSum += nums[end];
                end += 1;
            }
        }

        return returnValue;
    }
};


void test(const int target, const std::vector<int>& nums, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto numsCopy = nums;
    auto result = solutionInstance.minSubArrayLen(target, numsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << target << ", " << nums << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << target << ", " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(12, {9,1,1,1,1,1,1,1,4,4,4}, 3);
    test(7, {2,3,1,2,4,3}, 2);
    test(15, {2,14}, 2);
    test(5, {2,3,1,1,1,1,1}, 2);
    test(15, {1,2,3,4,5}, 5);
    test(4, {1,4,4}, 1);
    test(11, {1,1,1,1,1,1,1,1,1,1}, 0);
    test(3, {3,2,1,2,3}, 1);
    test(5, {3,2,1,2,3}, 2);
    test(6, {3,2,1,2,3}, 3);
    test(3, {3,2,1,1,2,3}, 1);
    test(5, {3,2,1,1,2,3}, 2);
    test(6, {3,2,1,1,2,3}, 3);

    test(697439, {5334,6299,4199,9663,8945,3566,9509,3124,6026,6250,7475,5420,9201,9501,38,5897,4411,6638,9845,161,9563,8854,3731,5564,5331,4294,3275,1972,1521,2377,3701,6462,6778,187,9778,758,550,7510,6225,8691,3666,4622,9722,8011,7247,575,5431,4777,4032,8682,5888,8047,3562,9462,6501,7855,505,4675,6973,493,1374,3227,1244,7364,2298,3244,8627,5102,6375,8653,1820,3857,7195,7830,4461,7821,5037,2918,4279,2791,1500,9858,6915,5156,970,1471,5296,1688,578,7266,4182,1430,4985,5730,7941,3880,607,8776,1348,2974,1094,6733,5177,4975,5421,8190,8255,9112,8651,2797,335,8677,3754,893,1818,8479,5875,1695,8295,7993,7037,8546,7906,4102,7279,1407,2462,4425,2148,2925,3903,5447,5893,3534,3663,8307,8679,8474,1202,3474,2961,1149,7451,4279,7875,5692,6186,8109,7763,7798,2250,2969,7974,9781,7741,4914,5446,1861,8914,2544,5683,8952,6745,4870,1848,7887,6448,7873,128,3281,794,1965,7036,8094,1211,9450,6981,4244,2418,8610,8681,2402,2904,7712,3252,5029,3004,5526,6965,8866,2764,600,631,9075,2631,3411,2737,2328,652,494,6556,9391,4517,8934,8892,4561,9331,1386,4636,9627,5435,9272,110,413,9706,5470,5008,1706,7045,9648,7505,6968,7509,3120,7869,6776,6434,7994,5441,288,492,1617,3274,7019,5575,6664,6056,7069,1996,9581,3103,9266,2554,7471,4251,4320,4749,649,2617,3018,4332,415,2243,1924,69,5902,3602,2925,6542,345,4657,9034,8977,6799,8397,1187,3678,4921,6518,851,6941,6920,259,4503,2637,7438,3893,5042,8552,6661,5043,9555,9095,4123,142,1446,8047,6234,1199,8848,5656,1910,3430,2843,8043,9156,7838,2332,9634,2410,2958,3431,4270,1420,4227,7712,6648,1607,1575,3741,1493,7770,3018,5398,6215,8601,6244,7551,2587,2254,3607,1147,5184,9173,8680,8610,1597,1763,7914,3441,7006,1318,7044,7267,8206,9684,4814,9748,4497,2239}, 132);

    return 0;
}
