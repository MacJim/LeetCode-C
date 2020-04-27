/*
 * 855. Exam Room
 * https://leetcode.com/problems/exam-room/
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>


#pragma mark - 1
class ExamRoom1 {
private:
    /*
     * I don't use a bitwise vector because:
     *
     * - 1 <= N <= 10^9
     * - ExamRoom.seat() and ExamRoom.leave() will be called at most 10^4 times across all test cases.
     */
    // std::vector<bool> students;

    int N;
    std::vector<int> students;

public:
    ExamRoom1(int N) {
        this->N = N;
        students = std::vector<int>();
    }
    
    int seat() {
        if (students.empty()) {
            students.push_back(0);
            return 0;
        }

        
    }
    
    void leave(int p) {
        auto it = std::find(students.begin(), students.end(), p);
        students.erase(it);
    }
};


#pragma mark - 2
/// This solution is WRONG. The `gaps` map cannot contains multiple gaps with the same distance.
class ExamRoom2 {
private:
    int N;

    /**
     * (distance, start index)
     *
     * Distance from 2 to 1 is 1.
     */
    std::map<int, int> gaps;

    std::unordered_set<int> occupiedPositions;

public:
    explicit ExamRoom2(int N) {
        this->N = N;
        gaps = std::map<int, int>();

        gaps.emplace(N - 1, 0);
    }
    
    int seat() {
        auto largestGap = *(gaps.rbegin());
        const int distance = largestGap.first;
        const int startIndex = largestGap.second;
    }
    
    void leave(int p) {
        
    }
};


#pragma mark - 3. (Ordered) set solution
/// This solution is WRONG. It maximizes the distance between both neighbors instead of the nearest neighbor.
class ExamRoom3 {
private:
    int N;

    std::set<int> occupiedPositions;


public:
    explicit ExamRoom3(int N) {
        this->N = N;
        this->occupiedPositions = std::set<int>();
    }

    int seat() {
        const auto size = occupiedPositions.size();
        if (size == 0) {
            occupiedPositions.insert(0);
            return 0;
        }

        int maxDistance = 1;
        int returnValue = -1;

        // 0 ~ first element.
        auto it = occupiedPositions.begin();
        auto firstDistance = *it;
        if (firstDistance > maxDistance) {
            returnValue = 0;
            maxDistance = firstDistance;
        }

//        int startPos = -1;
//        int endPos = -1;
        if (size > 1) {
            for (; it != std::prev(occupiedPositions.end(), 1); it ++) {
                auto nextIt = std::next(it, 1);
                int currentDistance = *nextIt - *it - 1;
                if (currentDistance > maxDistance) {
                    maxDistance = currentDistance;
//                startIterator = it;
//                endIterator = nextIt;
                    int startPos = *it;
                    int endPos = *nextIt - 1;
                    returnValue = (startPos + endPos) / 2;
                }
            }
        }

        // last element ~ (N - 1);
        auto lastDistance = N - 1 - *it - 1;
        if (lastDistance > maxDistance) {
            returnValue = (N - 1);
//            maxDistance = lastDistance;    // No need.
        }

        occupiedPositions.insert(returnValue);

        return returnValue;
    }

    void leave(int p) {
        occupiedPositions.erase(p);
    }


public:
    void printStudents() {
        for (const auto& pos: occupiedPositions) {
            std::cout << pos << " ";
        }
        std::cout << std::endl;
    }
};


#pragma mark - 4. Fixes 3
// Runtime: 64 ms, faster than 21.31% of C++ online submissions for Exam Room.
// Memory Usage: 11.7 MB, less than 100.00% of C++ online submissions for Exam Room.
class ExamRoom {
private:
    int N;

    std::set<int> occupiedPositions;


public:
    explicit ExamRoom(int N) {
        this->N = N;
        this->occupiedPositions = std::set<int>();
    }

    int seat() {
        const auto size = occupiedPositions.size();
        if (size == 0) {
            occupiedPositions.insert(0);
            return 0;
        }

        /// This value is 1 when there's no gap.
        int maxDistance = -1;
        int returnValue = -1;

        // 0 ~ first element.
        auto it = occupiedPositions.begin();
        auto firstPos = *it;
        auto firstDistance = firstPos;
        if (firstDistance > maxDistance) {
            maxDistance = firstDistance;
            returnValue = 0;
        }

        // Middle elements.
        auto previousPos = firstPos;
        for (it ++; it != occupiedPositions.end(); it ++) {
            auto currentPos = *it;
            auto currentDistance = currentPos - previousPos;
            currentDistance = currentDistance / 2;

            if (currentDistance > maxDistance) {
                maxDistance = currentDistance;
                returnValue = (currentPos + previousPos) / 2;
            }

            previousPos = currentPos;
        }

        // Last element ~ (N - 1).
        auto& lastPos = previousPos;
        auto lastDistance = (N - 1) - lastPos;
        if (lastDistance > maxDistance) {
//            maxDistance = lastDistance;    // No need here.
            returnValue = (N - 1);
        }

        occupiedPositions.insert(returnValue);

        return returnValue;
    }

    void leave(int p) {
        occupiedPositions.erase(p);
    }


public:
    void printStudents() {
        for (const auto& pos: occupiedPositions) {
            std::cout << pos << " ";
        }
        std::cout << std::endl;
    }
};


int main() {
    auto room1 = new ExamRoom(10);

    int s1 = room1->seat();    // 0
    int s2 = room1->seat();    // 9
    int s3 = room1->seat();    // 4
    int s4 = room1->seat();    // 2
    room1->printStudents();

    room1->leave(4);
    room1->printStudents();

    int s5 = room1->seat();    // 5
    room1->printStudents();

    return 0;
}
