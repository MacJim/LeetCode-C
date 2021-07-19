/*
 * 821. Shortest Distance to a Character
 * https://leetcode.com/problems/shortest-distance-to-a-character/
 */

#include <iostream>
#include <vector>
#include <string>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1
// Runtime: 4 ms, faster than 69.50% of C++ online submissions for Shortest Distance to a Character.
// Memory Usage: 6.6 MB, less than 83.44% of C++ online submissions for Shortest Distance to a Character.
class Solution {
private:
    static constexpr int MAX_LEN = 10000;

public:
    std::vector<int> shortestToChar(const std::string& s, const char c) {
//        bool previousOccurrence = false;

        auto returnValue = std::vector<int>(s.size(), MAX_LEN);

        for (int currentIndex = 0; currentIndex < s.size(); currentIndex += 1) {
            if (s[currentIndex] == c) {
                returnValue[currentIndex] = 0;

                // Update previous.
                for (int previousIndex = (currentIndex - 1); previousIndex >= 0; previousIndex -= 1) {
                    const int potentialNewDistance = returnValue[previousIndex + 1] + 1;
                    if (potentialNewDistance < returnValue[previousIndex]) {
                        returnValue[previousIndex] = potentialNewDistance;
                    } else {
                        break;
                    }
                }

//                previousOccurrence = true;
            } else {
                if (currentIndex != 0) {
                    returnValue[currentIndex] = returnValue[currentIndex - 1] + 1;
                }
            }
        }

        return returnValue;
    }
};


void test(const std::string& s, const char c, const std::vector<int>& expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.shortestToChar(s, c);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << s << " " << c << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << s << " " << c << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test("aaab", 'b', {3,2,1,0});
    test("loveleetcode", 'e', {3,2,1,0,1,0,0,1,2,2,1,0});
    test("leetcode", 'e', {1,0,0,1,2,2,1,0});

    return 0;
}
