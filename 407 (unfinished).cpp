/**
 * 407. Trapping Rain Water II
 * https://leetcode.com/problems/trapping-rain-water-ii/
 */

#include <iostream>
#include <vector>
#include <memory>

using namespace std;


class Solution {
public:
    //MARK: 1. Brute force.
    //Result: Wrong Answer. This is apparently the wrong approach.
    int trapRainWater(vector<vector<int>>& heightMap) {
        int matrixWidth = heightMap.size();
        if (matrixWidth < 3) {
            //2 pillars are not enough.
            return 0;
        }
        
        int matrixHeight = heightMap.at(0).size();
        if (matrixHeight < 3) {
            //2 pillars are not enough.
            return 0;
        }
        
        int returnValue = 0;
        
        for (int w = 1; w < (matrixWidth - 1); w += 1) {
            for (int h = 1; h < (matrixHeight - 1); h += 1) {
                int currentElevation = heightMap.at(w).at(h);
                
                //Calculate 0 ~ (w - 1).
                int maximumElevation1 = 0;
                for (int smallerW = 0; smallerW < w; smallerW += 1) {
                    int elevation = heightMap.at(smallerW).at(h);
                    if (elevation > maximumElevation1) {
                        maximumElevation1 = elevation;
                    }
                }
                
                if (currentElevation >= maximumElevation1) {
                    continue;
                }
                
                //Calculate (w + 1) ~ (matrixWidth - 1).
                int maximumElevation2 = 0;
                for (int largerW = (w + 1); largerW < matrixWidth; largerW += 1) {
                    int elevation = heightMap.at(largerW).at(h);
                    if (elevation > maximumElevation2) {
                        maximumElevation2 = elevation;
                    }
                }
                
                if (currentElevation >= maximumElevation2) {
                    continue;
                }
                
                //Calculate 0 ~ (h - 1).
                int maximumElevation3 = 0;
                for (int smallerH = 0; smallerH < h; smallerH += 1) {
                    int elevation = heightMap.at(w).at(smallerH);
                    if (elevation > maximumElevation3) {
                        maximumElevation3 = elevation;
                    }
                }
                
                if (currentElevation >= maximumElevation3) {
                    continue;
                }
                
                //Calculate (h + 1) ~ (matrixHeight - 1).
                int maximumElevation4 = 0;
                for (int largerH = (h + 1); largerH < matrixHeight; largerH += 1) {
                    int elevation = heightMap.at(w).at(largerH);
                    if (elevation > maximumElevation4) {
                        maximumElevation4 = elevation;
                    }
                }
                
                if (currentElevation >= maximumElevation4) {
                    continue;
                }
                
                //Calculate the minimum maximum elevation.
                int minimumMaximumElevation = maximumElevation1;
                if (maximumElevation2 < minimumMaximumElevation) {
                    minimumMaximumElevation = maximumElevation2;
                }
                if (maximumElevation3 < minimumMaximumElevation) {
                    minimumMaximumElevation = maximumElevation3;
                }
                if (maximumElevation4 < minimumMaximumElevation) {
                    minimumMaximumElevation = maximumElevation4;
                }
                
                int capacity = minimumMaximumElevation - currentElevation;
                returnValue += capacity;
            }
        }
        
        return returnValue;
    }
};

int main() {
    unique_ptr<Solution> solutionInstance (new Solution());
    
    vector<vector<int>> testValue1 = {
        {1,4,3,1,3,2},
        {3,2,1,3,2,4},
        {2,3,3,2,3,1}
    };
    cout << "Result 1: " << solutionInstance->trapRainWater(testValue1) << endl;    //4
    
    vector<vector<int>> testValue2 = {
        {12,13,1,12},
        {13,4,13,12},
        {13,8,10,12},
        {12,13,12,12},
        {13,13,13,13}
    };
    cout << "Result 2: " << solutionInstance->trapRainWater(testValue2) << endl;    //14
    
    return 0;
}
