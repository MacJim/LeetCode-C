/*
 * 552. Student Attendance Record II
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <numeric>

//#include "helpers/Operators.hpp"


#pragma mark - 1
// Runtime: 92 ms, faster than 59.54% of C++ online submissions for Student Attendance Record II.
// Memory Usage: 23 MB, less than 48.43% of C++ online submissions for Student Attendance Record II.
/*
 * States:
 *
 * 1. P ending:
 *   1. P: 1
 *   2. A: 4
 *   3. L: 2
 * 2. L ending
 *   1. P: 1
 *   2. A: 4
 *   3. L: 3
 * 3. LL ending
 *   1. P: 1
 *   2. A: 4
 * 4. Contains A, P or A ending
 *   1. P: 4
 *   2. L: 5
 * 5. Contains A, L ending
 *   1. P: 4
 *   2. L: 6
 * 6. Contains A, LL ending
 *   1. P: 4
 */
#define P 0
#define L 1
#define LL 2
#define AP 3
#define AL 4
#define ALL 5

class Solution {
private:
    static std::vector<std::array<int, 6>> states;
    static const int MOD;

    template <typename T>
    inline int accumulateWithMod(const T& arr) {
        int returnValue = 0;
        for (const auto& num: arr) {
            returnValue += num;
            returnValue %= MOD;
        }

        return returnValue;
    }

public:
    int checkRecord(int n) {
        if (states.size() > n) {
            const auto& existingState = states[n];
//            return std::accumulate(existingState.begin(), existingState.end(), 0);
            return accumulateWithMod(existingState);
        }

        for (int i = states.size(); i <= n; i += 1) {
            const auto& lastState = states.back();

            auto currentState = std::array<int, 6>({
                accumulateWithMod(std::vector<int>({lastState[P], lastState[L], lastState[LL]})),
                lastState[P] % MOD,
                lastState[L] % MOD,
                accumulateWithMod(std::vector<int>({lastState[P], lastState[L], lastState[LL], lastState[AP], lastState[AL], lastState[ALL]})),
                lastState[AP] % MOD,
                lastState[AL] % MOD
            });

            states.push_back(currentState);
        }

        const auto& lastState = states.back();
//        return std::accumulate(lastState.begin(), lastState.end(), 0);
        return accumulateWithMod(lastState);
    }
};

std::vector<std::array<int, 6>> Solution::states = std::vector<std::array<int, 6>>({std::array<int, 6>(), std::array<int, 6>({1, 1, 0, 1, 0, 0})});    // Index 0 is all 0.
const int Solution::MOD = pow(10, 9) + 7;


void test(const int n, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.checkRecord(n);

    if (result == expectedResult) {
        std::cout << "[Correct] " << n << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << n << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(2, 8);
    test(100, 985598218);

    return 0;
}
