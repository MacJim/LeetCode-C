/*
 * 1451. Rearrange Words in a Sentence
 * https://leetcode.com/problems/rearrange-words-in-a-sentence/
 */

#include <iostream>
#include <vector>
#include <utility>
#include <string>

//#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Heap
// Runtime: 31 ms, faster than 51.82% of C++ online submissions for Rearrange Words in a Sentence.
// Memory Usage: 11.3 MB, less than 99.42% of C++ online submissions for Rearrange Words in a Sentence.
class Solution {
public:
    std::string arrangeWords(std::string& text) {
        if (text.size() <= 2) {
            // 2-long strings can only contain a single word.
            return text;
        }

        // 1. Change first character to lower-case.
        text[0] += ('a' - 'A');

        // 2. Start indices and lengths.
//        auto startIndices = std::vector<int>();
//        auto lengths = std::vector<int>();

        auto startIndicesAndLengths = std::vector<std::pair<int, int>>();

        int startIndex = -1;
        for (int i = 0; i < text.size(); i += 1) {
            if (startIndex == -1) {
                startIndex = i;
            } else if (text[i] == ' ') {
                const int length = i - startIndex;

                startIndicesAndLengths.emplace_back(startIndex, length);

                startIndex = -1;
            }
        }

        // The last word has no whitespace ending.
        if (startIndex != -1) {
            const int length = text.size() - startIndex;

            startIndicesAndLengths.emplace_back(startIndex, length);
        }

        // 3. Heap.
        auto cmp = [](const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) -> bool {
            if (lhs.second == rhs.second) {
                // Same-length words.
                // Prefer the one with smaller start index.
                return lhs.first > rhs.first;
            } else {
                return lhs.second > rhs.second;
            }
        };
        std::make_heap(startIndicesAndLengths.begin(), startIndicesAndLengths.end(), cmp);

        // 4. Pop from heap.
        auto returnValue = std::string();
        returnValue.reserve(text.size());

        // First word: capitalize.
        returnValue.append(text, startIndicesAndLengths.front().first, startIndicesAndLengths.front().second);
        if (returnValue[0] > 'Z') {
            returnValue[0] -= ('z' - 'Z');
        }

        std::pop_heap(startIndicesAndLengths.begin(), startIndicesAndLengths.end(), cmp);
        startIndicesAndLengths.pop_back();

        // Upcoming words.
        while (!startIndicesAndLengths.empty()) {
            returnValue.push_back(' ');
            returnValue.append(text, startIndicesAndLengths.front().first, startIndicesAndLengths.front().second);

            std::pop_heap(startIndicesAndLengths.begin(), startIndicesAndLengths.end(), cmp);
            startIndicesAndLengths.pop_back();
        }

        return returnValue;
    }
};


void test(const std::string& text, const std::string& expectedResult) {
    auto solutionInstance = Solution();

    auto textCopy = text;
    auto result = solutionInstance.arrangeWords(textCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << text << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << text << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("Keep calm and code", "And keep calm code");
    test("Keep calm and code on", "On and keep calm code");
    test("Leetcode is cool", "Is cool leetcode");
    test("To be or not to be", "To be or to be not");

    return 0;
}
