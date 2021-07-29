/*
 * 846. Hand of Straights
 * https://leetcode.com/problems/hand-of-straights/
 *
 * Note: This question is the same as 1296: https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/
 */

#include <iostream>
#include <vector>
#include <map>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Sort
// Runtime: 180 ms, faster than 8.45% of C++ online submissions for Hand of Straights.
// Memory Usage: 18.7 MB, less than 96.92% of C++ online submissions for Hand of Straights.
class Solution1 {
public:
    bool isNStraightHand(std::vector<int>& hand, const int groupSize) {
        if (hand.size() % groupSize) {
            // Not dividable.
            return false;
        }

        const int maxGroups = hand.size() / groupSize;

        std::sort(hand.begin(), hand.end());

        auto visited = std::vector<bool>(hand.size(), false);
        // Start from the smallest unvisited number.
        for (int group = 0; group < maxGroups; group += 1) {
            int remainingCount = groupSize;
            int previousNum = -1;    // This should always be positive.

            for (int i = 0; i < hand.size(); i += 1) {
                if (!visited[i]) {
                    if (previousNum != -1) {
                        // Has a previous num.
                        if (hand[i] == previousNum) {
                            continue;
                        } else if (hand[i] != (previousNum + 1)) {
                            return false;
                        }
                    }

                    previousNum = hand[i];
                    visited[i] = true;
                    remainingCount -= 1;

                    if (remainingCount == 0) {
                        break;
                    }
                }
            }

            if (remainingCount) {
                // The remaining numbers cannot form a sequence.
                return false;
            }
        }

        return true;
    }
};


#pragma mark - 2. Red-black tree
// Runtime: 60 ms, faster than 90.07% of C++ online submissions for Hand of Straights.
// Memory Usage: 26.4 MB, less than 24.89% of C++ online submissions for Hand of Straights.
class Solution2 {
public:
    bool isNStraightHand(std::vector<int>& hand, const int groupSize) {
        if (groupSize == 1) {
            return true;
        }
        if (hand.size() % groupSize) {
            // Not dividable.
            return false;
        }

        auto occurrences = std::map<int, int>();
        for (const int& num: hand) {
            occurrences[num] += 1;
        }

        // Start from the smallest unvisited number.
        while (!occurrences.empty()) {
            int remainingCount = groupSize;
            int previousNum = -1;    // This should always be positive.
            int beginCount = -1;

            for (auto& occurrence : occurrences) {
                if (occurrence.second) {
                    if (previousNum == -1) {
                        beginCount = occurrence.second;
                        occurrence.second = 0;
                    } else {
                        // Has a previous num.
                        if (occurrence.first != (previousNum + 1)) {
                            return false;
                        } else {
                            // Check count.
                            if (occurrence.second < beginCount) {
                                return false;
                            } else {
                                occurrence.second -= beginCount;
                            }
                        }
                    }

                    previousNum = occurrence.first;
                    remainingCount -= 1;

                    if (remainingCount == 0) {
                        break;
                    }
                }
            }

            if (remainingCount) {
                // The remaining numbers cannot form a sequence.
                return false;
            }

            while (!occurrences.empty() && (occurrences.begin()->second == 0)) {
                occurrences.erase(occurrences.begin());
            }
        }

        return true;
    }
};


#pragma mark - 3. Optimized 2: For each starting number, just check its upcoming numbers
// Runtime: 68 ms, faster than 67.47% of C++ online submissions for Hand of Straights.
// Memory Usage: 26.4 MB, less than 24.89% of C++ online submissions for Hand of Straights.
class Solution {
public:
    bool isNStraightHand(std::vector<int>& hand, const int groupSize) {
        if (groupSize == 1) {
            return true;
        }
        if (hand.size() % groupSize) {
            // Not dividable.
            return false;
        }

        auto occurrences = std::map<int, int>();
        for (const int& num: hand) {
            occurrences[num] += 1;
        }

        // Start from the smallest unvisited number.
        while (!occurrences.empty()) {
            const int beginNum = occurrences.begin()->first;    // This should always be positive.
            const int beginCount = occurrences.begin()->second;

            occurrences.erase(occurrences.begin());

            // Check upcoming numbers.
            for (int increment = 1; increment < groupSize; increment += 1) {
                const int currentNum = beginNum + increment;
                if ((occurrences.count(currentNum) == 0) || (occurrences[currentNum] < beginCount)) {
                    return false;
                } else if (occurrences[currentNum] == beginCount) {
                    occurrences.erase(currentNum);
                } else {
                    occurrences[currentNum] -= beginCount;
                }
            }
        }

        return true;
    }
};



void test(const std::vector<int>& hand, const int groupSize, const bool expectedResult) {
    auto solutionInstance = Solution();

    auto handCopy = hand;
    auto result = solutionInstance.isNStraightHand(handCopy, groupSize);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << hand << ", " << groupSize << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << hand << ", " << groupSize << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({1,2,3,6,2,3,4,7,8}, 3, true);
    test({1,1,2,2,3,3}, 2, false);
    test({1,1,2,2,3,3}, 3, true);
    test({1,2,3,4,5}, 4, false);

    return 0;
}
