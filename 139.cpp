/*
 * 139. Word Break
 * https://leetcode.com/problems/word-break/
 */

#include <iostream>
#include <vector>
#include <string>
#include <set>


// Runtime: 4 ms, faster than 98.99% of C++ online submissions for Word Break.
// Memory Usage: 7.4 MB, less than 95.29% of C++ online submissions for Word Break.
class Solution {
private:
    bool updateNextIndices(std::string& s, std::vector<std::string>& wordDict, std::set<int>& nextIndices, const int startIndex) {
        for (const auto& word: wordDict) {
            int wordI = 0;

            for (; wordI < word.size(); wordI += 1) {
                const auto stringI = wordI + startIndex;
                if (stringI >= s.size()) {
                    // Consider the out of range scenario.
                    break;
                }

                if (s.at(stringI) != word.at(wordI)) {
                    break;
                }
            }

            if (wordI == word.size()) {
                // Is a match.
                const auto stringI = wordI + startIndex;
                if (stringI == s.size()) {
                    // This is the final character.
                    return true;
                }

                nextIndices.insert(stringI);
            }
        }

        return false;
    }

public:
    bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
        auto nextIndices = std::set<int>({0});
        while (!nextIndices.empty()) {
            auto smallestIndex = *nextIndices.begin();
            nextIndices.erase(nextIndices.begin());

            const auto result = updateNextIndices(s, wordDict, nextIndices, smallestIndex);
            if (result) {
                return true;
            }
        }

        return false;
    }
};


int main() {
    auto solutionInstance = Solution();

    std::string s1 = "leetcode";
    std::vector<std::string> words1 = {"code", "leet"};
    std::cout << solutionInstance.wordBreak(s1, words1) << std::endl;    // true

    std::string s2 = "applepenapple";
    std::vector<std::string> words2 = {"apple", "pen"};
    std::cout << solutionInstance.wordBreak(s2, words2) << std::endl;    // true

    std::string s3 = "catsandog";
    std::vector<std::string> words3 = {"cats", "dog", "sand", "and", "cat"};
    std::cout << solutionInstance.wordBreak(s3, words3) << std::endl;    // false

    std::string s4 = "bb";
    std::vector<std::string> words4 = {"a","b","bbb","bbbb"};
    std::cout << solutionInstance.wordBreak(s4, words4) << std::endl;    // false

    return 0;
}
