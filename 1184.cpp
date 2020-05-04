/*
 * 1184. Distance Between Bus Stops
 * https://leetcode.com/problems/distance-between-bus-stops/
 */

#include <iostream>
#include <vector>


// Runtime: 4 ms, faster than 94.74% of C++ online submissions for Distance Between Bus Stops.
// Memory Usage: 9 MB, less than 100.00% of C++ online submissions for Distance Between Bus Stops.
class Solution {
public:
    int distanceBetweenBusStops(std::vector<int>& distance, int start, int destination) {
        int stopsCount = distance.size();

        int min = std::min(start, destination);
        int max = std::max(start, destination);

        int sum1 = 0;
        int sum2 = 0;

        size_t i = 0;
        for (; i < min; i += 1) {
            sum1 += distance.at(i);
        }
        for (; i < max; i += 1) {
            sum2 += distance.at(i);
        }
        for (; i < stopsCount; i += 1) {
            sum1 += distance.at(i);
        }

        return std::min(sum1, sum2);
    }
};


int main() {
    auto solutionInstance = Solution();

    std::vector<int> distance1 = {1,2,3,4};
    int start1 = 0;
    int end1 = 1;
    int result1 = solutionInstance.distanceBetweenBusStops(distance1, start1, end1);
    std::cout << result1 << std::endl;    // 1

    std::vector<int> distance2 = {1,2,3,4};
    int start2 = 0;
    int end2 = 2;
    int result2 = solutionInstance.distanceBetweenBusStops(distance2, start2, end2);
    std::cout << result2 << std::endl;    // 3

    return 0;
}
