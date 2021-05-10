/*
 * 718. Maximum Length of Repeated Subarray
 * https://leetcode.com/problems/maximum-length-of-repeated-subarray/
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <random>

#include "helpers/Operators.hpp"


#pragma mark - 1. DP
// Runtime: 212 ms, faster than 58.76% of C++ online submissions for Maximum Length of Repeated Subarray.
// Memory Usage: 11.9 MB, less than 86.62% of C++ online submissions for Maximum Length of Repeated Subarray.
class Solution {
public:
    int findLength(std::vector<int>& nums1, std::vector<int>& nums2) {
        auto previousRow = std::vector<int>(nums1.size(), 0);
        auto currentRow = std::vector<int>(nums1.size(), 0);

        int returnValue = 0;

        // 0th row.
        for (size_t i1 = 0; i1 < nums1.size(); i1 += 1) {
            if (nums1[i1] == nums2[0]) {
                previousRow[i1] = 1;
                returnValue = 1;
            }
        }

        // Upcoming rows.
        for (size_t i2 = 1; i2 < nums2.size(); i2 += 1) {
            if (nums1[0] == nums2[i2]) {
                currentRow[0] = 1;
                returnValue = std::max(returnValue, 1);
            } else {
                currentRow[0] = 0;
            }

            for (size_t i1 = 1; i1 < nums1.size(); i1 += 1) {
                if (nums1[i1] == nums2[i2]) {
                    currentRow[i1] = previousRow[i1 - 1] + 1;
                    returnValue = std::max(returnValue, currentRow[i1]);
                } else {
                    currentRow[i1] = 0;
                }
            }

            std::swap(previousRow, currentRow);
        }

        return returnValue;
    }
};


void test(const std::vector<int>& nums1, const std::vector<int>& nums2, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto nums1Copy = nums1;
    auto nums2Copy = nums2;
    auto result = solutionInstance.findLength(nums1Copy, nums2Copy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << nums1 << " " << nums2 << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << nums1 << " " << nums2 << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


void testRandom(const size_t numsLength, const size_t subArrayLength) {
    const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto generator = std::default_random_engine(seed);

    auto distribution1 = std::uniform_int_distribution<int>(0, 49);    // This is a closed interval.
    auto dice1 = std::bind(distribution1, generator);
    auto nums1 = std::vector<int>(numsLength, 0);
    std::generate(nums1.begin(), nums1.end(), dice1);
//    std::cout << nums1 << std::endl;

    auto distribution2 = std::uniform_int_distribution<int>(50, 100);
    auto dice2 = std::bind(distribution2, generator);
    auto nums2 = std::vector<int>(numsLength, 0);
    std::generate(nums2.begin(), nums2.end(), dice2);
//    std::cout << nums2 << std::endl;

    if (subArrayLength > 0) {
        auto sharedDistribution = std::uniform_int_distribution<int>(0, 100);
        auto sharedDice = std::bind(sharedDistribution, generator);
        auto sharedSubArray = std::vector<int>(subArrayLength, 0);
        std::generate(sharedSubArray.begin(), sharedSubArray.end(), sharedDice);

        auto startIndexDistribution = std::uniform_int_distribution<int>(0, numsLength - subArrayLength - 1);
        const auto startIndex1 = startIndexDistribution(generator);
        const auto startIndex2 = startIndexDistribution(generator);

        std::copy(sharedSubArray.begin(), sharedSubArray.end(), nums1.begin() + startIndex1);
        std::copy(sharedSubArray.begin(), sharedSubArray.end(), nums2.begin() + startIndex2);
    }

    test(nums1, nums2, subArrayLength);
}


int main() {
    test({27,26,13,98,73,14,35,45,11,72,6,31,55,80,87,24,81,75,53,22,46,9,22,85,60,87,56,35,12,49,80,33,30,56,29,77,28,99,52,37,82,20,43,62,32,2,3,54,58,10,92,70,5,68,82,86,95,6,73,92,97,7,34,5,78,57,10,70,78,92,81,94,72,62,3,94,57,29,26,48,88,74,76,75,20,94,38,87,22,12,3,12,13,58,62,43,43,74,66,99}, {50,88,0,77,54,73,76,53,17,5,25,42,42,95,31,32,10,54,94,2,65,38,86,70,98,31,27,84,77,78,41,4,81,32,82,92,22,49,6,21,32,8,80,67,12,27,41,16,62,12,45,27,34,39,54,37,24,90,73,54,48,85,3,67,42,52,97,18,69,26,22,80,39,11,47,60,9,58,53,9,91,7,0,29,43,55,55,43,21,13,97,4,98,60,21,78,74,15,23,74}, 1);

    test({1,0,0,0,1,0}, {0,1,1,1,0,1}, 2);
    test({1,0,0,0,1,0,0,1,0,0}, {0,1,1,1,0,1,1,1,0,0}, 3);
    test({1,0,0,0}, {1,0,0,1}, 3);

    test({1,2,3,2,1}, {3,2,1,4,7}, 3);
    test({0,0,0,0,0}, {0,0,0,0,0}, 5);

    for (int i = 0; i < 10; i += 1) {
        testRandom(40, 1);
        testRandom(40, 10);
        testRandom(40, 15);
        testRandom(39, 9);
        testRandom(39, 10);
    }

    testRandom(1000, 99);

    return 0;
}
