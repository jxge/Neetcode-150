// Example 1: [2,4,6,8] => [2,8,4,6]
// Example 2: [2,4,6,8,10] => [2,10,4,8,6]

// Do the following steps:
//   1. Find the Middle (Use a slow and fast pointer approach).
//   2. Reverse the Second Half: ked list in place.
//   3. Merge the Two Halves.

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
    void reorderList(ListNode* head) noexcept {
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        // Step 1: Find the middle of the linked list
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Step 2: Reverse the second half of the list
        // 'slow' points to the middle node. The second half starts right after it.
        ListNode* second_half = slow->next;
        slow->next = nullptr; // Split the list into two distinct halves

        ListNode* prev = nullptr;
        ListNode* curr = second_half;
        while (curr != nullptr) {
            ListNode* next_node = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next_node;
        }
        ListNode* head2 = prev; // 'prev' holds the head of the reversed second half

        // Step 3: Merge the two sorted halves alternatively
        ListNode* head1 = head;
        while (head2 != nullptr) {
            ListNode* temp1 = head1->next;
            ListNode* temp2 = head2->next;

            head1->next = head2; // Connect first half node to second half node
            head2->next = temp1; // Connect second half node to next first half node

            head1 = temp1; // Advance pointer 1
            head2 = temp2; // Advance pointer 2
        }
    }
};

// --- Helper Functions for the Driver Program ---

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
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Solution solver;

    // --- Example 1 ---
    ListNode* head1 = createList({2, 4, 6, 8});
    solver.reorderList(head1);
    std::cout << "Example 1 Output: ";
    printList(head1); // Expected: [2,8,4,6]
    freeList(head1);

    // --- Example 2 ---
    ListNode* head2 = createList({2, 4, 6, 8, 10});
    solver.reorderList(head2);
    std::cout << "Example 2 Output: ";
    printList(head2); // Expected: [2,10,4,8,6]
    freeList(head2);

    return 0;
}
