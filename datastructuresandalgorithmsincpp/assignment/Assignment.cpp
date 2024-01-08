#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>

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
    Student(int id, string fName, string lName, int a, char s)
    {
        studentId = id;
        firstName = fName;
        lastName = lName;
        age = a;
        sex = s;
    }

    Student()
    {
    }

    Student(const Student &obj){
        studentId = obj.studentId;
        firstName = obj.firstName;
        lastName = obj.lastName;
        age = obj.age;
        sex = obj.sex;
    }

    ~Student(){}

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

    Course() {}

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

    void setCourseNumber(string coNumber)
    {
        courseNumber = coNumber;
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
    struct StudentTreeNode
    {
        int studentId;
        Student studentInfo;
        StudentTreeNode *left;
        StudentTreeNode *right;

        StudentTreeNode(int id, const Student &StudInfo)
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

            cout << "Student Id: " << nodeptr->studentInfo.getId() << endl;
            cout << "First Name: " << nodeptr->studentInfo.getFirstName() << endl;
            cout << "Last Name: " << nodeptr->studentInfo.getLastName() << endl;
            cout << "Age: " << nodeptr->studentInfo.getAge() << endl;
            cout << "Sex: " << nodeptr->studentInfo.getSex() << endl;
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
        if(nodeptr == nullptr)  
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
        cout << nodeptr->studentId << endl;
        StudentTreeNode *tempNodePtr = nullptr;
        // Student *studInfoTODelete = nodeptr->studentInfo;
        if (nodeptr->right == nullptr)
        {
            cout << "Right\n";
            tempNodePtr = nodeptr;
            cout << "tempNode:" << tempNodePtr->studentId << endl;
            // nodeptr = nodeptr->left;
            nodeptr = nullptr;
            cout << "NodePtr: " << (nodeptr == nullptr) << endl;
            // cout << "Deleting Sudent\n";
            // delete tempNodePtr->studentInfo;
            cout << "Deleting Node\n";
            delete tempNodePtr;
            cout << "NodePtr: " << (nodeptr == nullptr) << endl;
        }
        else if (nodeptr->left == nullptr)
        {
            tempNodePtr = nodeptr;
            nodeptr = nodeptr->right;
            // delete tempNodePtr->studentInfo;
            delete tempNodePtr;
        }
        else
        {
            tempNodePtr = nodeptr->right;

            while (tempNodePtr->left)
                tempNodePtr = tempNodePtr->left;

            tempNodePtr->left = nodeptr->left;
            StudentTreeNode *tNode = nodeptr;
            // tempNodePtr = nodeptr;
            nodeptr = nodeptr->right;
            // delete tNode->studentInfo;
            delete tNode;
        }
        // delete studInfoTODelete;
        cout << "Successfull Deleted!\n";
    }

    void saveToFile(StudentTreeNode *nodeptr)
    {
        if(nodeptr){
            saveToFile(nodeptr->left);
            fstream dataStream;
            dataStream.open("StudentTable.txt", ios::app);
            dataStream << nodeptr->studentInfo.getId() << ",";
            dataStream << nodeptr->studentInfo.getFirstName() << ",";
            dataStream << nodeptr->studentInfo.getLastName() << ",";
            dataStream << nodeptr->studentInfo.getAge() << ",";
            dataStream << nodeptr->studentInfo.getSex();
            dataStream << endl;
            dataStream.close();
            saveToFile(nodeptr->right);
        }
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
    void insertStudent(int id, Student studInfo)
    {
        StudentTreeNode *newNode = new StudentTreeNode(id, studInfo);

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
                cout << "First Name: " << nodeptr->studentInfo.getFirstName() << endl;
                cout << "Last Name: " << nodeptr->studentInfo.getLastName() << endl;
                cout << "Age: " << nodeptr->studentInfo.getAge() << endl;
                cout << "Sex: " << nodeptr->studentInfo.getSex() << endl;
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
    
    void save(){
        fstream dataStream;
        dataStream.open("StudentTable.txt", ios::out);

        dataStream.close();
        // cout << "Now Writing data to file\n";

        saveToFile(root);
    }
};

class CourseTree
{
private:
    struct CourseTreeNode
    {
        string courseNumber;
        Course *coursePointer;
        CourseTreeNode *left;
        CourseTreeNode *right;

        CourseTreeNode(string coNum, Course *coPtr)
        {
            courseNumber = coNum;
            coursePointer = coPtr;
            left = nullptr;
            right = nullptr;
        }
    };

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
    void insertCourse(string courseNumber, Course &coPtr)
    {
        CourseTreeNode *newNode = new CourseTreeNode(courseNumber, &coPtr);

        insertNode(root, newNode);
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
                cout << "Course Number: " << nodeptr->courseNumber << endl;
                cout << "Course Name: " << nodeptr->coursePointer->getCourseTitle() << endl;
                cout << "Credit Hour: " << nodeptr->coursePointer->getCreditHour() << endl;
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
};

StudentTree * readFromStudentFile(){
    StudentTree *studBinTree = new StudentTree();

    ifstream readStream;

    readStream.open("StudentTable.txt");

    if(!readStream.is_open()){
        cout << "Error Opening File\n";
        return nullptr;
    }

    string line;
    while(readStream >> line){
        string token;
        char delimiter = ',';
        vector<string> info;
        istringstream stream(line);
        
        int i = 0;
        while (std::getline(stream, token, delimiter))
            info.push_back(token);

        Student obj;
        obj.setStudentId(stoi(info[0]));
        obj.setFirstName(info[1]);
        obj.setLastName(info[2]);
        obj.setAge(stoi(info[3]));
        char ch = info[4][0];
        obj.setSex(ch);
        studBinTree->insertStudent(obj.getId(), obj);
    }

    readStream.close();
    return studBinTree;
}

int main()
{

    // CourseTree *coBinTree = new CourseTree();

    // Course c1;
    // c1.setCourseNumber("Co1");
    // c1.setCourseTitle("Maths");
    // c1.setCreditHour(20);

    // Course c2;
    // c2.setCourseNumber("Co2");
    // c2.setCourseTitle("Physics");
    // c2.setCreditHour(20);
    // Course c3;
    // c3.setCourseNumber("Co3");
    // c3.setCourseTitle("asdad");
    // c3.setCreditHour(20);
    // Course c4;
    // c4.setCourseNumber("Co4");
    // c4.setCourseTitle("ojonl");
    // c4.setCreditHour(20);
    // Course c5;
    // c5.setCourseNumber("Co5");
    // c5.setCourseTitle("uihyb");
    // c5.setCreditHour(20);

    // coBinTree->insertCourse("Co3", c3);
    // coBinTree->insertCourse("Co4", c4);
    // coBinTree->insertCourse("Co5", c5);
    // coBinTree->insertCourse("Co2", c2);
    // coBinTree->insertCourse("Co1", c1);

    // coBinTree->searchCourse("Co1");
    // coBinTree->searchCourse("Co3");
    // coBinTree->searchCourse("Co0");

    StudentTree *studBinTree = readFromStudentFile();
    cout << "Before \n";
    studBinTree->displayInOrder();
    cout << endl;
    studBinTree->displayInOrder();

    Student s1;
    s1.setStudentId(6);
    s1.setAge(20);
    s1.setFirstName("qwerty");
    s1.setLastName("zxcvbn");
    s1.setSex('M');

    studBinTree->insertStudent(6, s1);
    studBinTree->save();

    // cout << "After\n";
    // studBinTree->save();
    delete studBinTree;

    // Student s1;
    // s1.setStudentId(1);
    // s1.setAge(20);
    // s1.setFirstName("Yohannes");
    // s1.setLastName("Woldeyes");
    // s1.setSex('M');

    // Student s2;
    // s2.setStudentId(2);
    // s2.setAge(20);
    // s2.setFirstName("Menilik");
    // s2.setLastName("Woldeyes");
    // s2.setSex('M');
    // Student s3;
    // s3.setStudentId(3);
    // s3.setAge(20);
    // s3.setFirstName("Makeda");
    // s3.setLastName("Woldeyes");
    // s3.setSex('F');
    // Student s4;
    // s4.setStudentId(4);
    // s4.setAge(20);
    // s4.setFirstName("Dagmawi");
    // s4.setLastName("Woldeyes");
    // s4.setSex('M');
    // Student s5;
    // s5.setStudentId(5);
    // s5.setAge(20);
    // s5.setFirstName("adsafasf");
    // s5.setLastName("asfasfas");
    // s5.setSex('F');

    // cout << "Inserting Students.\n";
    // studBinTree->insertStudent(3, s3);
    // studBinTree->insertStudent(1, s1);
    // studBinTree->insertStudent(2, s2);
    // studBinTree->insertStudent(4, s4);
    // studBinTree->insertStudent(5, s5);

    studBinTree->displayInOrder();
    studBinTree->save();
    // delete studBinTree;

    // cout << "Searching for a student.\n";
    // studBinTree->searchStudent(3);
    // studBinTree->searchStudent(2);
    // studBinTree->searchStudent(9);

    // cout << "displaying inorder\n";
    // studBinTree->displayInOrder();

    // studBinTree->displayInOrder();
    // cout << "Deleting 5\n";
    // studBinTree->deleteStudent(5);
    // studBinTree->displayInOrder();
    // cout << "Deleting 1\n";
    // studBinTree->deleteStudent(1);
    // studBinTree->displayInOrder();

    delete studBinTree;
}
