/*
 * 847. Shortest Path Visiting All Nodes
 * https://leetcode.com/problems/shortest-path-visiting-all-nodes/
 */

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <set>
#include <unordered_set>
#include <exception>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. BFS with memorization (revisit)
// Source: https://leetcode.com/problems/shortest-path-visiting-all-nodes/discuss/135809/Fast-BFS-Solution-(46ms)-Clear-Detailed-Explanation-Included
/*
 * - BFS: All paths in the current loop have the same length
 * - Memorization: (current node, visited nodes)
 */
// Runtime: 168 ms, faster than 28.79% of C++ online submissions for Shortest Path Visiting All Nodes.
// Memory Usage: 19.2 MB, less than 37.61% of C++ online submissions for Shortest Path Visiting All Nodes.

/// (current node, visited nodes bitmask)
using Element1 = std::pair<size_t, int>;

class Solution1 {
public:
    int shortestPathLength(const std::vector<std::vector<int>>& graph) {
        const size_t N = graph.size();
        const int allNodesBitmask = (1 << N) - 1;

        auto currentPaths = std::deque<Element1>();
        auto visitedPaths = std::set<Element1>();

        for (size_t i = 0; i < N; i += 1) {
            const int bitmask = 1 << i;
            currentPaths.emplace_back(i, bitmask);
            visitedPaths.emplace(i, bitmask);
        }

        int currentLength = 1;
        // Main loop.
        while (true) {
            auto nextPaths = std::deque<Element1>();

            for (const auto [currentNode, currentBitmask]: currentPaths) {
                if (currentBitmask == allNodesBitmask) {
                    // All nodes are visited. Return.
                    currentLength -= 1;
                    return currentLength;
                }

                // Some nodes are not visited.
                // Visit all neighbors.
                const auto& neighbors = graph[currentNode];

                for (const int& neighbor: neighbors) {
                    const int newBitmask = (1 << neighbor) | currentBitmask;

                    auto newPair = std::make_pair(neighbor, newBitmask);
                    if (!visitedPaths.count(newPair)) {
                        // This path is new.
                        nextPaths.emplace_back(newPair);
                        visitedPaths.emplace(newPair);
                    }
                }
            }

            currentPaths = std::move(nextPaths);
            currentLength += 1;
        }
    }
};


#pragma mark - 2. Improved 1: replaces `set` with `unordered_set` with custom hash function
// Runtime: 84 ms, faster than 44.46% of C++ online submissions for Shortest Path Visiting All Nodes.
// Memory Usage: 20.6 MB, less than 29.02% of C++ online submissions for Shortest Path Visiting All Nodes.

/// (current node, visited nodes bitmask)
using Element = std::pair<size_t, int>;

template<>
struct std::hash<Element> {
    std::size_t operator() (const Element& element) const noexcept {
        return (element.first << 12) | element.second;
    }
};

class Solution {
public:
    int shortestPathLength(const std::vector<std::vector<int>>& graph) {
        const size_t N = graph.size();
        const int allNodesBitmask = (1 << N) - 1;

        auto currentPaths = std::deque<Element>();
        auto visitedPaths = std::unordered_set<Element>();

        for (size_t i = 0; i < N; i += 1) {
            const int bitmask = 1 << i;
            currentPaths.emplace_back(i, bitmask);
            visitedPaths.emplace(i, bitmask);
        }

        int currentLength = 1;
        // Main loop.
        while (true) {
            auto nextPaths = std::deque<Element>();

            for (const auto [currentNode, currentBitmask]: currentPaths) {
                if (currentBitmask == allNodesBitmask) {
                    // All nodes are visited. Return.
                    currentLength -= 1;
                    return currentLength;
                }

                // Some nodes are not visited.
                // Visit all neighbors.
                const auto& neighbors = graph[currentNode];

                for (const int& neighbor: neighbors) {
                    const int newBitmask = (1 << neighbor) | currentBitmask;

                    auto newPair = std::make_pair(neighbor, newBitmask);
                    if (!visitedPaths.count(newPair)) {
                        // This path is new.
                        nextPaths.emplace_back(newPair);
                        visitedPaths.emplace(newPair);
                    }
                }
            }

            currentPaths = std::move(nextPaths);
            currentLength += 1;
        }
    }
};


void test(const std::vector<std::vector<int>>& graph, const int expectedResult) {
    auto solutionInstance = Solution();

//    auto graphCopy = graph;
    auto result = solutionInstance.shortestPathLength(graph);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << graph << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << graph << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{1,2,3},{0},{0},{0}}, 4);
    test({{1},{0,2,4},{1,3,4},{2},{1,2}}, 4);

    return 0;
}
