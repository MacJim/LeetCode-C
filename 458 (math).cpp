/*
 * 458. Poor Pigs
 * https://leetcode.com/problems/poor-pigs/
 */

/*
 * - Note: Need additional pigs after one died of poison
 */

/*
 * - Equal length segments
 * - No pig drinks from the final segment
 * - Sacrifice more than 1 pig to achieve more segments, but less remaining pigs
 *   - Recursion to find the best combination
 */

#include <iostream>
#include <array>
#include <unordered_map>
#include <climits>
//#include <exception>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Recursion
// WRONG ANSWER
class Solution1 {
private:
    /// (test count, (bucket count, pig count))
    static std::unordered_map<int, std::unordered_map<int, int>> resultsCache;

private:
    int poorPigs(const int buckets, const int testCount) {
        // Edge case: 1 bucket, no pig needed.
        if (buckets == 1) {
            return 0;
        }

        // Edge case: No tests remaining.
        if (testCount == 0) {
            return INT_MAX;
        }

        // Trivial case: 2 buckets.
        if (buckets == 2) {
            return 1;
        }

        // Search in result cache.
        if (resultsCache[testCount].count(buckets)) {
            return resultsCache[testCount][buckets];
        }

        // Pig count: Count from 2, as 1 is handled by the "trivial case" above.
        int pigCount = 2;
        bool feasible = false;

        while (true) {
            // Try all possible overlap/sacrificed pig counts.
            for (int overlapCount = 0; overlapCount < pigCount; overlapCount += 1) {
                const int sacrificedPigs = overlapCount + 1;
                const int segmentsCount = pigCount + sacrificedPigs;
                const int segmentLength = (buckets / segmentsCount) + ((buckets % segmentsCount) != 0);    // Ceil up the result.

                const int nextResult = poorPigs(segmentLength, testCount - 1);
                const int remainingPigs = pigCount - sacrificedPigs;
                if (nextResult <= remainingPigs) {
                    feasible = true;
                    break;
                }
            }

            if (feasible) {
                break;
            }
            pigCount += 1;
        }

        // Store in result cache.
        resultsCache[testCount][buckets] = pigCount;

        return pigCount;
    }

public:
    int poorPigs(const int buckets, const int minutesToDie, const int minutesToTest) {
        const int testCount = minutesToTest / minutesToDie;

        return poorPigs(buckets, testCount);
    }
};

auto Solution1::resultsCache = std::unordered_map<int, std::unordered_map<int, int>>();


#pragma mark - 2. Like bitmap: n pigs: 2^n permutations
class Solution2 {
private:
    /// 2 ** 10 is 1024, larger than our bucket constraint 1000.
    static constexpr int MAX_PIG_COUNT = 10;

    /// Power of 2, up to 10.
    static std::array<int, MAX_PIG_COUNT + 1> powerOfTwo;

private:
    int poorPigs(const int buckets, const int testCount) {
        // Edge case: 1 bucket, no pig needed.
        if (buckets == 1) {
            return 0;
        }

        // Edge case: No tests remaining.
        if (testCount == 0) {
            return INT_MAX;
        }

        // Trivial case: Only 1 test allowed: `2^pigCount` permutations
        if (testCount == 1) {
            for (int pigCount = 1; ; pigCount += 1) {    // No need to check for `pigCount <= MAX_PIG_COUNT` because the upper bound of `buckets` is 1000.
                if (powerOfTwo[pigCount] >= buckets) {
                    return pigCount;
                }
            }
        }

        // Pig count.
        for (int pigCount = 1; ; pigCount += 1) {    // No need to check for `pigCount <= MAX_PIG_COUNT` because the upper bound of `buckets` is 1000.
            for (int sacrificedPigCount = 1; sacrificedPigCount <= pigCount; sacrificedPigCount += 1) {
                const int permutations = powerOfTwo[sacrificedPigCount];
                const int segmentLength = (buckets / permutations) + ((buckets % permutations) != 0);

                const int nextResult = poorPigs(segmentLength, testCount - 1);
                const int remainingPigCount = pigCount - sacrificedPigCount;
                if (nextResult <= remainingPigCount) {
                    return pigCount;
                }
            }
        }
    }

public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        const int testCount = minutesToTest / minutesToDie;

        return poorPigs(buckets, testCount);
    }
};

std::array<int, 11> Solution2::powerOfTwo = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};


#pragma mark - 3. Permutations
/*
 * Find minimum `pigCount` where `(testCount + 1) ^ pigCount >= buckets`
 */
// Runtime: 3 ms, faster than 6.43% of C++ online submissions for Poor Pigs.
// Memory Usage: 5.9 MB, less than 97.66% of C++ online submissions for Poor Pigs.
class Solution {
private:
    // Too bad that `exp` isn't a compile-time constant :(
//    template<int exp>
//    constexpr int intPow(const int base) {
//        if constexpr (exp == 0) {
//            return 1;
//        }
//        if constexpr (exp == 1) {
//            return base;
//        }
//
//        int returnValue = intPow<exp / 2>(base);    // Dividing power by 2 is more efficient than -1.
//        returnValue *= returnValue;
//        if constexpr ((exp % 2) != 0) {
//            returnValue *= base;
//        }
//
//        return returnValue;
//    }

    int intPow(const int base, const int exp) {
        if (exp == 0) {
            return 1;
        }
        if (exp == 1) {
            return base;
        }

        int returnValue = intPow(base, exp / 2);
        returnValue *= returnValue;
        if (exp % 2) {
            returnValue *= base;
        }

        return returnValue;
    }

public:
    int poorPigs(const int buckets, const int minutesToDie, const int minutesToTest) {
        // Trivial case.
        if (buckets == 1) {
            return 0;
        }

        const int testCount = minutesToTest / minutesToDie;

        for (int pigCount = 1; ; pigCount += 1) {
            if (intPow(testCount + 1, pigCount) >= buckets) {
                return pigCount;
            }
        }
    }
};


void test(const int buckets, const int minutesToDie, const int minutesToTest, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.poorPigs(buckets, minutesToDie, minutesToTest);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << buckets << ", " << minutesToDie << ", " << minutesToTest << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << buckets << ", " << minutesToDie << ", " << minutesToTest << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(1, 1, 1, 0);

    test(4, 15, 15, 2);
    test(4, 15, 30, 2);

    test(12, 15, 15, 4);
    test(16, 15, 15, 4);
    test(34, 15, 15, 6);
    test(100, 15, 15, 7);

    test(3, 15, 30, 1);    // Does "minimum amount" assume the best-case scenario (where no pigs die)? No. Assume that pigs die randomly (includes the worst case).
    test(5, 15, 30, 2);
    test(9, 15, 30, 2);
    test(17, 15, 30, 3);
    test(34, 15, 30, 4);
    test(100, 15, 45, 4);
    test(1000, 15, 60, 5);

    return 0;
}
