// graph.cpp
#include "data_structures.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cfloat>

void buildGraph(const std::string &filename, std::vector<Vertex *> &V, std::vector<std::vector<Node *>> &ADJ, int &numVertices, int &numEdges, int flag, const std::string &graphType)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    // Read number of vertices and edges
    file >> numVertices >> numEdges;

    // Resize vectors
    V.resize(numVertices + 1);   // +1 to make indexing 1-based
    ADJ.resize(numVertices + 1); // +1 to make indexing 1-based

    // Initialize vertices
    for (int i = 1; i <= numVertices; ++i)
    {
        V[i] = new Vertex{i, DBL_MAX, -1}; // Initialize with infinite key and no predecessor
    }

    // Read edges and populate adjacency lists
    for (int i = 0; i < numEdges; ++i)
    {
        int edgeIndex, u, v;
        double weight;
        file >> edgeIndex >> u >> v >> weight;

        // Create new nodes for the edge
        Node *nodeUV = new Node(v, weight);
        Node *nodeVU = new Node(u, weight);

        // Insert nodes into adjacency lists based on flag and graph type
        if (flag == 1)
        {
            if (graphType == "UndirectedGraph")
            {
                // For undirected graphs with flag 1, insert at the front of ADJ[u] and ADJ[v]
                ADJ[u].insert(ADJ[u].begin(), nodeUV);
                if (u != v)
                {
                    ADJ[v].insert(ADJ[v].begin(), nodeVU);
                }
            }
            else if (graphType == "DirectedGraph")
            {

                // For directed graphs with flag 1, insert at the front of ADJ[u]
                ADJ[u].insert(ADJ[u].begin(), nodeUV);
            }
        }
        else if (flag == 2)
        {
            if (graphType == "UndirectedGraph")
            {
                // For undirected graphs with flag 2, insert at the rear of ADJ[u] and ADJ[v]
                ADJ[u].push_back(nodeUV);
                if (u != v)
                {
                    ADJ[v].push_back(nodeVU);
                }
            }
            else if (graphType == "DirectedGraph")
            {

                // For directed graphs with flag 2, insert at the rear of ADJ[u]
                ADJ[u].push_back(nodeUV);
            }
        }
    }

    file.close();
}
