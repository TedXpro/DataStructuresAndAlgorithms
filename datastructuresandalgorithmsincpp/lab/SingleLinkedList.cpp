#include <iostream>

using namespace std;

class LinkedList
{
private:
    struct Node
    {
        int value;
        Node *next;

        Node(int value, Node *next = nullptr)
        {
            this->value = value;
            this->next = next;
        }
    };

    Node *head;

public:
    LinkedList()
    {
        head = nullptr;
    }

    void addToHead(int);
    void addToTail(int);
    void deleteNode(int);
};

void LinkedList::addToHead(int value)
{

    // Node *newNode = new Node(value, head);
    // head = newNode;

    Node *newNode = new Node(value);
    newNode->next = head;
    head = newNode;
}

void LinkedList::addToTail(int value)
{
    /* head -> 1 -> 2 -> 3 -> 4 -> null */
    Node *newNode = new Node(value);
    if (head == nullptr)
    { // if its empty??
        head = newNode;
        return;
    }

    Node *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

void LinkedList::deleteNode(int value)
{
    /*              p    ct */
    /* head -> 1 -> 2 -> 3 -> 4 -> null delete 3*/
    if(!head)
    {
        cout << "Value Not Found!\n";
        return;
    }
    if(head->value == value){
        Node *temp = head;
        head = head->next;
        delete temp;
        cout << "Successfully deleted!\n";
        return;
    }
    Node *prev = nullptr;
    Node *current = head;

    while (current != nullptr && current->value != value)
    {
        prev = current;
        current = current->next;
    }

    if (current)
    {
        Node *temp = current;
        prev->next = current->next;
        delete temp;
        cout << "Successfully deletede!\n";
    }
    else
        cout << "Value Not Found!\n";
}

int main()
{
    
}