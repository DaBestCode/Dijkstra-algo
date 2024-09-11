// util.h
#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include "graph.h"


void relax(Node *node, std::vector<Vertex *> &V, MinHeap &minHeap, int source);
void dijkstra(std::vector<Vertex *> &V, const std::vector<std::vector<Node *>> &ADJ, int source);
void printADJ(const std::vector<std::vector<Node *>> &ADJ);
void printLength(const std::vector<Vertex *> &V, int s, int t);
void printPath(const std::vector<Vertex *> &V, int s, int t);
void dijkstraSinglePair(const std::vector<std::vector<Node *>> &ADJ, std::vector<Vertex *> &V, int source, int destination);

#endif // UTIL_H
