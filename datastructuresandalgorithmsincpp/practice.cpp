#include <iostream>

using namespace std;

class BinarySearchTree
{
private:
    struct TreeNode{
        int val;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode *root;

    void insertNode(TreeNode*& nodeptr, TreeNode *&newNode){
        if(nodeptr == nullptr)
            nodeptr = newNode;
        else if(nodeptr->val > newNode->val)
            insertNode(nodeptr->left, newNode);
        else
            insertNode(nodeptr->right, newNode);
    }

    void displayInOder(TreeNode *nodeptr){
        if(nodeptr){
            displayInOder(nodeptr->left);
            cout << nodeptr->val << " ";
            displayInOder(nodeptr->right);
        }
    }

public:
    BinarySearchTree(){
        root = nullptr;
    }

    void insertValue(int value){
        TreeNode *newNode = nullptr;
        newNode->val = value;
        newNode->left = nullptr;
        newNode->right = nullptr;

        insertNode(root, newNode);
    }

    bool searchValue(int value){
        TreeNode *nodeptr = root;

        while(nodeptr){
            if(nodeptr->val == value)
                return true;
            else if(nodeptr->val > value)
                nodeptr = nodeptr->left;
            else
                nodeptr = nodeptr->right;
        }

        return false;
    }

    void inorder(){
        displayInOder(root);
    }
};

int main()
{
    BinarySearchTree *tree ;
    tree->insertValue(30);
    cout << "inserted\n";
    tree->insertValue(40);
    tree->insertValue(60);
    tree->insertValue(20);
    tree->insertValue(10);
    tree->insertValue(19);
    tree->insertValue(29);
    tree->insertValue(9);
    tree->insertValue(0);
    tree->insertValue(53);
    tree->insertValue(3);
    tree->insertValue(72);
    tree->insertValue(47);
    tree->insertValue(30);
    tree->insertValue(10);
    tree->insertValue(20);

    tree->inorder();
}