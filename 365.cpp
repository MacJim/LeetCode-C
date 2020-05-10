/*
 * 365. Water and Jug Problem
 * https://leetcode.com/problems/water-and-jug-problem/
 */

/*
 * This is a math problem.
 * ax + by = c
 * Bézout's identity
 */

#include <iostream>
#include <numeric>


// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Water and Jug Problem.
// Memory Usage: 5.9 MB, less than 100.00% of C++ online submissions for Water and Jug Problem.
class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        // We may use "Bézout's identity" only if we have enough capacity to hold the water.
        if ((x + y) < z) {
            return false;
        }

        if ((x == z) || (y == z) || ((x + y) == z)) {
            return true;
        }

        const auto gcd = std::gcd(x, y);
        return (z % gcd == 0);
    }
};


void test(int x, int y, int z) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.canMeasureWater(x, y, z);
    std::cout << "(" << x << ", " << y << ", " << z << "): " << result << std::endl;
}

int main() {
    test(3, 5, 4);    // true
    test(2, 6, 5);    // false
    test(4, 6, 8);    // true

    return 0;
}

