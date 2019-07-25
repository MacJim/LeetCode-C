/*
 * 42. Trapping Rain Water
 * https://leetcode.com/problems/trapping-rain-water/
 */

#include <iostream>
#include <vector>
#include <memory>

using namespace std;


class Solution {
public:
    //MARK: 1. Brute force.
    //Result: Success! This solution is quite slow though.
    int trap1(vector<int>& height) {
        const int elevationsCount = height.size();
        if (elevationsCount < 3) {
            //2 elevations are not enough.
            return 0;
        }
        
        int returnValue = 0;
        
        for (int i = 1; i < (elevationsCount - 1); i += 1) {    //Please note that the side elevations cannot hold water.
            int leftMaximumElevation = -1;
            int rightMaximumElevation = -1;
            
            for (int j = 0; j < i; j += 1) {
                int leftElevation = height.at(j);
                if (leftElevation > leftMaximumElevation) {
                    leftMaximumElevation = leftElevation;
                }
            }
            for (int k = i + 1; k < elevationsCount; k += 1) {
                int rightElevation = height.at(k);
                if (rightElevation > rightMaximumElevation) {
                    rightMaximumElevation = rightElevation;
                }
            }
            
            if ((leftMaximumElevation > 0) && (rightMaximumElevation > 0)) {
                int minimumSideHeight = (leftMaximumElevation < rightMaximumElevation)? leftMaximumElevation: rightMaximumElevation;
                int currentElevation = height.at(i);
                
                int currentCapacity = 0;
                if (currentElevation < minimumSideHeight) {
                    currentCapacity = minimumSideHeight - currentElevation;
                }
                
                returnValue += currentCapacity;
            }
        }
        
        return returnValue;
    }
    
    //MARK: 2. Find shorter pillar from 2 sides (needs revisit).
    //Result: Success! This solution is really fast!
    //Runtime: 4 ms, faster than 99.65% of C++ online submissions for Trapping Rain Water.
    //Memory Usage: 9.3 MB, less than 60.61% of C++ online submissions for Trapping Rain Water.
    int trap(vector<int>& height) {
        const int elevationsCount = height.size();
        if (elevationsCount < 3) {
            //2 elevations are not enough.
            return 0;
        }
        
        int returnValue = 0;
        
        int leftIndex = 0;
        int rightIndex = elevationsCount - 1;
        
        int maximumLeftElevation = 0;
        int maximumRightElevation = 0;
        
        while (leftIndex < rightIndex) {
            int leftElevation = height.at(leftIndex);
            int rightElevation = height.at(rightIndex);
            
            if (leftElevation < rightElevation) {
                if (leftElevation > maximumLeftElevation) {
                    maximumLeftElevation = leftElevation;
                } else {
                    returnValue += (maximumLeftElevation - leftElevation);
                }
                
                leftIndex += 1;
            } else {
                if (rightElevation > maximumRightElevation) {
                    maximumRightElevation = rightElevation;
                } else {
                    returnValue += (maximumRightElevation - rightElevation);
                }
                
                rightIndex -= 1;
            }
        }
        
        return returnValue;
    }
};

int main() {
    unique_ptr<Solution> solutionInstance (new Solution());
    
    vector<int> testValue = {0,1,0,2,1,0,1,3,2,1,2,1};
    auto result = solutionInstance->trap(testValue);
    cout << "Result: " << result << endl;
    
    return 0;
}
