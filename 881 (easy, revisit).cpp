/*
 * 881. Boats to Save People
 * https://leetcode.com/problems/boats-to-save-people/
 */

/*
 * Note: It is guaranteed each person can be carried by a boat.
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "helpers/Operators.hpp"


#pragma mark - 1. Use a map to optimize the counting process
// Time Limit Exceeded
// I think I should have chosen the lightest person in "A large person and a small person" because the lightest person can and should pair with anyone.
class Solution1 {
public:
    int numRescueBoats(std::vector<int>& people, int limit) {
        // 1. Calculate occurrences.
        auto weightOccurrences = std::map<int, int, std::greater<>>();    // Bigger weights first.
        for (const auto& weight: people) {
            auto it = weightOccurrences.find(weight);
            if (it == weightOccurrences.end()) {
                weightOccurrences.emplace(weight, 1);
            } else {
                it->second += 1;
            }
        }

        // 2. Iterate from back.
        int returnValue = 0;

        while (!weightOccurrences.empty()) {
            auto itLarge = weightOccurrences.begin();
            const int largeWeight = itLarge->first;
            int largeCount = itLarge->second;

            weightOccurrences.erase(itLarge);    // Base is in fact `end()`. So `--` is needed here.

            // Special case: 2 large persons.
            if ((largeCount > 1) && ((largeWeight * 2) <= limit)) {
                const int boats = largeCount / 2;
                returnValue += boats;

                if (largeCount % 2 == 0) {
                    continue;
                } else {
                    largeCount = 1;
                }
            }

            // A large person and a small person.
//            bool eraseRange = false;    // We want to erase multiple small persons.
//            auto eraseStart = weightOccurrences.end();
//            auto eraseEnd = weightOccurrences.end();

            for (auto itSmall = weightOccurrences.begin(); itSmall != weightOccurrences.end(); ) {
                const int smallWeight = itSmall->first;
                int& smallCount = itSmall->second;

                const auto totalWeight = largeWeight + smallWeight;

                if (totalWeight <= limit) {
                    if (largeCount == smallCount) {
                        returnValue += largeCount;

                        largeCount = 0;

                        weightOccurrences.erase(itSmall);

                        break;
                    } else if (largeCount < smallCount) {
                        returnValue += largeCount;

                        smallCount -= largeCount;
                        largeCount = 0;

                        break;
                    } else {
                        returnValue += smallCount;

                        largeCount -= smallCount;

                        itSmall = weightOccurrences.erase(itSmall);

//                        eraseEnd = itSmall.base();
//                        eraseRange = true;
                        // Continue.
                    }
                } else {
                    itSmall ++;
                }
            }

            // A single large person.
            returnValue += largeCount;
        }

        return returnValue;
    }
};


#pragma mark - 2. Improved 1 (unfinished, won't finish)
class Solution2 {
public:
    int numRescueBoats(std::vector<int>& people, int limit) {
        // 1. Calculate occurrences.
        auto weightOccurrences = std::map<int, int, std::greater<>>();    // Bigger weights first.
        for (const auto& weight: people) {
            auto it = weightOccurrences.find(weight);
            if (it == weightOccurrences.end()) {
                weightOccurrences.emplace(weight, 1);
            } else {
                it->second += 1;
            }
        }

        // 2. Iterate from back.
        int returnValue = 0;

        while (!weightOccurrences.empty()) {
            auto itLarge = weightOccurrences.begin();
            const int largeWeight = itLarge->first;
            int largeCount = itLarge->second;

            weightOccurrences.erase(itLarge);    // Base is in fact `end()`. So `--` is needed here.

            // Special case: 2 large persons.
            if ((largeCount > 1) && ((largeWeight * 2) <= limit)) {
                const int boats = largeCount / 2;
                returnValue += boats;

                if (largeCount % 2 == 0) {
                    continue;
                } else {
                    largeCount = 1;
                }
            }

            // A large person and a small person.
            std::vector<int>* weightsToErase = nullptr;

            for (auto& [smallWeight, smallCount]: weightOccurrences) {
                const auto totalWeight = largeWeight + smallWeight;

                if (totalWeight <= limit) {
                    if (largeCount == smallCount) {
                        returnValue += largeCount;
                        largeCount = 0;
                        weightOccurrences.erase(smallWeight);
                        break;
                    } else if (largeCount < smallCount) {
                        returnValue += largeCount;

                        smallCount -= largeCount;
                        largeCount = 0;

                        break;
                    }
                }
            }

            // A single large person.
            returnValue += largeCount;
        }

        return returnValue;
    }
};


#pragma mark - 3. Sort and greedy
// Runtime: 64 ms, faster than 100.00% of C++ online submissions for Boats to Save People.
// Memory Usage: 41.9 MB, less than 100.00% of C++ online submissions for Boats to Save People.
// [Revisit] Note that we prefer choosing the lightest person to pair with the heaviest person: "if the lightest person can pair with anyone, they might as well pair with the heaviest person".
class Solution {
public:
    int numRescueBoats(std::vector<int>& people, int limit) {
        std::sort(people.begin(), people.end());

        int returnValue = 0;

        int bigIndex = people.size() - 1;
        int smallIndex = 0;

        while (smallIndex <= bigIndex) {
            returnValue += 1;

            const int& bigWeight = people[bigIndex];
            const int& smallWeight = people[smallIndex];
            if ((bigWeight + smallWeight) <= limit) {
                smallIndex += 1;
            }

            bigIndex -= 1;
        }

        return returnValue;
    }
};



void test(const std::vector<int>& people, const int& limit, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto peopleCopy = people;
    auto limitCopy = limit;
    auto result = solutionInstance.numRescueBoats(peopleCopy, limitCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << people << " " << limit << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << people << " " << limit << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({3, 2, 2, 1}, 3, 3);
    test({1, 1, 1}, 1, 3);
    test({1, 2}, 3, 1);
    test({3, 5, 3, 4}, 5, 4);

    return 0;
}
