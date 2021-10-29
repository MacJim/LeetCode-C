/*
 * 1615. Maximal Network Rank
 * https://leetcode.com/problems/maximal-network-rank/
 */

#include <iostream>
#include <vector>
#include <unordered_set>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Try every pair of cities & use an unordered set to store roads
// Runtime: 80 ms, faster than 78.66% of C++ online submissions for Maximal Network Rank.
// Memory Usage: 33 MB, less than 58.62% of C++ online submissions for Maximal Network Rank.
class Solution {
private:
    inline int getRoadHash(const int city1, const int city2) {
        if (city1 < city2) {
            return city1 * 128 + city2;
        } else {
            return city2 * 128 + city1;
        }
    }

    inline int getRoadHash(const std::vector<int>& road) {
        // We have up to 100 cities.
        if (road[0] < road[1]) {
            return road[0] * 128 + road[1];
        } else {
            return road[1] * 128 + road[0];
        }
    }

public:
    int maximalNetworkRank(const int citiesCount, const std::vector<std::vector<int>>& roads) {
        // Calculate each city's road counts.
        auto cityDegrees = std::vector<int>(citiesCount, 0);
        for (const auto& road: roads) {
            cityDegrees[road[0]] += 1;
            cityDegrees[road[1]] += 1;
        }

        // Sort cities according to road counts (no longer needed because I calculate all pairs anyway).
//        auto cities = std::vector<int>(citiesCount, 0);
//        for (int i = 1; i < citiesCount; i += 1) {
//            cities[i] = i;
//        }
//
//        auto cmp = [&cityDegrees] (const int& lhs, const int& rhs) -> bool {
//            return cityDegrees[lhs] > cityDegrees[rhs];
//        };
//        std::sort(cities.begin(), cities.end(), cmp);

        // Convert roads into hashes.
        auto roadHashes = std::unordered_set<int>();
        for (const auto& road: roads) {
            const int roadHash = getRoadHash(road);
            roadHashes.insert(roadHash);
        }

        // Try all pairs.
        int returnValue = 0;
        for (int i1 = 0; i1 < citiesCount; i1 += 1) {
            for (int i2 = i1 + 1; i2 < citiesCount; i2 += 1) {
                int currentValue = cityDegrees[i1] + cityDegrees[i2];

                const int roadHash = getRoadHash(i1, i2);
                if (roadHashes.count(roadHash)) {
                    // The 2 cities are connected by a road.
                    currentValue -= 1;
                }

                returnValue = std::max(returnValue, currentValue);
            }
        }

        return returnValue;
    }
};


void test(const int citiesCount, const std::vector<std::vector<int>>& roads, const int expectedResult) {
    auto solutionInstance = Solution();

    auto result = solutionInstance.maximalNetworkRank(citiesCount, roads);

    if (result == expectedResult) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << citiesCount << ", " << roads << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << citiesCount << ", " << roads << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test(8, {{0,1},{1,2},{2,3},{2,4},{5,6},{5,7}}, 5);    // The chosen cities don't need to be connected.
    test(4, {{0,1},{0,3},{1,2},{1,3}}, 4);
    test(5, {{0,1},{0,3},{1,2},{1,3},{2,3},{2,4}}, 5);

    return 0;
}
