#include <iostream>
#include <string>
#include <map>

using namespace std;

/*
 * 8. String to Integer (atoi)
 * https://leetcode.com/problems/string-to-integer-atoi/
 */


//MARK: 1. C++ solution
/*
 * This solution uses many string operations, which might be slower than C style direct pointer operations.
 */

#define resultMaxLength 10    //Numbers longer than 10 will surely overflow.

int myAtoi(string str) {
    //1. Remove leading white spaces.
    string stringToConvert = str;
    while ((stringToConvert.length() > 0) && (stringToConvert.front() == ' ')) {
        stringToConvert.erase(0, 1);
    }
    
    //2. Return 0 if the string contains nothing or only white spaces.
    if (stringToConvert.length() <= 0) {
        return 0;
    }
    
    //3. Process positive / negative signs and erase them.
    bool isPositive = true;
    if (stringToConvert.front() == '-') {
        isPositive = false;
        stringToConvert.erase(0, 1);
    } else if (stringToConvert.front() == '+') {
        stringToConvert.erase(0, 1);
    }
    
    //4. Trim leading 0.
    while ((stringToConvert.length() > 0) && (stringToConvert.front() == '0')) {
        stringToConvert.erase(0, 1);
    }
    
    //5. Number
    long long result = 0;    //I must use `long long` instead of `int` on LeetCode. Otherwise, this variable is prone to overflow.
    int resultLength = 0;    //If larger than `resultMaxLength`, will surely overflow.
    
    while (stringToConvert.length() > 0) {
        const char& currentCharacter = stringToConvert.front();
        
        if ((currentCharacter < '0') || (currentCharacter > '9')) {
            break;
        } else {
            //4-1. Overflow protection 1. If `resultLength` is larger than `resultMaxLength`, will surely overflow.
            resultLength += 1;
            if (resultLength > resultMaxLength) {
                //Overflow
                if (isPositive) {
                    return INT_MAX;
                } else {
                    return INT_MIN;
                }
            }
            
            //4-2. Add result and trim string.
            result *= 10;
            int currentNumber = currentCharacter - '0';
            result += currentNumber;
            
            stringToConvert.erase(0, 1);
        }
    }
    
    //6. Apply sign.
    if (!isPositive) {
        result = -result;
    }
    
    //7. Overflow protection 2. Check if `result` is too large or too small.
    if (result > INT_MAX) {
        return INT_MAX;
    } else if (result < INT_MIN) {
        return INT_MIN;
    }
    
    return (int)result;
}

void test() {
    map<string, int> testCases = {{"     ", 0}, {"42", 42}, {"   -42", -42}, {"4193 with words", 4193}, {"words and 987", 0}, {"-91283472332", -2147483648}, {"  0000000000012345678", 12345678}};
    
    for (auto const& currentTestCase: testCases) {
        string testString = currentTestCase.first;
        int expectedResult = currentTestCase.second;

        int actualResult = myAtoi(testString);
        
        if (actualResult == expectedResult) {
            cout << "[Succeeded] Test string: \"" << testString << "\" Result: " << actualResult << endl;
        } else {
            cout << "[Failed] Test string: \"" << testString <<"Actual result:" << actualResult << " Expected result: " << expectedResult << endl;
        }
    }
}

int main(int argc, const char * argv[]) {
    test();
    return 0;
}
