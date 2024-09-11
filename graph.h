// graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

// Structure to represent an edge node
struct Node
{
    int dest;
    double weight;
    Node(int d, double w) : dest(d), weight(w) {}
};

// Structure to represent a vertex
struct Vertex
{
    int index;
    double key;
    int pi;
};

// Function to build the graph from the input file
void buildGraph(const std::string &filename, std::vector<Vertex *> &V, std::vector<std::vector<Node *>> &ADJ, int &numVertices, int &numEdges, int flag, const std::string &graphType);

#endif // GRAPH_H
