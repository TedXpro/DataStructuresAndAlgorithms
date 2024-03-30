#include <iostream>

using namespace std;

class LinkedList
{
private:
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

    ListNode *head;

    ListNode *merge(ListNode *left, ListNode *right);
    ListNode *mergeSort(ListNode *head);

    ListNode *findMidPoint(ListNode *head);

public:
    void addToHead(int);
    void addToTail(int);
    void displayElements();
    void sort()
    {
        head = mergeSort(head);
    }

    LinkedList() : head(nullptr) {}
};

void LinkedList::addToHead(int num)
{
    ListNode *newNode = new ListNode(num);
    newNode->next = head;
    head = newNode;
}

void LinkedList::addToTail(int num)
{
    ListNode *newNode = new ListNode(num);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        ListNode *nodeptr = head;
        while (nodeptr->next != nullptr)
            nodeptr = nodeptr->next;
        nodeptr->next = newNode;
    }
}

void LinkedList::displayElements()
{
    ListNode *nodeptr = head;
    while (nodeptr != nullptr)
    {
        cout << nodeptr->val << " -> ";
        nodeptr = nodeptr->next;
    }
    cout << "nullptr" << endl;
}

LinkedList::ListNode *LinkedList::findMidPoint(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    ListNode *slow = head;
    ListNode *fast = head->next;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

LinkedList::ListNode *LinkedList::merge(ListNode *left, ListNode *right)
{
    ListNode dummy(0);
    ListNode *tail = &dummy;

    while (left != nullptr && right != nullptr)
    {
        if (left->val < right->val)
        {
            tail->next = left;
            left = left->next;
        }
        else
        {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }

    tail->next = (left != nullptr) ? left : right;
    return dummy.next;
}

LinkedList::ListNode *LinkedList::mergeSort(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    ListNode *mid = findMidPoint(head);
    ListNode *left = head;
    ListNode *right = mid->next;
    mid->next = nullptr;

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

int main()
{
    LinkedList llist;

    llist.addToHead(1);
    llist.addToHead(2);
    llist.addToHead(4);
    llist.addToHead(6);
    llist.addToHead(3);
    llist.addToHead(0);

    cout << "Before sorting: ";
    llist.displayElements(); // expected outcome: 0 3 6 4 2 1

    llist.sort();

    cout << "After sorting: ";
    llist.displayElements(); // expected outcome: 0 1 2 3 4 6

    cout << "\nAdding elements to head after sorting\n";
    llist.addToHead(19);
    llist.addToHead(-8);
    llist.addToHead(13);
    llist.displayElements(); // expected outcome: 13 -8 19 0 1 2 3 4 6

    cout << "\nAdding elements to tail\n";
    llist.addToTail(100);
    llist.addToTail(99);
    llist.addToTail(5);
    llist.displayElements(); // expected outcome: 13 -8 19 0 1 2 3 4 6 100 99 5

    cout << "\nSorting the current linked list\n";
    llist.sort();
    llist.displayElements(); // expected outcome: -8 0 1 2 3 4 5 6 13 19 99 100 

    return 0;
}
