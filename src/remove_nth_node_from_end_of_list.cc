// Step 1: add a dummy node in the beginning of the list.
// Step 2: Advance the first pointer to n+1'th node 
// Step 3: Advance the first pointer and the 2nd pointer till the first pointer hits the last node
// Step 4: Remove the node pointed by second->next.
// 

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
    [[nodiscard]] ListNode* removeNthFromEnd(ListNode* head, int n) const noexcept {
        // A dummy node protects against edge cases like deleting the head node
        ListNode dummy(0, head);
        ListNode* first = &dummy;
        ListNode* second = &dummy;

        // Advance the 'first' pointer so that there is a gap of 'n' nodes between first and second
        for (int i = 0; i <= n; ++i) {
            if (first == nullptr) return head; // Safety check
            first = first->next;
        }

        // Move both pointers simultaneously until 'first' reaches the end
        while (first != nullptr) {
            first = first->next;
            second = second->next;
        }

        // 'second' now points to the node right before the target deletion node
        ListNode* to_delete = second->next;
        second->next = second->next->next; // Bypass the target node

        delete to_delete; // Free the memory of the removed node

        return dummy.next; // Return the actual head of the modified list
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
    // Fast I/O optimization
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Solution solver;

    // --- Example 1 ---
    ListNode* head1 = createList({1, 2, 3, 4});
    ListNode* res1 = solver.removeNthFromEnd(head1, 2);
    std::cout << "Example 1 Output: ";
    printList(res1); // Expected: [1,2,4]
    freeList(res1);

    // --- Example 2 ---
    ListNode* head2 = createList({5});
    ListNode* res2 = solver.removeNthFromEnd(head2, 1);
    std::cout << "Example 2 Output: ";
    printList(res2); // Expected: []
    freeList(res2);

    // --- Example 3 ---
    ListNode* head3 = createList({1, 2});
    ListNode* res3 = solver.removeNthFromEnd(head3, 2);
    std::cout << "Example 3 Output: ";
    printList(res3); // Expected: [2]
    freeList(res3);

    return 0;
}
