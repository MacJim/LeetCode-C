/*
 * 621. Task Scheduler
 * https://leetcode.com/problems/task-scheduler/
 */

/*
 * Characters are only uppercase English letters.
 */

#include <iostream>
#include <vector>
//#include <unordered_map>
#include <array>

#include "helpers/Operators.hpp"


#pragma mark - 1. Use vector cache to arrange the tasks
// Runtime: 176 ms, faster than 19.07% of C++ online submissions for Task Scheduler.
// Memory Usage: 34.4 MB, less than 90.86% of C++ online submissions for Task Scheduler.
class Solution {
public:
    int leastInterval(std::vector<char>& tasks, const int n) {
        if (tasks.empty()) {
            return 0;
        }

        auto occurrences = std::array<int, 26>();
        for (const auto& t: tasks) {
            size_t i = t - 'A';
            occurrences[i] += 1;
        }

        auto cooldown = std::array<int, 26>();

        int returnValue = 0;
        bool tasksRemaining;

        do {
            tasksRemaining = false;

            // Find the biggest occurrence with no cooldown.
            size_t currentIndex = 27;
            for (size_t i = 0; i < 26; i += 1) {
                if (occurrences[i] > 0) {
                    tasksRemaining = true;
                } else {
                    continue;
                }

                if (cooldown[i] > 0) {
                    cooldown[i] -= 1;
                    continue;
                }

                if ((currentIndex == 27) || (occurrences[i] > occurrences[currentIndex])) {
                    currentIndex = i;
                }
            }

            if (currentIndex != 27) {
                // Valid job found.
                occurrences[currentIndex] -= 1;
                cooldown[currentIndex] = n;
            }

            returnValue += 1;    // This is executed in the last iteration where `tasksRemaining` is false. Thus we need to subtract it by 1.
        } while (tasksRemaining);

        return (returnValue - 1);
    }
};


#pragma mark - 2. No arrangement, find out the amount of idles needed (revisit)
// Source: https://leetcode.com/problems/task-scheduler/discuss/104500/Java-O(n)-time-O(1)-space-1-pass-no-sorting-solution-with-detailed-explanation


void test(const std::vector<char>& tasks, const int n, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto tasksCopy = tasks;
    auto result = solutionInstance.leastInterval(tasksCopy, n);

    if (result == expectedResult) {
        std::cout << "[Correct] " << tasks << " " << n << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << tasks << " " << n << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({'A', 'A', 'A'}, 2, 7);
    test({'A', 'A', 'A', 'B', 'B', 'B'}, 2, 8);
    test({'A', 'A', 'A', 'B', 'B', 'B'}, 0, 6);
    test({'A','A','A','A','A','A','B','C','D','E','F','G'}, 2, 16);
    test({'A','A','A','B','B','C','C','D','D','E','E','F','F'}, 2, 13);

    return 0;
}
