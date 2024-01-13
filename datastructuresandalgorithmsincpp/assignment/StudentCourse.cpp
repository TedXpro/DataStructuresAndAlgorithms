#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

// Global variable to hold the file name for studentcoursetable.
const string STUDENT_COURSE_FILE_NAME = "StudentCourseTable.csv";

/**
 * This class defines the class for student course.
 * has constructors, destructors, setters, and getters.
 */
class StudentCourse
{
private:
    string studentId;
    string courseNumber;
    int semester;
    string year;
    int grade;
    string letterGrade;

public:
    StudentCourse(string studId, string coNum, int sem, string yr, int grade, string lGrade)
    {
        studentId = studId;
        courseNumber = coNum;
        semester = sem;
        year = yr;
        grade = grade;
        letterGrade = lGrade;
    }

    StudentCourse() {}

    StudentCourse(const StudentCourse &obj)
    {
        studentId = obj.studentId;
        courseNumber = obj.courseNumber;
        semester = obj.semester;
        grade = obj.grade;
        letterGrade = obj.letterGrade;
        year = obj.year;
    }

    ~StudentCourse() {}

    string getStudentId()
    {
        return studentId;
    }

    string getCourseNumber()
    {
        return courseNumber;
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

    void setStudentId(string studId)
    {
        studentId = studId;
    }

    void setCourseNumber(string coNum)
    {
        courseNumber = coNum;
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

/**
 * This class defines the binary search tree for the student course class.
 * has insert, save, search methods.
 */
class StudentCourseTree
{
private:
    /**
     * defines the structure for the student course tree.
     */
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

    set<string> uniqueStudentCourses;
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
    void displayStudentCourses(StudentCourseTreeNode *nodeptr, string studId, bool &status)
    {
        if (nodeptr)
        {
            if (nodeptr->studentCourse.getStudentId() == studId)
            {
                cout << "CourseNumber: " << nodeptr->studentCourse.getCourseNumber() << endl;
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

    /**
     * This method traverses the tree and saves all the
     * information to course file
     */
    void saveToFile(StudentCourseTreeNode *nodeptr)
    {
        if (nodeptr)
        {
            fstream dataStream;
            dataStream.open(STUDENT_COURSE_FILE_NAME, ios::app);
            dataStream << nodeptr->studentCourse.getStudentId() << ",";
            dataStream << nodeptr->studentCourse.getCourseNumber() << ",";
            dataStream << nodeptr->studentCourse.getGrade() << ",";
            dataStream << nodeptr->studentCourse.getLetterGrade() << ",";
            dataStream << nodeptr->studentCourse.getYear() << ",";
            dataStream << nodeptr->studentCourse.getSemester();
            dataStream << endl;
            dataStream.close();
            saveToFile(nodeptr->left);
            saveToFile(nodeptr->right);
        }
    }

    /**
     * This method destorys all the nodes in the binary tree
     * when the destructor is called.
     */
    void destroySubTree(StudentCourseTreeNode *nodeptr)
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

public:
    /**
     * Constructor to initialize and set the root to nullptr.
     */
    StudentCourseTree()
    {
        root = nullptr;
    }

    /**
     * Desturctor to delete the nodes and clear out the set.
     */
    ~StudentCourseTree()
    {
        destroySubTree(root);
        uniqueStudentCourses.clear();
    }

    /**
     * This function inserts a new student course node to the tree.
     */
    void insertStudentCourse(string str, StudentCourse studCo)
    {
        if (uniqueStudentCourses.insert(str).second)
        {
            StudentCourseTreeNode *newNode = new StudentCourseTreeNode(str, studCo);
            insertNode(root, newNode);
        }
        else
            cout << "Student " << studCo.getStudentId() << " is already registered to " << studCo.getCourseNumber() << endl;
    }

    /**
     * This method checks if a student is registered to a particular course
     * in the tree by checking the set using str.
     * @return true if student course exists.
     */
    bool StudentCourseExists(string str)
    {
        return uniqueStudentCourses.find(str) != uniqueStudentCourses.end();
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
    void displayCourseofStudent(string studId)
    {
        bool status = false;
        displayStudentCourses(root, studId, status);

        if (!status)
            cout << "There are No Courses taken by student Id: " << studId << endl;
    }

    /**
     * This method clears the StudentCourseTable file and calls
     * save to file method passing the root.
     */
    void save()
    {
        fstream dataStream;
        dataStream.open(STUDENT_COURSE_FILE_NAME, ios::out);
        dataStream.close();
        saveToFile(root);
    }

    void maintainGrade(string id, int newGrade, string newLetterGrade){
        StudentCourseTreeNode *nodeptr = root;

        while(nodeptr){
            if(nodeptr->id == id){
                nodeptr->studentCourse.setGrade(newGrade);
                nodeptr->studentCourse.setLetterGrade(newLetterGrade);
                break;
            }
            else if(nodeptr->id > id)
                nodeptr = nodeptr->left;
            else
                nodeptr = nodeptr->right;
        }
    }
};

/**
 * This method reads information from studentcourse file
 * and adds it to the tree.
 */
StudentCourseTree readFromStudentCourseFile()
{
    StudentCourseTree studCoBinTree;

    ifstream readStream;
    readStream.open(STUDENT_COURSE_FILE_NAME);

    if (!readStream.is_open())
    {
        cout << "Error Opening File\n";
        return studCoBinTree;
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
        obj.setStudentId(info[0]);
        obj.setCourseNumber(info[1]);
        obj.setGrade(stoi(info[2]));
        obj.setLetterGrade(info[3]);
        obj.setYear(info[4]);
        obj.setSemester(stoi(info[5]));
        string id = info[0] + info[1] + info[4] + info[5];
        studCoBinTree.insertStudentCourse(id, obj);
    }

    readStream.close();
    return studCoBinTree;
}

// int main(){
// StudentCourseTree scoTree = readFromStudentCourseFile();
// scoTree.display();
// cout << "displaying\n";
// scoTree.displayCourseofStudent(2);
// StudentCourse sc1;
// sc1.setCourseNumber("Co1");
// sc1.setGrade(85);
// sc1.setLetterGrade("A");
// sc1.setSemester(3);
// sc1.setYear("2024");
// sc1.setStudentId(6);
// scoTree.insertStudentCourse("6Co120243", sc1);
// cout << "trying to insert an already existing node.\n";
// StudentCourse sc2;
// sc2.setCourseNumber("Co1");
// sc2.setGrade(100);
// sc2.setLetterGrade("A+");
// sc2.setSemester(3);
// sc2.setYear("2024");
// sc2.setStudentId(1);
// scoTree.insertStudentCourse("1Co120243", sc2);
// scoTree.display();
// scoTree.save();
// }
