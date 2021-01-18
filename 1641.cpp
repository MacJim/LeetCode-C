/*
 * 1641. Count Sorted Vowel Strings
 * https://leetcode.com/problems/count-sorted-vowel-strings/
 */

#include <iostream>
#include <unordered_map>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Recursion and cache
// Runtime: 4 ms, faster than 25.97% of C++ online submissions for Count Sorted Vowel Strings.
// Memory Usage: 6.1 MB, less than 94.00% of C++ online submissions for Count Sorted Vowel Strings.
class Solution {
public:
    /// Cache for 5 vowels.
    static std::vector<int> cache5;
//    static std::unordered_map<int, int> cache5;
    /// Cache for 4 vowels.
    static std::vector<int> cache4;
//    static std::unordered_map<int, int> cache4;
    /// Cache for 3 vowels.
    static std::vector<int> cache3;
//    static std::unordered_map<int, int> cache3;
    /// Cache for 2 vowels.
    static std::vector<int> cache2;
//    static std::unordered_map<int, int> cache2;

private:
    int countRecursively(const int availableVowels, const int length) {
        // Special cases.
        if (availableVowels == 1) {
            return 1;
        }
        if (length == 1) {
            return availableVowels;
        }

        // Find the proper cache.
        std::vector<int>* cache = &cache2;
        switch (availableVowels) {
            case 5:
                cache = &cache5;
                break;
            case 4:
                cache = &cache4;
                break;
            case 3:
                cache = &cache3;
                break;
            default:
                break;
        }

        // Use cached value.
        const int indexInCache = length;
        if (cache->size() > indexInCache) {
            return cache->at(indexInCache);
        }

        // Recursion.
        int returnValue = 0;
        const int nextLength = length - 1;
        for (int nextAvailableVowels = availableVowels; nextAvailableVowels > 0; nextAvailableVowels -= 1) {
            returnValue += countRecursively(nextAvailableVowels, nextLength);
        }
        cache->push_back(returnValue);    // This looks risky.

        return returnValue;
    }

public:
    int countVowelStrings(int length) {
        if (length == 0) {
            return 0;
        }

        return countRecursively(5, length);
    }
};

std::vector<int> Solution::cache5 = std::vector<int>({0, 0});
std::vector<int> Solution::cache4 = std::vector<int>({0, 0});
std::vector<int> Solution::cache3 = std::vector<int>({0, 0});
std::vector<int> Solution::cache2 = std::vector<int>({0, 0});
//std::unordered_map<int, int> Solution::cache5 = std::unordered_map<int, int>();
//std::unordered_map<int, int> Solution::cache4 = std::unordered_map<int, int>();
//std::unordered_map<int, int> Solution::cache3 = std::unordered_map<int, int>();
//std::unordered_map<int, int> Solution::cache2 = std::unordered_map<int, int>();


void test(const int n, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto result = solutionInstance.countVowelStrings(n);

    if (result == expectedResult) {
        std::cout << "[Correct] " << n << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << n << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(1, 5);
    test(2, 15);
    test(33, 66045);

//    for (const auto& [k, v]: Solution::cache5) {
//        std::cout << k << " " << v << std::endl;
//    }

    return 0;
}
