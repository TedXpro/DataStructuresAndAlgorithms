#ifndef ARRAY_QUEUE
#define ARRAY_QUEUE

template <class T, int size = 100>
class ArrayQueue
{
private:
    int first, last;
    T storage[size];

public:
    ArrayQueue()
    {
        first = last = -1;
    }

    T dequeue();
    void enqueue(T);

    bool isFull(){
        return first == 0 && last == size - 1 || first == last + 1;
    }

    bool isEmpty(){
        return first == -1;
    }
};

template<class T, int size>
void ArrayQueue<T,size>::enqueue(T value){
    if(!isFull()){
        if(last == size - 1|| last == -1){
            storage[0] = value;
            last = 0;
            if(first == -1)
                first = 0;
        }
        else
            cout << "Queue is Full!\n";
    }
}

template<class T, int size>
T ArrayQueue<T,size>::dequeue(){
    T value = storage[first];
    if(first == last)
        last = first = -1;
    else if(first == size - 1)
        first = 0;
    else
        first++;
}


#endif