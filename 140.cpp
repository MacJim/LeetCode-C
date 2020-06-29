/*
 * 140. Word Break II
 * https://leetcode.com/problems/word-break-ii/
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <algorithm>    // std::find


#pragma mark - Helper functions
template <typename A, typename B>
std::ostream& operator << (std::ostream& os, const std::pair<A, B>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) {
    if (v.empty()) {
        os << "[ ]";
        return os;
    } else {
        os << "[";
        for (const auto& element: v) {
            os << element << ", ";
        }
        os << "\b\b]";
        return os;
    }
}


#pragma mark - 1. Front to back. Vector of pairs (unoptimized, but should produce the correct results).
// Time Limit Exceeded
class Solution1 {
public:
    std::vector<std::string> wordBreak(std::string s, std::vector<std::string>& wordDict) {
        const auto sLen = s.size();

        auto startIndices = std::vector<std::pair<size_t, std::string>>();
        startIndices.emplace_back(0, "");

        auto returnValue = std::vector<std::string>();

        while (!startIndices.empty()) {
            const auto pair = std::move(startIndices.back());
            startIndices.pop_back();

            const auto& i = pair.first;
            const auto& currentResult = pair.second;

            const auto remainingLen = sLen - i;

            for (const auto& word: wordDict) {
                // Length is cached. No need to pre-compute.
                const auto wordLen = word.size();

                if (wordLen > remainingLen) {
                    // Remaining string is too short.
                    continue;
                }

                if (s.compare(i, wordLen, word) == 0) {
                    // Substring equals.
                    const auto nextIndex = i + wordLen;
                    auto nextResult = word;
                    if (!currentResult.empty()) {
                        nextResult = currentResult + " " + nextResult;
                    }

                    if (nextIndex == sLen) {
                        returnValue.push_back(std::move(nextResult));
                    } else {
                        startIndices.emplace_back(nextIndex, std::move(nextResult));
                    }
                }
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Optimized 1
// Time Limit Exceeded
class Solution2 {
public:
    std::vector<std::string> wordBreak(std::string s, std::vector<std::string> &wordDict) {
        const auto sLen = s.size();

        auto startIndices = std::map<size_t, std::vector<std::string>>();
        std::vector<std::string> initialResults = {""};
        startIndices.emplace(0, std::move(initialResults));

        auto returnValue = std::vector<std::string>();

        while (!startIndices.empty()) {
            auto pair = *startIndices.begin();

            const auto i = pair.first;
            const auto currentResults = std::move(pair.second);

            startIndices.erase(startIndices.begin());

            const auto remainingLen = sLen - i;

            for (const auto& word: wordDict) {
                // Length is cached. No need to pre-compute.
                const auto wordLen = word.size();

                if (wordLen > remainingLen) {
                    // Remaining string is too short.
                    continue;
                }

                if (s.compare(i, wordLen, word) == 0) {
                    // Substring equals.
                    const auto nextIndex = i + wordLen;

                    if (nextIndex == sLen) {
                        if (currentResults.front().empty()) {
                            returnValue.push_back(word);
                        } else {
                            for (auto& r: currentResults) {
                                returnValue.push_back(r + " " + word);
                            }
                        }
                    } else {
//                        const auto it = std::find(startIndices.begin(), startIndices.end(), nextIndex);
                        const auto it = startIndices.find(nextIndex);
                        if (it == startIndices.end()) {
                            std::vector<std::string> emptyResults = {};
                            startIndices.emplace(nextIndex, std::move(emptyResults));
                        }

                        auto& nextResults = startIndices.at(nextIndex);

                        if (currentResults.front().empty()) {
                            nextResults.push_back(word);
                        } else {
                            for (auto& r: currentResults) {
                                nextResults.push_back(r + " " + word);
                            }
                        }
                    }
                }
            }
        }

        return returnValue;
    }
};


#pragma mark - 3. Cache results of strings instead of indices
// Runtime: 28 ms, faster than 50.29% of C++ online submissions for Word Break II.
// Memory Usage: 12.3 MB, less than 61.20% of C++ online submissions for Word Break II.
class Solution {
private:
    std::unordered_map<std::string, std::vector<std::string>> stringCache;

    std::vector<std::string> appendWordToStrings(std::vector<std::string> strs, const std::string& w) {
        for (auto& s: strs) {
            s += (" " + w);
        }

        return strs;
    }

public:
    std::vector<std::string> wordBreak(std::string s, std::vector<std::string> &wordDict) {
        // Look into the cache first.
        const auto it = stringCache.find(s);
        if (it != stringCache.end()) {
            return it->second;
        }

        auto returnValue = std::vector<std::string>();

        // Entire string is a word.
        if (std::find(wordDict.begin(), wordDict.end(), s) != wordDict.end()) {
            returnValue.push_back(s);
        }

        // Shorter strings. Don't ignore them!
        // Start from the back because we append strings from the back.
        for (size_t i = 1; i < s.size(); i += 1) {
             const auto subString = s.substr(i);

             if (std::find(wordDict.begin(), wordDict.end(), subString) != wordDict.end()) {
                 // [i:] is in the dictionary.
                 std::string remainingString = s.substr(0, i);

                 auto remainingBreakDown = wordBreak(remainingString, wordDict);

                 auto previousPartitions = appendWordToStrings(remainingBreakDown, subString);

                 returnValue.insert(returnValue.end(), previousPartitions.begin(), previousPartitions.end());
             }
        }

        stringCache.emplace(s, returnValue);
        return returnValue;
    }
};


int main() {
    auto solutionInstance = Solution();

    std::string s1 = "catsanddog";
    std::vector<std::string> d1 = {"cat", "cats", "and", "sand", "dog"};
    std::cout << solutionInstance.wordBreak(s1, d1) << std::endl;

    std::string s2 = "pineapplepenapple";
    std::vector<std::string> d2 = {"apple", "pen", "applepen", "pine", "pineapple"};
    std::cout << solutionInstance.wordBreak(s2, d2) << std::endl;

    std::string s3 = "catsandog";
    std::vector<std::string> d3 = {"cats", "dog", "sand", "and", "cat"};
    std::cout << solutionInstance.wordBreak(s3, d3) << std::endl;    // No result.

    std::string s4 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    std::vector<std::string> d4 = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
    std::cout << solutionInstance.wordBreak(s4, d4) << std::endl;    // No result because of that single 'b' character.

    std::string s5 = "aaaaaaaaaaaaaaaaaaaaaa";
    std::vector<std::string> d5 = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
    std::cout << solutionInstance.wordBreak(s5, d5) << std::endl;    // A lot of results.

    return 0;
}
