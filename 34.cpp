/*
 * 34. Find First and Last Position of Element in Sorted Array
 * https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
 */

#include <iostream>
#include <vector>


// The run time seems quite random...

// [OLD]
// Runtime: 12 ms, faster than 34.44% of C++ online submissions for Find First and Last Position of Element in Sorted Array.
// Memory Usage: 10.3 MB, less than 84.62% of C++ online submissions for Find First and Last Position of Element in Sorted Array.

// [NEW]
// Runtime: 4 ms, faster than 99.23% of C++ online submissions for Find First and Last Position of Element in Sorted Array.
// Memory Usage: 10.3 MB, less than 82.42% of C++ online submissions for Find First and Last Position of Element in Sorted Array.
class Solution {
public:
    std::vector<int> searchRange(std::vector<int>& numbers, int target) {
        auto numbersCount = numbers.size();
        if (numbersCount < 1) {
            return {-1, -1};
        } else if (numbersCount == 1) {
            if (numbers.at(0) == target) {
                return {0, 0};
            } else {
                return {-1, -1};
            }
        }

        if ((numbers.front() > target) || (numbers.back() < target)) {
            return {-1, -1};
        }

        int targetIndex = -1;

        /// This index is NOT the return value.
        int leftIndex = 0;
        int rightIndex = numbersCount - 1;
        while (leftIndex <= rightIndex) {
            if (leftIndex == rightIndex) {
                if (numbers.at(leftIndex) == target) {
                    return {leftIndex, leftIndex};
                } else {
                    break;
                }
            }

            // [leftIndex, threshold), [threshold, rightIndex]
            int thresholdIndex = leftIndex + (rightIndex - leftIndex + 1) / 2;
            int thresholdValue = numbers.at(thresholdIndex);
            if (thresholdValue == target) {
                targetIndex = thresholdIndex;
                break;
            } else if (thresholdValue > target) {
                // Check the left side.
                rightIndex = thresholdIndex - 1;
                continue;
            } else {
                // Check the right side.
                if (thresholdIndex == (numbersCount - 1)) {
                    // The threshold is already the last index of the `numbers` array.
                    break;
                } else {
                    // There are still items to the right.
                    leftIndex = thresholdIndex + 1;
                    continue;
                }
            }
        }

        if (targetIndex == -1) {
            return {-1, -1};
        }

        std::vector<int> returnValue = {targetIndex - 1, targetIndex + 1};
        int& returnValueLeft = returnValue.at(0);
        for (; returnValueLeft >= 0; returnValueLeft -= 1) {
            if (numbers.at(returnValueLeft) != target) {
                break;
            }
        }
        returnValueLeft += 1;

        int& returnValueRight = returnValue.at(1);
        for (; returnValueRight < numbersCount; returnValueRight += 1) {
            if (numbers.at(returnValueRight) != target) {
                break;
            }
        }
        returnValueRight -= 1;

        return {returnValueLeft, returnValueRight};
    }
};

int main() {
    auto solutionInstance = Solution();

    std::vector<int> testVector1 = {5,7,7,8,8,10};
    int target1 = 8;
    auto results1 = solutionInstance.searchRange(testVector1, target1);
    for (const auto& aResult: results1) {
        std::cout << aResult << " ";
    }
    std::cout << std::endl;

    std::vector<int> testVector2 = {5,7,7,8,8,10};
    int target2 = 6;
    auto results2 = solutionInstance.searchRange(testVector2, target2);
    for (const auto& aResult: results2) {
        std::cout << aResult << " ";
    }
    std::cout << std::endl;

    return 0;
}
