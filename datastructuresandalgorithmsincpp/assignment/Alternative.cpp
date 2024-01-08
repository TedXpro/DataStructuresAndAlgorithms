#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class Course
{
public:
    int courseNo;
    string courseTitle;
    int crh;

    Course(int no, const string &title, int hours) : courseNo(no), courseTitle(title), crh(hours) {}
};

class Student
{
public:
    int id;
    string firstName;
    string fatherName;
    int age;
    char sex;

    map<int, int> grades; // Map to store courses and grades

    Student(int studentId, const string &fName, const string &father, int studentAge, char studentSex)
        : id(studentId), firstName(fName), fatherName(father), age(studentAge), sex(studentSex) {}
};

class TreeNode
{
public:
    int key;
    Student student;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int k, const Student &s) : key(k), student(s), left(nullptr), right(nullptr) {}
};

class StudentRecordManager
{
private:
    TreeNode *root;

public:
    StudentRecordManager() : root(nullptr) {}

    TreeNode *insert(TreeNode *root, int key, const Student &student)
    {
        if (root == nullptr)
        {
            return new TreeNode(key, student);
        }

        if (key < root->key)
        {
            root->left = insert(root->left, key, student);
        }
        else if (key > root->key)
        {
            root->right = insert(root->right, key, student);
        }

        return root;
    }

    void insertStudent(int key, const Student &student)
    {
        root = insert(root, key, student);
    }

    void displayInOrder(TreeNode *root)
    {
        if (root != nullptr)
        {
            displayInOrder(root->left);
            cout << "Student ID: " << root->key << endl;
            cout << "First Name: " << root->student.firstName << endl;
            cout << "Last Name:  " << root->student.fatherName << endl;
            cout << "Age: " << root->student.age << endl;
            cout << "Sex: " << root->student.sex << endl;
            cout << "-----------------------------------\n";
            displayInOrder(root->right);
        }
    }

    void displayAllStudents()
    {
        displayInOrder(root);
    }

    void writeToFile(const string &fileName)
    {
        ofstream outFile(fileName, ios::out);

        if (!outFile)
        {
            cerr << "Error: Unable to open file for writing." << endl;
            return;
        }

        writeToFileHelper(outFile, root);

        outFile.close();
        cout << "Student records have been written to the file successfully." << endl;
    }

    void writeToFileHelper(ofstream &outFile, TreeNode *root)
    {
        if (root != nullptr)
        {
            outFile << root->key << " " << root->student.id << " " << root->student.firstName << " "
                    << root->student.fatherName << " " << root->student.age << " " << root->student.sex << endl;

            writeToFileHelper(outFile, root->left);
            writeToFileHelper(outFile, root->right);
        }
    }

    void readFromFile(const string &fileName)
    {
        ifstream inFile(fileName, ios::in);

        if (!inFile)
        {
            cerr << "Error: Unable to open file for reading." << endl;
            return;
        }

        int key, studentId, age;
        string fName, fatherName;
        char sex;

        while (inFile >> key >> studentId >> fName >> fatherName >> age >> sex)
        {
            Student student(studentId, fName, fatherName, age, sex);
            insertStudent(key, student);
        }

        inFile.close();
        cout << "Student records have been read from the file successfully." << endl;
    }
};

int main()
{
    // StudentRecordManager recordManager;

    // // Sample data
    // Student student1(1, "John", "Doe", 20, 'M');
    // Student student2(2, "Jane", "Smith", 22, 'F');

    
    // recordManager.insertStudent(student1.id, student1);
    // recordManager.insertStudent(student2.id, student2);

    // recordManager.displayAllStudents();

    // Write student records to a file
    // recordManager.writeToFile("student_records.txt");

    // Read student records from the file
    StudentRecordManager newRecordManager;
    newRecordManager.readFromFile("student_records.txt");

    Student student1(1, "John", "Doasafae", 20, 'M');
    newRecordManager.insertStudent(student1.id, student1);
    newRecordManager.writeToFile("student_records.txt");

    // Display all students from the newly loaded records
    newRecordManager.displayAllStudents();

    return 0;
}
