#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

const string STUDENT_FILE_NAME = "StudentTable.csv";

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

    set<int> ids; // a set to hold all the unique ids of students.
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
            cout << "There is no student by student id = " << studId << endl;
            return;
        }
        if (nodeptr->studentId == studId){
            // ids.erase(studId);
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
    StudentTree()
    {
        root = nullptr;
    }

    ~StudentTree(){
        destroySubTree(root);
    }

    /**
     * This method accepts the student id and the
     * student info and passes it to the insertNode function
     */
    void insertStudent(int id, Student studInfo)
    {
        if(ids.insert(id).second){
            StudentTreeNode *newNode = new StudentTreeNode(id, studInfo);
            insertNode(root, newNode);
        }
        else
            cout << "A student with student id = " << id << " already exists!\n";
    }

    /**
     * This method checks if a student with a specific id exists.
     */
    bool studentIdExists(int id){
        return ids.find(id) != ids.end();
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

    void save()
    {
        fstream dataStream;
        dataStream.open(STUDENT_FILE_NAME, ios::out);

        dataStream.close();
        // cout << "Now Writing data to file\n";

        saveToFile(root);
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

// int main(){
//     StudentTree scTree = readFromStudentFile();
//     // StudentTree scTree;

//     // scTree.displayInOrder();

//     Student s1;
//     s1.setStudentId(1);
//     s1.setAge(20);
//     s1.setFirstName("Yodahe");
//     s1.setLastName("Gossa");
//     s1.setSex('M');

//     // scTree.displayInOrder();
//     // scTree.save();

//     Student s2;
//     s2.setStudentId(2);
//     s2.setAge(20);
//     s2.setFirstName("Yohannes");
//     s2.setLastName("Belay");
//     s2.setSex('M');
//     Student s3;
//     s3.setStudentId(3);
//     s3.setAge(20);
//     s3.setFirstName("Yoak");
//     s3.setLastName("Moges");
//     s3.setSex('M');
//     Student s4;
//     s4.setStudentId(4);
//     s4.setAge(20);
//     s4.setFirstName("qwerty");
//     s4.setLastName("zxcvbn");
//     s4.setSex('M');
//     scTree.insertStudent(1, s1);
//     scTree.insertStudent(2, s2);
//     scTree.insertStudent(3, s3);
//     scTree.insertStudent(4, s4);
//     scTree.displayInOrder();
//     scTree.save();
//     // scTree.insertStudent()
// }