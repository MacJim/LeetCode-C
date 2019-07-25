/*
 * 48. Rotate Image
 * https://leetcode.com/problems/rotate-image/
 */

#include <iostream>
#include <vector>
#include <memory>

using namespace std;


class Solution {
public:
    //Runtime: 4 ms, faster than 85.35% of C++ online submissions for Rotate Image.
    //Memory Usage: 8.8 MB, less than 100.00% of C++ online submissions for Rotate Image.
    void rotate(vector<vector<int>>& matrix) {
        auto matrixSideLength = matrix.size();
        if (matrixSideLength <= 1) {
            //No need to rotate.
            return;
        }

        int maximumWidthOrHeight = matrixSideLength - 1;
        
        for (int y = 0; y < (matrixSideLength / 2); y += 1) {    //Considering both even and odd lengths.
            /*
             * Numbers to rotate: considering (x, y).
             * 
             * (x, y)
             * (y, max - x)
             * (max - x, max - y)
             * (max - y, x)
             */
            for (int x = y; x < (maximumWidthOrHeight - y); x += 1) {
                int firstNumber = matrix.at(y).at(x);
//                matrix.at(y).at(x) = matrix.at(x).at(maximumWidthOrHeight - y);
//                matrix.at(x).at(maximumWidthOrHeight - y) = matrix.at(maximumWidthOrHeight - y).at(maximumWidthOrHeight - x);
//                matrix.at(maximumWidthOrHeight - y).at(maximumWidthOrHeight - x) = matrix.at(maximumWidthOrHeight - x).at(y);
//                matrix.at(maximumWidthOrHeight - x).at(y) = firstNumber;
                
                matrix.at(y).at(x) = matrix.at(maximumWidthOrHeight - x).at(y);
                matrix.at(maximumWidthOrHeight - x).at(y) = matrix.at(maximumWidthOrHeight - y).at(maximumWidthOrHeight - x);
                matrix.at(maximumWidthOrHeight - y).at(maximumWidthOrHeight - x) = matrix.at(x).at(maximumWidthOrHeight - y);
                matrix.at(x).at(maximumWidthOrHeight - y) = firstNumber;
            }
        }
    }
};

void printArray(vector<vector<int>> array) {
    for (auto innerArray: array) {
        for (int element: innerArray) {
            cout << element << " ";
        }
        cout << endl;
    }
}

int main() {
    unique_ptr<Solution> solutionInstance (new Solution());
    
    vector<vector<int>> testArray1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
//    printArray(testArray1);
    solutionInstance->rotate(testArray1);
    printArray(testArray1);
    
    vector<vector<int>> testArray2 = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
//    printArray(testArray2);
    solutionInstance->rotate(testArray2);
    printArray(testArray2);
    
    return 0;
}
