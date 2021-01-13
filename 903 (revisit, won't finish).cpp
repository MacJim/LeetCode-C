/*
 * 903. Valid Permutations for DI Sequence
 * https://leetcode.com/problems/valid-permutations-for-di-sequence/
 */

/*
 * Thoughts 1:
 *
 * - Maybe using dp[1:n]
 * - Maybe get dp[n] from dp[n - 1]
 * - This way, the newly introduced number is always the largest
 *     - If the start is `D`, replace start
 *     - If `ID` is anywhere in the middle, replace middle
 */

/*
 * Thoughts 2: Divide into 3 parts: s[:n], s[n], s[n+1:]
 *
 * - No numbers equal each other
 *     - Numbers don't affect permutation count
 */

/*
 * Thoughts 3: Divide into 2 parts: s[:n] and s[n:]
 */

/*
 * Thoughts 4: Special circumstances:
 *
 * - Consecutive D
 * - Consecutive I
 */

#include <iostream>
#include <vector>
#include <string>
#include <cmath>


#pragma mark - 1. Official solution: Place smallest number first
/*
 * Thought 2 is correct and very important.
 *
 * The smallest number goes into:
 *
 * - Start: I
 * - End: D
 * - Middle: DI
 */
class Solution {
private:
    /**
     *
     * @param s The DI string.
     * @param startIndex Inclusive.
     * @param endIndex Inclusive.
     * @param dp The DP array/cache.
     * @param MOD
     * @return
     */
    int subSequence(const std::string& s, int startIndex, int endIndex, std::vector<std::vector<int>>& dp, const int& MOD) {
        if (startIndex >= endIndex) {
            return 1;
        }

        // Use cached value.
        auto& returnValue = dp[startIndex][endIndex];
        if (returnValue != -1) {
            return returnValue;
        }

        // Set the cached value to 0 for future computations.
        returnValue = 0;

        // Start.
        const auto& firstChar = s[startIndex];
        if (firstChar == 'I') {
            // We can insert the smallest number before the first char.
            returnValue += subSequence(s, startIndex + 1, endIndex, dp, MOD);
        }

        // Middle.
        for (int i = startIndex + 1; i <= endIndex; i += 1) {
            const auto& previousChar = s[i - 1];
            const auto& currentChar = s[i];
            if ((previousChar == 'D') && (currentChar == 'I')) {
                // TODO: We should choose `((i - 2) - startIndex + 1)` numbers for `permutations1` from `endIndex - startIndex + 1` numbers.
                // TODO: This selection is random because of thoughts 2: number values don't affect permutation count.
                const int selection = 0;

                const int permutations1 = subSequence(s, startIndex, i - 2, dp, MOD);    // Note the new end index is `i - 2`.
                const int permutations2 = subSequence(s, i + 1, endIndex, dp, MOD);    // Note the new start index is `i + 1`.

                returnValue += (selection * permutations1 * permutations2);
            }
        }

        // End.
        const auto& lastChar = s[endIndex];
        if (lastChar == 'D') {
            returnValue += subSequence(s, startIndex, endIndex - 1, dp, MOD);
        }

        return returnValue;
    }


public:
    int numPermsDISequence(std::string& s) {
        const int MOD = pow(10, 9) + 7;

        auto dp = std::vector<std::vector<int>>(s.size(), std::vector<int>(s.size(), -1));    // I hate it that I cannot determine the size of this vector in the constructor.

        return subSequence(s, 0, s.size() - 1, dp, MOD);
    }
};


void test(const std::string& s, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto sCopy = s;
    auto result = solutionInstance.numPermsDISequence(sCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << s << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("D", 1);
    test("I", 1);
    test("DID", 5);

    return 0;
}
