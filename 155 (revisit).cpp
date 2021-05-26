/*
 * 155. Min Stack
 * https://leetcode.com/problems/min-stack/
 */

#include <iostream>
#include <vector>
#include <stack>

//#include "helpers/Operators.hpp"


#pragma mark - 1. 2 stacks
// Runtime: 20 ms, faster than 80.99% of C++ online submissions for Min Stack.
// Memory Usage: 16.4 MB, less than 21.43% of C++ online submissions for Min Stack.
class MinStack1 {
private:
    std::stack<int> storage;
    std::stack<int> minElements;    // Same size as `storage`.

public:
    /** initialize your data structure here. */
    MinStack1() {
        storage = std::stack<int>();
        minElements = std::stack<int>();
    }

    void push(int val) {
        storage.push(val);
        if (minElements.empty()) {
            minElements.push(val);
        } else {
            minElements.push(std::min(minElements.top(), val));
        }
    }

    void pop() {
        storage.pop();
        minElements.pop();
    }

    int top() {
        return storage.top();
    }

    int getMin() {
        return minElements.top();
    }
};


#pragma mark - 2. Optimized 1 (revisit)
/*
 * We only push to `minElements` if the new element is smaller or equal than top.
 *
 * The equal case handles duplicate min elements.
 */
// Runtime: 24 ms, faster than 45.99% of C++ online submissions for Min Stack.
// Memory Usage: 16.6 MB, less than 13.42% of C++ online submissions for Min Stack.
// Somehow this solution is slower than version 1 despite being an optimization.
class MinStack {
private:
    std::stack<int> storage;
    std::stack<int> minElements;    // Same size as `storage`.

public:
    /** initialize your data structure here. */
    MinStack() {
        storage = std::stack<int>();
        minElements = std::stack<int>();
    }

    void push(int val) {
        storage.push(val);
        if (minElements.empty() || (val <= minElements.top())) {
            minElements.push(val);
        }
    }

    void pop() {
        if (storage.top() == minElements.top()) {
            minElements.pop();
        }
        storage.pop();
    }

    int top() {
        return storage.top();
    }

    int getMin() {
        return minElements.top();
    }
};


//void test(const std::vector<int>& nums, const int expectedResult) {
//    static auto solutionInstance = Solution();
//
//    auto numsCopy = nums;
//    auto result = solutionInstance.findMin(numsCopy);
//
//    if (result == expectedResult) {
//        std::cout << "[Correct] " << nums << ": " << result << std::endl;
//    } else {
//        std::cout << "[Wrong] " << nums << ": " << result << " (should be " << expectedResult << ")" << std::endl;
//    }
//}


int main() {
    MinStack* obj = new MinStack();
    obj->push(6);
    obj->push(21);
    obj->push(100);
    obj->push(1);
    obj->pop();
    obj->push(0);
    std::cout << "Top: " << obj->top() << std::endl;
    std::cout << "Min: " << obj->getMin() << std::endl;

    return 0;
}
