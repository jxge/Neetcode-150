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
    [[nodiscard]] ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) const noexcept {
        ListNode* head = nullptr;
        // 'link_ptr' holds the address of the pointer we need to update next.
        // Initially points to 'head', and will later point to 'curr_node->next'.
        ListNode** link_ptr = &head;
        int carry = 0;

        // Continue looping as long as there are digits to add or a remaining carry
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int sum = carry;

            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }

            carry = sum / 10; // Extract tens place digit for next loop pass

            // Allocate a new node with the ones place digit and link it upstream instantly
            *link_ptr = new ListNode(sum % 10);
            
            // Advance link_ptr to track the 'next' member address of our newly created node
            link_ptr = &((*link_ptr)->next);
        }

        return head;
    }
};

// --- Helper Functions for the Driver Program ---

ListNode* createList(const std::vector<int>& values) {
    ListNode* head = nullptr;
    ListNode** link_ptr = &head;
    for (int val : values) {
        *link_ptr = new ListNode(val);
        link_ptr = &((*link_ptr)->next);
    }
    return head;
}

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
    // Represents 321 + 654 = 975
    ListNode* l1_ex1 = createList({1, 2, 3});
    ListNode* l2_ex1 = createList({4, 5, 6});
    ListNode* result1 = solver.addTwoNumbers(l1_ex1, l2_ex1);
    std::cout << "Example 1 Output: ";
    printList(result1); // Expected: [5,7,9]

    freeList(l1_ex1); freeList(l2_ex1); freeList(result1);

    // --- Example 2 ---
    // Represents 9 + 9 = 18
    ListNode* l1_ex2 = createList({9});
    ListNode* l2_ex2 = createList({9});
    ListNode* result2 = solver.addTwoNumbers(l1_ex2, l2_ex2);
    std::cout << "Example 2 Output: ";
    printList(result2); // Expected: [8,1]

    freeList(l1_ex2); freeList(l2_ex2); freeList(result2);

    return 0;
}
