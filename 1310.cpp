/*
 * 1310. XOR Queries of a Subarray
 * https://leetcode.com/problems/xor-queries-of-a-subarray/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Prefix sum
/*
 * num ^ num = 0
 */
// Runtime: 76 ms, faster than 86.21% of C++ online submissions for XOR Queries of a Subarray.
// Memory Usage: 37.7 MB, less than 92.84% of C++ online submissions for XOR Queries of a Subarray.
class Solution {
public:
    std::vector<int> xorQueries(const std::vector<int>& arr, const std::vector<std::vector<int>>& queries) {
        auto prefixXors = std::vector<int>(arr.size() + 1, 0);
        int currentXor = 0;
        for (int i = 0; i < arr.size(); i += 1) {
            currentXor ^= arr[i];
            prefixXors[i + 1] = currentXor;
        }

        auto returnValue = std::vector<int>(queries.size(), 0);
        for (int i = 0; i < queries.size(); i += 1) {
            returnValue[i] = prefixXors[queries[i][1] + 1] ^ prefixXors[queries[i][0]];
        }

        return returnValue;
    }
};


void test(const std::vector<int>& arr, const std::vector<std::vector<int>>& queries, const std::vector<int>& expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.xorQueries(arr, queries);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << arr << ", " << queries << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << arr << ", " << queries << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,3,4,8}, {{0,1},{1,2},{0,3},{3,3}}, {2,7,14,8});
    test({4,8,2,10}, {{2,3},{1,3},{0,0},{0,3}}, {8,0,4,4});

    return 0;
}
