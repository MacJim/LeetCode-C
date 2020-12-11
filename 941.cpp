/*
 * 941. Valid Mountain Array
 * https://leetcode.com/problems/valid-mountain-array/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


// Runtime: 48 ms, faster than 90.66% of C++ online submissions for Valid Mountain Array.
// Memory Usage: 22.7 MB, less than 77.82% of C++ online submissions for Valid Mountain Array.
class Solution {
public:
    bool validMountainArray(std::vector<int>& arr) {
        if (arr.size() < 3) {
            return false;
        }

        int front = 0;
        int back = arr.size() - 1;

        for (; front < arr.size(); front += 1) {
            if (arr[front] >= arr[front + 1]) {
                break;
            }
        }
        if (front >= (arr.size() - 1)) {
            return false;
        }

        for (; back > 0; back -= 1) {
            if (arr[back - 1] <= arr[back]) {
                break;
            }
        }
        if (back <= 0) {
            return false;
        }

        return (back == front);
    }
};


void test(const std::vector<int>& arr, const bool expectedResult) {
    static auto solutionInstance = Solution();

    auto arrCopy = arr;
    auto result = solutionInstance.validMountainArray(arrCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << arr << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << arr << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({0,1,2,3,4,5,6,7,8,9}, false);
    test({9,8,7,6,5,4,3,2,1,0}, false);
    test({2, 1}, false);
    test({3, 5, 5}, false);
    test({0, 3, 2, 1}, true);
    test({0,2,3,4,5,2,1,0}, true);
    test({0,2,3,3,5,2,1,0}, false);

    return 0;
}
