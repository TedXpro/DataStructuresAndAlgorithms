#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

// global variable to holds the file name of StudentTable.
const string STUDENT_FILE_NAME = "StudentTable.csv"; 

/**
 * This class holds information for students.
 * has consturctors, destructors, copy constructors, setters, and getters.
 */
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

    Student(const Student &obj)
    {
        studentId = obj.studentId;
        firstName = obj.firstName;
        lastName = obj.lastName;
        age = obj.age;
        sex = obj.sex;
    }

    ~Student() {}

    int getStudentId()
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

/**
 * This is a binary search tree using for student class.
 * has operations to insert, delete, search and save to file methods.
 */
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

        StudentTreeNode(int id, Student StudInfo)
        {
            studentId = id;
            studentInfo = StudInfo;
            left = nullptr;
            right = nullptr;
        }
    };

    set<int> uniqueIds; // a set to hold all the unique ids of students.
    StudentTreeNode *root; // create a variable for root node;

    /**
     * This function inserts the student info at the
     * exact node by traversing the tree.
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

            cout << "Student Id: " << nodeptr->studentInfo.getStudentId() << endl;
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
    void remove(int studId, StudentTreeNode *&nodeptr)
    {
        if (nodeptr == nullptr)
        {
            cout << "\n\nThere is no student by student id = " << studId << endl << endl;
            return;
        }
        if (nodeptr->studentId == studId){
            uniqueIds.erase(studId);
            makeDeletion(nodeptr);
        }
        else if (studId > nodeptr->studentId)
            remove(studId, nodeptr->right);
        else
            remove(studId, nodeptr->left);
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
     * This method saves the nodes in the tree to
     * the StudentTable.csv file
     */
    void saveToFile(StudentTreeNode *nodeptr)
    {
        if (nodeptr)
        {
            fstream dataStream;
            dataStream.open(STUDENT_FILE_NAME, ios::app);
            dataStream << nodeptr->studentInfo.getStudentId() << ",";
            dataStream << nodeptr->studentInfo.getFirstName() << ",";
            dataStream << nodeptr->studentInfo.getLastName() << ",";
            dataStream << nodeptr->studentInfo.getAge() << ",";
            dataStream << nodeptr->studentInfo.getSex();
            dataStream << endl;
            dataStream.close();
            saveToFile(nodeptr->left);
            saveToFile(nodeptr->right);
        }
    }

    /**
     * This function is called by the destructor to destroy 
     * all the nodes in the binary tree.
     */
    void destroySubTree(StudentTreeNode *nodeptr){
        if(nodeptr){
            if(nodeptr->left)
                destroySubTree(nodeptr->left);
            if(nodeptr->right)
                destroySubTree(nodeptr->right);
            delete nodeptr;
        }
    }

public:
    /**
     * Constructor to initialize the root node and set to nullptr.
     */
    StudentTree()
    {
        root = nullptr;
    }

    /**
     * Destructor called when program execution called.
     */
    ~StudentTree(){
        destroySubTree(root);
        uniqueIds.clear();
    }

    /**
     * This method accepts the student id and the
     * student info and passes it to the insertNode function
     */
    void insertStudent(int id, Student studInfo)
    {
        if(uniqueIds.insert(id).second){
            StudentTreeNode *newNode = new StudentTreeNode(id, studInfo);
            insertNode(root, newNode);
        }
        else
            cout << "A student with student id = " << id << " already exists!\n";
    }

    /**
     * This method checks if a student with a specific id exists.
     * @return true if student exists in the tree.
     */
    bool studentIdExists(int id){
        return uniqueIds.find(id) != uniqueIds.end();
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
            cout << "There are No Students registered at the moment!\n\n";
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

        cout << "There is No Student with student id = " << studentId << endl;
    }

    /**
     * This function accepts student id to be
     * deleted and passes it to remove.
     */
    void deleteStudent(int studId)
    {
        remove(studId, root);
    }

    /**
     * This method clears all the existing information 
     * from the student file and calls the saveToFile 
     * to save all the nodes to the student file.
     */
    void save()
    {
        fstream dataStream;
        dataStream.open(STUDENT_FILE_NAME, ios::out);
        dataStream.close();
        saveToFile(root);
    }
};

class StudentNameTree
{
private:
    struct StudentNameTreeNode
    {
        string name;
        Student studentInfo;
        StudentNameTreeNode *left;
        StudentNameTreeNode *right;

        StudentNameTreeNode(string n, Student stud){
            name = n;
            studentInfo = stud;
            left = nullptr;
            right = nullptr;
        }
    };

    StudentNameTreeNode *root;

    /**
     * This function is called by the destructor to destroy
     * all the nodes in the binary tree.
     */
    void destroySubTree(StudentNameTreeNode *nodeptr)
    {
        if (nodeptr)
        {
            if (nodeptr->left)
                destroySubTree(nodeptr->left);
            if (nodeptr->right)
                destroySubTree(nodeptr->right);
            delete nodeptr;
        }
    }

    /**
     * This function inserts the student info at the
     * exact node by traversing the tree.
     */
    void insertNode(StudentNameTreeNode *&nodeptr, StudentNameTreeNode *&newNode)
    {
        if (nodeptr == nullptr)
            nodeptr = newNode;
        else if (nodeptr->name > newNode->name)
            insertNode(nodeptr->left, newNode);
        else
            insertNode(nodeptr->right, newNode);
    }

    /**
     * This function displays all the students in the
     * binary tree in InOrder Traversal
     */
    void displayInOrder(StudentNameTreeNode *nodeptr)
    {
        if (nodeptr)
        {
            displayInOrder(nodeptr->left);

            cout << "First Name: " << nodeptr->studentInfo.getFirstName() << endl;
            cout << "Last Name: " << nodeptr->studentInfo.getLastName() << endl;
            cout << "Age: " << nodeptr->studentInfo.getAge() << endl;
            cout << "Sex: " << nodeptr->studentInfo.getSex() << endl;
            cout << "Student Id: " << nodeptr->studentInfo.getStudentId() << endl;
            cout << "--------------------------------------------\n";

            displayInOrder(nodeptr->right);
        }
    }

public:
    /**
     * Constructor to initialize the root node and set to nullptr.
     */
    StudentNameTree(){
        root = nullptr;
    }

    /**
     * Destructor called when program execution called.
     */
    ~StudentNameTree(){
        destroySubTree(root);
    }

    /**
     * This method accepts the student id and the
     * student info and passes it to the insertNode function
     */
    void insertStudent(string name, Student stud){
        StudentNameTreeNode *newNode = new StudentNameTreeNode(name, stud);
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
            cout << "There are No Students registered at the moment!\n\n";
        }
    }
};

/**
 * This method reads all the students from StudentTable.csv
 */
StudentTree readFromStudentFile()
{
    StudentTree studBinTree;

    ifstream readStream;

    readStream.open(STUDENT_FILE_NAME);

    if (!readStream.is_open())
    {
        cout << "Error Opening File\n";
        return studBinTree;
    }

    string line;
    while (readStream >> line)
    {
        string token;
        char delimiter = ',';
        vector<string> info;
        istringstream stream(line);

        while (getline(stream, token, delimiter))
            info.push_back(token);

        Student obj;
        obj.setStudentId(stoi(info[0]));
        obj.setFirstName(info[1]);
        obj.setLastName(info[2]);
        obj.setAge(stoi(info[3]));
        obj.setSex(info[4][0]);
        studBinTree.insertStudent(obj.getStudentId(), obj);
    }

    readStream.close();
    return studBinTree;
}

/**
 * This method reads all the students from StudentTable.csv
 */
StudentNameTree readFromStudentFileInName()
{
    StudentNameTree studNTree;

    ifstream readStream;

    readStream.open(STUDENT_FILE_NAME);

    if (!readStream.is_open())
    {
        cout << "Error Opening File\n";
        return studNTree;
    }

    string line;
    while (readStream >> line)
    {
        string token;
        char delimiter = ',';
        vector<string> info;
        istringstream stream(line);

        while (getline(stream, token, delimiter))
            info.push_back(token);

        Student obj;
        obj.setStudentId(stoi(info[0]));
        obj.setFirstName(info[1]);
        obj.setLastName(info[2]);
        obj.setAge(stoi(info[3]));
        obj.setSex(info[4][0]);

        string name = info[1] + info[2] + info[0];
        studNTree.insertStudent(name, obj);
    }

    readStream.close();
    return studNTree;
}

// int main(){
//     StudentTree scTree = readFromStudentFile();
//     scTree.deleteStudent(4);
//     scTree.save();
//     Student s1;
//     s1.setStudentId(4);
//     s1.setAge(20);
//     s1.setFirstName("Kebede");
//     s1.setLastName("Balcha");
//     s1.setSex('M');
//     scTree.insertStudent(4, s1);
//     scTree.save();
    // scTree.save();
    // StudentTree scTree;
    // scTree.displayInOrder();
    // scTree.displayInOrder();
    // scTree.save();
// }