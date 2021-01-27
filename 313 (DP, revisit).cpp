/*
 * 313. Super Ugly Number
 * https://leetcode.com/problems/super-ugly-number/
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <set>

#include "helpers/Operators.hpp"


#pragma mark - 1. Unfinished (promising, but too complicated to implement)
/*
 * 1. Primes to power
 * 2. Primes multiplied by a number in prime
 */
class Solution1 {
public:
    int nthSuperUglyNumber(int n, std::vector<int>& primes) {
        const size_t primeToPowerIndex = 0;

        auto primeMultipliedIndices = std::vector<size_t>();
        for (size_t i = 1; i <= primes.size(); i += 1) {
            primeMultipliedIndices.push_back(i * primes.size());
        }

        const size_t cacheLen = primeMultipliedIndices.back() + primes.size();

        auto cache = std::vector<int>(cacheLen, 0);

        // Initial values.
        for (size_t i = 0; i < primes.size(); i += 1) {
            cache[primeToPowerIndex + i] = primes[i];
        }
        for (size_t i = 0; i < primes.size(); i += 1) {
            for (size_t j = 0; j < primes.size(); j += 1) {
                if (i != j) {
                    cache[primeMultipliedIndices[i] + j] = primes[i] * primes[j];
                }
            }
        }

        return 0;
    }
};


#pragma mark - 2. Easier 1 (unfinished)
class Solution2 {
public:
    int nthSuperUglyNumber(int n, std::vector<int>& primes) {
        auto powerCache = primes;

        // Initial values.
        auto multipliedCache = std::vector<std::vector<int>>(primes.size(), std::vector<int>(0, primes.size() - 1));
        for (size_t outerIndex = 0; outerIndex < primes.size(); outerIndex += 1) {
            for (size_t j = 0; j < primes.size(); j += 1) {
                if (j == outerIndex) {
                    continue;
                }
                const auto innerIndex = (j > outerIndex) ? (j - 1) : j;
                multipliedCache[outerIndex][innerIndex] = primes[outerIndex] * primes[j];
            }
        }

        return 0;
    }
};


#pragma mark - 3. Brute force
// Time Limit Exceeded
class Solution3 {
public:
    int nthSuperUglyNumber(int n, std::vector<int>& primes) {
        auto products = std::vector<int>({1});

        for (int i = 1; i < n; i += 1) {
            int smallestProduct = INT_MAX;

            for (const auto& existingNum: products) {
                for (const auto& prime: primes) {
                    const int currentProduct = existingNum * prime;
                    if (currentProduct <= products.back()) {
                        /*
                         * - Equal: Duplicate with the last product
                         * - Smaller: Must exist before the last product
                         */
                        continue;
                    }

                    smallestProduct = std::min(currentProduct, smallestProduct);
                }
            }

            products.push_back(smallestProduct);
        }

        return products.back();
    }
};


#pragma mark - 4. Combine 1 and 3
/*
 * Multiply each number in `primes` by 1 and each number in `primes`.
 */
// Apparently too slow.
class Solution4 {
public:
    int nthSuperUglyNumber(int n, std::vector<int>& primes) {
        auto products = std::vector<int>({1});
//        auto productsCache = std::vector<int>(primes.size() + 1, );    // Index 0 is multiplied by 1.

        auto productsCache = std::set<int>(primes.begin(), primes.end());
        while (products.size() < n) {
            auto smallestIt = productsCache.begin();
            if (*smallestIt <= products.back()) {
                continue;
            }

            for (const auto& prime: primes) {
                const int newNum = (*smallestIt) * prime;
                productsCache.insert(newNum);
            }

            products.push_back(*smallestIt);
            productsCache.erase(smallestIt);
        }

        return products.back();
    }
};


#pragma mark - 5. LeetCode discussion solution: Re-use the generated ugly numbers to multiply the provided prime numbers (revisit)
// Code: https://leetcode.com/problems/super-ugly-number/discuss/76298/7-line-consice-O(kn)-c%2B%2B-solution
// Explanation: https://leetcode.com/problems/super-ugly-number/discuss/277313/My-view-of-this-question-hope-it-can-help-you-understand
// Runtime: 128 ms, faster than 52.05% of C++ online submissions for Super Ugly Number.
// Memory Usage: 8.8 MB, less than 92.64% of C++ online submissions for Super Ugly Number.
class Solution {
public:
    int nthSuperUglyNumber(int n, std::vector<int>& primes) {
        /**
         * Multiply `prime[i]` with a generated ugly number `uglyNums[primeIndices[i]]`.
         *
         * Of course in the first iteration, we multiply our prime numbers with `uglyNums[0] = 1`.
         */
        auto primeIndices = std::vector<int>(primes.size(), 0);

        auto uglyNums = std::vector<int>(n, INT_MAX);
        uglyNums[0] = 1;

        for (int i = 1; i < n; i += 1) {
            for (int j = 0; j < primes.size(); j += 1) {
                uglyNums[i] = std::min(uglyNums[i], uglyNums[primeIndices[j]] * primes[j]);
            }

            // Handles multiple/duplicate min values.
            for (int j = 0; j < primes.size(); j += 1) {
                primeIndices[j] += (uglyNums[i] == uglyNums[primeIndices[j]] * primes[j]);
            }
        }

        return uglyNums.back();
    }
};


void test(const int n, const std::vector<int>& primes, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto primesCopy = primes;
    auto result = solutionInstance.nthSuperUglyNumber(n, primesCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << n << " " << primes << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << n << " " << primes << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(12, {2, 7, 13, 19}, 32);
    test(4, {2}, 8);
    test(100000, {7,19,29,37,41,47,53,59,61,79,83,89,101,103,109,127,131,137,139,157,167,179,181,199,211,229,233,239,241,251}, 1092889481);

    return 0;
}
