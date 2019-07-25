/**
 * 22. Generate Parentheses
 * https://leetcode.com/problems/generate-parentheses/
 */

#include <iostream>
#include <vector>
#include <memory>

using namespace std;


void addParenthesis(vector<string>& vector, string currentString, int leftParenthesesToAdd, int rightParenthesesToAdd) {
    if ((leftParenthesesToAdd == 0) && (rightParenthesesToAdd == 0)) {
        vector.push_back(currentString);
        return;
    }
    
    if (rightParenthesesToAdd > 0) {
        addParenthesis(vector, currentString + ")", leftParenthesesToAdd, rightParenthesesToAdd - 1);
    }
    if (leftParenthesesToAdd > 0) {
        addParenthesis(vector, currentString + "(", leftParenthesesToAdd - 1, rightParenthesesToAdd + 1);
    }
}

vector<string> generateParenthesis(int parenthesesCount) {
    if (parenthesesCount == 0) {
        return {};
    }
    
    vector<string> returnValue = {};
    addParenthesis(returnValue, "", parenthesesCount, 0);
    
    return returnValue;
}

int main() {
    auto resultSet1 = generateParenthesis(3);
    for (auto& aResult: resultSet1) {
        cout << aResult << " " << flush;
    }
    
    return 0;
}
