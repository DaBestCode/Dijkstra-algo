// util.cpp
#include "data_structures.h"
#include <iostream>
#include <iomanip>
#include <cfloat>
#include <vector>
#include <limits>
#include <cmath>
#include <queue>

void relax(Node *node, std::vector<Vertex *> &V, MinHeap &minHeap, int source)
{
    int v = node->dest;
    double weight = node->weight;
    if (V[v]->key > V[source]->key + weight)
    {
        V[v]->key = V[source]->key + weight;
        V[v]->pi = source;
        minHeap.decreaseKey(v, V[v]->key);
    }
}

void dijkstraSinglePair(const std::vector<std::vector<Node *>> &ADJ, std::vector<Vertex *> &V, int source, int destination)
{
    int n = V.size();
    MinHeap minHeap(n);

    // Initialize single source
    for (int i = 1; i < n; ++i)
    {
        V[i]->key = DBL_MAX;
        V[i]->pi = -1;
    }
    V[source]->key = 0;

    // Insert all vertices into minHeap
    for (int i = 1; i < n; ++i)
    {
        minHeap.insertKey(i, V[i]->key);
    }

    while (!minHeap.isEmpty())
    {
        MinHeapNode minNode = minHeap.extractMin();
        int u = minNode.vertex;

        for (Node *node : ADJ[u])
        {
            relax(node, V, minHeap, u);
        }
    }
}

void dijkstra(std::vector<Vertex *> &V, const std::vector<std::vector<Node *>> &ADJ, int source)
{
    int n = V.size();
    MinHeap minHeap(n);

    // Initialize single source
    for (int i = 1; i < n; ++i)
    {
        V[i]->key = DBL_MAX;
        V[i]->pi = -1;
    }
    V[source]->key = 0;

    // Insert all vertices into minHeap
    for (int i = 1; i < n; ++i)
    {
        minHeap.insertKey(i, V[i]->key);
    }

    while (!minHeap.isEmpty())
    {
        MinHeapNode minNode = minHeap.extractMin();
        int u = minNode.vertex;

        for (Node *node : ADJ[u])
        {
            relax(node, V, minHeap, u);
        }
    }
}

void printADJ(const std::vector<std::vector<Node *>> &ADJ)
{
    for (size_t i = 1; i < ADJ.size(); ++i)
    {
        std::cout << "ADJ[" << i << "]:";
        if (!ADJ[i].empty())
        {
            std::cout << "-->";
            for (size_t j = 0; j < ADJ[i].size(); ++j)
            {
                Node *node = ADJ[i][j];
                std::cout << "[" << i << " " << node->dest << ": " << std::fixed << std::setprecision(2) << node->weight << "]";
                if (j < ADJ[i].size() - 1)
                {
                    std::cout << "-->";
                }
            }
        }
        std::cout << std::endl;
    }
}

void printLength(const std::vector<Vertex *> &V, int s, int t)
{
    if (V[t]->key != DBL_MAX)
    {
        std::cout << "The length of the shortest path from " << s << " to " << t << " is: ";
        std::cout << std::fixed << std::setprecision(2) << std::setw(8) << V[t]->key << std::endl;
    }
    else
    {
        std::cout << "There is no path from " << s << " to " << t << "." << std::endl;
    }
}

void printPath(const std::vector<Vertex *> &V, int s, int t)
{
    std::vector<int> path;
    int current = t;
    while (current != -1)
    {
        path.push_back(current);
        current = V[current]->pi;
    }

    if (path.back() == s)
    {
        std::cout << "The shortest path from " << s << " to " << t << " is:" << std::endl;
        std::cout << "[" << s << ":    0.00]";
        for (auto it = path.rbegin() + 1; it != path.rend(); ++it)
        {
            std::cout << "-->[" << *it << ":   " << std::setw(5) << std::fixed << std::setprecision(2) << V[*it]->key << "]";
        }
        std::cout << "." << std::endl;
    }
    else
    {
        std::cout << "There is no path from " << s << " to " << t << "." << std::endl;
    }
}
