/*
 * 56. Merge Intervals
 * https://leetcode.com/problems/merge-intervals/
 */

#include <iostream>
#include <vector>


// MARK: - 1. Real time comparison
// It's correct but is really slow.
// Runtime: 1000 ms, faster than 5.21% of C++ online submissions for Merge Intervals.
// Memory Usage: 26.6 MB, less than 9.30% of C++ online submissions for Merge Intervals.
class Solution1 {
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
        auto intervalsCount = intervals.size();
        if (intervalsCount <= 1) {
            return intervals;
        }

        std::sort(intervals.begin(), intervals.end(), [] (std::vector<int> vector1, std::vector<int> vector2) {
            return (vector1.at(0) < vector2.at(0));
        });

        std::vector<std::vector<int>> returnValues = {intervals.at(0)};

        while (!intervals.empty()) {
            auto& lastReturnValue = returnValues.back();
            const auto& firstInterval = intervals.front();
            
            if (lastReturnValue.at(1) >= firstInterval.at(0)) {
                // They overlap.
                if (lastReturnValue.at(1) < firstInterval.at(1)) {
                    lastReturnValue.at(1) = firstInterval.at(1);
                }
            } else {
                returnValues.push_back(firstInterval);
            }

            intervals.erase(intervals.begin());
        }
        
        return returnValues;
    }
};


// MARK: - 2. Improved 1, removed the erase operation of the `intervals` vector.
// Runtime: 16 ms, faster than 94.18% of C++ online submissions for Merge Intervals.
// Memory Usage: 12.3 MB, less than 100.00% of C++ online submissions for Merge Intervals.
class Solution {
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
        auto intervalsCount = intervals.size();
        if (intervalsCount <= 1) {
            return intervals;
        }

        std::sort(intervals.begin(), intervals.end());

        std::vector<std::vector<int>> returnValues;

        for (const auto& anInterval: intervals) {
            if (returnValues.empty()) {
                returnValues.push_back(anInterval);
                continue;
            }

            auto& lastReturnValue = returnValues.back();
            
            if (lastReturnValue.at(1) >= anInterval.at(0)) {
                // They overlap.
                if (lastReturnValue.at(1) < anInterval.at(1)) {
                    lastReturnValue.at(1) = anInterval.at(1);
                }
            } else {
                returnValues.push_back(anInterval);
            }
        }
        
        return returnValues;
    }
};


void test(std::vector<std::vector<int>> testCase) {
    static auto solutionInstance = Solution();
    auto results = solutionInstance.merge(testCase);
    for (const auto& aResult: results) {
        std::cout << "(" << aResult.at(0) << ", " << aResult.at(1) << ")" << " ";
    }
    std::cout << std::endl;
}


int main() {
    const std::vector<std::vector<std::vector<int>>> testCases = {
        {{1,3},{2,6},{8,10},{15,18}},
        {{8,10},{2,6},{1,3},{15,18}},
        {{1,4},{4,5}}
    };
    
    for (const auto& aTestCase: testCases) {
        test(aTestCase);
    }

    return 0;
}
