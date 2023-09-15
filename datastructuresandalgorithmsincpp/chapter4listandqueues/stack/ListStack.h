#ifndef STACK_List
#define STACK_LIST

#include <list>

template<class T>
class ListStack
{
private:
    list<T> listPool;

public:
    StackList(){
    }

    void clear(){
        listPool.clear();
    }

    bool isEmpty() const {
        return listPool.empty();
    }

    T& topEl(){
        return listPool.back();
    }

    T pop(){
        T el = listPool.back();
        listPool.pop_back();
        return el;
    }

    void push(T el){
        listPool.push_back(el);
    }
};

#endif