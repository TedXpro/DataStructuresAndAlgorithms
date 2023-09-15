#ifndef VECTOR_STACK
#define VECTOR_STACK

#include <vector>

using namespace std;

template <class T>
class VectorStack
{
private:
    vector<T> pool;
    const int size = 30;

public:
    Stack()
    {
        pool.reserve(size);
    }

    bool isEmpty()
    {
        return pool.empty();
    }

    void push(T value)
    {
        pool.push_back(value);
    }

    T pop()
    {
        T value = pool.back();
        pool.pop_back();
        return value;
    }

    T& peak()
    {
        return pool.back();
    }

    void clear()
    {
        pool.clear();
    }
};

#endif