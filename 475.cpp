/*
 * 475. Heaters
 * https://leetcode.com/problems/heaters/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1
// Runtime: 48 ms, faster than 95.70% of C++ online submissions for Heaters.
// Memory Usage: 25.4 MB, less than 59.78% of C++ online submissions for Heaters.
class Solution {
public:
    int findRadius(std::vector<int>& houses, std::vector<int>& heaters) {
        std::sort(houses.begin(), houses.end());
        std::sort(heaters.begin(), heaters.end());

        int returnValue = 0;

        auto heaterIt = heaters.begin();
        for (const int house: houses) {
            int currentDistance = std::abs(house - *heaterIt);

            auto nextHeaterIt = std::next(heaterIt);
            while (nextHeaterIt != heaters.end()) {
                const int nextDistance = std::abs(house - *nextHeaterIt);
                if (nextDistance <= currentDistance) {    // Equal case: duplicate heaters.
                    currentDistance = nextDistance;
                    heaterIt = nextHeaterIt;
                    std::advance(nextHeaterIt, 1);
                } else {
                    break;
                }
            }

            returnValue = std::max(returnValue, currentDistance);
        }

        return returnValue;
    }
};


void test(const std::vector<int>& houses, const std::vector<int>& heaters, const int expectedResult) {
    auto solutionInstance = Solution();

    auto housesCopy = houses;
    auto heatersCopy = heaters;
    auto result = solutionInstance.findRadius(housesCopy, heatersCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << houses << ", " << heaters << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << houses << ", " << heaters << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    auto longHouses = std::vector<int>(100, 0);
    auto longHeaters = std::vector<int>(100, 0);
    for (int i = 0; i < longHouses.size(); i += 1) {
        longHouses[i] = i;
        longHeaters[i] = i;
    }
    test(longHouses, longHeaters, 0);

    // Test duplicate heaters.
    longHouses.push_back(15);
    longHeaters.push_back(15);
    test(longHouses, longHeaters, 0);

    // Houses and heaters may come in any order.
    test({282475249,622650073,984943658,144108930,470211272,101027544,457850878,458777923}, {823564440,115438165,784484492,74243042,114807987,137522503,441282327,16531729,823378840,143542612}, 161834419);
    test({1,999}, {499,500,501}, 498);
    test({1,1,1,1,1,1,999,999,999,999,999}, {499,500,501}, 498);
    test({1,999}, {499,500,501,502,503}, 498);
    test({1}, {2,3}, 1);
    test({1}, {1,2}, 0);
    test({1,2,3}, {1}, 2);
    test({1}, {1}, 0);
    test({1}, {2}, 1);
    test({1,2,3}, {2}, 1);
    test({1,2,3,4}, {1,4}, 1);
    test({1,5}, {2}, 3);
    test({1,2,3}, {1,2,3}, 0);

    return 0;
}
