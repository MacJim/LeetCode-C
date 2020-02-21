/*
 * 33. Search in Rotated Sorted Array
 * https://leetcode.com/problems/search-in-rotated-sorted-array/
 */

#include <iostream>
#include <vector>


// MARK: - Wrong solution
class Solution1 {
public:
    int search(const std::vector<int>& nums, const int target) {
        return searchRecursively(nums, target, 0, nums.size() - 1);
    }

    /// Both indices are inclusive.
    int searchRecursively(const std::vector<int>& nums, const int& target, const size_t startIndex, const size_t endIndex) {
        auto numsCount = endIndex - startIndex + 1;
        if (numsCount == 0) {
            return -1;
        }

        int startNum = nums.at(startIndex);
        if (target == startNum) {
            return startIndex;
        }

        if (numsCount == 1) {
            if (target == startNum) {
                return startIndex;
            } else {
                return -1;
            }
        }

        int endNum = nums.at(endIndex);
        if (target == endNum) {
            return endIndex;
        }

        if (numsCount == 2) {
            if (target == startNum) {
                return startIndex;
            } else if (target == endNum) {
                return endIndex;
            } else {
                return -1;
            }
        }

        if ((target < startNum) && (target > endNum)) {
            return -1;
        }

        int midIndex = (endIndex + startIndex + 1) / 2;
        int midNum = nums.at(midIndex);

        if (midNum == target) {
            return midIndex;
        }
        if (midNum > target) {
            if (target > startNum) {
                return searchRecursively(nums, target, startIndex, midIndex - 1);
            } else {
                return searchRecursively(nums, target, midIndex + 1, endIndex);
            }
        }
        if (midNum < target) {
            if (target < endNum) {
                return searchRecursively(nums, target, midIndex + 1, endIndex);
            } else {
                return searchRecursively(nums, target, startIndex, midIndex - 1); 
            }
        }

        return -1;
    }
};


// MARK: 2. Find rotation point first
// Runtime: 4 ms, faster than 81.85% of C++ online submissions for Search in Rotated Sorted Array.
// Memory Usage: 8.9 MB, less than 21.69% of C++ online submissions for Search in Rotated Sorted Array.
class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        auto numsCount = nums.size();
        if (numsCount == 0) {
            return -1;
        }

        const size_t startID = 0;
        const size_t endID = numsCount - 1;

        const auto rotationPoint = findRotationPoint(nums, startID, endID);
        std::cout << "Rotation point: " << rotationPoint << std::endl;

        if (rotationPoint == 0) {
            // The array is already sorted.
            return binarySearch(nums, target, startID, endID);
        } else {
            if (target > nums.at(endID)) {
                return binarySearch(nums, target, startID, rotationPoint - 1);
            } else {
                return binarySearch(nums, target, rotationPoint, endID);
            }
        }

        return -1;
    }

    size_t findRotationPoint(const std::vector<int>& nums, const size_t startID, const size_t endID) {
        if (endID == startID) {
            return startID;
        }

        const int& startValue = nums.at(startID);
        const int& endValue = nums.at(endID);

        if ((endID - startID) == 1) {
            if (endValue > startValue) {
                return startID;
            } else {
                return endID;
            }
        }
        
        if (startValue < endValue) {
            return startID;
        }

        const size_t midID = (endID + startID + 1) / 2;
        const int& midValue = nums.at(midID);
        if (midValue > endValue) {
            // [midID, endID]
            return findRotationPoint(nums, midID, endID);
        } else {
            // [startID, midID]
            return findRotationPoint(nums, startID, midID);
        }
        // const int& previousValue = nums.at(midID - 1);
        // if (midValue > previousValue) {
        //     // Check [midID, endID]
        //     return findRotationPoint(nums, midID, endID);
        // } else {
        //     return midID;
        // }
    }

    int binarySearch(const std::vector<int>& nums, const int& target, const size_t startID, const size_t endID) {
        const auto numsCount = endID - startID + 1;
        if (numsCount < 1) {
            return -1;
        }

        const int startValue = nums.at(startID);
        if (numsCount <= 2) {
            if (target == startValue) {
                return startID;
            }
        }

        const int endValue = nums.at(endID);
        if (numsCount == 2) {
            if (target == endValue) {
                return endID;
            }
        }
        
        const size_t midID = (startID + endID + 1) / 2;
        const int& midValue = nums.at(midID);
        
        if (midValue == target) {
            return midID;
        } else if (midValue < target) {
            return binarySearch(nums, target, midID + 1, endID);
        } else {
            return binarySearch(nums, target, startID, midID - 1);
        }
    }
};


int main() {
    auto solutionInstance = Solution();

    std::vector<int> testNums1 = {4,5,6,7,0,1,2};
    int target1 = 0;
    std::cout << solutionInstance.search(testNums1, target1) << std::endl;    // 4
    
    std::vector<int> testNums2 = {4,5,6,7,0,1,2};
    int target2 = 3;
    std::cout << solutionInstance.search(testNums2, target2) << std::endl;    // -1

    std::vector<int> testNums3 = {1,3};
    int target3 = 0;
    std::cout << solutionInstance.search(testNums3, target3) << std::endl;    // -1

    std::vector<int> testNums4 = {3,1};
    int target4 = 3;
    std::cout << solutionInstance.search(testNums4, target4) << std::endl;    // 0

    std::vector<int> testNums5 = {3,5,1};
    int target5 = 3;
    std::cout << solutionInstance.search(testNums5, target5) << std::endl;    // 0
}
