/*
 * 207. Course Schedule
 * https://leetcode.com/problems/course-schedule/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Kahn's algorithm-based (BFS) (revisit)
// Runtime: 20 ms, faster than 88.84% of C++ online submissions for Course Schedule.
// Memory Usage: 13.2 MB, less than 91.51% of C++ online submissions for Course Schedule.
class Solution1 {
public:
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        if (numCourses < 2) {
            return true;
        }

        // Build a graph
        /// A graph of out nodes.
        auto graph = std::vector<std::vector<int>>(numCourses, std::vector<int>());
        /// Direct dependencies count.
        auto inDegrees = std::vector<int>(numCourses, 0);

        bool hasPositiveDegree = false;
        for (const auto& p: prerequisites) {
            graph[p[1]].push_back(p[0]);
            inDegrees[p[0]] += 1;
            hasPositiveDegree = true;
        }

        // (Roughly) Kahn's algorithm.
        while (hasPositiveDegree) {
            hasPositiveDegree = false;
            bool hasZeroDegree = false;

            for (int i = 0; i < numCourses; i += 1) {
                if (inDegrees[i] > 0) {
                    hasPositiveDegree = true;
                } else if (inDegrees[i] == 0) {
                    inDegrees[i] = -1;
                    for (const auto& dependant: graph[i]) {
                        inDegrees[dependant] -= 1;
                    }

                    hasZeroDegree = true;
                }
            }

            if (!hasZeroDegree) {
                return false;
            }
        }


        return true;
    }
};


#pragma mark - 2. DFS (revisit)
// Source: https://leetcode.com/problems/course-schedule/discuss/58586/Python-20-lines-DFS-solution-sharing-with-explanation
// Runtime: 16 ms, faster than 97.38% of C++ online submissions for Course Schedule.
// Memory Usage: 13.7 MB, less than 73.14% of C++ online submissions for Course Schedule.
class Solution {
private:
    bool dfs(const std::vector<std::vector<int>>& graph, std::vector<short>& nodeStatus, const int i) {
        auto& status = nodeStatus[i];
        if (status == -1) {
            return false;
        } else if (status == 1) {
            return true;
        }

        status = -1;

        for (const auto& dependant: graph[i]) {
            const auto result = dfs(graph, nodeStatus, dependant);
            if (!result) {
                return false;
            }
        }

        status = 1;

        return true;
    }

public:
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        if (numCourses < 2) {
            return true;
        }

        // Build a graph
        /// A graph of out nodes.
        auto graph = std::vector<std::vector<int>>(numCourses, std::vector<int>());

        for (const auto& p: prerequisites) {
            graph[p[1]].push_back(p[0]);
        }

        // DFS


        /// -1 for being visited, 0 for unvisited, 1 for visited.
        auto nodeStatus = std::vector<short>(numCourses, 0);
        for (int i = 0; i < numCourses; i += 1) {
            const auto result = dfs(graph, nodeStatus, i);
            if (!result) {
                return false;
            }
//            auto& status = nodeStatus[i];
//            if (status == 1) {
//                continue;
//            } else if (status == 0) {
//                status = -1;
//
//                auto nodesToVisit = std::stack<int>();
//                for (const auto& dependant: graph[i]) {
//                    nodesToVisit.push(dependant);
//                }
//
//                while (!nodesToVisit.empty()) {
//                    auto topNode = nodesToVisit.top();
//
//                    if (nodeStatus[topNode] == -1) {
//                        return false;
//                    }
//
//                    nodesToVisit.pop();
//
//                    nodeStatus[topNode] = -1;
//                    for (const auto& dependant: graph[topNode]) {
//                        nodesToVisit.push(dependant);
//                    }
//
//                    nodeStatus[topNode]
//                }
//            }
        }

        return true;
    }
};


void test(const int numCourses, const std::vector<std::vector<int>>& prerequisites, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto prerequisitesCopy = prerequisites;
    auto result = solutionInstance.canFinish(numCourses, prerequisitesCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << numCourses << prerequisites << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << numCourses << prerequisites << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(2, {{1,0}}, true);
    test(2, {{0,1}}, true);
    test(2, {{1,0}, {0,1}}, false);
    test(4, {{1,0}, {2,1}, {3,2}}, true);
    test(4, {{1,0}, {2,1}, {3,2}, {0,3}}, false);
    test(100, {{1,0},{2,0},{2,1},{3,1},{3,2},{4,2},{4,3},{5,3},{5,4},{6,4},{6,5},{7,5},{7,6},{8,6},{8,7},{9,7},{9,8},{10,8},{10,9},{11,9},{11,10},{12,10},{12,11},{13,11},{13,12},{14,12},{14,13},{15,13},{15,14},{16,14},{16,15},{17,15},{17,16},{18,16},{18,17},{19,17},{19,18},{20,18},{20,19},{21,19},{21,20},{22,20},{22,21},{23,21},{23,22},{24,22},{24,23},{25,23},{25,24},{26,24},{26,25},{27,25},{27,26},{28,26},{28,27},{29,27},{29,28},{30,28},{30,29},{31,29},{31,30},{32,30},{32,31},{33,31},{33,32},{34,32},{34,33},{35,33},{35,34},{36,34},{36,35},{37,35},{37,36},{38,36},{38,37},{39,37},{39,38},{40,38},{40,39},{41,39},{41,40},{42,40},{42,41},{43,41},{43,42},{44,42},{44,43},{45,43},{45,44},{46,44},{46,45},{47,45},{47,46},{48,46},{48,47},{49,47},{49,48},{50,48},{50,49},{51,49},{51,50},{52,50},{52,51},{53,51},{53,52},{54,52},{54,53},{55,53},{55,54},{56,54},{56,55},{57,55},{57,56},{58,56},{58,57},{59,57},{59,58},{60,58},{60,59},{61,59},{61,60},{62,60},{62,61},{63,61},{63,62},{64,62},{64,63},{65,63},{65,64},{66,64},{66,65},{67,65},{67,66},{68,66},{68,67},{69,67},{69,68},{70,68},{70,69},{71,69},{71,70},{72,70},{72,71},{73,71},{73,72},{74,72},{74,73},{75,73},{75,74},{76,74},{76,75},{77,75},{77,76},{78,76},{78,77},{79,77},{79,78},{80,78},{80,79},{81,79},{81,80},{82,80},{82,81},{83,81},{83,82},{84,82},{84,83},{85,83},{85,84},{86,84},{86,85},{87,85},{87,86},{88,86},{88,87},{89,87},{89,88},{90,88},{90,89},{91,89},{91,90},{92,90},{92,91},{93,91},{93,92},{94,92},{94,93},{95,93},{95,94},{96,94},{96,95},{97,95},{97,96},{98,96},{98,97},{99,97}},
         true);
    return 0;
}
