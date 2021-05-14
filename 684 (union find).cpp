/*
 * 684. Redundant Connection
 * https://leetcode.com/problems/redundant-connection/
 */

#include <iostream>
#include <vector>

#include "helpers/Operators.hpp"


#pragma mark - 1. Disjoint set/union find, without "union by rank" or "path compression" optimizations
/*
 * This is insane: I just learned about the union find algorithm earlier today!
 *
 * More information: https://www.geeksforgeeks.org/disjoint-set-data-structures/
 */
// Runtime: 4 ms, faster than 97.56% of C++ online submissions for Redundant Connection.
// Memory Usage: 8.7 MB, less than 94.68% of C++ online submissions for Redundant Connection.
class Solution {
private:
    inline int findRepresentative(std::vector<int>& parents, int index) {
        if (parents[index] == -1) {
            return -1;
        }

        while (parents[index] != index) {
            index = parents[index];
        }

        return index;
    }

    inline void uniteTrees(std::vector<int>& parents, int representative1, int representative2) {
        parents[representative1] = representative2;
    }

public:
    std::vector<int> findRedundantConnection(std::vector<std::vector<int>>& edges) {
        auto parents = std::vector<int>(edges.size(), -1);

        for (const auto& edge: edges) {
            const auto& start = edge[0] - 1;
            const auto& end = edge[1] - 1;

            const auto startRepresentative = findRepresentative(parents, start);
            const auto endRepresentative = findRepresentative(parents, end);

            if ((startRepresentative == -1) && (endRepresentative == -1)) {
                parents[start] = start;
                parents[end] = start;
            } else if (startRepresentative == -1) {
                parents[start] = end;
            } else if (endRepresentative == -1) {
                parents[end] = start;
            } else if (startRepresentative == endRepresentative) {
                // The 2 points are already connected.
                return edge;
            } else {
                uniteTrees(parents, startRepresentative, endRepresentative);
            }
        }

        throw std::runtime_error("Should never reach here.");
    }
};


void test(const std::vector<std::vector<int>>& edges, const std::vector<int>& expectedResult) {
    static auto solutionInstance = Solution();

    auto edgesCopy = edges;
    auto result = solutionInstance.findRedundantConnection(edgesCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << edges << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << edges << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{1,2},{1,3},{2,3}}, {2,3});
    test({{1,2},{2,3},{3,4},{1,4},{1,5}}, {1,4});
    test({{2,3},{4,5},{1,2},{3,4},{5,1}}, {5,1});
    test({{2,3},{4,5},{1,2},{5,1},{3,4}}, {3,4});
    test({{2,3},{4,5},{1,2},{5,1},{3,4},{1,6}}, {3,4});

    return 0;
}
