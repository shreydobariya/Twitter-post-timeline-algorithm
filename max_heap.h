
#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <vector>
#include <stdexcept>

template <typename T>
class MaxHeap {
private:
    std::vector<T> heap;

    void maxHeapify(int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < heap.size() && heap[left] > heap[largest])
            largest = left;

        if (right < heap.size() && heap[right] > heap[largest])
            largest = right;

        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            maxHeapify(largest);
        }
    }

public:
    MaxHeap() {}

    MaxHeap(const std::vector<T>& arr) {
        heap = arr;
        int n = heap.size();
        for (int i =n / 2 - 1; i >= 0; i--) {
            maxHeapify(i);
        }
    }

    void insert(const T& value) {
        // Provide your implementation here
        heap.push_back(value);
        int i =heap.size()-1;
        while(i>0 && heap[(i-1)/2]<heap[i])
        {
            std::swap(heap[i],heap[(i-1)/2]);
            i=(i-1)/2;
        }
        // End of your implementation
    }

    T getMax() {
        if (!isEmpty()) {
            return heap[0];
        }
        throw std::runtime_error("Heap is empty.");
    }

    T extractMax() {
        if (!isEmpty()) {
            // Provide your implementation here
             T maxVal=heap[0];
            heap[0]=heap.back();
            heap.pop_back();
            maxHeapify(0);
            return maxVal;
            // Don't forget to return the extacted Max item
            // End of your implementation
        }
        throw std::runtime_error("Heap is empty.");
    }

    bool isEmpty() {
        return heap.empty();
    }
};

#endif // MAX_HEAP_H
