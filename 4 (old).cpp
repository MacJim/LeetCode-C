/**
 * 4. Median of Two Sorted Arrays
 * https://leetcode.com/problems/median-of-two-sorted-arrays/
 */

#include <iostream>
#include <vector>

using namespace std;


double findMedianSortedArrays(vector<int>& array1, vector<int>& array2) {
    const int array1Length = array1.size();
    const int array2Length = array2.size();
    
    if (array1Length > array2Length) {    //Make sure that array 1 is always shorter than array 2.
        return findMedianSortedArrays(array2, array1);
    }
    
    const int totalNumbersCount = array1Length + array2Length;
    const bool isTotalNumbersCountEven = (totalNumbersCount % 2 == 0)? true: false;
    
    for (int separationIndex1 = 0; separationIndex1 <= array1Length; separationIndex1 += 1) {
        int separationIndex2;
        if (isTotalNumbersCountEven) {
            separationIndex2 = totalNumbersCount / 2 - separationIndex1;
        } else {
            if (separationIndex1 < (array1Length - array2Length + 1) / 2) {
                //This will make `separationIndex2` out of range.
                continue;
            }
            separationIndex2 = (totalNumbersCount + 1) / 2 - separationIndex1;
        }
        
        int leftSegmentLargestElement;
        int rightSegmentSmallestElement;
        
        if (separationIndex1 == 0) {
            leftSegmentLargestElement = array2.at(separationIndex2 - 1);
        } else {
            const int array1LeftSegmentLargestElement = array1.at(separationIndex1 - 1);
            const int array2LeftSegmentLargestElement = array2.at(separationIndex2 - 1);
            leftSegmentLargestElement = (array1LeftSegmentLargestElement > array2LeftSegmentLargestElement)? array1LeftSegmentLargestElement: array2LeftSegmentLargestElement;
        }
        
        if (separationIndex1 == array1Length) {
            rightSegmentSmallestElement = array2.at(separationIndex2);
        } else {
            const int array1RightSegmentSmallestElement = array1.at(separationIndex1);
            const int array2RightSegmentSmallestElement = array2.at(separationIndex2);
            rightSegmentSmallestElement = (array1RightSegmentSmallestElement < array2RightSegmentSmallestElement)? array1RightSegmentSmallestElement: array2RightSegmentSmallestElement;
        }
        
        if (leftSegmentLargestElement < rightSegmentSmallestElement) {
            if (isTotalNumbersCountEven) {
                return ((double)leftSegmentLargestElement + (double)rightSegmentSmallestElement) / 2;
            } else {
                return (double)leftSegmentLargestElement;
            }
        }
    }
    
    return 0.0;
}

int main() {
    vector<int> testArray1 {1, 3};
    vector<int> testArray2 {2};
    cout << findMedianSortedArrays(testArray1, testArray2) << endl;
    
    vector<int> testArray3 {1, 2};
    vector<int> testArray4 {3, 4};
    cout << findMedianSortedArrays(testArray3, testArray4) << endl;
    return 0;
}
