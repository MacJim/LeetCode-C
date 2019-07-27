/*
 * 274. H-Index
 * https://leetcode.com/problems/h-index/
 */

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;


#pragma mark - Solution class
class Solution {
public:
    //MARK: 1. Brute force.
    //Runtime: 4 ms, faster than 74.38% of C++ online submissions for H-Index.
    //Memory Usage: 8.9 MB, less than 73.86% of C++ online submissions for H-Index.
    int hIndex(vector<int>& citations) {
        auto citationsCount = citations.size();
        if (citationsCount == 0) {
            return 0;
        }

        int bruteForceStartNumber = citationsCount;

        int maximumCitation = *max_element(citations.begin(), citations.end());
        if (maximumCitation < citationsCount) {
            bruteForceStartNumber = maximumCitation;
        }

        for (int possibleH = bruteForceStartNumber; possibleH >= 0; possibleH -= 1) {
            int largeNumbersCount = 0;
            for (const auto& aCitation: citations) {
                if (aCitation >= possibleH) {
                    largeNumbersCount += 1;
                    if (largeNumbersCount >= possibleH) {
                        //This is the largest H.
                        return possibleH;
                    }
                }
            }
        }

        return 0;
    }
};

int main() {
    unique_ptr<Solution> solutionInstance (new Solution());

    vector<int> testValue1 = {3,0,6,1,5};    // 3
    cout << solutionInstance->hIndex(testValue1) << endl;
    
//    vector<int> testValue2 = {3,0,6,1,5};
//    cout << solutionInstance->hIndex(testValue2) << endl;
    return 0;
}
