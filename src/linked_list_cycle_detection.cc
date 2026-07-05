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
    [[nodiscard]] bool hasCycle(ListNode* head) const noexcept {
        // Edge case: An empty list or a list with only one node cannot have a cycle
        if (head == nullptr || head->next == nullptr) {
            return false;
        }

        ListNode* slow = head;
        ListNode* fast = head;

        // Traverse the list safely tracking the fast pointer's boundary
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;          // Moves 1 step
            fast = fast->next->next;    // Moves 2 steps

            // If they point to the exact same memory address, a cycle exists
            if (slow == fast) {
                return true;
            }
        }

        return false; // Fast pointer reached the end of the list, so no cycle exists
    }
};

// --- Helper Functions for the Driver Program ---

// Creates a linked list from a vector and loops the tail back to a specific index if provided
ListNode* createListWithCycle(const std::vector<int>& values, int cycle_index) {
    if (values.empty()) return nullptr;

    ListNode* head = new ListNode(values[0]);
    ListNode* curr = head;
    ListNode* cycle_target = (cycle_index == 0) ? head : nullptr;

    for (size_t i = 1; i < values.size(); ++i) {
        curr->next = new ListNode(values[i]);
        curr = curr->next;
        if (static_cast<int>(i) == cycle_index) {
            cycle_target = curr;
        }
    }

    // Connect the tail node back to the target node to complete the cycle loop
    if (cycle_index != -1 && cycle_target != nullptr) {
        curr->next = cycle_target;
    }

    return head;
}

// Cleans up memory safely (Handles cyclic configurations correctly)
void freeList(ListNode* head, bool has_cycle) {
    if (head == nullptr) return;

    if (has_cycle) {
        // If it has a cycle, break the cycle loop link first to make it a normal list for deletion
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* break_node = nullptr;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                break_node = slow;
                break;
            }
        }

        if (break_node != nullptr) {
            // Find the tail node and set its next back to nullptr
            ListNode* ptr = break_node;
            while (ptr->next != break_node && ptr->next != head) {
                // Step around until we pinpoint a node pointing back to parts we visited
                ListNode* check = head;
                bool linked_to_history = false;
                while (check != ptr) {
                    if (ptr->next == check) {
                        linked_to_history = true;
                        break;
                    }
                    check = check->next;
                }
                if (linked_to_history) break;
                ptr = ptr->next;
            }
            ptr->next = nullptr; // Safely sever the cycle connection
        }
    }

    // Delete normal sequential items
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
    std::vector<int> vals1 = {1, 2, 3, 4};
    int index1 = 1;
    ListNode* head1 = createListWithCycle(vals1, index1);
    bool res1 = solver.hasCycle(head1);
    std::cout << "Example 1 Output: " << (res1 ? "true" : "false") << " (Expected: true)\n";
    freeList(head1, res1);

    // --- Example 2 ---
    std::vector<int> vals2 = {1, 2};
    int index2 = -1;
    ListNode* head2 = createListWithCycle(vals2, index2);
    bool res2 = solver.hasCycle(head2);
    std::cout << "Example 2 Output: " << (res2 ? "true" : "false") << " (Expected: false)\n";
    freeList(head2, res2);

    return 0;
}
