#include <iostream>

using namespace std;

class Student
{
private:
    int studentId;
    string firstName;
    string lastName;
    int age;
    char sex;

public:
    Student(int id)
    {
        // studentId = id;
    }

    Student()
    {
    }
    // ~Student();

    int getId()
    {
        return studentId;
    }

    string getFirstName()
    {
        return firstName;
    }
    string getLastName()
    {
        return lastName;
    }

    int getAge()
    {
        return age;
    }

    char getSex()
    {
        return sex;
    }

    void setStudentId(int id)
    {
        studentId = id;
    }

    void setFirstName(string fName)
    {
        firstName = fName;
    }

    void setLastName(string lName)
    {
        lastName = lName;
    }

    void setAge(int a)
    {
        age = a;
    }

    void setSex(char s)
    {
        sex = s;
    }
};

class StudentTree
{
private:
    /*  create a structure called TreeNode
    that holds the Binary Search Tree Information */
    struct StudentTreeNode
    {
        int studentId;
        Student *studentInfo;
        StudentTreeNode *left;
        StudentTreeNode *right;

        StudentTreeNode(int id, Student *StudInfo)
        {
            studentId = id;
            studentInfo = StudInfo;
            left = nullptr;
            right = nullptr;
        }
    };

    StudentTreeNode *root; // create a variable for root node;

    /**
     * This function inserts the student info at the
     * right node by traversing the tree.
     */
    void insertNode(StudentTreeNode *&nodeptr, StudentTreeNode *&newNode)
    {
        if (nodeptr == nullptr)
            nodeptr = newNode;
        else if (nodeptr->studentId > newNode->studentId)
            insertNode(nodeptr->left, newNode);
        else
            insertNode(nodeptr->right, newNode);
    }

    /**
     * This function displays all the students in the
     * binary tree in InOrder Traversal
     */
    void displayInOrder(StudentTreeNode *nodeptr)
    {
        if (nodeptr)
        { 
            displayInOrder(nodeptr->left);

            cout << "Student Id: " << nodeptr->studentInfo->getId() << endl;
            cout << "First Name: " << nodeptr->studentInfo->getFirstName() << endl;
            cout << "Last Name: " << nodeptr->studentInfo->getLastName() << endl;
            cout << "Age: " << nodeptr->studentInfo->getAge() << endl;
            cout << "Sex: " << nodeptr->studentInfo->getSex() << endl;
            cout << "--------------------------------------------\n";

            displayInOrder(nodeptr->right);
        }
    }

    /**
     * This function finds the exact position of the
     * student to be deleted and passes it to makeDeletion.
     */
    void remove(int studId, StudentTreeNode *nodeptr)
    {
        if (nodeptr == nullptr)
        {
            cout << "Student Not Found!\n";
            return;
        }
        if (studId > nodeptr->studentId)
            remove(studId, nodeptr->right);
        else if (studId < nodeptr->studentId)
            remove(studId, nodeptr->left);
        else if (nodeptr->studentId == studId)
            makeDeletion(nodeptr);
    }

    /**
     * This function deletes the treeNode if it actually exists.
     */
    void makeDeletion(StudentTreeNode *&nodeptr)
    {
        StudentTreeNode *tempNodePtr = nullptr;
        if (nodeptr->right == nullptr)
        {
            tempNodePtr = nodeptr;
            nodeptr = nullptr;
            delete tempNodePtr;
        }
        else if (nodeptr->left == nullptr)
        {
            tempNodePtr = nodeptr;
            nodeptr = nodeptr->right;
            delete tempNodePtr;
        }
        else
        {
            tempNodePtr = nodeptr->right;

            while (tempNodePtr->left)
                tempNodePtr = tempNodePtr->left;

            tempNodePtr->left = nodeptr->left;
            StudentTreeNode *tNode = nodeptr;
            nodeptr = nodeptr->right;
            delete tNode;
        }
        cout << "Successfully Deleted!\n";
    }

public:
    StudentTree()
    {
        root = nullptr;
    }
    /**
     * This method accepts the student id and the
     * student info and passes it to the insertNode function
     */
    void insertStudent(int id, Student &studInfo)
    {
        StudentTreeNode *newNode = new StudentTreeNode(id, &studInfo);

        insertNode(root, newNode);
    }

    /**
     * This function calls the displayInOder function
     * by passing the root node of the Binary Search Tree
     */
    void displayInOrder()
    {
        if (root)
            displayInOrder(root);
        else
        {
            cout << "There are No Students registered at the moment\n\n";
        }
    }

    /**
     * This function searches the binary search tree to
     * find a student using student id and displays the
     * student information if found.
     */
    void searchStudent(int studentId)
    {
        StudentTreeNode *nodeptr = root;

        while (nodeptr)
        {
            if (nodeptr->studentId == studentId)
            {
                cout << "Student id: " << nodeptr->studentId << endl;
                cout << "First Name: " << nodeptr->studentInfo->getFirstName() << endl;
                cout << "Last Name: " << nodeptr->studentInfo->getLastName() << endl;
                cout << "Age: " << nodeptr->studentInfo->getAge() << endl;
                cout << "Sex: " << nodeptr->studentInfo->getSex() << endl;
                cout << "-----------------------------------\n";
                return;
            }
            else if (nodeptr->studentId > studentId)
                nodeptr = nodeptr->left;
            else
                nodeptr = nodeptr->right;
        }

        cout << "\nThere is No Student with this id!\n\n";
    }

    /**
     * This function accepts student id to be
     * deleted and passes it to remove.
     */
    void deleteStudent(int studId)
    {
        remove(studId, root);
    }
};

int main()
{

    StudentTree *studBinTree = new StudentTree();

    Student s1;
    s1.setStudentId(1);
    s1.setAge(20);
    s1.setFirstName("Yohannes");
    s1.setLastName("Woldeyes");
    s1.setSex('M');

    Student s2;
    s2.setStudentId(2);
    s2.setAge(20);
    s2.setFirstName("Menilik");
    s2.setLastName("Woldeyes");
    s2.setSex('M');
    Student s3;
    s3.setStudentId(3);
    s3.setAge(20);
    s3.setFirstName("Makeda");
    s3.setLastName("Woldeyes");
    s3.setSex('F');
    Student s4;
    s4.setStudentId(4);
    s4.setAge(20);
    s4.setFirstName("Dagmawi");
    s4.setLastName("Woldeyes");
    s4.setSex('M');
    Student s5;
    s5.setStudentId(5);
    s5.setAge(20);
    s5.setFirstName("adsafasf");
    s5.setLastName("asfasfas");
    s5.setSex('F');

    cout << "Inserting Students.\n";
    studBinTree->insertStudent(3, s3);
    studBinTree->insertStudent(1, s1);
    studBinTree->insertStudent(2, s2);
    studBinTree->insertStudent(4, s4);
    studBinTree->insertStudent(5, s5);

    // cout << "displaying inorder\n";
    // studBinTree->displayInOrder();

    // studBinTree->displayInOrder();
    cout << "Deleting 5\n";
    studBinTree->deleteStudent(5);
    cout << "Searching for a student.\n";
    studBinTree->searchStudent(3);
    studBinTree->searchStudent(2);
    studBinTree->searchStudent(5);
    studBinTree->displayInOrder();

    delete studBinTree;
}
