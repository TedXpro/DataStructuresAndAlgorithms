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

            cout << "Student Id: " << nodeptr->studentInfo.getStudentId() << endl;
            cout << "First Name: " << nodeptr->studentInfo.getFirstName() << endl;
            cout << "Last Name: " << nodeptr->studentInfo.getLastName() << endl;
            cout << "Age: " << nodeptr->studentInfo.getAge() << endl;
            cout << "Sex: " << nodeptr->studentInfo.getSex() << endl;
            cout << "--------------------------------------------\n";

            displayInOrder(nodeptr->right);
        }
    }

    // void deleteStudentObject(Student &obj)
    // {
    //     delete obj;
    // }

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
        cout << nodeptr->studentId << endl;
        StudentTreeNode *tempNodePtr = nullptr;
        // Student *studInfoTODelete = nodeptr->studentInfo;
        if (nodeptr->right == nullptr)
        {
            // cout << "Right\n";
            tempNodePtr = nodeptr;
            // cout << "tempNode:" << tempNodePtr->studentId << endl;
            nodeptr = nodeptr->left;
            // nodeptr = nullptr;
            // cout << "NodePtr: " << (nodeptr == nullptr) << endl;
            // cout << "Deleting Sudent\n";
            // delete tempNodePtr->studentInfo;
            cout << "Deleting Node\n";
            // delete tempNodePtr->studentInfo;
            // deleteStudentObject(tempNodePtr->studentInfo);
            delete tempNodePtr;
            // cout << "NodePtr: " << (nodeptr == nullptr) << endl;
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
            // StudentTreeNode *tNode = nodeptr;
            tempNodePtr = nodeptr;
            nodeptr = nodeptr->right;
            delete tempNodePtr;
            // delete tNode->studentInfo;
            // delete tNode;
        }
        // delete studInfoTODelete;
        cout << "Successfull Deleted!\n";
    }

    void saveToFile(StudentTreeNode *nodeptr)
    {
        if (nodeptr)
        {
            saveToFile(nodeptr->left);
            fstream dataStream;
            dataStream.open("StudentTable.txt", ios::app);
            dataStream << nodeptr->studentInfo.getStudentId() << ",";
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

    void save()
    {
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

    void saveToFile(CourseTreeNode *nodeptr)
    {
        if (nodeptr)
        {
            saveToFile(nodeptr->left);
            fstream dataStream;
            dataStream.open("CourseTable.txt", ios::app);
            dataStream << nodeptr->courseInfo.getCourseNumber() << ",";
            dataStream << nodeptr->courseInfo.getCourseTitle() << ",";
            dataStream << nodeptr->courseInfo.getCreditHour();
            dataStream << endl;
            dataStream.close();
            saveToFile(nodeptr->right);
        }
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
    void insertCourse(string courseNumber, Course coPtr)
    {
        CourseTreeNode *newNode = new CourseTreeNode(courseNumber, coPtr);

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
                cout << "Course Name: " << nodeptr->courseInfo.getCourseTitle() << endl;
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
        dataStream.open("CourseTable.txt", ios::out);

        dataStream.close();
        // cout << "Now Writing data to file\n";

        saveToFile(root);
    }
};

CourseTree *readFromCourseFile()
{
    CourseTree *coTree = new CourseTree();

    ifstream readStream;
    readStream.open("CourseTable.txt");
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

        while (std::getline(stream, token, delimiter))
            info.push_back(token);

        Course co;
        co.setCourseNumber(info[0]);
        co.setCourseTitle(info[1]);
        co.setCreditHour(stoi(info[2]));

        coTree->insertCourse(info[0], co);
    }

    readStream.close();
    return coTree;
}

StudentTree *readFromStudentFile()
{
    StudentTree *studBinTree = new StudentTree();

    ifstream readStream;

    readStream.open("StudentTable.txt");

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

        while (std::getline(stream, token, delimiter))
            info.push_back(token);

        Student obj;
        obj.setStudentId(stoi(info[0]));
        obj.setFirstName(info[1]);
        obj.setLastName(info[2]);
        obj.setAge(stoi(info[3]));
        char ch = info[4][0];
        obj.setSex(ch);
        studBinTree->insertStudent(obj.getStudentId(), obj);
    }

    readStream.close();
    return studBinTree;
}

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

    // void maintainGrade(int studentId, string coNumber, int semester, int year, int grade, string letterGrade){
    //     StudentCourse studCo(studentId, coNumber, semester, year, grade, letterGrade);

    // }
};

int menu()
{
    int choice;

    cout << "\t\tWelcome to Student Course Registry:\n";
    cout << "1. Register Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Search Student by Id\n";
    cout << "4. Register Student To Course\n";
    cout << "5. Sort Students by Name\n";
    cout << "6. Delete Student\n";
    cout << "7. Delete Course\n";
    cout << "8. Insert Courses\n";
    cout << "9. EXIT\n";
    cout << "------------------------------\n";
    cout << "Enter your Desired choice: ";
    cin >> choice;

    while (choice <= 0 || choice >= 10)
    {
        cout << "Enter your choice between 1 - 8: ";
        cin >> choice;
    }
    return choice;
}

int main()
{
    // StudentCourse sc1(1, "Co1", "Maths", 3, 2024, 100, "A+");
    StudentCourse sc1;
    sc1.setStudentId(1);
    sc1.setCourseNumber("Co1");
    sc1.setCourseName("Math");
    sc1.setGrade(100);
    sc1.setSemester(3);
    sc1.setYear("2024");
    sc1.setLetterGrade("A+");
    cout << "inserted\n";
    // StudentCourse sc5(5, "Co1", "Maths", 3, "2024", 60, "B+");
    StudentCourse sc5;
    sc5.setStudentId(5);
    sc5.setCourseNumber("Co1");
    sc5.setCourseName("Math");
    sc5.setGrade(70);
    sc5.setSemester(3);
    sc5.setYear("2024");
    sc5.setLetterGrade("B");

    StudentCourse sc2;
    sc2.setStudentId(2);
    sc2.setCourseNumber("Co1");
    sc2.setCourseName("Math");
    sc2.setGrade(60);
    sc2.setSemester(3);
    sc2.setYear("2024");
    sc2.setLetterGrade("C+");

    StudentCourse sc3;
    sc3.setStudentId(3);
    sc3.setCourseNumber("Co1");
    sc3.setCourseName("Math");
    sc3.setGrade(50);
    sc3.setSemester(3);
    sc3.setYear("2024");
    sc3.setLetterGrade("D");

    // StudentCourse sc3(3, "Co1", "Maths", 3, "2024", 70, "C+");
    // StudentCourse sc2(2, "Co1", "Maths", 3, "2024", 50, "D+");

    StudentCourseTree scTree;
    cout << "about to\n";
    scTree.insertStudentCourse("1Co132024", sc5);
    cout << "I did\n";
    scTree.insertStudentCourse("5Co132024", sc2);
    scTree.insertStudentCourse("3Co132024", sc3);
    scTree.insertStudentCourse("2Co132024", sc1);

    cout << "About to display\n";
    scTree.display();

    cout << "\n displayer\n";

    scTree.displayCourseofStudent(1);

    // int choice = menu();
    // int choice = 9;

    // if (choice == 9)
    // {
    //     cout << "Thank you for using!\n";
    //     return 0;
    // }

    // initially read from user.
    // StudentTree *studBinTree = readFromStudentFile();

    // do
    // {
    //     if (choice == 1)
    //     {
    //         Student s1;
    //         int num;
    //         cout << "Enter The Student ID: ";
    //         cin >> num;
    //         s1.setStudentId(num);
    //         string name;
    //         cout << "Enter First Name of Student: ";
    //         cin >> name;
    //         s1.setFirstName(name);
    //         cout << "Enter Last Name of Student: ";
    //         cin >> name;
    //         s1.setLastName(name);
    //         cout << "Enter Age of Student: ";
    //         cin >> num;
    //         s1.setAge(num);
    //         char ch;
    //         cout << "Enter Sex of Student: ";
    //         cin >> ch;
    //         s1.setSex(ch);

    //         studBinTree->insertStudent(s1.getStudentId(), s1);
    //         studBinTree->save();
    //         cout << "The Student has successfully been registered.\n";
    //     }
    //     // else if(choice == 2)
    //     // choice = menu();
    // } while (choice != 9);

    // CourseTree *coBinTree = readFromCourseFile();

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
    // coBinTree->save();

    // coBinTree->searchCourse("Co1");
    // coBinTree->searchCourse("Co3");
    // coBinTree->searchCourse("Co0");

    // cout << "Before \n";
    // studBinTree->displayInOrder();
    // cout << endl;
    // studBinTree->displayInOrder();

    // Student s1;
    // s1.setStudentId(6);
    // s1.setAge(20);
    // s1.setFirstName("qwerty");
    // s1.setLastName("zxcvbn");
    // s1.setSex('M');

    // studBinTree->insertStudent(6, s1);
    // studBinTree->save();
    // cout << "After Adding\n";
    // // studBinTree->displayInOrder();
    // studBinTree->deleteStudent(6);
    // cout << "After Deleting\n";
    // studBinTree->displayInOrder();

    // cout << "After\n";
    // studBinTree->save();
    // delete studBinTree;

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

    // studBinTree->displayInOrder();
    // studBinTree->save();
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

    // delete studBinTree;
}
