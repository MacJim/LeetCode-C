/*
 * 743. Network Delay Time
 * https://leetcode.com/problems/network-delay-time/
 */

/*
 * Do we judge connectivity using the disjoint set structure?
 */

#include <iostream>
#include <vector>
#include <set>
#include <queue>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Dijkstra's algorithm
// Runtime: 112 ms, faster than 66.41% of C++ online submissions for Network Delay Time.
// Memory Usage: 41.4 MB, less than 45.71% of C++ online submissions for Network Delay Time.
class Solution1 {
public:
    int networkDelayTime(const std::vector<std::vector<int>>& times, const int nodeCount, int start) {
        if (nodeCount == 1) {
            // Guaranteed to be no circles on the same node.
            return 0;
        }

        start -= 1;    // Question is 1-indexed.

        // Create graph.
        auto graph = std::vector<std::vector<std::pair<int, int>>>(nodeCount, std::vector<std::pair<int, int>>());    // Up to 100 nodes. Using vector instead of unordered_map.
        for (const auto& t: times) {
            graph[t[0] - 1].emplace_back(t[1] - 1, t[2]);
        }

        // Dijkstra's algorithm.
        /// `INT_MAX` means unreachable.
        auto distances = std::vector<int>(nodeCount, INT_MAX);
        distances[start] = 0;

        auto cmp = [&distances] (const int& lhs, const int& rhs) -> bool {
            if (distances[lhs] == distances[rhs]) {
                return lhs < rhs;    // Make sure that they don't equal.
            } else {
                return distances[lhs] < distances[rhs];
            }
        };
        auto unvisitedNodes = std::set<int, decltype(cmp)>(cmp);
        for (int i = 0; i < nodeCount; i += 1) {
            unvisitedNodes.insert(i);
        }

        while (!unvisitedNodes.empty()) {
            const int currentNode = *unvisitedNodes.begin();
            const int& currentDistance = distances[currentNode];
            if (currentDistance == INT_MAX) {
                // All remaining nodes are unreachable.
                return -1;
            }

            unvisitedNodes.erase(unvisitedNodes.begin());    // Mark the current node as visited.

            auto currentNeighbors = graph[currentNode];
            for (const auto& [neighbor, distance]: currentNeighbors) {
                if (unvisitedNodes.count(neighbor) == 0) {
                    // This neighbor's been visited.
                    continue;
                }

                const int newDistance = currentDistance + distance;
                if (newDistance < distances[neighbor]) {
                    // Update neighbor's distance.
                    unvisitedNodes.erase(neighbor);
                    distances[neighbor] = newDistance;
                    unvisitedNodes.insert(neighbor);
                }
            }
        }

        return *std::max_element(distances.begin(), distances.end());
    }
};


#pragma mark - 2. Use a binary heap
// Doesn't work because I can't easily find a number in the heap.
class Solution2 {
public:
    int networkDelayTime(const std::vector<std::vector<int>>& times, const int nodeCount, int start) {
        // Edge case: No need to travel.
        if (nodeCount == 1) {
            return 0;
        }

        // Create graph.
        auto graph = std::vector<std::vector<std::pair<int, int>>>(nodeCount + 1, std::vector<std::pair<int, int>>());  // Up to 100 nodes. Using vector instead of unordered_map.
        for (const auto& t: times) {
            graph[t[0]].emplace_back(t[1], t[2]);
        }

        // Priority queue.
        auto distances = std::vector<int>(nodeCount + 1, INT_MAX);  // The nodes are 1-indexed.
        distances[start] = 0;

        auto cmp = [&distances] (const int& lhs, const int& rhs) -> bool {
            return distances[lhs] > distances[rhs];
        };
        auto heap = std::priority_queue<int, std::vector<int>, decltype(cmp)>(cmp);
        for (int i = 1; i <= nodeCount; i += 1) {  // Note: 1-indexed
            heap.push(i);
        }

        int currentNode = -1;
        while (!heap.empty()) {
            currentNode = heap.top();
            heap.pop();

            for (const auto& [neighbor, distance]: graph[currentNode]) {
                // TODO: Can't easily tell if the neighbor is in the heap.
            }
        }

        if (heap.empty()) {
            return distances[currentNode];
        } else {
            // Has unreachable nodes.
            return -1;
        }
    }
};


#pragma mark - 3. Optimized 1. Dijkstra's algorithm
// Hmm. Why is this slower than 1? Maybe new test cases got added sometime in between?
// Runtime: 263 ms, faster than 23.82% of C++ online submissions for Network Delay Time.
// Memory Usage: 40.4 MB, less than 56.23% of C++ online submissions for Network Delay Time.
class Solution {
public:
    int networkDelayTime(const std::vector<std::vector<int>>& times, const int nodeCount, const int start) {
        if (nodeCount == 1) {
            // Guaranteed to be no circles on the same node.
            return 0;
        }

        // Create graph.
        auto graph = std::vector<std::vector<std::pair<int, int>>>(nodeCount + 1, std::vector<std::pair<int, int>>());  // Up to 100 nodes. Using vector instead of unordered_map. Note 1-index.
        for (const auto& t: times) {
            graph[t[0]].emplace_back(t[1], t[2]);
        }

        // Dijkstra's algorithm.
        /// `INT_MAX` means unreachable.
        auto distances = std::vector<int>(nodeCount + 1, INT_MAX);  // Note 1-index.
        distances[start] = 0;

        auto cmp = [&distances] (const int& lhs, const int& rhs) -> bool {
            if (distances[lhs] == distances[rhs]) {
                return lhs < rhs;    // Make sure that they don't equal. TODO: Is this necessary?
            } else {
                return distances[lhs] < distances[rhs];
            }
        };
        auto unvisitedNodes = std::set<int, decltype(cmp)>(cmp);
        for (int i = 1; i <= nodeCount; i += 1) {  // Note 1-index.
            unvisitedNodes.insert(i);
        }

        int currentNode = -1;
        while (!unvisitedNodes.empty()) {
            currentNode = *unvisitedNodes.begin();
            const int& currentDistance = distances[currentNode];
            if (currentDistance == INT_MAX) {
                // All remaining nodes are unreachable.
                return -1;
            }

            unvisitedNodes.erase(unvisitedNodes.begin());    // Mark the current node as visited.

            for (const auto& [neighbor, distance]: graph[currentNode]) {
                if (unvisitedNodes.count(neighbor) == 0) {
                    // This neighbor's been visited.
                    continue;
                }

                const int newDistance = currentDistance + distance;
                if (newDistance < distances[neighbor]) {
                    // Update neighbor's distance.
                    unvisitedNodes.erase(neighbor);
                    distances[neighbor] = newDistance;
                    unvisitedNodes.insert(neighbor);
                }
            }
        }

        return distances[currentNode];
    }
};


void test(const std::vector<std::vector<int>>& times, const int nodeCount, const int start, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.networkDelayTime(times, nodeCount, start);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << times << ", " << nodeCount << ", " << start << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << times << ", " << nodeCount << ", " << start << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{2,1,1},{2,3,1},{3,4,1}}, 4, 2, 2);
    test({{2,1,1},{2,3,1},{3,4,1}}, 4, 3, -1);
    test({{1,2,1}}, 2, 1, 1);
    test({{1,2,1}}, 2, 2, -1);

    return 0;
}
