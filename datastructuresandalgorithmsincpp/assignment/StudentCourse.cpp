#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class StudentCourse
{
private:
    int studentId;
    string courseNumber;
    string courseName;
    int semester;
    string year;
    int grade;
    string letterGrade;

public:
    StudentCourse(int studId, string coNum, string coName, int sem, string yr, int grade, string lGrade)
    {
        studentId = studId;
        courseNumber = coNum;
        courseName = coName;
        semester = sem;
        year = yr;
        grade = grade;
        letterGrade = lGrade;
    }

    StudentCourse()
    {
    }

    int getStudentId()
    {
        return studentId;
    }

    string getCourseNumber()
    {
        return courseNumber;
    }

    string getCourseName()
    {
        return courseName;
    }

    int getSemester()
    {
        return semester;
    }

    string getYear()
    {
        return year;
    }

    int getGrade()
    {
        return grade;
    }

    string getLetterGrade()
    {
        return letterGrade;
    }

    void setStudentId(int studId)
    {
        studentId = studId;
    }

    void setCourseNumber(string coNum)
    {
        courseNumber = coNum;
    }

    void setCourseName(string coName)
    {
        courseName = coName;
    }

    void setSemester(int sem)
    {
        semester = sem;
    }

    void setYear(string yr)
    {
        year = yr;
    }

    void setGrade(int gd)
    {
        grade = gd;
    }

    void setLetterGrade(string lGrade)
    {
        letterGrade = lGrade;
    }
};

class StudentCourseTree
{
private:
    struct StudentCourseTreeNode
    {
        string id;
        StudentCourse studentCourse;
        StudentCourseTreeNode *left;
        StudentCourseTreeNode *right;

        StudentCourseTreeNode(string i, StudentCourse studCo)
        {
            id = i;
            studentCourse = studCo;
            left = nullptr;
            right = nullptr;
        }
    };

    StudentCourseTreeNode *root;

    /**
     * This function takes the root node aand new node and
     * inserts the node at the right place by traversing the tree
     */
    void insertNode(StudentCourseTreeNode *&nodeptr, StudentCourseTreeNode *&newNode)
    {
        if (nodeptr == nullptr)
            nodeptr = newNode;
        else if (nodeptr->id > newNode->id)
            insertNode(nodeptr->left, newNode);
        else
            insertNode(nodeptr->right, newNode);
    }

    /**
     * This method displays the the nodes in inorder traversal
     */
    void displayNodes(StudentCourseTreeNode *nodeptr)
    {
        if (nodeptr)
        {
            displayNodes(nodeptr->left);

            cout << "Student Id: " << nodeptr->studentCourse.getStudentId() << endl;
            cout << "Course Number: " << nodeptr->studentCourse.getCourseNumber() << endl;
            cout << "Course Name: " << nodeptr->studentCourse.getCourseName() << endl;
            cout << "Grade: " << nodeptr->studentCourse.getGrade() << endl;
            cout << "Letter Grade: " << nodeptr->studentCourse.getLetterGrade() << endl;
            cout << "Year: " << nodeptr->studentCourse.getYear() << endl;
            cout << "Semester: " << nodeptr->studentCourse.getSemester() << endl;
            cout << "----------------------------------------\n";

            displayNodes(nodeptr->right);
        }
    }

    /**
     * This method accepts the root node, student id and
     * status and displays info of all the courses a student takes
     */
    void displayStudentCourses(StudentCourseTreeNode *nodeptr, int studId, bool &status)
    {
        if (nodeptr)
        {
            if (nodeptr->studentCourse.getStudentId() == studId)
            {
                cout << "CourseNumber: " << nodeptr->studentCourse.getCourseNumber() << endl;
                cout << "CourseName: " << nodeptr->studentCourse.getCourseName() << endl;
                cout << "Grade: " << nodeptr->studentCourse.getGrade() << endl;
                cout << "Letter Grade: " << nodeptr->studentCourse.getLetterGrade() << endl;
                cout << "Year: " << nodeptr->studentCourse.getYear() << endl;
                cout << "Semester: " << nodeptr->studentCourse.getSemester() << endl;
                cout << "------------------------------------\n";
                status = true;
            }
            displayStudentCourses(nodeptr->left, studId, status);
            displayStudentCourses(nodeptr->right, studId, status);
        }
    }

    void saveToFile(StudentCourseTreeNode *nodeptr)
    {
        if (nodeptr)
        {
            saveToFile(nodeptr->left);
            fstream dataStream;
            dataStream.open("StudentCourseTable.txt", ios::app);
            dataStream << nodeptr->studentCourse.getStudentId() << ",";
            dataStream << nodeptr->studentCourse.getCourseNumber() << ",";
            dataStream << nodeptr->studentCourse.getCourseName() << ",";
            dataStream << nodeptr->studentCourse.getGrade() << ",";
            dataStream << nodeptr->studentCourse.getLetterGrade() << ",";
            dataStream << nodeptr->studentCourse.getYear() << ",";
            dataStream << nodeptr->studentCourse.getSemester();
            dataStream << endl;
            dataStream.close();
            saveToFile(nodeptr->right);
        }
    }

public:
    StudentCourseTree()
    {
        root = nullptr;
    }
    /**
     * This function inserts a new student course node to the tree.
     */
    void insertStudentCourse(string i, StudentCourse studCo)
    {
        StudentCourseTreeNode *newNode = new StudentCourseTreeNode(i, studCo);
        insertNode(root, newNode);
    }

    /**
     * This method passes the root node to the displayNodes function.
     */
    void display()
    {
        displayNodes(root);
    }

    /**
     * This function takes the student id of a student and
     * passes it to displayStudentCourses function
     */
    void displayCourseofStudent(int studId)
    {
        bool status = false;
        displayStudentCourses(root, studId, status);

        if (!status)
            cout << "There are No Courses taken by student Id: " << studId << endl;
    }

    void save()
    {
        fstream dataStream;
        dataStream.open("StudentCourseTable.txt", ios::out);
        if (!dataStream.is_open())
        {
            cout << "Cannot Open file.\n";
            return;
        }
        dataStream.close();
        saveToFile(root);
    }

    // void maintainGrade(int studentId, string coNumber, int semester, int year, int grade, string letterGrade){
    //     StudentCourse studCo(studentId, coNumber, semester, year, grade, letterGrade);

    // }
};

StudentCourseTree *readFromStudentCourseFile()
{
    StudentCourseTree *studCoBinTree = new StudentCourseTree();

    ifstream readStream;
    readStream.open("StudentCourseTable.txt");

    if (!readStream.is_open())
    {
        cout << "Error Opening File\n";
        return nullptr;
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

        StudentCourse obj;
        obj.setStudentId(stoi(info[0]));
        obj.setCourseNumber(info[1]);
        obj.setCourseName(info[2]);
        obj.setGrade(stoi(info[3]));
        obj.setLetterGrade(info[4]);
        obj.setYear(info[5]);
        obj.setSemester(stoi(info[6]));
        string id = info[0] + info[1] + info[5] + info[6];
        studCoBinTree->insertStudentCourse(id, obj);
    }

    readStream.close();
    return studCoBinTree;
}
