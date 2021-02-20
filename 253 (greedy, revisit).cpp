/*
 * 253. Meeting Rooms II
 * https://leetcode.com/problems/meeting-rooms-ii/
 */

/*
 * Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.
 *
 * Example 1:
 * Input: [[0, 30],[5, 10],[15, 20]]
 * Output: 2
 *
 * Example 2:
 * Input: [[7,10],[2,4]]
 * Output: 1
 *
 * NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>

#include "helpers/Operators.hpp"


#pragma mark - 1. Sort according to start time and cache end times
class Solution1 {
public:
    int minMeetingRooms(std::vector<std::vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        }

//        std::sort(intervals.begin(), intervals.end(), [] (const std::vector<int>& left, const std::vector<int>& right) {
//            const auto leftDistance = left[1] - left[0];
//            const auto rightDistance = right[1] - right[0];
//
//            return (leftDistance < rightDistance);    // Longest interval last.
//        });

        std::sort(intervals.begin(), intervals.end(), [] (const std::vector<int>& left, const std::vector<int>& right) {
            return (left[0] < right[0]);
        });

        auto endTimes = std::vector<int>();

        for (const auto& interval: intervals) {
            if (endTimes.empty()) {
                endTimes.push_back(interval[1]);
            } else {
                const auto& currentStartTime = interval[0];

                // MARK: Here: actually no need to find the max one because the upcoming intervals all start later.
                int maxEndTimeIndex = -1;
                for (int i = 0; i < endTimes.size(); i += 1) {
                    const auto& currentEndTime = endTimes[i];
                    if (currentEndTime <= currentStartTime) {
                        if ((maxEndTimeIndex == -1) || (currentEndTime > endTimes[maxEndTimeIndex])) {
                            maxEndTimeIndex = i;
                        }
                    }
                }

                const auto& currentEndTime = interval[1];
                if (maxEndTimeIndex == -1) {
                    // Overlaps with all existing time intervals.
                    endTimes.push_back(currentEndTime);
                } else {
                    // Update end time
                    endTimes[maxEndTimeIndex] = currentEndTime;
                }
            }
        }

        return endTimes.size();
    }
};


#pragma mark - 2. Optimized 1 using a min heap (revisit)
class Solution {
public:
    int minMeetingRooms(std::vector<std::vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        }

        std::sort(intervals.begin(), intervals.end(), [] (const std::vector<int>& left, const std::vector<int>& right) {
            return (left[0] < right[0]);
        });

        auto endTimes = std::priority_queue<int, std::vector<int>, std::greater<>>();

        for (const auto& interval: intervals) {
            if (endTimes.empty()) {
                endTimes.push(interval[1]);
            } else {
                const auto& currentStartTime = interval[0];
                const auto& currentEndTime = interval[1];

                if (endTimes.top() > currentStartTime) {
                    endTimes.push(currentEndTime);
                } else {
                    endTimes.pop();
                    endTimes.push(currentEndTime);
                }
            }
        }

        return endTimes.size();
    }
};


void test(const std::vector<std::vector<int>>&& intervals, const int expectedResult) {
    static auto solutionInstance = Solution();

    auto intervalsCopy = intervals;
    auto result = solutionInstance.minMeetingRooms(intervalsCopy);

    if (result == expectedResult) {
        std::cout << "[Correct] " << intervals << ": " << result << std::endl;
    } else {
        std::cout << "[Wrong] " << intervals << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{0, 30},{5, 10},{15, 20}}, 2);
    test({{7,10},{2,4}}, 1);
    test({{10,20},{15,25},{20,30}}, 2);

    return 0;
}
