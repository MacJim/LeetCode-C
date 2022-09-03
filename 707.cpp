/*
 * 707. Design Linked List
 * https://leetcode.com/problems/design-linked-list/
 */


#include <cassert>


#pragma mark - 1. Cache the length
// Runtime: 73 ms, faster than 34.71% of C++ online submissions for Design Linked List.
// Memory Usage: 19.7 MB, less than 65.69% of C++ online submissions for Design Linked List.
class MyListNode {
public:
    int val;
    MyListNode* next;

public:
    explicit MyListNode(int val = 0) : val{val}, next{nullptr} {}
};


class MyLinkedList {
private:
    int length;  // Should've used `size_t` but our function parameters are `int`.
    MyListNode* head;

public:
    MyLinkedList(): length{0}, head{nullptr} {}

    [[nodiscard]] int get(int index) const {
        if (index >= length) {
            return -1;
        }

        auto currentNode = head;
        for (; index != 0; index -= 1) {  // Could've used `while(index--)`, but I personally don't like `++`/`--`.
            currentNode = currentNode->next;
            if (!currentNode) {
                return -1;
            }
        }

        return currentNode->val;
    }

    void addAtHead(int val) {
        auto newNode = new MyListNode(val);

        if (head) {
            newNode->next = head;
        }
        head = newNode;

        length += 1;
    }

    void addAtTail(int val) {
        auto newNode = new MyListNode(val);

        if (!head) {
            head = newNode;
        } else {
            auto currentNode = head;
            while (currentNode->next) {
                currentNode = currentNode->next;
            }
            currentNode->next = newNode;
        }

        length += 1;
    }

    void addAtIndex(int index, int val) {
        if (index > length) {
            // Do nothing if the index exceeds the length.
            return;
        }

        auto newNode = new MyListNode(val);

        if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            auto currentNode = head;
            for (; index > 1; index -= 1) {
                currentNode = currentNode->next;
            }
            newNode->next = currentNode->next;
            currentNode->next = newNode;
        }

        length += 1;
    }

    void deleteAtIndex(int index) {
        if (index >= length) {
            // Do nothing if the index is invalid.
            return;
        }

        if (index == 0) {
            auto previousHead = head;
            head = head->next;
            delete previousHead;
        } else {
            auto currentNode = head;
            for (; index > 1; index -= 1) {
                currentNode = currentNode->next;
            }
            auto nodeToDelete = currentNode->next;
            currentNode->next = nodeToDelete->next;
            delete nodeToDelete;
        }

        length -= 1;
    }
};


int main() {
    auto myLinkedList = new MyLinkedList();
    myLinkedList->addAtHead(1);
    myLinkedList->addAtTail(3);
    myLinkedList->addAtIndex(1, 2);    // linked list becomes 1->2->3
    assert(myLinkedList->get(1) == 2);              // return 2
    myLinkedList->deleteAtIndex(1);    // now the linked list is 1->3
    assert(myLinkedList->get(1) == 3);              // return 3

    return 0;
}
