#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>

using namespace std;

const string COURSE_FILE_NAME = "CourseTable.csv";

class Course
{
private:
    string courseNumber;
    string courseTitle;
    string creditHour;

public:
    Course(string courseNum)
    {
        courseNumber = courseNum;
    }

    Course() {}

    string getCourseNumber()
    {
        return courseNumber;
    }

    string getCourseTitle()
    {
        return courseTitle;
    }

    string getCreditHour()
    {
        return creditHour;
    }

    void setCourseNumber(string coNumber)
    {
        courseNumber = coNumber;
    }

    void setCourseTitle(string coTitle)
    {
        courseTitle = coTitle;
    }

    void setCreditHour(string creditHr)
    {
        creditHour = creditHr;
    }
};

class CourseTree
{
private:
    struct CourseTreeNode
    {
        string courseNumber;
        Course courseInfo;
        CourseTreeNode *left;
        CourseTreeNode *right;

        CourseTreeNode(string coNum, Course coPtr)
        {
            courseNumber = coNum;
            courseInfo = coPtr;
            left = nullptr;
            right = nullptr;
        }
    };
    set<string> courseNumbers;
    CourseTreeNode *root;

    /**
     * This function inserts a new node to the binary tree.
     */
    void insertNode(CourseTreeNode *&nodeptr, CourseTreeNode *&newNode)
    {
        if (nodeptr == nullptr)
            nodeptr = newNode;
        else if (nodeptr->courseNumber > newNode->courseNumber)
            insertNode(nodeptr->left, newNode);
        else
            insertNode(nodeptr->right, newNode);
    }

    void displayInOrder(CourseTreeNode *nodeptr)
    {
        if (nodeptr)
        {
            displayInOrder(nodeptr->left);

            cout << "Course Number: " << nodeptr->courseInfo.getCourseNumber() << endl;
            cout << "Course Title: " << nodeptr->courseInfo.getCourseTitle() << endl;
            cout << "Credit Hour: " << nodeptr->courseInfo.getCreditHour() << endl;
            cout << "------------------------------------------\n";

            displayInOrder(nodeptr->right);
        }
    }

    void saveToFile(CourseTreeNode *nodeptr)
    {
        if (nodeptr)
        {
            fstream dataStream;
            dataStream.open(COURSE_FILE_NAME, ios::app);
            dataStream << nodeptr->courseInfo.getCourseNumber() << ",";
            dataStream << nodeptr->courseInfo.getCourseTitle() << ",";
            dataStream << nodeptr->courseInfo.getCreditHour();
            dataStream << endl;
            dataStream.close();
            saveToFile(nodeptr->left);
            saveToFile(nodeptr->right);
        }
    }

    void remove(string coNum, CourseTreeNode *&nodeptr)
    {
        if (nodeptr == nullptr)
        {
            cout << "There is No Course by this Course Number - " << coNum << endl;
            return;
        }
        if (nodeptr->courseNumber == coNum)
            makeDeletion(nodeptr);
        else if (coNum > nodeptr->courseNumber)
            remove(coNum, nodeptr->right);
        else
            remove(coNum, nodeptr->left);
    }

    void makeDeletion(CourseTreeNode *&nodeptr)
    {
        CourseTreeNode *tempNodePtr = nullptr;
        if (nodeptr->right == nullptr)
        {
            tempNodePtr = nodeptr;
            nodeptr = nodeptr->left;
        }
        else if (nodeptr->left == nullptr)
        {
            tempNodePtr = nodeptr;
            nodeptr = nodeptr->right;
        }
        else
        {
            tempNodePtr = nodeptr->right;

            while (tempNodePtr->left)
                tempNodePtr = tempNodePtr->left;

            tempNodePtr->left = nodeptr->left;
            tempNodePtr = nodeptr;
            nodeptr = nodeptr->right;
        }

        delete tempNodePtr;
        cout << "Successfull Deleted!\n";
    }

    /**
     * This method destorys all the nodes in the binary tree 
     * when the destructor is called.
     */
    void destroySubTree(CourseTreeNode *nodeptr){
        if (nodeptr)
        {
            if (nodeptr->left)
                destroySubTree(nodeptr->left);
            if (nodeptr->right)
                destroySubTree(nodeptr->right);
            delete nodeptr;
        }
    }

public:
    CourseTree()
    {
        root = nullptr;
    }

    ~CourseTree(){
        destroySubTree(root);
        courseNumbers.erase();
    }

    /**
     * This function takes the course number and the course,
     * creates a new node and calls the insertNode function
     * by passing the root node and new node.
     */
    void insertCourse(string coNumber, Course coPtr)
    {
        if (courseNumbers.insert(coNumber).second)
        {
            CourseTreeNode *newNode = new CourseTreeNode(coNumber, coPtr);
            insertNode(root, newNode);
        }
        else
            cout << "A course with course number - " << coNumber << " already exists\n";
    }

    bool courseNumberExists(string coNumber)
    {
        return courseNumbers.find(coNumber) != courseNumbers.end();
    }

    /**
     * This method searches a course from the binary
     * search tree using its course number.
     */
    void searchCourse(string coNum)
    {
        CourseTreeNode *nodeptr = root;

        while (nodeptr)
        {
            if (nodeptr->courseNumber == coNum)
            {
                cout << "Course Number: " << nodeptr->courseInfo.getCourseNumber() << endl;
                cout << "Course Title: " << nodeptr->courseInfo.getCourseTitle() << endl;
                cout << "Credit Hour: " << nodeptr->courseInfo.getCreditHour() << endl;
                cout << "------------------------------------------\n";
                return;
            }
            else if (nodeptr->courseNumber > coNum)
                nodeptr = nodeptr->left;
            else
                nodeptr = nodeptr->right;
        }

        cout << "There is No Course By This number!\n\n";
    }

    void save()
    {
        fstream dataStream;
        dataStream.open(COURSE_FILE_NAME, ios::out);
        if (!dataStream.is_open())
        {
            cout << "Cannot Open file.\n";
            return;
        }
        dataStream.close();
        saveToFile(root);
    }

    void deleteCourse(string coNum)
    {
        remove(coNum, root);
    }

    void displayCourses()
    {
        if (root)
            displayInOrder(root);
        else
            cout << "There are no registered courses\n";
    }
};

/**
 * This method reads all the courses from 
 * the CourseTable.csv file
 */
CourseTree readFromCourseFile()
{
    CourseTree coTree;

    ifstream readStream;
    readStream.open(COURSE_FILE_NAME);
    if (!readStream.is_open())
    {
        cout << "Error Opening File\n";
        return coTree;
    }
    // else
    // {
    string line;
    while (readStream >> line)
    {
        string token;
        char delimiter = ',';
        vector<string> info;
        istringstream stream(line);

        while (getline(stream, token, delimiter))
            info.push_back(token);

        Course co;
        co.setCourseNumber(info[0]);
        co.setCourseTitle(info[1]);
        co.setCreditHour(info[2]);

        coTree.insertCourse(info[0], co);
    }
    // }
    readStream.close();
    return coTree;
}

int main()
{
    CourseTree coBinTree = readFromCourseFile();
    Course c1;
    c1.setCourseNumber("Co1");
    c1.setCourseTitle("Data Structure and Algorithm");
    c1.setCreditHour("7");
    Course c2;
    c2.setCourseNumber("Co2");
    c2.setCourseTitle("Numerial Analysis");
    c2.setCreditHour("5");
    Course c3;
    c3.setCourseNumber("Co3");
    c3.setCourseTitle("Networking");
    c3.setCreditHour("5");
    Course c4;
    c4.setCourseNumber("Co4");
    c4.setCourseTitle("Discrete Mathematics");
    c4.setCreditHour("7");
    Course c5;
    c5.setCourseNumber("Co5");
    c5.setCourseTitle("Advanced Database");
    c5.setCreditHour("6");

    coBinTree.insertCourse("Co3", c3);
    coBinTree.insertCourse("Co4", c4);
    coBinTree.insertCourse("Co5", c5);
    coBinTree.insertCourse("Co2", c2);
    coBinTree.insertCourse("Co1", c1);
    coBinTree.displayCourses();
    coBinTree.save();
}