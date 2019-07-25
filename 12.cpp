/*
 * 12. Integer to Roman
 * https://leetcode.com/problems/integer-to-roman/
 */

/*
 * Subtraction:
 *
 * 1. I can be placed before V (5) and X (10) to make 4 and 9.
 * 2. X can be placed before L (50) and C (100) to make 40 and 90.
 * 3. C can be placed before D (500) and M (1000) to make 400 and 900.
 */

#include <iostream>
#include <string>
#include <map>

using namespace std;

#define ROMAN_I 1
#define ROMAN_V 5
#define ROMAN_X 10
#define ROMAN_L 50
#define ROMAN_C 100
#define ROMAN_D 500
#define ROMAN_M 1000

#define ROMAN_IV_DELTA 4
#define ROMAN_IX_DELTA 9
#define ROMAN_XL_DELTA 40
#define ROMAN_XC_DELTA 90
#define ROMAN_CD_DELTA 400
#define ROMAN_CM_DELTA 900

//NOTE: Input is guaranteed to be within the range from 1 to 3999
string intToRoman(int num) {
    int remainingNumber = num;
    string resultString = "";
    
    //1. M 1000
    int M = remainingNumber / ROMAN_M;
    if (M > 0) {
        remainingNumber -= (M * ROMAN_M);
        resultString += string(M, 'M');
    }
    
    //2. CM 900
    //CM should only be 0 or 1.
    if (remainingNumber >= ROMAN_CM_DELTA) {
        remainingNumber -= ROMAN_CM_DELTA;
        resultString += "CM";
    }
    
    //3. D 500
    //D should only be 0 or 1.
    if (remainingNumber >= ROMAN_D) {
        remainingNumber -= ROMAN_D;
        resultString += "D";
    }
    
    //4. CD 400
    //CD should only be 0 or 1.
    if (remainingNumber >= ROMAN_CD_DELTA) {
        remainingNumber -= ROMAN_CD_DELTA;
        resultString += "CD";
    }
    
    //5. C 100
    int C = remainingNumber / ROMAN_C;
    if (C > 0) {
        remainingNumber -= (C * ROMAN_C);
        resultString += string(C, 'C');
    }
    
    //6. XC 90
    //XC should only be 0 or 1.
    if (remainingNumber >= ROMAN_XC_DELTA) {
        remainingNumber -= ROMAN_XC_DELTA;
        resultString += "XC";
    }
    
    //7. L 50
    //L should only be 0 or 1.
    if (remainingNumber >= ROMAN_L) {
        remainingNumber -= ROMAN_L;
        resultString += "L";
    }
    
    //8. XL 40
    //XL should only be 0 or 1.
    if (remainingNumber >= ROMAN_XL_DELTA) {
        remainingNumber -= ROMAN_XL_DELTA;
        resultString += "XL";
    }
    
    //9. X 10
    int X = remainingNumber / ROMAN_X;
    if (X > 0) {
        remainingNumber -= (X * ROMAN_X);
        resultString += string(X, 'X');
    }
    
    //10. IX 9
    //IX should only be 0 or 1.
    if (remainingNumber >= ROMAN_IX_DELTA) {
        remainingNumber -= ROMAN_IX_DELTA;
        resultString += "IX";
    }
    
    //11. V 5
    //V should only be 0 or 1.
    if (remainingNumber >= ROMAN_V) {
        remainingNumber -= ROMAN_V;
        resultString += "V";
    }
    
    //12. IV 4
    //IV should only be 0 or 1.
    if (remainingNumber >= ROMAN_IV_DELTA) {
        remainingNumber -= ROMAN_IV_DELTA;
        resultString += "IV";
    }
    
    //13. I 1
    int I = remainingNumber / ROMAN_I;
    resultString += string(I, 'I');
    
    return resultString;
}

void test() {
    map<int, string> testCases = {{3, "III"}, {4, "IV"}, {9, "IX"}, {58, "LVIII"}, {1994, "MCMXCIV"}};
    
    for (auto const& currentTestCase: testCases) {
        int testNumber = currentTestCase.first;
        string expectedResult = currentTestCase.second;
        
        string actualResult = intToRoman(testNumber);
        
        if (actualResult == expectedResult) {
            cout << "[Succeeded] Test number: " << testNumber << " Result: " << actualResult << endl;
        } else {
            cout << "[Failed] Test number: " << testNumber << " Actual result: " << actualResult << " Expected result: " << expectedResult << endl;
        }
    }
}

int main() {
    test();
    return 0;
}
