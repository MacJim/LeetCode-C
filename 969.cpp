/*
 * 969. Pancake Sorting
 * https://leetcode.com/problems/pancake-sorting/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Find largest number, swap front, swap all
// Runtime: 4 ms, faster than 78.12% of C++ online submissions for Pancake Sorting.
// Memory Usage: 11.1 MB, less than 65.25% of C++ online submissions for Pancake Sorting.
class Solution {
public:
    std::vector<int> pancakeSort(std::vector<int>& arr) {
//        if (arr.size() == 1) {
//            return {};
//        }

        auto returnValue = std::vector<int>();

        for (int num = arr.size(); num > 1; num -= 1) {
            if (arr[num - 1] == num) {
                // No need to move.
                continue;
            }

            auto it = std::find(arr.begin(), arr.end(), num);

            if (it != arr.begin()) {
                returnValue.push_back(std::distance(arr.begin(), it) + 1);    // Note that the return indices start with 1.
                std::reverse(arr.begin(), it + 1);
            }

            returnValue.push_back(num);
            std::reverse(arr.begin(), arr.begin() + num);
        }

        return returnValue;
    }
};


void test(const std::vector<int>& arr) {
    static auto solutionInstance = Solution();

    auto arrCopy = arr;
    auto result = solutionInstance.pancakeSort(arrCopy);

    arrCopy = arr;
    for (const int& i: result) {
        std::reverse(arrCopy.begin(), arrCopy.begin() + i);
    }

    auto sortedArr = arr;
    std::sort(sortedArr.begin(), sortedArr.end());

    if (arrCopy == sortedArr) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << arr << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << arr << ": " << result << " (" << arrCopy << ")" << std::endl;
    }
}


int main() {
    test({3,2,4,1});
    test({3,2,1,5,4});
    test({3,2,1,4});
    test({1,2,3});
    test({5,3,1,4,2,6});

    return 0;
}
