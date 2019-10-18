/*
 * 391. Perfect Rectangle
 * https://leetcode.com/problems/perfect-rectangle/
 */

/*
 * - Each rectangle is represented as a bottom-left point and a top-right point.
 * - Overlapping rectangles count as failures.
 */

/*
 * Solution:
 * - All small rectangles' total size must equal the big rectangle's size.
 * - Counts of all vertices' occurrences (other than the big rectangle's 4 corner points) should be even.
 * - Counts of the big rectangle's 4 corner points' occurrences should be odd.
 */


#include <iostream>
#include <memory>
#include <vector>
//#include <map>
//#include <unordered_map>
#include <set>
//#include <unordered_set>

using namespace std;


// Runtime: 124 ms, faster than 69.14% of C++ online submissions for Perfect Rectangle.
// Memory Usage: 25.8 MB, less than 100.00% of C++ online submissions for Perfect Rectangle.
class Solution {
public:
    bool isRectangleCover(const vector<vector<int>>& rectangles) {
        auto rectanglesCount = rectangles.size();
        if (rectanglesCount == 1) {
            return true;
        } else if (rectanglesCount < 1) {
            return false;
        }
        
        int optimalLeftX = rectangles.at(1).at(0);
        int optimalBottomY = rectangles.at(1).at(1);
        int optimalRightX = rectangles.at(1).at(2);
        int optimalTopY = rectangles.at(1).at(3);
        
        int smallRectanglesTotalSize = 0;
        
        set<pair<int, int>> pointsOccurrences;
//        unordered_set<pair<int, int>> pointsOccurrences;    // This doesn't compile because of the hashing algorithm of `map` and `unordered_map` are different.
        
        for (const auto& aRectangle: rectangles) {
            // 1. Find bottom left and top right coordinates.
            int leftX = aRectangle.at(0);
            int bottomY = aRectangle.at(1);
            int rightX = aRectangle.at(2);
            int topY = aRectangle.at(3);
            
            if (leftX < optimalLeftX) {
                optimalLeftX = leftX;
            }
            if (bottomY < optimalBottomY) {
                optimalBottomY = bottomY;
            }
            if (rightX > optimalRightX) {
                optimalRightX = rightX;
            }
            if (topY > optimalTopY) {
                optimalTopY = topY;
            }
            
            // 2. Calculate the current rectangle's size.
            int currentRectangleSize = (rightX - leftX) * (topY - bottomY);
            smallRectanglesTotalSize += currentRectangleSize;
            
            // 3. Count each point's occurrences.
            auto bottomLeftPoint = make_pair(leftX, bottomY);
            auto bottomRightPoint = make_pair(rightX, bottomY);
            auto topLeftPoint = make_pair(leftX, topY);
            auto topRightPoint = make_pair(rightX, topY);
            
            auto previousBottomLeftPoint = pointsOccurrences.find(bottomLeftPoint);
            if (previousBottomLeftPoint == pointsOccurrences.end()) {
                // Not found.
                pointsOccurrences.insert(bottomLeftPoint);
            } else {
                pointsOccurrences.erase(previousBottomLeftPoint);
            }
            
            auto previousBottomRightPoint = pointsOccurrences.find(bottomRightPoint);
            if (previousBottomRightPoint == pointsOccurrences.end()) {
                // Not found.
                pointsOccurrences.insert(bottomRightPoint);
            } else {
                pointsOccurrences.erase(previousBottomRightPoint);
            }
            
            auto previousTopLeftPoint = pointsOccurrences.find(topLeftPoint);
            if (previousTopLeftPoint == pointsOccurrences.end()) {
                // Not found.
                pointsOccurrences.insert(topLeftPoint);
            } else {
                pointsOccurrences.erase(previousTopLeftPoint);
            }
            
            auto previousTopRightPoint = pointsOccurrences.find(topRightPoint);
            if (previousTopRightPoint == pointsOccurrences.end()) {
                // Not found.
                pointsOccurrences.insert(topRightPoint);
            } else {
                pointsOccurrences.erase(previousTopRightPoint);
            }
        }
        
        int bigRectangleSize = (optimalRightX - optimalLeftX) * (optimalTopY - optimalBottomY);
        if (bigRectangleSize != smallRectanglesTotalSize) {
            // Size mismatch.
            return false;
        }
        
        // There must be only 4 even points -> big rectangle corner points.
        if (pointsOccurrences.size() != 4) {
            // Count of even occurrence points is not correct.
            return false;
        }
        auto bottomLeftPoint = make_pair(optimalLeftX, optimalBottomY);
        auto bottomRightPoint = make_pair(optimalRightX, optimalBottomY);
        auto topLeftPoint = make_pair(optimalLeftX, optimalTopY);
        auto topRightPoint = make_pair(optimalRightX, optimalTopY);
        if ((pointsOccurrences.find(bottomLeftPoint) == pointsOccurrences.end()) || (pointsOccurrences.find(bottomRightPoint) == pointsOccurrences.end() || (pointsOccurrences.find(topLeftPoint) == pointsOccurrences.end()) || (pointsOccurrences.find(topRightPoint) == pointsOccurrences.end()))) {
            // The corner points are not all in the occurrence set.
            return false;
        }
        
        return true;
    }
};

int main() {
    unique_ptr<Solution> solutionInstance (new Solution());
    
    vector<vector<int>> testCase1 = {
        {1,1,3,3},
        {3,1,4,2},
        {3,2,4,4},
        {1,3,2,4},
        {2,3,3,4}
    };
    cout << "Test case 1 result: " << solutionInstance->isRectangleCover(testCase1)  << " (should be true)." << endl;
    
    vector<vector<int>> testCase2 = {
        {1,1,2,3},
        {1,3,2,4},
        {3,1,4,2},
        {3,2,4,4}
    };
    cout << "Test case 2 result: " << solutionInstance->isRectangleCover(testCase2)  << " (should be false)." << endl;
    
    return 0;
}
