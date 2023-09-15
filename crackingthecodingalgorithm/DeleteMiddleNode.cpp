// 2.3 Delete Middle Node

#include <iostream>

using namespace std;

struct LinkedNode
{
    int value;
    LinkedNode *next;
};

void deleteMiddleNode(LinkedNode *middleNode)
{
    if (middleNode->next == nullptr)
    {
        middleNode = nullptr;
    }
    else{
        LinkedNode *tempNode = middleNode->next;
        middleNode->value = tempNode->value;
        middleNode->next = tempNode->next;
    }
}