/*
 * 935. Knight Dialer
 * https://leetcode.com/problems/knight-dialer/
 */

#include <iostream>
#include <array>

#include "helpers/terminal_format.h"


#pragma mark - 1. Prototype DP, no caching
class Solution1 {
private:
    static constexpr int MOD = 1000000007;
    static constexpr int NUMS_COUNT = 10;
    std::array<int, NUMS_COUNT> currentCounts {1,1,1,1,1,1,1,1,1,1};

public:
    int knightDialer(int n) {
        for (; n > 1; n -= 1) {
            auto newCounts = std::array<int, 10>();  // Default initialized to 0.
            newCounts[0] = currentCounts[4] + currentCounts[6];
            newCounts[1] = currentCounts[6] + currentCounts[8];
            newCounts[2] = currentCounts[7] + currentCounts[9];
            newCounts[3] = currentCounts[4] + currentCounts[8];
            newCounts[4] = (currentCounts[0] + currentCounts[3]) % MOD + currentCounts[9];  // Well, we can overflow in every step.
            // 5 is unreachable.
            newCounts[6] = (currentCounts[0] + currentCounts[1]) % MOD + currentCounts[7];
            newCounts[7] = currentCounts[2] + currentCounts[6];
            newCounts[8] = currentCounts[1] + currentCounts[3];
            newCounts[9] = currentCounts[2] + currentCounts[4];

            for (int i = 0; i < NUMS_COUNT; i += 1) {
                newCounts[i] %= MOD;
            }

            currentCounts = newCounts;
        }

        int returnValue = 0;
        for (int i = 0; i < NUMS_COUNT; i += 1) {
            returnValue += currentCounts[i];
            returnValue %= MOD;
        }

        return returnValue;
    }
};


#pragma mark - 2. 1 with cache
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Knight Dialer.
// Memory Usage: 6.3 MB, less than 87.22% of C++ online submissions for Knight Dialer.
class Solution {
public:
    static constexpr int MOD = 1000000007;
    static constexpr int MAX_STEPS = 5000;
    static constexpr int NUMS_COUNT = 10;
    /**
     * Hmm will this cause stack overflow?
     * Does LeetCode allocate `Solution` instances on the stack?
     */
    static std::array<std::array<int, NUMS_COUNT>, MAX_STEPS> allCounts;

public:
    int knightDialer(int n) {
        // Calculate all 5000 results up front.
        if (allCounts.front().front() == 0) {  // Default initialized to 0.
            allCounts[0] = {1,1,1,1,1,1,1,1,1,1};

            for (int i = 1; i < MAX_STEPS; i += 1) {
                const auto& currentCounts = allCounts[i - 1];
                auto& newCounts = allCounts[i];

                newCounts[0] = currentCounts[4] + currentCounts[6];
                newCounts[1] = currentCounts[6] + currentCounts[8];
                newCounts[2] = currentCounts[7] + currentCounts[9];
                newCounts[3] = currentCounts[4] + currentCounts[8];
                newCounts[4] = (currentCounts[0] + currentCounts[3]) % MOD + currentCounts[9];  // Well, we can overflow in every step.
                // 5 is unreachable.
                newCounts[6] = (currentCounts[0] + currentCounts[1]) % MOD + currentCounts[7];
                newCounts[7] = currentCounts[2] + currentCounts[6];
                newCounts[8] = currentCounts[1] + currentCounts[3];
                newCounts[9] = currentCounts[2] + currentCounts[4];

                for (int j = 0; j < NUMS_COUNT; j += 1) {
                    newCounts[j] %= MOD;
                }
            }
        }

        const auto& currentCounts = allCounts[n - 1];
        int returnValue = 0;
        for (int i = 0; i < NUMS_COUNT; i += 1) {
            returnValue += currentCounts[i];
            returnValue %= MOD;
        }

        return returnValue;
    }
};


std::array<std::array<int, Solution::NUMS_COUNT>, Solution::MAX_STEPS> Solution::allCounts {};


void test(const int n, const int expectedResult) {
//    auto solutionInstance = Solution();  // Solution 1
    static auto solutionInstance = Solution();  // Solution 2

    auto result = solutionInstance.knightDialer(n);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << n << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << n << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(1, 10);
    test(2, 20);
    test(3, 46);
    test(3131, 136006598);
    test(3200, 408535055);
    test(5000, 406880451);

    return 0;
}
