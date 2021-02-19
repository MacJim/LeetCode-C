/*
 * 406. Queue Reconstruction by Height
 * https://leetcode.com/problems/queue-reconstruction-by-height/
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#include "helpers/Operators.hpp"


#pragma mark - 1
/*
 * - Initial person must have 0 k
 * - Initial person has small h
 * - Find smallest h person with the right amount of k
 */
/*
 * Sort by h (primary) and k (secondary)?
 * [[5, 0], [7, 0], [6, 1], [7, 1], [5, 2], [4, 4]]
 *
 * Sort by h?
 * [[4, 4], [5, 0], [5, 2], [6, 1], [7, 0], [7, 1]]
 */
// Time Limit Exceeded
class Solution1 {
public:
    std::vector<std::vector<int>> reconstructQueue(std::vector<std::vector<int>>& people) {
        if (people.empty()) {
            return {};
        }

        std::sort(people.begin(), people.end(), [] (const std::vector<int>& left, const std::vector<int>& right) {
            return (left[0] > right[0]);    // Largest first.
        });

        auto returnValue = std::vector<std::vector<int>>();

        // Initial tuple with 0 k.
        for (auto it = people.rbegin(); it < people.rend(); it += 1) {
            if (it->back() == 0) {
                returnValue.push_back(*it);
                people.erase(it.base() - 1);
                break;
            }
        }

        while (!people.empty()) {
            for (auto it = people.rbegin(); it < people.rend(); it += 1) {
                int largerOrEqualValues = 0;
                for (auto it2 = returnValue.begin(); it2 < returnValue.end(); it2 += 1) {
                    if (it2->front() >= it->front()) {
                        largerOrEqualValues += 1;
                    }
                }
                if (largerOrEqualValues == it->back()) {
                    returnValue.push_back(*it);
                    people.erase(it.base() - 1);
                    break;
                }
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Find smallest height first (revisit)
// The index for the smallest height is easy to obtain.
// Runtime: 72 ms, faster than 83.20% of C++ online submissions for Queue Reconstruction by Height.
// Memory Usage: 11.8 MB, less than 91.99% of C++ online submissions for Queue Reconstruction by Height.
class Solution {
public:
    std::vector<std::vector<int>> reconstructQueue(std::vector<std::vector<int>>& people) {
        if (people.empty()) {
            return {};
        }

        std::sort(people.begin(), people.end(), [] (const std::vector<int>& left, const std::vector<int>& right) {
            return (left[0] < right[0]);    // Shortest first.
        });

        auto returnValue = std::vector<std::vector<int>>(people.size(), std::vector<int>({INT_MAX, 0}));    // Well I really hate this sort of pre-allocation. This is why I came up with solution 1 first.

        for (const auto& p: people) {
            auto assumedIndex = p[1];
            for (size_t i = 0; i < returnValue.size(); i += 1) {
                if (returnValue[i][0] < p[0]) {
                    // Found a smaller value. Need to reserve an additional space for an upcoming larger value.
                    assumedIndex += 1;
                } else if (i == assumedIndex) {
                    returnValue[i] = p;
                }
            }
        }

        return returnValue;
    }
};


void test(const std::vector<std::vector<int>>& people, const std::vector<std::vector<int>>& expectedResult) {
    static auto solutionInstance = Solution();

    auto peopleCopy = people;
    auto result = solutionInstance.reconstructQueue(peopleCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << people << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << people << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}}, {{5,0},{7,0},{5,2},{6,1},{4,4},{7,1}});
    test({{6,0},{5,0},{4,0},{3,2},{2,2},{1,4}}, {{4,0},{5,0},{2,2},{3,2},{1,4},{6,0}});

    return 0;
}
