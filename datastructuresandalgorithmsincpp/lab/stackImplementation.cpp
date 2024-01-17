#include <iostream>
#include <vector>

using namespace std;

class StackArray
{
private:
    int *stArray;
    int stackSize;
    int top;

    bool isEmpty(){
        return top == -1;
    }

    bool isFull(){
        return top == stackSize - 1;
    }

public:
    StackArray(int size){
        stArray = new int[size];
        stackSize = size;
        top = -1;
    }

    ~StackArray(){
        delete[] stArray;
    }    

    void push(int val){
        if(isFull())
        {
            cout << "Stack overflow\n";
            return;
        }

        top++;
        stArray[top] = val;
    }

    void pop(){
        if(isEmpty())
        {
            cout << "Stack underflow\n";
            return;
        }

        int x = stArray[top];
        top--;
        cout << "the value being poped is: " << x << endl;
    }
};

int main(){

}