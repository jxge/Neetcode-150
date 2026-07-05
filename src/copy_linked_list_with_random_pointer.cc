#include <iostream>
#include <vector>


// Follow the following steps:
//  1. Clone each node and insert the cloned node after the original node.
//  2. For each original node n:
//     n->next->random = n->random->next
//  3. Unweave the lists to restore the original and isolate the copy
// 
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) noexcept {
        if (head == nullptr) {
            return nullptr;
        }

        // Step 1: Clone each node and interweave it into the original list
        // [A] -> [B] becomes [A] -> [A'] -> [B] -> [B']
        Node* curr = head;
        while (curr != nullptr) {
            Node* clone = new Node(curr->val);
            clone->next = curr->next;
            curr->next = clone;
            curr = clone->next;
        }

        // Step 2: Assign the random pointers for the cloned nodes
        curr = head;
        while (curr != nullptr) {
            Node* clone = curr->next;
            if (curr->random != nullptr) {
                // The clone's random pointer points to the original target's clone
                clone->random = curr->random->next;
            }
            curr = clone->next; // Move to the next original node
        }

        // Step 3: Unweave the lists to restore the original and isolate the copy
        Node* dummy = new Node(0);
        Node* copy_tail = dummy;
        curr = head;

        while (curr != nullptr) {
            Node* clone = curr->next;
            
            // Extract the clone out to our deep copy list
            copy_tail->next = clone;
            copy_tail = clone;

            // Restore original list linkage
            curr->next = clone->next;
            curr = curr->next;
        }

        Node* deep_copy_head = dummy->next;
        delete dummy; // Free the temporary anchor node
        return deep_copy_head;
    }
};

// --- Helper Functions for the Driver Program ---

// Helper to compile tracking indexes back to pointers during instantiation
Node* createRandomList(const std::vector<std::pair<int, int>>& data) {
    if (data.empty()) return nullptr;

    std::vector<Node*> nodes;
    for (const auto& item : data) {
        nodes.push_back(new Node(item.first));
    }

    for (size_t i = 0; i < data.size(); ++i) {
        if (i < data.size() - 1) {
            nodes[i]->next = nodes[i + 1];
        }
        int random_idx = data[i].second;
        if (random_idx != -1) {
            nodes[i]->random = nodes[random_idx];
        }
    }
    return nodes[0];
}

// Maps nodes back to positional relative index markers for logging output
void printRandomList(Node* head) {
    std::cout << "[";
    std::vector<Node*> node_registry;
    Node* curr = head;
    while (curr != nullptr) {
        node_registry.push_back(curr);
        curr = curr->next;
    }

    curr = head;
    while (curr != nullptr) {
        std::cout << "[" << curr->val << ",";
        if (curr->random == nullptr) {
            std::cout << "null";
        } else {
            // Find target placement positional index matching pointer
            int index = -1;
            for (size_t i = 0; i < node_registry.size(); ++i) {
                if (node_registry[i] == curr->random) {
                    index = static_cast<int>(i);
                    break;
                }
            }
            std::cout << index;
        }
        std::cout << "]";
        if (curr->next != nullptr) std::cout << ",";
        curr = curr->next;
    }
    std::cout << "]\n";
}

void freeList(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Solution solver;

    // --- Example 1 ---
    // Pairs: {Value, Random Target Index (-1 for null)}
    std::vector<std::pair<int, int>> data1 = {{3, -1}, {7, 3}, {4, 0}, {5, 1}};
    Node* head1 = createRandomList(data1);
    
    Node* cloned_head1 = solver.copyRandomList(head1);
    std::cout << "Example 1 Output: ";
    printRandomList(cloned_head1); // Expected: [[3,null],[7,3],[4,0],[5,1]]

    freeList(head1);
    freeList(cloned_head1);

    // --- Example 2 ---
    std::vector<std::pair<int, int>> data2 = {{1, -1}, {2, 2}, {3, 2}};
    Node* head2 = createRandomList(data2);
    
    Node* cloned_head2 = solver.copyRandomList(head2);
    std::cout << "Example 2 Output: ";
    printRandomList(cloned_head2); // Expected: [[1,null],[2,2],[3,2]]

    freeList(head2);
    freeList(cloned_head2);

    return 0;
}
