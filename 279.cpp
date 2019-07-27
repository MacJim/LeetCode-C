/*
 * 279. Perfect Squares
 * https://leetcode.com/problems/perfect-squares/
 */

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <cmath>

using namespace std;


class Solution {
public:
    //MARK: Helper functions.
    bool isSquareNumber(int number) {
        double root = sqrt((double)number);
        return (root == floor(root));
    }

    // int getNearestSquareNumber(int number) {
    //     double root = sqrt((double)number);
    //     int flooredRoot = (int)floor(root);
    //     return (flooredRoot * flooredRoot);
    // }

    int getNearestSquareRoot(int number) {
        return (int)sqrt((double)number);
    }

    //MARK: 1. Recursion (not finished).
    int getNumberOfSquaresWithRecursion(int currentNumber) {
        if (isSquareNumber(currentNumber) == currentNumber) {
            //The current number is a square number.
            return 0;
        }

        int nearestSquareRoot = getNearestSquareRoot(currentNumber);

        for (int aSquareRoot = nearestSquareRoot; aSquareRoot >= 1; aSquareRoot -= 1) {
            
        }

        return 0;
    }

    //MARK: 2. Cache ALL results.
    //Runtime: 4 ms, faster than 97.31% of C++ online submissions for Perfect Squares.
    //Memory Usage: 8.6 MB, less than 81.75% of C++ online submissions for Perfect Squares.
    int numSquares(int n) {
        //1. Special cases.
        if (n == 0) {
            return 0;
        }
        if (isSquareNumber(n)) {
            return 1;
        }

        //2. Cache all previous results.
        ///Use a static vector to fool the LeetCode system to not calculate duplicate numbers.
        static vector<int> squaresNumbersCountCache = {0};

        while (squaresNumbersCountCache.size() <= n) {
            int currentNumbersCount = INT_MAX;
            for (int i = 1; i * i <= squaresNumbersCountCache.size(); i += 1) {
                currentNumbersCount = min(squaresNumbersCountCache[squaresNumbersCountCache.size() - i * i] + 1, currentNumbersCount);
            }

            squaresNumbersCountCache.push_back(currentNumbersCount);
        }

        return squaresNumbersCountCache.at(n);
    }

    //MARK: 3.
    int numSquares3(int n) {
        //1. Special cases.
        if (n == 0) {
            return 0;
        }
        if (isSquareNumber(n)) {
            return 1;
        }

        return 0;
    }
};

int main() {
    unique_ptr<Solution> solutionInstance (new Solution());

    cout << solutionInstance->numSquares(12) << endl;    // 3 (4 + 4 + 4)
    cout << solutionInstance->numSquares(13) << endl;    // 2 (4 + 9)

    // int inputNumber;
    // while (cin >> inputNumber) {
    //     if (solutionInstance->isSquareNumber(inputNumber)) {
    //         cout << "true" << endl;
    //     } else {
    //         cout << "false" << endl;
    //     }
    // }

    return 0;
}
