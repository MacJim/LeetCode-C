/*
 * 1640. Check Array Formation Through Concatenation
 * https://leetcode.com/problems/check-array-formation-through-concatenation/
 */

/*
 * Note the constraints of this problem.
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Check Array Formation Through Concatenation.
// Memory Usage: 10.2 MB, less than 80.72% of C++ online submissions for Check Array Formation Through Concatenation.
class Solution {
public:
    bool canFormArray(std::vector<int>& arr, std::vector<std::vector<int>>& pieces) {
        size_t i = 0;
        while (i < arr.size()) {
            bool matchFound = false;
            for (const auto& piece: pieces) {
                if (piece[0] == arr[i]) {
                    // 0th number match.
                    // Further numbers must also match.
                    size_t j = 0;
                    for (; j < piece.size(); j += 1) {
                        if (piece[j] != arr[i + j]) {
                            return false;
                        }
                    }

                    matchFound = true;
                    i += j;

                    break;
                }
            }

            if (!matchFound) {
                return false;
            }
        }

        return (i >= arr.size());
    }
};


#pragma mark - 2. May use an unordered map to store the first number of each piece (don't think this is needed)


void test(const std::vector<int>& arr, const std::vector<std::vector<int>>& pieces, const bool expectedResult) {
    static auto solutionInstance = Solution();

    auto arrCopy = arr;
    auto piecesCopy = pieces;
    auto result = solutionInstance.canFormArray(arrCopy, piecesCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << arr << " " << pieces << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << arr << " " << pieces << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({85}, {{85}}, true);
    test({15, 88}, {{88}, {15}}, true);
    test({49,18,16}, {{16,18,49}}, false);
    test({91,4,64,78}, {{78},{4,64},{91}}, true);
    test({1,3,5,7}, {{2,4,6,8}}, false);

    return 0;
}
