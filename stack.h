// stack.h
#ifndef STACK_H
#define STACK_H

#include <vector>

class Stack
{
private:
    std::vector<int> data;
    int capacity;
    int top;

public:
    Stack(int cap);
    ~Stack();

    int pop();
    void push(int v);
    bool isEmpty();
};

#endif // STACK_H
