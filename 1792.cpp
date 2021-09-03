/*
 * 1792. Maximum Average Pass Ratio
 * https://leetcode.com/problems/maximum-average-pass-ratio/
 */

#include <iostream>
#include <vector>
#include <utility>

#include "helpers/Operators.hpp"
#include "helpers/terminal_format.h"


#pragma mark - 1. Max heap
/*
 * Add 1 extra student at a time.
 */
// Runtime: 1093 ms, faster than 21.53% of C++ online submissions for Maximum Average Pass Ratio.
// Memory Usage: 87.1 MB, less than 97.59% of C++ online submissions for Maximum Average Pass Ratio.
class Solution {
public:
    double maxAverageRatio(std::vector<std::vector<int>>& classes, int extraStudents) {
        // Convert int to double (because I don't want to cast them to double every time `cmp` is called).
        // Well this conversion may be sub-optimal and takes up extra memory.
        // But anyway, the solution is mostly the same as the official solution.
        auto classesHeap = std::vector<std::pair<double, double>>();
        classesHeap.reserve(classes.size());
        for (const auto& c: classes) {
            classesHeap.emplace_back(static_cast<double>(c[0]), static_cast<double>(c[1]));
        }

        auto cmp = [] (const std::pair<double, double>& lhs, const std::pair<double, double>& rhs) -> bool {
            const double leftValue = (lhs.first + 1) / (lhs.second + 1) - lhs.first / lhs.second;
            const double rightValue = (rhs.first + 1) / (rhs.second + 1) - rhs.first / rhs.second;

            return leftValue < rightValue;
        };

        std::make_heap(classesHeap.begin(), classesHeap.end(), cmp);
        while (extraStudents --) {
            std::pop_heap(classesHeap.begin(), classesHeap.end(), cmp);
            classesHeap.back().first += 1;
            classesHeap.back().second += 1;
            std::push_heap(classesHeap.begin(), classesHeap.end(), cmp);
        }

        double returnValue = 0.0;
        for (const auto& c: classesHeap) {
            returnValue += (c.first / c.second);
        }
        returnValue /= classes.size();

        return returnValue;
    }
};


void test(const std::vector<std::vector<int>>& classes, const int extraStudents, const double expectedResult) {
    auto solutionInstance = Solution();

    auto classesCopy = classes;
    auto result = solutionInstance.maxAverageRatio(classesCopy, extraStudents);

    if (std::abs(result - expectedResult) < 1e-5) {
        std::cout << terminal_format::OK_GREEN << "[Correct] " << terminal_format::ENDC << classes << ", " << extraStudents << ": " << result << std::endl;
    } else {
        std::cout << terminal_format::FAIL << terminal_format::BOLD << "[Wrong] " << terminal_format::ENDC << classes << ", " << extraStudents << ": " << result << " (should be " << expectedResult << ")" << std::endl;
    }
}


int main() {
    test({{1,2},{3,5},{2,2}}, 2, 0.78333);
    test({{2,4},{3,9},{4,5},{2,10}}, 4, 0.53485);

    return 0;
}
