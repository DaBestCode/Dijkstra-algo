// stack.cpp
#include "data_structures.h"
#include <iostream>

Stack::Stack(int cap) : capacity(cap), top(-1)
{
    data.resize(capacity);
}

Stack::~Stack() {}

int Stack::pop()
{
    if (isEmpty())
    {
        std::cerr << "Stack underflow\n";
        return -1;
    }

    return data[top--];
}

void Stack::push(int v)
{
    if (top == capacity - 1)
    {
        std::cerr << "Stack overflow\n";
        return;
    }

    data[++top] = v;
}

bool Stack::isEmpty()
{
    return top == -1;
}
