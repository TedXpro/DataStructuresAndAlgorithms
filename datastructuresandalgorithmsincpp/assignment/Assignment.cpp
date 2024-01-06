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

class Course
{
private:
    string courseNumber;
    string courseTitle;
    int creditHour;

public:
    Course(string courseNum)
    {
        courseNumber = courseNum;
    }

    string getCourseNumber()
    {
        return courseNumber;
    }

    string getCourseTitle()
    {
        return courseTitle;
    }

    int getCreditHour()
    {
        return creditHour;
    }

    void setCourseTitle(string coTitle)
    {
        courseTitle = coTitle;
    }

    void setCreditHour(int creditHr)
    {
        creditHour = creditHr;
    }
};

class StudentTree
{
private:
    /*  create a structure called TreeNode
    that holds the Binary Search Tree Information */
    struct TreeNode
    {
        int studentId;
        Student *studentInfo;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int id, Student *StudInfo)
        {
            studentId = id;
            studentInfo = StudInfo;
            left = nullptr;
            right = nullptr;
        }
    };

    TreeNode *root; // create a variable for root node;

    /**
     * This function inserts the student info at the
     * right node by traversing the tree.
     */
    void insertNode(TreeNode *&nodeptr, TreeNode *&newNode)
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
    void displayInOrder(TreeNode *nodeptr)
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

public:
    /**
     * This method accepts the student id and the
     * student info and passes it to the insertNode function
     */
    void insertStudent(int id, Student *studInfo)
    {
        TreeNode *newNode = new TreeNode(id, studInfo);

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
        TreeNode *nodeptr = root;

        bool status = false;
        while (nodeptr)
        {
            if (nodeptr->studentId == studentId)
            {
                status = true;
                cout << "Student id: " << nodeptr->studentId << endl;
                cout << "First Name: " << nodeptr->studentInfo->getFirstName() << endl;
                cout << "Last Name: " << nodeptr->studentInfo->getLastName() << endl;
                cout << "Age: " << nodeptr->studentInfo->getAge() << endl;
                cout << "Sex: " << nodeptr->studentInfo->getSex() << endl;
                cout << "-----------------------------------\n";
            }
            else if (nodeptr->studentId > studentId)
                nodeptr = nodeptr->left;
            else
                nodeptr = nodeptr->right;
        }

        if (!status)
        {
            cout << "\nThere is No Student with this id!\n\n";
        }
    }
};

class CourseTree
{
private:
    struct TreeNode
    {
        string courseNumber;
        Course *coursePointer;
        TreeNode *left;
        TreeNode *right;

        TreeNode(string coNum, Course *coPtr)
        {
            courseNumber = coNum;
            coursePointer = coPtr;
            left = nullptr;
            right = nullptr;
        }
    };

    TreeNode *root;

    /**
     * This function inserts a new node to the binary tree.
     */
    void insertNode(TreeNode *&nodeptr, TreeNode *&newNode)
    {
        if (nodeptr == nullptr)
            nodeptr = newNode;
        else if (nodeptr->courseNumber > newNode->courseNumber)
            insertNode(nodeptr->left, newNode);
        else
            insertNode(nodeptr->right, newNode);
    }

public:
    CourseTree()
    {
        root = nullptr;
    }

    /**
     * This function takes the course number and the course,
     * creates a new node and calls the insertNode function
     * by passing the root node and new node.
     */
    void insertCourse(string courseNumber, Course *coPtr)
    {
        TreeNode *newNode = new TreeNode(courseNumber, coPtr);

        insertNode(root, newNode);
    }

    /**
     * This method searches a course from the binary
     * search tree using its course number.
     */
    void searchCourse(string coNum)
    {
        TreeNode *nodeptr = root;
        bool status = false;

        while (nodeptr)
        {
            if (nodeptr->courseNumber == coNum)
            {
                cout << "Course Number: " << nodeptr->courseNumber << endl;
                cout << "Course Name: " << nodeptr->coursePointer->getCourseTitle() << endl;
                cout << "Credit Hour: " << nodeptr->coursePointer->getCreditHour() << endl;
                cout << "------------------------------------------\n";
                status = true;
            }
            else if (nodeptr->courseNumber > coNum)
                nodeptr = nodeptr->left;
            else
                nodeptr = nodeptr->right;
        }

        if (!status)
            cout << "There is No Course By This number!\n\n";
    }
};
