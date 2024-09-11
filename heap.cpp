// heap.cpp
#include "data_structures.h"
#include <limits>
#include <iostream>

MinHeap::MinHeap(int cap) : capacity(cap), heapSize(0)
{
    heap.resize(capacity);
}

MinHeap::~MinHeap() {}

void MinHeap::heapify(int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heapSize && heap[left].key < heap[smallest].key)
        smallest = left;

    if (right < heapSize && heap[right].key < heap[smallest].key)
        smallest = right;

    if (smallest != idx)
    {
        std::swap(heap[idx], heap[smallest]);
        heapify(smallest);
    }
}

void MinHeap::insertKey(int v, double key)
{
    if (heapSize == capacity)
    {
        std::cerr << "Heap overflow\n";
        return;
    }

    int i = heapSize++;
    heap[i].vertex = v;
    heap[i].key = key;

    while (i != 0 && heap[(i - 1) / 2].key > heap[i].key)
    {
        std::swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

MinHeapNode MinHeap::extractMin()
{
    if (isEmpty())
    {
        std::cerr << "Heap underflow\n";
        return {0, std::numeric_limits<double>::infinity()};
    }

    MinHeapNode root = heap[0];
    heap[0] = heap[--heapSize];
    heapify(0);

    return root;
}

void MinHeap::decreaseKey(int v, double newKey)
{
    int i;
    for (i = 0; i < heapSize; i++)
    {
        if (heap[i].vertex == v)
            break;
    }

    heap[i].key = newKey;

    while (i != 0 && heap[(i - 1) / 2].key > heap[i].key)
    {
        std::swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

bool MinHeap::isEmpty()
{
    return heapSize == 0;
}
