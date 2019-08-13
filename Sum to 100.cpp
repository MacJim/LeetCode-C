/*
 * Sum to 100 (this is not an official question).
 * https://leetcode.com/discuss/interview-question/357345/uber-phone-screen-sum-to-100
 */

/*
 * Possible optimizations:
 * 
 * 1. Even - odd pairs. There are 5 odd numbers. Thus, either 1, 3, 5 of them must be in the tens digit (not yet implemented in the recursion algorithm).
 */


#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;


/**
 * I HATE RECURSION!!!
 */
vector<string> sumToRecursively(string sourceString, int targetNumber) {
    auto sourceStringLength = sourceString.size();

    if (sourceStringLength == 0) {
        if (targetNumber == 0) {
            return {""};
        } else {
            return {};
        }
    } else if (sourceStringLength == 1) {
        auto integerValue = stoi(sourceString);
        if (integerValue == targetNumber) {
            return {"+" + sourceString};
        } else if (integerValue == -targetNumber) {
            return {"-" + sourceString};
        } else {
            return {};
        }
    }

    vector<string> returnValue = {};

    for (int assumedFirstNumberLength = 1; assumedFirstNumberLength <= sourceStringLength; assumedFirstNumberLength  += 1) {
        string assumedFirstNumberString = sourceString.substr(0, assumedFirstNumberLength);
        auto assumedFirstNumber = stoi(assumedFirstNumberString);

        string remainingString = sourceString.substr(assumedFirstNumberLength);

        //1. Adds `assumedFirstNumber` / subtracts from `targetNumber`.
        string addPrefix = "+" + assumedFirstNumberString;
        auto remainingStringResults1 = sumToRecursively(remainingString, targetNumber - assumedFirstNumber);
        for (auto& aRemainingStringResult: remainingStringResults1) {
            returnValue.push_back(addPrefix + aRemainingStringResult);
        }

        //2. Minus `assumedFirstNumber` / adds to `targetNumber`.
        string minusPrefix = "-" + assumedFirstNumberString;
        auto remainingStringResults2 = sumToRecursively(remainingString, targetNumber + assumedFirstNumber);
        for (auto& aRemainingStringResult: remainingStringResults2) {
            returnValue.push_back(minusPrefix + aRemainingStringResult);
        }
    }

    return returnValue;
}


int main() {
    unordered_set<string> allResults = {
        "+1+2+3-4+5+6+78+9",
        "+1+2+34-5+67-8+9",
        "+1+23-4+5+6+78-9",
        "+1+23-4+56+7+8+9",
        "+12+3+4+5-6-7+89",
        "+12+3-4+5+67+8+9",
        "+12-3-4+5-6+7+89",
        "+123+4-5+67-89",
        "+123+45-67+8-9",
        "+123-4-5-6-7+8-9",
        "+123-45-67+89",
        "-1+2-3+4+5+6+78+9"
    };

    for (auto& aResult: sumToRecursively("123456789", 100)) {
        if (allResults.find(aResult) == allResults.end()) {
            cout << "Found extraneous result: " << aResult << endl;
        } else {
            allResults.erase(aResult);
            cout << "Found result: " << aResult << endl;
        }
    }

    if (allResults.size() > 0) {
        cout << "\nResults that were not found:" << endl;
        for (auto anUnfoundResult: allResults) {
            cout << anUnfoundResult << endl;
        }
    }
    
    return 0;
}
