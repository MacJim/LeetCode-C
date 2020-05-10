/*
 * 152. Maximum Product Subarray
 * https://leetcode.com/problems/maximum-product-subarray/
 */

/*
 * The subarray contains at least one number.
 */

#include <iostream>
#include <vector>
#include <algorithm>


#pragma mark - Helpers
template <typename T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) {
    os << "[";
    for (const auto& element: v) {
        os << " " << element;
    }
    os << " ]";
    return os;
}


#pragma mark - 1. My solution: cumulative products.
// Runtime: 12 ms, faster than 9.46% of C++ online submissions for Maximum Product Subarray.
// Memory Usage: 12.4 MB, less than 5.00% of C++ online submissions for Maximum Product Subarray.
class Solution1 {
public:
    int maxProduct(std::vector<int>& nums) {
        const auto len = nums.size();
        if (len == 1) {
            return nums.at(0);
        }

        auto maxPositiveResults = std::vector<int>();
        auto minNegativeResults = std::vector<int>();

        for (const auto& num: nums) {
            // First number
            if (maxPositiveResults.empty()) {
                if (num >= 0) {
                    maxPositiveResults.push_back(num);
                    minNegativeResults.push_back(0);
                } else {
                    maxPositiveResults.push_back(0);
                    minNegativeResults.push_back(num);
                }

                continue;
            }

            const auto lastPositiveResult = maxPositiveResults.back();
            const auto lastNegativeResult = minNegativeResults.back();

            if (num >= 0) {
                if (lastPositiveResult == 0) {
                    maxPositiveResults.push_back(num);
                } else {
                    maxPositiveResults.push_back(num * lastPositiveResult);
                }
                minNegativeResults.push_back(num * lastNegativeResult);
            } else {
                if (lastPositiveResult == 0) {
                    minNegativeResults.push_back(num);
                } else {
                    minNegativeResults.push_back(num * lastPositiveResult);
                }
                maxPositiveResults.push_back(num * lastNegativeResult);
            }
        }

        return *std::max_element(maxPositiveResults.begin(), maxPositiveResults.end());
    }
};


#pragma mark - 2. Improved 1
// Runtime: 8 ms, faster than 23.44% of C++ online submissions for Maximum Product Subarray.
// Memory Usage: 11.9 MB, less than 5.00% of C++ online submissions for Maximum Product Subarray.
class Solution {
public:
    int maxProduct(std::vector<int>& nums) {
        const auto len = nums.size();
        if (len == 1) {
            return nums.at(0);
        }

        int returnValue = 0;
        int previousPositive = 0;
        int previousNegative = 0;

        // In this solution, the first number is treated equally as other numbers.
        for (const auto& num: nums) {
            if (num == 0) {
                previousPositive = 0;
                previousNegative = 0;
            } else if (num > 0) {
                previousNegative *= num;
                if (previousPositive == 0) {
                    previousPositive = num;
                } else {
                    previousPositive *= num;
                }

                returnValue = std::max(returnValue, previousPositive);
            } else {
                int newPositive = num * previousNegative;
                if (previousPositive == 0) {
                    previousNegative = num;
                } else {
                    previousNegative = num * previousPositive;
                }
                previousPositive = newPositive;

                returnValue = std::max(returnValue, previousPositive);
            }
        }

        return returnValue;
    }
};


void test(std::vector<int>& testCase) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.maxProduct(testCase);
    std::cout << testCase << " Result: " << result << std::endl;
}


int main() {
    std::vector<int> testCase1 = {2,3,-2,4};
    test(testCase1);    // 6

    std::vector<int> testCase2 = {-2,0,-1};
    test(testCase2);    // 0

    return 0;
}
