class Solution {
public:
    [[nodiscard]] ListNode* reverseList(ListNode* head) const noexcept {
        ListNode* curr = head;
        head = nullptr;

        while (curr != nullptr) {
            ListNode* next_node = curr->next; // Temporarily save the next node
            curr->next = head;               // Reverse the current node's pointer
            head = curr;                     // Move 'prev' one step forward
            curr = next_node;                // Move 'curr' one step forward
        }

        return head; // 'prev' now points to the new head of the reversed list
    }
};
