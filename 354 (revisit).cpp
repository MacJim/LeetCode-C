/*
 * 354. Russian Doll Envelopes
 * https://leetcode.com/problems/russian-doll-envelopes/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Sort and find the longest increasing subsequence (like 300)
// Runtime: 57 ms, faster than 78.93% of C++ online submissions for Russian Doll Envelopes.
// Memory Usage: 16.1 MB, less than 93.95% of C++ online submissions for Russian Doll Envelopes.
class Solution {
public:
    int maxEnvelopes(std::vector<std::vector<int>>& envelopes) {
        if (envelopes.size() == 1) {
            return 1;
        }

        // Sort by x
        auto cmp = [](const std::vector<int>& lhs, const std::vector<int>& rhs) -> bool {
            if (lhs[0] == rhs[0]) {
                // Bigger y comes first.
                return lhs[1] > rhs[1];
            } else {
                // Smaller x comes first.
                return lhs[0] < rhs[0];
            }
        };
        std::sort(envelopes.begin(), envelopes.end(), cmp);

        // Find the longest increasing subsequence of y.
        auto sequence = std::vector<int>();
        for (const auto& envelope: envelopes) {
            const int& y = envelope[1];

            if (sequence.empty() || (y > sequence.back())) {
                sequence.push_back(y);
            }

            for (int i = 0; i < sequence.size(); i += 1) {
                if (y == sequence[i]) {
                    // Ignore duplicate numbers.
                    break;
                } else if (y < sequence[i]) {
                    // Update a previous number in the streak.
                    sequence[i] = y;
                    break;
                }
            }
        }

        return static_cast<int>(sequence.size());
    }
};


void test(const std::vector<std::vector<int>>& envelopes, const int expectedResult) {
    auto solutionInstance = Solution();

    auto envelopesCopy = envelopes;
    auto result = solutionInstance.maxEnvelopes(envelopesCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << envelopes << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << envelopes << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{5,4},{6,4},{6,7},{2,3}}, 3);
    test({{1,1},{1,1},{1,1}}, 1);
    test({{5,4},{6,4},{6,7},{2,3},{5,3},{5,5},{7,4},{7,7}}, 3);

    return 0;
}
