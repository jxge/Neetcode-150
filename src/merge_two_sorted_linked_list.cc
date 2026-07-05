#include <iostream>
#include <vector>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    [[nodiscard]] ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) const noexcept {
        // A dummy node acts as a permanent anchor point for the start of the list
        ListNode dummyHead;
        ListNode* tail = &dummyHead;

        // Traverse both lists simultaneously until one runs empty
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;   // Link the smaller node from list1
                list1 = list1->next;  // Advance list1 pointer
            } else {
                tail->next = list2;   // Link the smaller node from list2
                list2 = list2->next;  // Advance list2 pointer
            }
            tail = tail->next;        // Advance the tail pointer
        }

        // Optimization: Append the entire remaining segment of the non-empty list
        tail->next = (list1 != nullptr) ? list1 : list2;

        return dummyHead.next; // The actual sorted list starts immediately after the dummy node
    }
};

// --- Helper Functions for the Driver Program ---

// Creates a linked list from a vector and returns its head pointer
ListNode* createList(const std::vector<int>& values) {
    if (values.empty()) return nullptr;
    ListNode* head = new ListNode(values[0]);
    ListNode* curr = head;
    for (size_t i = 1; i < values.size(); ++i) {
        curr->next = new ListNode(values[i]);
        curr = curr->next;
    }
    return head;
}

// Prints the linked list elements in an array-like format
void printList(ListNode* head) {
    std::cout << "[";
    ListNode* curr = head;
    while (curr != nullptr) {
        std::cout << curr->val;
        if (curr->next != nullptr) std::cout << ",";
        curr = curr->next;
    }
    std::cout << "]\n";
}

// Cleans up the allocated list memory to prevent leaks
void freeList(ListNode* head) {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    // Fast I/O optimization
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Solution solver;

    // --- Example 1 ---
    ListNode* l1_ex1 = createList({1, 2, 4});
    ListNode* l2_ex1 = createList({1, 3, 5});
    ListNode* result1 = solver.mergeTwoLists(l1_ex1, l2_ex1);
    std::cout << "Example 1 Output: ";
    printList(result1); // Expected: [1,1,2,3,4,5]
    freeList(result1);

    // --- Example 2 ---
    ListNode* l1_ex2 = createList({});
    ListNode* l2_ex2 = createList({1, 2});
    ListNode* result2 = solver.mergeTwoLists(l1_ex2, l2_ex2);
    std::cout << "Example 2 Output: ";
    printList(result2); // Expected: [1,2]
    freeList(result2);

    // --- Example 3 ---
    ListNode* l1_ex3 = createList({});
    ListNode* l2_ex3 = createList({});
    ListNode* result3 = solver.mergeTwoLists(l1_ex3, l2_ex3);
    std::cout << "Example 3 Output: ";
    printList(result3); // Expected: []
    freeList(result3);

    return 0;
}
