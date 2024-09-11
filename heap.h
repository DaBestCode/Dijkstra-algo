// heap.h
#ifndef HEAP_H
#define HEAP_H

#include <vector>

struct MinHeapNode {
    int vertex;
    double key;
};

class MinHeap {
private:
    std::vector<MinHeapNode> heap;
    int capacity;
    int heapSize;

public:
    MinHeap(int capacity);
    ~MinHeap();

    void heapify(int idx);
    void insertKey(int v, double key);
    MinHeapNode extractMin();
    void decreaseKey(int v, double newKey);
    bool isEmpty();
};

#endif // HEAP_H
