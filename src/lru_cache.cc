#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

/**************************************************************
Hash Map + Doubly Linked List LRU cache: 
  ┌────────────────────────────────────────────────────────┐
  │                 cache_map (Hash Map)                   │
  ├───────────────┬────────────────────────────────────────┤
  │   Key (int)   │  Value (std::list::iterator)           │
  ├───────────────┼────────────────────────────────────────┤
  │       1       │  ───────┐                              │
  ├───────────────┼─────────┼──────────────────────────────┤
  │       2       │  ───────┼───────────────┐              │
  ├───────────────┼─────────┼───────────────┼──────────────┤
  │       3       │  ───────┼────────┐      │              │
  └───────────────┴─────────┼────────┼──────┼──────────────┘
                            │        │      │
     ┌──────────────────────┘        │      │
     │                               │      │
     │      ┌────────────────────────┘      │
     │      │                               │
     ▼      ▼                               ▼
  ┌───────────┐      ┌───────────┐      ┌───────────┐
  │ CacheNode │◄────►│ CacheNode │◄────►│ CacheNode │
  │  key: 1   │      │  key: 3   │      │  key: 2   │
  │  value: 10│      │  value: 30│      │  value: 20│
  └───────────┘      └───────────┘      └───────────┘
   ▲                                             ▲
   │                                             │
[Front]                                       [Back]
(Most Recently Used)                   (Least Recently Used)
  │                                             │
  └────────────────── usage_list ───────────────┘

The industry uses more efficient algorithms designed to fix these issues.

1. The Clock Algorithm (Second Chance)
Instead of an expensive doubly linked list, Clock organizes memory blocks in a circular 
ring buffer with a single moving pointer (the "clock hand"). Each item has a single 
visited bit (0 or 1).
  - On Cache Hit: The bit is simply flipped to 1. No pointers are shifted, resulting in
    excellent concurrency.
  - On Eviction: The clock hand steps through the ring. If it sees a 1, it clears it to 0
    (giving it a second chance) and moves on. If it sees a 0, that item is immediately evicted.
Why it's better: It approximates LRU performance with near-zero pointer alteration overhead.

2. SIEVE (Modern Breakthrough)
In stead of using a fixed-size contiguous circular array (vector) in the clock algorithm, 
the  sieve algorithm uses a doubely linked list (queue). the SIEVE algorithm is not a true
LRU (Least Recently Used) algorithm. Instead, it is classified as a lazy approximation of
LRU with a heavy bias toward FIFO (First-In, First-Out).
********************************************************************/
class LRUCache {
private:
    // Structure to hold our key-value pairs inside the list
    struct CacheNode {
        int key;
        int value;
    };

    int max_capacity;
    
    // Doubly linked list tracking the access timeline:
    // Front = Most Recently Used (MRU), Back = Least Recently Used (LRU)
    std::list<CacheNode> usage_list;
    
    // Hash map for O(1) lookups pointing directly to the list nodes
    std::unordered_map<int, std::list<CacheNode>::iterator> cache_map;

    // Helper function to shift an existing node to the front (marking it as MRU)
    void make_recently_used(std::list<CacheNode>::iterator it) noexcept {
        // std::list::splice moves the node seamlessly in O(1) without reallocation
        usage_list.splice(usage_list.begin(), usage_list, it);
    }

public:
    explicit LRUCache(int capacity) : max_capacity(capacity) {
        // Optimization: Pre-reserve hash map buckets to minimize re-hashing overhead
        cache_map.reserve(capacity);
    }
    
    int get(int key) {
        auto it = cache_map.find(key);
        if (it == cache_map.end()) {
            return -1; // Key not found
        }
        
        // Refresh usage order
        make_recently_used(it->second);
        
        return it->second->value;
    }
    
    void put(int key, int value) {
        auto it = cache_map.find(key);
        
        if (it != cache_map.end()) {
            // Case 1: Key already exists. Update its value and refresh usage order.
            it->second->value = value;
            make_recently_used(it->second);
            return;
        }
        
        // Case 2: New key introduction. Check capacity before adding.
        if (static_cast<int>(cache_map.size()) >= max_capacity) {
            // Identify the least recently used item at the back of the list
            int lru_key = usage_list.back().key;
            
            // Evict from both the hash map and the list
            cache_map.erase(lru_key);
            usage_list.pop_back();
        }
        
        // Insert the new node at the front of the list
        usage_list.push_front({key, value});
        
        // Map the key to the newly created front iterator node
        cache_map[key] = usage_list.begin();
    }
};

#include <iostream>
#include <unordered_map>
#include <string>

#include <iostream>
#include <vector>
#include <unordered_map>

class ClockCache {
private:
    struct CacheEntry {
        int key;
        int value;
        bool referenced; // The "Second Chance" bit flag
        bool is_valid;   // Tracks if the slot contains active data
    };

    int capacity;
    int clock_hand; // Index pointer moving around the ring buffer
    
    // Circular ring buffer holding the physical data cache
    std::vector<CacheEntry> ring_buffer;
    
    // Hash map mapping Key -> Ring Buffer Index for O(1) lookups
    std::unordered_map<int, int> cache_map;

public:
    explicit ClockCache(int cap) : capacity(cap), clock_hand(0) {
        ring_buffer.resize(capacity, {0, 0, false, false});
        cache_map.reserve(capacity);
    }

    int get(int key) {
        auto it = cache_map.find(key);
        if (it == cache_map.end()) {
            return -1; // Cache Miss
        }

        int index = it->second;
        // Optimization: Give it a "second chance" by just setting the bit.
        // No heavy pointer swapping or list mutations happen here!
        ring_buffer[index].referenced = true;
        
        return ring_buffer[index].value;
    }

    void put(int key, int value) {
        auto it = cache_map.find(key);
        if (it != cache_map.end()) {
            // Case 1: Key already exists. Update value and set referenced bit.
            int index = it->second;
            ring_buffer[index].value = value;
            ring_buffer[index].referenced = true;
            return;
        }

        // Case 2: Key does not exist. We need an entry slot.
        // If we have an empty unallocated slot, use it immediately before evicting
        if (cache_map.size() < static_cast<size_t>(capacity)) {
            for (int i = 0; i < capacity; ++i) {
                if (!ring_buffer[i].is_valid) {
                    ring_buffer[i] = {key, value, true, true};
                    cache_map[key] = i;
                    return;
                }
            }
        }

        // Case 3: Cache is completely full. Rotate the clock hand to find a victim.
        while (true) {
            CacheEntry& current = ring_buffer[clock_hand];

            if (!current.referenced) {
                // Victim found! Evict old key from map
                cache_map.erase(current.key);

                // Overwrite slot with new cache item
                current.key = key;
                current.value = value;
                current.referenced = true; // Mark as recently accessed
                current.is_valid = true;

                cache_map[key] = clock_hand;
                
                // Move clock hand forward by one step for the next operation
                clock_hand = (clock_hand + 1) % capacity;
                return;
            }

            // If the bit was true, clear it to false (Second Chance given)
            current.referenced = false;
            
            // Advance the clock hand around the ring loop
            clock_hand = (clock_hand + 1) % capacity;
        }
    }
};

class SieveCache {
private:
    struct Node {
        int key;
        int value;
        bool visited; // SIEVE's 1-bit tracking flag
        Node* prev;
        Node* next;

        Node(int k, int v) : key(k), value(v), visited(false), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    Node* head; // Newest insertions go here
    Node* tail; // Oldest insertions sit here
    Node* hand; // The moving pointer used to filter eviction targets

    // Hash map mapping key -> raw pointer node for O(1) random access
    std::unordered_map<int, Node*> cache_map;

    // Helper to insert a fresh node directly at the head of our queue
    void insert_at_head(Node* node) noexcept {
        node->next = head;
        node->prev = nullptr;
        if (head != nullptr) {
            head->prev = node;
        }
        head = node;
        if (tail == nullptr) {
            tail = node;
        }
    }

    // Helper to remove an identified victim node from anywhere in the list
    void remove_node(Node* node) noexcept {
        // If the eviction target happens to be pointed by the hand,
        // move the hand to the previous node (towards tail) before severing links.
        if (hand == node) {
            hand = node->prev;
        }

        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            head = node->next; // Node was head
        }

        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev; // Node was tail
        }
    }

public:
    explicit SieveCache(int cap) : capacity(cap), head(nullptr), tail(nullptr), hand(nullptr) {
        cache_map.reserve(capacity);
    }

    ~SieveCache() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* next_node = curr->next;
            delete curr;
            curr = next_node;
        }
    }

    int get(int key) {
        auto it = cache_map.find(key);
        if (it == cache_map.end()) {
            return -1; // Cache Miss
        }

        // Cache Hit: Toggle bit to true. No pointer changes occur.
        it->second->visited = true;
        return it->second->value;
    }

    void put(int key, int value) {
        auto it = cache_map.find(key);
        if (it != cache_map.end()) {
            // Key exists: update content and update visited flag
            it->second->value = value;
            it->second->visited = true;
            return;
        }

        // Cache Miss: Eviction logic applies if capacity boundary is exceeded
        if (cache_map.size() >= static_cast<size_t>(capacity)) {
            // If the hand has not been initialized or fell off, reset it to the tail
            if (hand == nullptr) {
                hand = tail;
            }

            // Sift through the list to find an unvisited node
            while (hand != nullptr && hand->visited) {
                hand->visited = false; // Reset flag (Lazy Demotion / Second Chance)
                hand = hand->prev;     // Move hand up towards the head
                if (hand == nullptr) {
                    hand = tail;       // Wrap around to tail if head is passed
                }
            }

            // At this point, hand is guaranteed to point to an unvisited node
            Node* victim = hand;
            
            // Advance the hand before deleting the victim so it isn't orphaned
            hand = victim->prev;

            // Evict the node
            cache_map.erase(victim->key);
            remove_node(victim);
            delete victim;
        }

        // Add the fresh incoming node straight to the head position
        Node* new_node = new Node(key, value);
        insert_at_head(new_node);
        cache_map[key] = new_node;
    }
};


int main() {
    // Fast I/O optimization
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Initializing an LRU Cache with a capacity of 2
    LRUCache lRUCache(2);

    lRUCache.put(1, 10); // cache: {1=10}
    
    std::cout << "get(1): " << lRUCache.get(1) << " (Expected: 10)\n";
    
    lRUCache.put(2, 20); // cache: {1=10, 2=20}
    lRUCache.put(3, 30); // Evicts key 1. cache: {2=20, 3=30}
    
    std::cout << "get(2): " << lRUCache.get(2) << " (Expected: 20)\n";
    std::cout << "get(1): " << lRUCache.get(1) << " (Expected: -1)\n";

    return 0;
}
