/*
 * 1079. Letter Tile Possibilities
 * https://leetcode.com/problems/letter-tile-possibilities/
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Permutation and select with brute force (revisit)
/*
 * IMO this is unoptimized but somehow is pretty fast.
 */
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Letter Tile Possibilities.
// Memory Usage: 6.1 MB, less than 67.36% of C++ online submissions for Letter Tile Possibilities.
class Solution1 {
private:
    static const std::vector<int> factorials;

private:
    /**
     * @return `false` for not enough characters; `true` for enough characters.
     */
    bool recursion(const std::vector<int>& occurrences, const std::vector<int>& remainingLengths, const size_t currentIndex, const int length, const int previousResult, int& returnValue) {
        if (currentIndex >= occurrences.size()) {
            // No more characters.
            return false;
        }

        const int& remainingLength = remainingLengths[currentIndex];
        if (remainingLength < length) {
            // Not enough remaining characters.
            return false;
        }

        // Current character count
        const int currentCharMaxCount = std::min(occurrences[currentIndex], length);
        for (int currentCharCount = currentCharMaxCount; currentCharCount >= 0; currentCharCount -= 1) {
            const int currentResult = previousResult / factorials[currentCharCount];    // See note: permutations = countSum! / count1! / count2! / ...

            if (currentCharCount == length) {
                // Add to return value directly. No need to recurse.
                returnValue += currentResult;
                continue;
            }

            const auto hasEnoughCharacters = recursion(occurrences, remainingLengths, currentIndex + 1, length - currentCharCount, currentResult, returnValue);

            if (!hasEnoughCharacters) {
                // Cannot use. Will result in not enough remaining characters.
                break;
            }
        }

        return true;
    }

public:
    int numTilePossibilities(std::string& tiles) {
        if (tiles.size() == 1) {
            return 1;
        }

        // Calculate occurrences.
        auto occurrences = std::vector<int>(26, 0);
        for (const char& c: tiles) {
            const size_t& index = static_cast<size_t>(c - 'A');
            occurrences[index] += 1;
        }

        occurrences.erase(std::remove(occurrences.begin(), occurrences.end(), 0), occurrences.end());    // Remove 0 entries to optimize looping performance.

        // Cache remaining length for premature termination.
        auto remainingLengths = occurrences;
        for (int i = occurrences.size() - 2; i >= 0; i -= 1) {    // i cannot equal 25 here.
            remainingLengths[i] += remainingLengths[i + 1];
        }

        int returnValue = 0;

        // For each possible length.
        for (int length = 1; length <= tiles.size(); length += 1) {
            const int& initialResult = factorials[length];    // See note: permutations = countSum! / count1! / count2! / ...
            recursion(occurrences, remainingLengths, 0, length, initialResult, returnValue);
        }

        return returnValue;
    }
};


const std::vector<int> Solution1::factorials = {1, 1, 2, 6, 24, 120, 720, 5040};


#pragma mark - 2. Optimized 1: No need for return values from recursion thanks to boundary check on both ends
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Letter Tile Possibilities.
// Memory Usage: 6 MB, less than 71.48% of C++ online submissions for Letter Tile Possibilities.
class Solution {
private:
    static const std::vector<int> factorials;

private:
    void recursion(const std::vector<int>& occurrences, const std::vector<int>& remainingLengths, const size_t currentIndex, const int length, const int previousResult, int& returnValue) {
        if (currentIndex >= occurrences.size()) {
            // No more characters.
            return;
        }

        // Current character count caps.
        const int currentCharMaxCount = std::min(occurrences[currentIndex], length);
        int currentCharMinCount = length;
        if (currentIndex < (occurrences.size() - 1)) {
            // This is not the last index.
            currentCharMinCount = std::max(0, length - remainingLengths[currentIndex + 1]);
        }

        // Recursion.
        for (int currentCharCount = currentCharMaxCount; currentCharCount >= currentCharMinCount; currentCharCount -= 1) {
            const int currentResult = previousResult / factorials[currentCharCount];    // See note: permutations = countSum! / count1! / count2! / ...

            if (currentCharCount == length) {
                // Add to return value directly. No need to recurse.
                returnValue += currentResult;
                continue;
            }

            recursion(occurrences, remainingLengths, currentIndex + 1, length - currentCharCount, currentResult, returnValue);
        }
    }

public:
    int numTilePossibilities(std::string& tiles) {
        if (tiles.size() == 1) {
            return 1;
        }

        // Calculate occurrences.
        auto occurrences = std::vector<int>(26, 0);
        for (const char& c: tiles) {
            const size_t& index = static_cast<size_t>(c - 'A');
            occurrences[index] += 1;
        }

        occurrences.erase(std::remove(occurrences.begin(), occurrences.end(), 0), occurrences.end());    // Remove 0 entries to optimize looping performance.

        // Cache remaining length for premature termination.
        auto remainingLengths = occurrences;
        for (int i = occurrences.size() - 2; i >= 0; i -= 1) {    // i cannot equal 25 here.
            remainingLengths[i] += remainingLengths[i + 1];
        }

        int returnValue = 0;

        // For each possible length.
        for (int length = 1; length <= tiles.size(); length += 1) {
            const int& initialResult = factorials[length];    // See note: permutations = countSum! / count1! / count2! / ...
            recursion(occurrences, remainingLengths, 0, length, initialResult, returnValue);
        }

        return returnValue;
    }
};


const std::vector<int> Solution::factorials = {1, 1, 2, 6, 24, 120, 720, 5040};


void test(const std::string& tiles, const int expectedResult) {
    auto solutionInstance = Solution();

    auto tilesCopy = tiles;
    auto result = solutionInstance.numTilePossibilities(tilesCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << tiles << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << tiles << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("AAABBC", 188);
    test("AAB", 8);
    test("V", 1);

    return 0;
}
