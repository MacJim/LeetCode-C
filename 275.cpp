/*
 * 275. H-Index II
 * https://leetcode.com/problems/h-index-ii/
 */

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;


class Solution {
public:
    //MARK: 1.
    //Runtime: 20 ms, faster than 93.24% of C++ online submissions for H-Index II.
    //Memory Usage: 12.4 MB, less than 39.44% of C++ online submissions for H-Index II.
    int hIndex(vector<int>& citations) {
        auto citationsCount = citations.size();
        if (citationsCount == 0) {
            return 0;
        } else if (citationsCount == 1) {
            int firstAndOnlyCitation = citations.front();
            if (firstAndOnlyCitation > 1) {
                return 1;
            } else {
                return firstAndOnlyCitation;
            }
        }

        int assumedH = citationsCount;

        int maximumCitation = citations.back();
        if (maximumCitation < citationsCount) {
            assumedH = maximumCitation;
        }

        for (int i = (citationsCount - 1); i >= 0; i -= 1) {
            int currentCitation = citations.at(i);
            int elapsedNumbersCount = citationsCount - i - 1;

            if (currentCitation < assumedH) {
                if (currentCitation > elapsedNumbersCount) {
                    assumedH = currentCitation;
                } else {
                    assumedH = elapsedNumbersCount;
                }
            }
            
            if (elapsedNumbersCount >= assumedH) {
                return assumedH;
            }
        }

        return assumedH;
    }
};

int main() {
    unique_ptr<Solution> solutionInstance (new Solution());

    vector<int> testValue1 = {0,1,3,5,6};    // 3
    cout << solutionInstance->hIndex(testValue1) << endl;
    
    vector<int> testValue2 = {0,0,4,4};    // 2
    cout << solutionInstance->hIndex(testValue2) << endl;
    
    vector<int> testValue3 = {1};    // 1
    cout << solutionInstance->hIndex(testValue3) << endl;
    
    vector<int> testValue4 = {11,15};    // 2
    cout << solutionInstance->hIndex(testValue4) << endl;

    return 0;
}
