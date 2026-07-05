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
private:
    // Helper function to find the k-th node from the current head
    [[nodiscard]] ListNode* getKthNode(ListNode* curr, int k) const noexcept {
        while (curr != nullptr && k > 1) {
            curr = curr->next;
            k--;
        }
        return curr;
    }

public:
    [[nodiscard]] ListNode* reverseKGroup(ListNode* head, int k) const noexcept {
        if (head == nullptr || k == 1) {
            return head;
        }

        // Dummy node acts as a permanent anchor point right before the head
        ListNode dummy(0, head);
        ListNode* group_prev = &dummy;

        while (true) {
            // Find the k-th node of the current group
            ListNode* kth_node = getKthNode(group_prev->next, k);
            if (kth_node == nullptr) {
                break; // Fewer than k nodes remain, preserve their order and exit
            }

            // Pin the boundaries of our current group manipulation window
            ListNode* group_start = group_prev->next;
            ListNode* group_next = kth_node->next;

            // Reverse the sub-segment of 'k' nodes
            ListNode* prev = group_next; // Link the tail of the reversed group directly to the next group
            ListNode* curr = group_start;
            
            for (int i = 0; i < k; ++i) {
                ListNode* next_node = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next_node;
            }

            // Connect the previous group's tail to the new head of the reversed group
            group_prev->next = kth_node;
            
            // Slide the group pointer forward to track the end of our newly reversed segment
            group_prev = group_start;
        }

        return dummy.next;
    }
};

// --- Helper Functions for the Driver Program ---

ListNode* createList(const std::vector<int>& values) {
    if (values.empty()) return nullptr;
    ListNode* head = new ListNode(values);
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
    ListNode* head1 = createList({1, 2, 3, 4, 5, 6});
    int k1 = 3;
    ListNode* res1 = solver.reverseKGroup(head1, k1);
    std::cout << "Example 1 Output: ";
    printList(res1); // Expected: [3,2,1,6,5,4]
    freeList(res1);

    // --- Example 2 ---
    ListNode* head2 = createList({1, 2, 3, 4, 5});
    int k2 = 3;
    ListNode* res2 = solver.reverseKGroup(head2, k2);
    std::cout << "Example 2 Output: ";
    printList(res2); // Expected: [3,2,1,4,5]
    freeList(res2);

    return 0;
}
