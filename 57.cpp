/*
 * 57. Insert Interval
 * https://leetcode.com/problems/insert-interval/
 */

#include <iostream>
#include <vector>


// MARK: - 1
// This solution is wrong.
class Solution1 {
public:
    std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) {
        auto existingIntervalsCount = intervals.size();
        if (existingIntervalsCount == 0) {
            return {newInterval};
        }

        // Get the minimum interval whose start is larger than the new interval start.
        size_t frontIndex = 0;
        for (; frontIndex < existingIntervalsCount; frontIndex += 1) {
            const auto& currentInterval = intervals.at(frontIndex);
            if (currentInterval.at(0) < newInterval.at(0)) {
                break;
            }
        }
        if (frontIndex >= existingIntervalsCount) {
            // No interval start is larger than the new interval start.
            auto returnValue = std::move(intervals);
            returnValue.push_back(newInterval);
            return returnValue;
        }
        
        // Get the maximum interval whose end is smaller than the new interval end.
        size_t backIndex = existingIntervalsCount - 1;
        for (; backIndex >= 0; backIndex -= 1) {
            const auto& currentInterval = intervals.at(frontIndex);
            if (currentInterval.at(1) < newInterval.at(1)) {
                break;
            }
        }
        if (backIndex < 0) {
            // No interval end is smaller than the new interval end.
            auto returnValue = std::move(intervals);
            returnValue.insert(returnValue.begin(), newInterval);
            return returnValue;
        }
        
        if ((frontIndex - backIndex) == 1) {
            // No overlap with existing intervals.
            auto returnValue = std::move(intervals);
            returnValue.insert(returnValue.begin() + frontIndex, newInterval);
            return returnValue;
        } else if (backIndex >= frontIndex) {
            
        }
        
        return {};
    }
};


// MARK: - 2
// Not finished.
class Solution2 {
public:
    std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) {
        auto existingIntervalsCount = intervals.size();
        if (existingIntervalsCount == 0) {
            return {newInterval};
        }
        
        // Reference the sorting algorithm of question 56.
        /// The start at this index is larger than the new interval's start.
        size_t leftIndex = 0;
        for (; leftIndex < (existingIntervalsCount - 1); leftIndex += 1) {
            const auto& currentInterval = intervals.at(leftIndex);
            if (currentInterval.at(0) > newInterval.at(0)) {
                // This is the first existing start value that is larger than the new start value.
                break;
            }
        }
        
        // Left overlap.
        size_t newIntervalIndex = 0;
        if (leftIndex > 0) {
            // Overlap with the left interval.
            const size_t leftIndex = leftIndex - 1;
            auto& leftInterval = intervals.at(leftIndex);
            if (leftInterval.at(1) > newInterval.at(0)) {
                // They overlap.
                leftInterval.at(1) = newInterval.at(1);
                newIntervalIndex = leftIndex;
            } else {
                // They don't overlap.
                newIntervalIndex = leftIndex + 1;
                intervals.insert(intervals.begin() + newIntervalIndex, newInterval);
                existingIntervalsCount = intervals.size();
            }
        } else {
            // This is the first interval.
            intervals.insert(intervals.begin(), newInterval);
            existingIntervalsCount = intervals.size();
        }
        
        // Right overlap.
        size_t rightIndex = -1;
        if (leftIndex < existingIntervalsCount) {
            // Overlap with the right intervals.
            for (size_t currentRightIndex = newIntervalIndex; currentRightIndex < existingIntervalsCount; currentRightIndex += 1) {
                const auto& currentRightInterval = intervals.at(currentRightIndex);
                if (currentRightInterval.at(0) < newInterval.at(1)) {
                    // Overlaps.
                    rightIndex = currentRightIndex;
                }
            }
        }
        if (rightIndex != -1) {
            
        }
        
        return intervals;
    }
};


// MARK: - 3. XJBD and it works
// Runtime: 16 ms, faster than 84.04% of C++ online submissions for Insert Interval.
// Memory Usage: 12.7 MB, less than 25.00% of C++ online submissions for Insert Interval.
class Solution3 {
public:
    std::vector<std::vector<int>> insert(const std::vector<std::vector<int>>& intervals, const std::vector<int>& newInterval) {
        auto existingIntervalsCount = intervals.size();
        if (existingIntervalsCount == 0) {
            return {newInterval};
        }

        auto returnValue = std::vector<std::vector<int>>();
        
        // Reference the sorting algorithm of question 56.
        /// The start at this index is larger than the new interval's start.
        int thresholdIndex = 0;    // This variable must be signed.
        for (; thresholdIndex < existingIntervalsCount; thresholdIndex += 1) {
            const auto& currentInterval = intervals.at(thresholdIndex);
            if (currentInterval.at(0) > newInterval.at(0)) {
                // This is the first existing start value that is larger than the new start value.
                break;
            }
        }
        
        // Left overlap.
        thresholdIndex -= 1;
        if (thresholdIndex >= 0) {
            // Overlap with the left interval.
            returnValue.insert(returnValue.end(), intervals.begin(), intervals.begin() + thresholdIndex);
            
            const auto& leftInterval = intervals.at(thresholdIndex);
            if (leftInterval.at(1) >= newInterval.at(0)) {
                // They overlap.
                returnValue.push_back({leftInterval.at(0), std::max(leftInterval.at(1), newInterval.at(1))});
            } else {
                // They don't overlap.
                returnValue.push_back(leftInterval);
                returnValue.push_back(newInterval);
            }
        } else {
            // This is the first interval.
            returnValue.push_back(newInterval);
        }
        
        // Right overlap.
        thresholdIndex += 1;
        // Now we start from `leftIndex` in the `intervals` array.
        // The new inteval is at the back of the `returnValue` array.
        size_t rightIndex = -1;
        for (size_t i = thresholdIndex; i < existingIntervalsCount; i += 1) {
            const auto& currentRightInterval = intervals.at(i);
            if (currentRightInterval.at(0) <= returnValue.back().at(1)) {
                // Overlap.
                rightIndex = i;
            } else {
                // Don't overlap.
                break;
            }
        }
        if (rightIndex != -1) {
            // There are right overlaps.
            returnValue.back().at(1) = std::max(returnValue.back().at(1), intervals.at(rightIndex).at(1));
            returnValue.insert(returnValue.end(), intervals.begin() + rightIndex + 1, intervals.end());
        } else {
            // There are no right overlaps.
            returnValue.insert(returnValue.end(), intervals.begin() + thresholdIndex, intervals.end());
        }
        
        return returnValue;
    }
};


// MARK: - 4. Segmented solution.
// Runtime: 16 ms, faster than 84.04% of C++ online submissions for Insert Interval.
// Memory Usage: 13.4 MB, less than 5.00% of C++ online submissions for Insert Interval.
class Solution {
private:
    bool hasIntersections(const std::vector<int> interval1, const std::vector<int> interval2) {
        if ((interval1.at(0) < interval2.at(0)) && (interval1.at(1) < interval2.at(0))) {
            return false;
        }
        if ((interval2.at(0) < interval1.at(0)) && (interval2.at(1) < interval1.at(0))) {
            return false;
        }
        return true;
    }
    
public:
    std::vector<std::vector<int>> insert(const std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) {
        auto existingIntervalsCount = intervals.size();
        if (existingIntervalsCount == 0) {
            return {newInterval};
        }

        auto returnValue = std::vector<std::vector<int>>();
        
        size_t i = 0;
        
        // Left no overlap.
        while ((i < existingIntervalsCount) && (intervals.at(i).at(1) < newInterval.at(0))) {
//            returnValue.push_back(intervals.at(i));
            i += 1;
        }
        returnValue.insert(returnValue.end(), intervals.begin(), intervals.begin() + i);
        
        // Overlaps.
//        int overlapStart = newInterval.at(0);
//        int overlapEnd = newInterval.at(1);
        while ((i < existingIntervalsCount) && (hasIntersections(newInterval, intervals.at(i)))) {
            newInterval.at(0) = std::min(newInterval.at(0), intervals.at(i).at(0));
            newInterval.at(1) = std::max(newInterval.at(1), intervals.at(i).at(1));
            
            i += 1;
        }
        
        returnValue.push_back({newInterval.at(0), newInterval.at(1)});
        
        // Right no overlap.
//        while (i < existingIntervalsCount) {
//            returnValue.push_back(intervals.at(i));
//            i += 1;
//        }
        returnValue.insert(returnValue.end(), intervals.begin() + i, intervals.end());
        
        return returnValue;
    }
};


void test(std::vector<std::vector<int>> intervals, std::vector<int> newInterval) {
    static auto templateSolutionInstance = Solution3();
    auto templateResults = templateSolutionInstance.insert(intervals, newInterval);
    
    static auto solutionInstance = Solution();
    auto results = solutionInstance.insert(intervals, newInterval);
    
    if (templateResults == results) {
        std::cout << "Correct solution: ";
    } else {
        std::cout << "Wrong solution: ";
    }
    
    for (const auto& aResult: results) {
        std::cout << "(" << aResult.at(0) << ", " << aResult.at(1) << ")" << " ";
    }
    std::cout << std::endl;
}


int main() {
    std::vector<std::vector<int>> intervals1 = {{1,3},{6,9}};
    std::vector<int> newInterval1 = {2,5};
    test(intervals1, newInterval1);

    std::vector<std::vector<int>> intervals2 = {{1,2},{3,5},{6,7},{8,10},{12,16}};
    std::vector<int> newInterval2 = {4,8};
    test(intervals2, newInterval2);
    
    std::vector<std::vector<int>> intervals3 = {{1,2},{3,5},{6,7},{8,10},{12,16}};
    std::vector<int> newInterval3 = {18,19};
    test(intervals3, newInterval3);
    
    std::vector<std::vector<int>> intervals4 = {{1,2},{3,5},{6,7},{8,10},{12,16}};
    std::vector<int> newInterval4 = {0,1};
    test(intervals4, newInterval4);
    
    std::vector<std::vector<int>> intervals5 = {{1,2},{3,5},{6,7},{8,10},{12,16}};
    std::vector<int> newInterval5 = {0,16};
    test(intervals5, newInterval5);
    
    std::vector<std::vector<int>> intervals6 = {{1,2},{3,5},{6,7},{8,10},{12,16}};
    std::vector<int> newInterval6 = {10,13};
    test(intervals6, newInterval6);
    
    std::vector<std::vector<int>> intervals7 = {{1,5}};
    std::vector<int> newInterval7 = {2,3};
    test(intervals7, newInterval7);

    return 0;
}
