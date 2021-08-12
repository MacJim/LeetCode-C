/*
 * 692. Top K Frequent Words
 * https://leetcode.com/problems/top-k-frequent-words/
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Hash table and insertion sort
/*
 * Some online solutions mention heapsort (priority queue).
 * But IMO insertion sort is faster because we don't have a lot of elements to sort (just up to 500).
 */
// Runtime: 12 ms, faster than 75.75% of C++ online submissions for Top K Frequent Words.
// Memory Usage: 12.1 MB, less than 99.25% of C++ online submissions for Top K Frequent Words.
class Solution {
public:
    std::vector<std::string> topKFrequent(std::vector<std::string>& words, int k) {
        auto occurrences = std::unordered_map<std::string, int>();
        for (const auto& word: words) {
            occurrences[word] += 1;
        }

        // Simulate an insertion sort here (we have less than 500 words so insertion sort would be very fast).
        auto returnValue = std::vector<std::string>(k, "");
        auto returnValueOccurrences = std::vector<int>(k, 0);

        for (const auto& [word, occurrence]: occurrences) {
            for (size_t i = 0; i < k; i += 1) {
                if ((occurrence > returnValueOccurrences[i]) || ((occurrence == returnValueOccurrences[i]) && (word.compare(returnValue[i]) < 0))) {
                    // Move.
                    for (size_t j = (k - 1); j > i; j -= 1) {
                        returnValue[j] = returnValue[j - 1];
                        returnValueOccurrences[j] = returnValueOccurrences[j - 1];
                    }

                    // Insert.
                    returnValue[i] = word;
                    returnValueOccurrences[i] = occurrence;

                    break;
                }
            }
        }

        return returnValue;
    }
};


void test(const std::vector<std::string>& words, const int k, const std::vector<std::string>& expectedResult) {
    auto solutionInstance = Solution();

    auto wordsCopy = words;
    auto result = solutionInstance.topKFrequent(wordsCopy, k);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << words << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << words << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({"i","love","leetcode","i","love","coding"}, 2, {"i","love"});
    test({"the","day","is","sunny","the","the","the","sunny","is","is"}, 4, {"the","is","sunny","day"});
    test({"b", "a", "c"}, 3, {"a", "b", "c"});

    return 0;
}
