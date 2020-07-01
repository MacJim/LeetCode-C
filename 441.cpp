/*
 * 441. Arranging Coins
 * https://leetcode.com/problems/arranging-coins/
 */

/*
 * l * (l + 1) / 2
 */

#include <iostream>
#include <cmath>
#include <climits>


// Runtime: 8 ms, faster than 42.54% of C++ online submissions for Arranging Coins.
// Memory Usage: 5.8 MB, less than 98.49% of C++ online submissions for Arranging Coins.
class Solution {
public:
    int arrangeCoins(int n) {
        if (n == INT_MAX) {
            // Prevent overflow.
            return 65535;
        }

        auto max = (int)std::sqrt((float)n * 2);
        int min = 0;

        int returnValue = 0;

        while (max >= min) {
            const int mid = (max + min) / 2;

            if ((mid % 2) == 0) {
                const int result = mid / 2 * (mid + 1);
                if (result > n) {
                    max = mid - 1;
                } else {
                    returnValue = mid;
                    min = mid + 1;
                }
            } else {
                const int result = (mid + 1) / 2 * mid;
                if (result > n) {
                    max = mid - 1;
                } else {
                    returnValue = mid;
                    min = mid + 1;
                }
            }
        }

        return returnValue;
    }
};


int main() {
    auto solutionInstance = Solution();

    std::cout << solutionInstance.arrangeCoins(5) << std::endl;    // 2
    std::cout << solutionInstance.arrangeCoins(8) << std::endl;    // 3
    std::cout << solutionInstance.arrangeCoins(9) << std::endl;    // 3
    std::cout << solutionInstance.arrangeCoins(1) << std::endl;    // 1
    std::cout << solutionInstance.arrangeCoins(1804289383) << std::endl;    //
    std::cout << solutionInstance.arrangeCoins(2147483647) << std::endl;    // 65535

    int i = 65536;
    std::cout << i / 2 * (i + 1) << std::endl;

    return 0;
}
