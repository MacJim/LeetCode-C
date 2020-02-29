#include "ListNode.hpp"


std::vector<int> ListHelper::serialize(ListNode* head) {
    if (head == nullptr) {
        return {};
    }

    auto returnValue = std::vector<int>();

    auto currentNode = head;
    while (currentNode != nullptr) {
        returnValue.push_back(currentNode->val);
        currentNode = currentNode->next;
    }

    return returnValue;
}

ListNode* ListHelper::deserialize(std::vector<int> data) {
    const auto dataLength = data.size();

    if (dataLength == 0) {
        return nullptr;
    }

    auto head = new ListNode(data.front());

    auto previousNode = head;
    for (auto it = data.begin() + 1; it < data.end(); it += 1) {
        auto newNode = new ListNode(*it);
        previousNode->next = newNode;
        previousNode = newNode;
    }

    return head;
}