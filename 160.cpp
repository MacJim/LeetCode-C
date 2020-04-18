/*
 * 160. Intersection of Two Linked Lists
 * https://leetcode.com/problems/intersection-of-two-linked-lists/
 */

#include <iostream>
#include <unordered_set>
#include <vector>

#include "helpers/ListNode.hpp"


// MARK: 1
// Runtime: 68 ms, faster than 20.68% of C++ online submissions for Intersection of Two Linked Lists.
// Memory Usage: 17.6 MB, less than 20.37% of C++ online submissions for Intersection of Two Linked Lists.
class Solution1 {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        if ((headA == nullptr) || (headB == nullptr)) {
            return nullptr;
        } else if (headA == headB) {
            return headA;
        }

        auto node1 = headA;
        auto node2 = headB;

        auto nodes = std::unordered_set<ListNode*>();

        while (node1 != nullptr) {
            nodes.insert(node1);
            node1 = node1->next;
        }

        while (node2 != nullptr) {
            if (nodes.find(node2) != nodes.end()) {
                return node2;
            }

            node2 = node2->next;
        }

        return nullptr;
    }
};


// MARK: 2. Even slower than 1
// Runtime: 176 ms, faster than 6.71% of C++ online submissions for Intersection of Two Linked Lists.
// Memory Usage: 20.5 MB, less than 5.55% of C++ online submissions for Intersection of Two Linked Lists.
class Solution2 {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        if ((headA == nullptr) || (headB == nullptr)) {
            return nullptr;
        } else if (headA == headB) {
            return headA;
        }

        auto node1 = headA;
        auto node2 = headB;

        auto nodes1 = std::unordered_set<ListNode*>();
        auto nodes2 = std::unordered_set<ListNode*>();

        while ((node1 != nullptr) || (node2 != nullptr)) {
            if (node1 != nullptr) {
                if (nodes2.find(node1) != nodes2.end()) {
                    return node1;
                }
                nodes1.insert(node1);
                node1 = node1->next;
            }

            if (node2 != nullptr) {
                if (nodes1.find(node2) != nodes1.end()) {
                    return node2;
                }
                nodes2.insert(node2);
                node2 = node2->next;
            }
        }

        return nullptr;
    }
};


// MARK: 3. The two lists must have the same tail. Start from tail to find common node.
// Runtime: 60 ms, faster than 25.61% of C++ online submissions for Intersection of Two Linked Lists.
// Memory Usage: 17 MB, less than 24.07% of C++ online submissions for Intersection of Two Linked Lists.
class Solution3 {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        if ((headA == nullptr) || (headB == nullptr)) {
            return nullptr;
        } else if (headA == headB) {
            return headA;
        }

        auto node1 = headA;
        auto node2 = headB;

        auto nodes1 = std::vector<ListNode*>();
        auto nodes2 = std::vector<ListNode*>();

        while (node1 != nullptr) {
            nodes1.push_back(node1);
            node1 = node1->next;
        }

        while (node2 != nullptr) {
            nodes2.push_back(node2);
            node2 = node2->next;
        }

        auto it1 = nodes1.rbegin();
        auto it2 = nodes2.rbegin();

        if (*it1 == *it2) {
            while (true) {
                if ((it1 == nodes1.rend()) || (it2 == nodes2.rend()) || (*it1 != *it2)) {
                    it1 -= 1;
                    it2 -= 1;
                    return (*it1);
                }
                
                it1 += 1;
                it2 += 1;
            }
        }

        return nullptr;
    }
};


// MARK: 4. The official 2 pointers solution.
// Runtime: 96 ms, faster than 10.91% of C++ online submissions for Intersection of Two Linked Lists.
// Memory Usage: 14.6 MB, less than 100.00% of C++ online submissions for Intersection of Two Linked Lists.
class Solution4 {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        if ((headA == nullptr) || (headB == nullptr)) {
            return nullptr;
        } else if (headA == headB) {
            return headA;
        }

        auto node1 = headA;
        auto node2 = headB;

        // 1. Find the first end.
        while ((node1 != nullptr) && (node2 != nullptr)) {
            node1 = node1->next;
            node2 = node2->next;
        }

        // 2. Find the second end.
        if ((node1 == nullptr) && (node2 == nullptr)) {
            node1 = headB;
            node2 = headA;
        } else if (node1 == nullptr) {
            node1 = headB;
            while (node2 != nullptr) {
                node1 = node1->next;
                node2 = node2->next;
            }
            node2 = headA;
        } else if (node2 == nullptr) {
            node2 = headA;
            while (node1 != nullptr) {
                node1 = node1->next;
                node2 = node2->next;
            }
            node1 = headB;
        }

        // 3. See if node1 and node2 equals.
        // If they don't equal, they both end up with `nullptr`.
        while (node1 != node2) {
            node1 = node1->next;
            node2 = node2->next;
        }

        return node1;
    }
};


// MARK: 5. Improved 4
// Runtime: 44 ms, faster than 95.09% of C++ online submissions for Intersection of Two Linked Lists.
// Memory Usage: 14.6 MB, less than 100.00% of C++ online submissions for Intersection of Two Linked Lists.
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        if ((headA == nullptr) || (headB == nullptr)) {
            return nullptr;
        } else if (headA == headB) {
            return headA;
        }

        auto node1 = headA;
        auto node2 = headB;

        while ((node1 != node2) && (node1 != nullptr) && (node2 != nullptr)) {
            node1 = node1->next;
            node2 = node2->next;

            /*
             * Deals with multiple circumstances:
             * 
             * 1. In the first pass, `node1` and `node2` are the same. -> Both lists have the same length and have an intersection.
             * 2. Both `node1` and `node2` are `nullptr` -> The second pass has completed. No intersection was found.
             */
            if (node1 == node2) {
                return node1;
            }

            /*
             * The equal comparison in `while` is necessary. When we assign `headA` or `headB` to either of the 2 nodes, we want to compare them with the other node.
             */
            if (node1 == nullptr) {
                node1 = headB;
            }
            if (node2 == nullptr) {
                node2 = headA;
            }
        }

        return node1;
    }
};


std::pair<ListNode*, ListNode*> createLists() {
    auto list1 = ListHelper::deserialize({0, 9, 1});
    auto list2 = ListHelper::deserialize({3});
    auto sharedList = ListHelper::deserialize({2, 4});

    auto node1 = list1;
    while (node1->next != nullptr) {
        node1 = node1->next;
    }
    node1->next = sharedList;

    auto node2 = list2;
    while (node2->next != nullptr) {
        node2 = node2->next;
    }
    node2->next = sharedList;

    return std::make_pair(list1, list2);
}

int main() {
    auto solutionInstance = Solution();
    auto testCase1 = createLists();
    auto solution1 = solutionInstance.getIntersectionNode(testCase1.first, testCase1.second);
    std::cout << solution1->val << std::endl;
    
    return 0;
}
