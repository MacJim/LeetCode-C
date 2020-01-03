/*
 * 221. Maximal Square
 * https://leetcode.com/problems/maximal-square/
 */

#include <iostream>
#include <vector>
#include <chrono>


// MARK: 0. Sample 4 ms solution from LeetCode
class SampleSolution
{
public:
    int maximalSquare(std::vector<std::vector<char>>& matrix)
    {
        std::ios_base::sync_with_stdio(false);
        
        if(matrix.size()==0)
            return 0;
        
        int i,j,ans=0;
        
        int m = matrix.size();
        int n = matrix[0].size();
        
        int mat[m][n];
        
        memset(mat,0,sizeof(mat));
        
        for(i=0;i<n;i++)
        {
          ans=std::max(ans,matrix[m-1][i]-48);
          mat[m-1][i]=matrix[m-1][i]-48;
        }
                  
        for(i=0;i<m;i++)
        {
            ans=std::max(ans,matrix[i][n-1]-48);
            mat[i][n-1]=matrix[i][n-1]-48;
        }
        
        for(i=m-2;i>=0;i--)
        {
            for(j=n-2;j>=0;j--)
            {
                if(matrix[i][j]=='1')
                {
                mat[i][j]=std::min(mat[i+1][j],std::min(mat[i][j+1],mat[i+1][j+1]))+1;
                ans=std::max(ans,mat[i][j]);
                }
            }
        }
        
      
        return ans*ans;
    }
};


// MARK: 1. Iterative approach
// Runtime: 436 ms, faster than 5.29% of C++ online submissions for Maximal Square.
// Memory Usage: 111.1 MB, less than 7.41% of C++ online submissions for Maximal Square.
// Why is this so slow?
class Solution1 {
public:
    int maximalSquare(std::vector<std::vector<char>>& matrix) {
        // Assume matrix.at(x).at(y)
        auto matrixWidth = matrix.size();
        if (matrixWidth < 1) {
            return 0;
        }

        auto matrixHeight = matrix.at(0).size();
        if (matrixHeight < 1) {
            return 0;
        }

        auto maximumPossibleSideLength = (matrixWidth > matrixHeight) ? matrixHeight : matrixWidth;

        auto solutionMatrix = std::vector<std::vector<int>>(matrixWidth, std::vector<int>(matrixHeight, 0));

        int currentBestSideLength = 0;

        // First iteration.
        for (int x = 0; x < matrixWidth; x += 1) {
            for (int y = 0; y < matrixHeight; y += 1) {
                char currentCharacter = matrix.at(x).at(y);
                if (currentCharacter == '1') {
                    solutionMatrix.at(x).at(y) = 1;
                    currentBestSideLength = 1;
                }
            }
        }

        // Following iterations.
        for (int i = 1; i < maximumPossibleSideLength; i += 1) {
            auto previousSolutionMatrix = std::move(solutionMatrix);
            solutionMatrix = std::vector<std::vector<int>>(matrixWidth, std::vector<int>(matrixHeight, 0));

            for (int x = 1; x < matrixWidth; x += 1) {
                for (int y = 1; y < matrixHeight; y += 1) {
                    // First confirm that the current tile is 1 in the original matrix.
                    int originalValue = matrix.at(x).at(y);
                    if (originalValue != '1') {
                        continue;
                    }

                    int previousValue1 = previousSolutionMatrix.at(x - 1).at(y);
                    int previousValue2 = previousSolutionMatrix.at(x - 1).at(y - 1);
                    int previousValue3 = previousSolutionMatrix.at(x).at(y - 1);
                    int currentIterationBestSideLength = std::min({previousValue1, previousValue2, previousValue3}) + 1;
                    solutionMatrix.at(x).at(y) = currentIterationBestSideLength;

                    if (currentBestSideLength < currentIterationBestSideLength) {
                        currentBestSideLength = currentIterationBestSideLength;
                    }
                }
            }
        }

        return currentBestSideLength * currentBestSideLength;
    }
};


// MARK: 2. Optimized 1
// Runtime: 476 ms, faster than 5.29% of C++ online submissions for Maximal Square.
// Memory Usage: 111.7 MB, less than 7.41% of C++ online submissions for Maximal Square.
// Why is this one even slower than version 1???
class Solution {
public:
    int maximalSquare(std::vector<std::vector<char>>& matrix) {
        // Assume matrix.at(x).at(y)
        auto matrixWidth = matrix.size();
        if (matrixWidth < 1) {
            return 0;
        }

        auto matrixHeight = matrix.at(0).size();
        if (matrixHeight < 1) {
            return 0;
        }

        auto maximumPossibleSideLength = (matrixWidth > matrixHeight) ? matrixHeight : matrixWidth;

        auto solutionMatrix = std::vector<std::vector<int>>(matrixWidth, std::vector<int>(matrixHeight, 0));
        auto previousSolutionMatrix = std::vector<std::vector<int>>(matrixWidth, std::vector<int>(matrixHeight, 0));

        int returnValue = 0;

        // First iteration.
        for (int x = 0; x < matrixWidth; x += 1) {
            for (int y = 0; y < matrixHeight; y += 1) {
                char currentCharacter = matrix.at(x).at(y);
                if (currentCharacter == '1') {
                    solutionMatrix.at(x).at(y) = 1;
                    returnValue = 1;
                }
            }
        }

        // Following iterations.
        for (int i = 1; i < maximumPossibleSideLength; i += 1) {
            auto previousSolutionMatrix = std::move(solutionMatrix);
            solutionMatrix = std::vector<std::vector<int>>(matrixWidth, std::vector<int>(matrixHeight, 0));

            for (int x = 1; x < matrixWidth; x += 1) {
                for (int y = 1; y < matrixHeight; y += 1) {
                    // First confirm that the current tile is 1 in the original matrix.
                    int originalValue = matrix.at(x).at(y);
                    if (originalValue != '1') {
                        continue;
                    }

                    int previousValue1 = previousSolutionMatrix.at(x - 1).at(y);
                    int previousValue2 = previousSolutionMatrix.at(x - 1).at(y - 1);
                    int previousValue3 = previousSolutionMatrix.at(x).at(y - 1);
                    // int currentIterationBestSideLength = std::min({previousValue1, previousValue2, previousValue3}) + 1;
                    int currentIterationBestSideLength = std::min(previousValue1, std::min(previousValue2, previousValue3)) + 1;
                    solutionMatrix.at(x).at(y) = currentIterationBestSideLength;

                    if (returnValue < currentIterationBestSideLength) {
                        returnValue = currentIterationBestSideLength;
                    }
                }
            }
        }

        return returnValue * returnValue;
    }
};


int main() {
    // 1. My solution.
    auto startTime1 = std::chrono::steady_clock::now();
    auto solutionInstance = Solution();

    auto testInput11 = std::vector<std::vector<char>>({
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    });
    auto solution11 = solutionInstance.maximalSquare(testInput11);
    std::cout << solution11 << std::endl;

    auto testInput12 = std::vector<std::vector<char>>({
        {'1', '1', '1', '0', '0'},
        {'1', '1', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    });
    auto solution12 = solutionInstance.maximalSquare(testInput12);
    std::cout << solution12 << std::endl;

    auto endTime1 = std::chrono::steady_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(endTime1 - startTime1).count();
    std::cout << "My solution: " << duration1 << " microseconds" << std::endl;

    // 2. Sample fast solution.
    auto startTime2 = std::chrono::steady_clock::now();
    auto sampleSolutionInstance = SampleSolution();

    auto testInput21 = std::vector<std::vector<char>>({
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    });
    auto solution21 = sampleSolutionInstance.maximalSquare(testInput21);
    std::cout << solution21 << std::endl;

    auto testInput22 = std::vector<std::vector<char>>({
        {'1', '1', '1', '0', '0'},
        {'1', '1', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    });
    auto solution22 = sampleSolutionInstance.maximalSquare(testInput22);
    std::cout << solution22 << std::endl;

    auto endTime2 = std::chrono::steady_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(endTime2 - startTime2).count();
    std::cout << "Sample solution: " << duration2 << " microseconds" << std::endl;


    return 0;
}
