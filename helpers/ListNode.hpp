#include <iostream>
#include <vector>


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class ListHelper {
public:
    static std::vector<int> serialize(ListNode* head);
    static ListNode* deserialize(std::vector<int> data);
};
