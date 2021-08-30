#ifndef STACK_CPP_
#define STACK_CPP_

#include "stack.h"
#include <cassert>


stack::stack(int size) {
    assert(size >= 0 && "stack size must be natural");
    m_size = size;
    m_stack = new int[m_size];
    m_index = 0;
}

stack::~stack() {
    delete[] m_stack;
}

bool stack::isEmpty() {
    if(m_index == 0) {
        return true;
    }
    return false;
}

bool stack::isFull() {
    if(m_index == m_size) {
        return true;
    }
    return false;
}

stack &stack::push(int i) {
    assert(!this->isFull() && "stack overflow");
    m_stack[m_index++] = i;
    return *this;
}

int stack::pop() {
    assert(!this->isEmpty() && "stack is empty");
    return m_stack[--m_index];
}

int stack::top() {
    assert(!this->isEmpty() && "stack is empty");
    return m_stack[m_index - 1];
}



#endif /* STACK_CPP_ */
