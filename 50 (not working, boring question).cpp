/*
 * 50. Pow(x, n)
 * https://leetcode.com/problems/powx-n/
 */

#include <iostream>


class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) {
            return 1;
        }
        if (n == 1) {
            return x;
        }
        if (n < 0) {
            return myPow(1 / x, -n);    // FIXME: Minus n results in an overflow when n is INT_MIN.
        }
        if (n % 2 == 0) {
            return myPow(x * x, n / 2);
        }
        return x * myPow(x * x, n / 2);
    }
};

int main() {
    auto solutionInstance = Solution();
    std::cout << solutionInstance.myPow(2, 4) << std::endl;
    std::cout << solutionInstance.myPow(2, -4) << std::endl;
    return 0;
}
