/*
 * 451. Sort Characters By Frequency
 * https://leetcode.com/problems/sort-characters-by-frequency/
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Count, sort and reconstruct the string
// Runtime: 13 ms, faster than 35.72% of C++ online submissions for Sort Characters By Frequency.
// Memory Usage: 8 MB, less than 91.45% of C++ online submissions for Sort Characters By Frequency.
class Solution1 {
public:
    std::string frequencySort(const std::string& s) {
        if (s.size() == 1) {
            // No need to sort.
            return s;
        }

        auto occurrences = std::unordered_map<char, int>();
        for (const auto& c: s) {
            occurrences[c] += 1;
        }

        // Insertion sort (we only have up to 26 + 26 + 10 characters).
        auto significantChars = std::vector<std::pair<char, int>>();
        significantChars.reserve(occurrences.size());

        for (const auto& [c, occurrence]: occurrences) {
            bool foundSmaller = false;

            for (int i = 0; i < significantChars.size(); i += 1) {
                if (significantChars[i].second < occurrence) {
                    significantChars.push_back(significantChars.back());

                    for (int j = (significantChars.size() - 1); j > i; j -= 1) {
                        significantChars[j] = significantChars[j - 1];
                    }

                    significantChars[i].first = c;
                    significantChars[i].second = occurrence;

                    foundSmaller = true;
                    break;
                }
            }

            if (!foundSmaller) {
                significantChars.emplace_back(c, occurrence);
            }
        }

        std::string returnValue;
        returnValue.reserve(s.size());

        for (const auto& [c, occurrence]: significantChars) {
            for (int i = 0; i < occurrence; i += 1) {
                returnValue += c;
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Optimized 1: Eliminates the `foundSmaller` variable
// Runtime: 13 ms, faster than 35.72% of C++ online submissions for Sort Characters By Frequency.
// Memory Usage: 8 MB, less than 84.64% of C++ online submissions for Sort Characters By Frequency.
class Solution {
public:
    std::string frequencySort(const std::string& s) {
        if (s.size() == 1) {
            // No need to sort.
            return s;
        }

        auto occurrences = std::unordered_map<char, int>();
        for (const auto& c: s) {
            occurrences[c] += 1;
        }

        // Insertion sort (we only have up to 26 + 26 + 10 characters).
        auto significantChars = std::vector<std::pair<char, int>>();
        significantChars.reserve(occurrences.size() + 1);
        significantChars.emplace_back('\0', 0);    // Dummy object at the end of this vector.

        for (const auto& [c, occurrence]: occurrences) {
            for (int i = 0; i < significantChars.size(); i += 1) {
                if (significantChars[i].second < occurrence) {
                    significantChars.push_back(significantChars.back());

                    for (int j = (significantChars.size() - 1); j > i; j -= 1) {
                        significantChars[j] = significantChars[j - 1];
                    }

                    significantChars[i].first = c;
                    significantChars[i].second = occurrence;

                    break;
                }
            }
        }

        std::string returnValue;
        returnValue.reserve(s.size());

        for (const auto& [c, occurrence]: significantChars) {
            for (int i = 0; i < occurrence; i += 1) {
                returnValue += c;
            }
        }

        return returnValue;
    }
};


void test(const std::string& s, const std::set<std::string>& expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.frequencySort(s);

    if (std::find(expectedResult.begin(), expectedResult.end(), result) != expectedResult.end()) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << s << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << s << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("tree", {"eert", "eetr"});
    test("cccaaa", {"cccaaa", "aaaccc"});
    test("Aabb", {"bbAa", "bbaA"});

    return 0;
}
