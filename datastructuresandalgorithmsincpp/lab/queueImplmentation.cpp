#include <iostream>

using namespace std;

class QueueArray
{
private:
    int *queArray;
    int queueSize;
    int elements;
    int front;
    int rear;

public:
    QueueArray(int size)
    {
        queArray = new int[size];
        queueSize = size;
        front = -1;
        rear = -1;
        elements = 0;
    }

    ~QueueArray()
    {
        delete[] queArray;
    }

    bool isFull()
    {
        return queueSize == elements;
    }

    bool isEmpty()
    {
        return elements == 0;
    }

    void enqueue(int val)
    {
        if (isFull())
        {
            cout << "Queue is full!\n";
            return;
        }

        rear = (rear + 1) % queueSize;
        queArray[rear] = val;
        elements++;
    }

    void dequeue(int &num)
    {
        if (isEmpty())
        {
            cout << "Queue is empty!\n";
            return;
        }

        front = (front + 1) % queueSize;
        num = queArray[front];
        elements--;
    }
};

int main() 
{
    const int MAX_VALUES = 5; 
    QueueArray iQueue(MAX_VALUES);

    cout << "Enqueuing " << MAX_VALUES << " items...\n";
    for (int x = 0; x < MAX_VALUES; x++)
         iQueue.enqueue(x);

    cout << "Now attempting to enqueue again...\n";
    iQueue.enqueue(MAX_VALUES);

    cout << "The values in the queue were:\n";
    while (!iQueue.isEmpty())
    {
        int value;
        iQueue.dequeue(value);
        cout << value << endl;
    }
    return 0;
}