/***********************************************************************
  To merge sorted linked lists efficiently, the most optimal approach is to use a Min-Heap
  (Priority Queue). We push the head node of every non-empty list into the min-heap. 
  The heap will automatically keep the smallest available node at the top. We repeatedly 
  extract this smallest node, attach it to our merged list, and then push that node's 
  next pointer back into the heap. This ensures we always find the next smallest node 
  in O(log k).
************************************************************************/
#include <iostream>
#include <vector>
#include <queue>

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
    // Custom comparator struct for the priority queue to maintain a min-heap
    struct CompareNodes {
        bool operator()(const ListNode* lhs, const ListNode* rhs) const noexcept {
            return lhs->val > rhs->val; // Greater-than makes it a Min-Heap
        }
    };

public:
    [[nodiscard]] ListNode* mergeKLists(std::vector<ListNode*>& lists) const noexcept {
        // Initialize the min-heap with our custom structural comparator
        std::priority_queue<ListNode*, std::vector<ListNode*>, CompareNodes> min_heap;

        // Step 1: Push the head node of each non-empty linked list into the heap
        for (ListNode* head : lists) {
            if (head != nullptr) {
                min_heap.push(head);
            }
        }

        // Dummy node acts as a permanent anchor point for the head of the new list
        ListNode dummy;
        ListNode* tail = &dummy;

        // Step 2: Extract the smallest element and push its next successor
        while (!min_heap.empty()) {
            ListNode* smallest = min_heap.top();
            min_heap.pop();

            tail->next = smallest; // Link node to our merged sequence
            tail = tail->next;     // Advance the tail pointer

            // If the extracted node has a next node, push it into the heap
            if (smallest->next != nullptr) {
                min_heap.push(smallest->next);
            }
        }

        return dummy.next; // The actual sorted list begins right after the dummy node
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
    std::vector<ListNode*> lists1 = {
        createList({1, 2, 4}),
        createList({1, 3, 5}),
        createList({3, 6})
    };
    ListNode* result1 = solver.mergeKLists(lists1);
    std::cout << "Example 1 Output: ";
    printList(result1); // Expected: [1,1,2,3,3,4,5,6]
    freeList(result1);

    // --- Example 2 ---
    std::vector<ListNode*> lists2 = {};
    ListNode* result2 = solver.mergeKLists(lists2);
    std::cout << "Example 2 Output: ";
    printList(result2); // Expected: []
    freeList(result2);

    // --- Example 3 ---
    std::vector<ListNode*> lists3 = {createList({})};
    ListNode* result3 = solver.mergeKLists(lists3);
    std::cout << "Example 3 Output: ";
    printList(result3); // Expected: []
    freeList(result3);

    return 0;
}
