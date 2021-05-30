/*
 * 210. Course Schedule II
 * https://leetcode.com/problems/course-schedule-ii/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Graph-like solution: log dependency count and dependants (similar to BFS, but not exactly the same)
// Runtime: 32 ms, faster than 16.22% of C++ online submissions for Course Schedule II.
// Memory Usage: 13.2 MB, less than 92.74% of C++ online submissions for Course Schedule II.
class Solution1 {
public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        if (numCourses == 1) {
            // Course number start at 0.
            return {0};
        }

        // Create graph.
        auto dependencyCounts = std::vector<int>(numCourses, 0);
        auto dependants = std::vector<std::vector<int>>(numCourses, std::vector<int>());

        for (const auto& pair: prerequisites) {
            dependencyCounts[pair[0]] += 1;
            dependants[pair[1]].push_back(pair[0]);
        }

        // Main loop.
        auto returnValue = std::vector<int>();
        for (int i = 0; i < numCourses; i += 1) {
            // Find the first course with no dependencies.
            int course = 0;
            while (course < numCourses) {
                if (dependencyCounts[course] == 0) {
                    break;
                } else {
                    course += 1;
                }
            }

            if (course == numCourses) {
                // No course with 0 dependencies.
                return {};
            }

            returnValue.push_back(course);

            // Update graph.
            dependencyCounts[course] = -1;
            for (const auto& dependant: dependants[course]) {
                dependencyCounts[dependant] -= 1;
            }
        }

        return returnValue;
    }
};


#pragma mark - 2. Optimized 1 (BFS) (reduced loop count) (like question 207)
// Runtime: 24 ms, faster than 43.28% of C++ online submissions for Course Schedule II.
// Memory Usage: 13.4 MB, less than 83.10% of C++ online submissions for Course Schedule II.
class Solution2 {
public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        if (numCourses == 1) {
            // Course number start at 0.
            return {0};
        }

        // Create graph.
        auto dependencyCounts = std::vector<int>(numCourses, 0);
        auto dependants = std::vector<std::vector<int>>(numCourses, std::vector<int>());

        for (const auto& pair: prerequisites) {
            dependencyCounts[pair[0]] += 1;
            dependants[pair[1]].push_back(pair[0]);
        }

        bool noDependencyNodeExists = false;
        for (const auto& dependencyCount: dependencyCounts) {
            if (dependencyCount == 0) {
                noDependencyNodeExists = true;
            }
        }

        // Main loop.
        auto returnValue = std::vector<int>();

        while (noDependencyNodeExists) {
            noDependencyNodeExists = false;

            for (int course = 0; course < numCourses; course += 1) {
                if (dependencyCounts[course] == 0) {
                    returnValue.push_back(course);

                    // Update graph.
                    dependencyCounts[course] = -1;
                    for (const auto& dependant: dependants[course]) {
                        dependencyCounts[dependant] -= 1;
                    }

                    noDependencyNodeExists = true;
                }
            }
        }

        if (returnValue.size() == numCourses) {
            return returnValue;
        } else {
            return {};
        }
    }
};


#pragma mark - 3. Official solution: DFS (revisit)
/*
 * Add a node to `returnValue` after visiting all of its dependants.
 *
 * I think DFS is faster because it finds cycles faster and aborts immediately.
 */
// Runtime: 12 ms, faster than 99.10% of C++ online submissions for Course Schedule II.
// Memory Usage: 14.1 MB, less than 52.04% of C++ online submissions for Course Schedule II.
class Solution {
private:
    [[nodiscard]] bool recursion(const int course, const std::vector<std::vector<int>>& dependants, std::vector<short>& visited, std::vector<int>& returnValue) {
        if (visited[course] == -1) {
            // Cycle.
            return false;
        } else if (visited[course] == 1) {
            // Fully visited.
            return true;
        }

        visited[course] = -1;

        for (const auto& dependant: dependants[course]) {
            const auto result = recursion(dependant, dependants, visited, returnValue);
            if (!result) {
                return false;
            }
        }

        visited[course] = 1;

        returnValue.push_back(course);

        return true;
    }

public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        if (numCourses == 1) {
            // Course number start at 0.
            return {0};
        }

        auto returnValue = std::vector<int>();

        // Create graph.
        auto dependants = std::vector<std::vector<int>>(numCourses, std::vector<int>());
        for (const auto& pair: prerequisites) {
            dependants[pair[1]].push_back(pair[0]);
        }

        /// -1 for being visited, 0 for unvisited, 1 for visited.
        auto visited = std::vector<short>(numCourses, 0);

        // Main loop.
        for (int course = 0; course < numCourses; course += 1) {
            const auto result = recursion(course, dependants, visited, returnValue);
            if (!result) {
                return {};
            }
        }

        std::reverse(returnValue.begin(), returnValue.end());
        return returnValue;
    }
};


void test(const int numCourses, const std::vector<std::vector<int>>& prerequisites, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto prerequisitesCopy = prerequisites;
    auto result = solutionInstance.findOrder(numCourses, prerequisitesCopy);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << numCourses << ", " << prerequisites << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << numCourses << ", " << prerequisites << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(2, {{0,1}}, {1,0});
    test(2, {{1,0}}, {0,1});
    test(4, {{1,0},{2,0},{3,1},{3,2}}, {0,1,2,3});
    test(1, {}, {0});

    return 0;
}
