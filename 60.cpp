/*
 * 60. Permutation Sequence
 * https://leetcode.com/problems/permutation-sequence/
 */

#include <iostream>
#include <vector>
#include <numeric>
//#include <cmath>
#include <unordered_map>

//#include "helpers/Operators.hpp"


#pragma mark - 1
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Permutation Sequence.
// Memory Usage: 6.1 MB, less than 6.53% of C++ online submissions for Permutation Sequence.
class Solution {
public:
    std::string getPermutation(int n, int k) {
        static const std::unordered_map<int, int> factorials = {{1,1}, {2,2}, {3,6}, {4,24}, {5,120}, {6,720}, {7,5040}, {8,40320}, {9,362880}};

        auto returnValue = std::string();

        auto remainingNums = std::vector<int>(n, 0);
        std::iota(remainingNums.begin(), remainingNums.end(), 1);
//        std::reverse(remainingNums.begin(), remainingNums.end());
//        for (int i = 0; i < n; i += 1) {
//            remainingNums[i] = n - i;
//        }

        k -= 1;
        while ((n > 0) && (k > 0)) {
            auto nextPermutationsCount = factorials.at(n - 1);
            const int currentNumIndex = k / nextPermutationsCount;
            returnValue += (static_cast<char>(remainingNums[currentNumIndex] - 0) + '0');
            remainingNums.erase(remainingNums.begin() + currentNumIndex);

            n -= 1;
            k = k % nextPermutationsCount;
        }

        // Remaining characters.
        for (const int& num: remainingNums) {
            const char c = static_cast<char>(num - 0) + '0';
            returnValue += c;
        }

        return returnValue;
    }
};


void test(const int n, const int k, const std::string& expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.getPermutation(n, k);

    if (result == expectedResult) {
        std::cout << "[Correct] " << n << ", " << k << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << n << ", " << k << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(3, 1, "123");
    test(3, 2, "132");
    test(3, 3, "213");
    test(3, 4, "231");
    test(3, 5, "312");
    test(3, 6, "321");

    test(4, 1, "1234");
    test(4, 2, "1243");
    test(4, 3, "1324");
    test(4, 9, "2314");

    return 0;
}
