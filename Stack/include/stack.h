#ifndef STACK_H
#define STACK_H

#include "data_structure.h"

template <typename T> class Stack: public Vector<T>
{
    public:
        void push(T const& e){ insert(size(), e);}
        T pop() { return remove(size() - 1);}
        T& top() { return (*this) [size - 1];}
};

#endif // STACK_H
