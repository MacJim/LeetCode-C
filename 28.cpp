/*
 * 28. Implement strStr()
 * https://leetcode.com/problems/implement-strstr/
 */

#include <iostream>
#include <string>
#include <vector>


// MARK: - 1. Assembly line like
// Runtime: 88 ms, faster than 20.68% of C++ online submissions for Implement strStr().
// Memory Usage: 61.2 MB, less than 5.71% of C++ online submissions for Implement strStr().
class Solution1 {
public:
    int strStr(std::string haystack, std::string needle) {
        auto needleLength = needle.length();
        if (needleLength == 0) {
            return 0;
        }

        auto haystackLength = haystack.length();
        if (haystackLength == 0) {
            return -1;
        }

        if (haystackLength < needleLength) {
            return -1;
        }

        auto possibleStartingIndices = std::vector<int>();
        for (int i = 0; i < haystackLength; i += 1) {
            char currentCharacter = haystack.at(i);

            auto nextStartingIndices = std::vector<int>();

            if (currentCharacter == needle.at(0)) {
                if (needleLength == 1) {
                    return i;
                } else {
                    nextStartingIndices.push_back(i);
                }
            }
            
            for (const auto& aPossibleStartingIndex: possibleStartingIndices) {
                char characterIndexInNeedle = i - aPossibleStartingIndex;
                if (characterIndexInNeedle >= needleLength) {
                    continue;
                }

                if (currentCharacter == needle.at(characterIndexInNeedle)) {
                    if (characterIndexInNeedle == (needleLength - 1)) {
                        // This is the final character.
                        return aPossibleStartingIndex;
                    } else {
                        nextStartingIndices.push_back(aPossibleStartingIndex);
                    }
                }
            }

            possibleStartingIndices = std::move(nextStartingIndices);
        }

        return -1;
    }
};


// MARK: - 2. The normal solution
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Implement strStr().
// Memory Usage: 9.1 MB, less than 67.14% of C++ online submissions for Implement strStr().
class Solution {
public:
    int strStr(std::string haystack, std::string needle) {
        auto needleLength = needle.length();
        if (needleLength == 0) {
            return 0;
        }

        auto haystackLength = haystack.length();
        if (haystackLength == 0) {
            return -1;
        }

        if (haystackLength < needleLength) {
            return -1;
        }

        for (int i = 0; i < haystackLength; i += 1) {
            int currentDeviation = i;
            bool needleFound = true;

            for (const char& aCharacter: needle) {
                if (currentDeviation >= haystackLength) {
                    // The search is beyond the haystack length.
                    return -1;
                }
                
                if (aCharacter != haystack.at(currentDeviation)) {
                    needleFound = false;
                    break;
                }

                currentDeviation += 1;
            }

            if (needleFound) {
                return i;
            }
        }

        return -1;
    }
};


int main() {
    auto solutionInstance = Solution();
    std::cout << solutionInstance.strStr("hello", "ll") << std::endl;    // 2
    std::cout << solutionInstance.strStr("aaaaa", "bba") << std::endl;    // -1
    std::cout << solutionInstance.strStr("a", "a") << std::endl;    // 0
    std::cout << solutionInstance.strStr("bbbaa", "a") << std::endl;    // 3
    std::cout << solutionInstance.strStr("mississippi", "mississippi") << std::endl;    // 0

    return 0;
}
