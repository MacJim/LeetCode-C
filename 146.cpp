/*
 * 146. LRU Cache
 * https://leetcode.com/problems/lru-cache/
 */

#include <iostream>
#include <vector>
#include <unordered_map>

#include "helpers/Operators.hpp"


#pragma mark - Linked list + hash table
// Runtime: 80 ms, faster than 94.09% of C++ online submissions for LRU Cache.
// Memory Usage: 39.7 MB, less than 96.24% of C++ online submissions for LRU Cache.
/*
 * O(1) for both `get` and `put`. So this combination seems to be the only option.
 */
class LRUListNode {
public:
    int key;
    int value;
    LRUListNode* previous;
    LRUListNode* next;

    LRUListNode(int key, int value) {
        this->key = key;
        this->value = value;
        this->previous = nullptr;
        this->next = nullptr;
    }
};

class LRUCache {
private:
    int capacity;
    int size;

    std::unordered_map<int, LRUListNode*> index;
    LRUListNode* head;
    LRUListNode* tail;

    void moveToTail(LRUListNode* node) {
        if (node->next == nullptr) {
            // Already the last node.
            return;
        }

        if (node == head) {
            node->next->previous = nullptr;
            head = node->next;
        } else {
            node->previous->next = node->next;
            node->next->previous = node->previous;
        }

        tail->next = node;
        node->previous = tail;
        node->next = nullptr;
        tail = node;
    }

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->size = 0;
        this->index = std::unordered_map<int, LRUListNode*>();
        this->head = nullptr;
        this->tail = nullptr;
    }

    int get(int key) {
        auto it = index.find(key);
        if (it == index.end()) {
            return -1;
        } else {
            auto node = it->second;
            moveToTail(node);

            return node->value;
        }
    }

    void put(int key, int value) {
        auto it = index.find(key);
        if (it != index.end()) {
            // Update the position of an existing element.
            auto node = it->second;
            node->value = value;
            moveToTail(node);
        } else {
            if (this->capacity > this->size) {
                // Insert directly.
                auto node = new LRUListNode(key, value);
                node->previous = tail;
                if (tail) {
                    tail->next = node;
                }
                tail = node;
                if (!head) {
                    head = tail;
                }

                index[key] = node;

                this->size += 1;
            } else {
                // Replace the oldest element (head).
                index.erase(head->key);

                head->key = key;
                head->value = value;
                index[key] = head;

                moveToTail(head);
            }
        }
    }
};


void test1() {
    auto instance = new LRUCache(2);
    instance->put(1, 1);
    instance->put(2, 2);
    std::cout << instance->get(1) << std::endl;
    instance->put(3, 3);
    std::cout << instance->get(2) << std::endl;
    instance->put(4, 4);
    std::cout << instance->get(1) << std::endl;
    std::cout << instance->get(3) << std::endl;
    std::cout << instance->get(4) << std::endl;
}

void test2() {
    auto instance = new LRUCache(4);
    instance->put(1, 1);
    instance->put(2, 2);
    instance->put(3, 3);
    instance->put(4, 4);
    instance->put(5, 5);
    instance->get(5);
    instance->put(2, 20);
}

void test3() {
    auto instance = new LRUCache(10);
    instance->put(10, 13);
    instance->put(3, 17);
    instance->put(6, 11);
    instance->put(10, 5);
    instance->put(9, 10);
    instance->get(13);
    instance->put(2, 19);
    instance->get(2);
    instance->get(3);
    instance->put(5, 25);
    instance->get(8);
    instance->put(9, 22);
    instance->put(5, 5);
    instance->put(1, 30);
    instance->get(11);
    instance->put(9, 12);
    instance->get(7);
    instance->get(5);
    instance->get(8);
    instance->get(9);
    instance->put(4, 30);
    instance->put(9, 3);
    instance->get(9);
    instance->get(10);
}


int main() {
    test3();

    return 0;
}
