/**
 * 20. Valid Parentheses
 * https://leetcode.com/problems/valid-parentheses/
 *
 * Runtime: 4 ms, faster than 96.65% of C++ online submissions for Valid Parentheses.
 * Memory Usage: 8.8 MB, less than 52.17% of C++ online submissions for Valid Parentheses.
 */

#include <iostream>
#include <stack>
#include <memory>

using namespace std;


enum class BracketType {
    roundLeft,    // (
//    roundRight,    // )
    curlyLeft,    // {
//    curlyRight,    // }
    squareLeft    // [
//    squareRight    // ]
};

bool isValid(string stringToExamine) {
    const unsigned long stringLength = stringToExamine.size();
    if (stringLength == 0) {
        return true;
    }
    
    unique_ptr<stack<BracketType>> examinerStack (new stack<BracketType>());
    
    for (auto& aCharacter: stringToExamine) {
        switch (aCharacter) {
            case '(':
                examinerStack->push(BracketType::roundLeft);
                break;
                
            case ')':
                if ((examinerStack->empty()) || (examinerStack->top() != BracketType::roundLeft)) {
                    return false;
                } else {
                    examinerStack->pop();
                }
                break;
                
            case '{':
                examinerStack->push(BracketType::curlyLeft);
                break;
                
            case '}':
                if ((examinerStack->empty()) || (examinerStack->top() != BracketType::curlyLeft)) {
                    return false;
                } else {
                    examinerStack->pop();
                }
                break;
                
            case '[':
                examinerStack->push(BracketType::squareLeft);
                break;
                
            case ']':
                if ((examinerStack->empty()) || (examinerStack->top() != BracketType::squareLeft)) {
                    return false;
                } else {
                    examinerStack->pop();
                }
                break;
                
            default:
                //Unknown character.
                return false;
        }
    }
    
    if (examinerStack->empty()) {
        return true;
    } else {
        return false;
    }
}

int main() {
    cout << isValid("()") << endl;
    cout << isValid("()[]{}") << endl;
    cout << isValid("(]") << endl;
    cout << isValid("([)]") << endl;
    cout << isValid("{[]}") << endl;
    cout << isValid("]") << endl;
    return 0;
}
