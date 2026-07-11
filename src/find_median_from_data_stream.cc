/*
 *  Array the data into 2 halves: low (max heap) and high (min heap)
 *  Any number in low half is less or equal to any number in the high half.
 *  In additon they follow the size constraint:
 *     low.size()>=high.size() && low.size() + 1 <= high.size()
 *     median = low.size() > high.size() ? low.top() : (low.top() + high.top())/2
 */    
#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <random>

class MedianFinderStandard {
protected: 
    // Max-heap to store the smaller half of the numbers
    std::priority_queue<int> low; 
    
    // Min-heap to store the larger half of the numbers
    std::priority_queue<int, std::vector<int>, std::greater<int>> high; 


public:
    MedianFinderStandard() = default;
    
    void addNum(int num) {
        // Step 1: Add to max-heap
        low.push(num);
        
        // Step 2: Balancing step - move the maximum element of 'low' to 'high'
        high.push(low.top());
        low.pop();
        
        // Step 3: Maintain size constraint (low.size() >= high.size())
        if (low.size() < high.size()) {
            low.push(high.top());
            high.pop();
        }
    }
    
    double findMedian() {
        // If total size is odd, 'low' contains the exact median
        if (low.size() > high.size()) {
            return low.top();
        }
        // If total size is even, return the average of both tops
        return (low.top() + high.top()) / 2.0;
    }
};


class MedianFinderOptimized : public MedianFinderStandard {
public:
    MedianFinderOptimized() = default;

    void addNum(int num) {
        // The number is on the left half
        if (low.empty() || num < low.top()) {
            low.push(num); 
            if (low.size() > high.size() + 1) {
                high.push(low.top());
                low.pop();
            }
        }
        // The number is on the right half
        else if (!high.empty() && num > high.top()) {
            high.push(num); 

            if (high.size() > low.size()) {
                low.push(high.top());
                high.pop();
            }
        }
        // The number falls perfectly in the middle
        else { 
            if (low.size() <= high.size()) { 
                low.push(num);
            }
            else {
                high.push(num);
            }
        }
    }
};

int main() {
    const int DATA_SIZE = 1000000; // 1 Million numbers
    std::vector<int> test_data(DATA_SIZE);

    // Initialize random number generator
    std::mt19937 rng(1337); // Fixed seed for identical test runs
    std::uniform_int_distribution<int> dist(-100000, 100000);

    for (int i = 0; i < DATA_SIZE; ++i) {
        test_data[i] = dist(rng);
    }

    std::cout << "Starting benchmark with " << DATA_SIZE << " integers...\n\n";

    // 1. Benchmark Standard Approach
    MedianFinderStandard mf_standard;
    auto start_standard = std::chrono::high_resolution_clock::now();
    for (int num : test_data) {
        mf_standard.addNum(num);
    }
    std::cout << "Median=" << mf_standard.findMedian() << std::endl;
    auto end_standard = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_standard = end_standard - start_standard;
    
    std::cout << "Standard Approach:  " << duration_standard.count() << " ms\n";

    // 2. Benchmark Optimized Approach
    MedianFinderOptimized mf_optimized;
    auto start_optimized = std::chrono::high_resolution_clock::now();
    for (int num : test_data) {
        mf_optimized.addNum(num);
    }
    std::cout << "Median=" << mf_optimized.findMedian() << std::endl;
    auto end_optimized = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_optimized = end_optimized - start_optimized;

    std::cout << "Optimized Approach: " << duration_optimized.count() << " ms\n";

    // Calculate percentage improvement
    double improvement = ((duration_standard.count() - duration_optimized.count()) / duration_standard.count()) * 100;
    std::cout << "\nPerformance Improvement: " << improvement << "%\n";

    return 0;
}

