#include <iostream>
#include "Student.cpp"
#include "Course.cpp"
#include "StudentCourse.cpp"

using namespace std;

Student registerStudent(string);
string getLetterGrade(int);
StudentCourse registerStudentToCourse(string, string, string &);
int menu();

int main()
{
    int choice = menu();
    if (choice == 10)
    {
        cout << endl;
        cout << "\t\t****************************\n";
        cout << "\t\t**->Thank you for using!<-**\n";
        cout << "\t\t****************************\n";
        return 0;
    }

    StudentTree studTree = readFromStudentFile();
    CourseTree coTree = readFromCourseFile();
    StudentCourseTree studCoTree = readFromStudentCourseFile();

    do
    {
        string studId;
        string coNumber;
        if (choice == 1)
        {
            cout << "Enter Student id: ";
            cin >> studId;
            while (studTree.studentIdExists(studId))
            {
                cout << "A student with id: " << studId << " already exists!\n";
                cout << "Please enter another id: ";
                cin >> studId;
            }
            Student stud = registerStudent(studId);
            studTree.insertStudent(stud.getStudentId(), stud);
            studTree.save();
            cout << "You have successfully register a student.\n";
        }
        else if (choice == 2)
        {
            cout << "List of all of the students\n";
            studTree.displayInOrder();
            cout << "===========================================\n";
        }
        else if (choice == 3)
        {
            cout << "Enter student id to search: ";
            cin >> studId;
            studTree.searchStudent(studId);
        }
        else if (choice == 4)
        {
            cout << "Enter student id: ";
            cin >> studId;
            while (!studTree.studentIdExists(studId))
            {
                cout << "There is no student with id: " << studId << " registered!\n";
                cout << "Please enter another id: ";
                cin >> studId;
            }

            cout << "Enter Course Number: ";
            cin >> coNumber;
            while (!coTree.courseNumberExists(coNumber))
            {
                cout << "There is no course with course number: " << coNumber << " registered!\n";
                cout << "Please enter another course number: ";
                cin >> coNumber;
            }

            string id;
            StudentCourse studCo = registerStudentToCourse(studId, coNumber, id);
            studCoTree.insertStudentCourse(id, studCo);
            studCoTree.save();
            cout << "\nRegistered student to course successfully!\n";
        }
        else if (choice == 5)
        {
            StudentNameTree studNameTree = readFromStudentFileInName();
            studNameTree.displayInOrder();
            cout << endl;
        }
        else if (choice == 6)
        {
            cout << "Enter Student id to delete student: ";
            cin >> studId;
            studTree.deleteStudent(studId);
            studTree.save();
        }
        else if (choice == 7)
        {

            cout << "Enter Course Number to register: ";
            cin >> coNumber;

            while (coTree.courseNumberExists(coNumber))
            {
                cout << "A Course with course number " << coNumber << " already Exists!\n";
                cout << "Please enter another course number: ";
                cin >> coNumber;
            }
            Course co;
            co.setCourseNumber(coNumber);

            string CoTitle;
            cout << "Enter course Title: ";
            cin >> CoTitle;
            co.setCourseTitle(CoTitle);

            string creditHour;
            cout << "Enter credit Hour: ";
            cin >> creditHour;
            co.setCreditHour(creditHour);

            coTree.insertCourse(coNumber, co);
            coTree.save();
        }
        else if (choice == 8)
        {
            cout << "Enter CourseNumber to be deleted: ";
            cin >> coNumber;
            coTree.deleteCourse(coNumber);
            coTree.save();
        }
        else if (choice == 9)
        {
            cout << "Enter Student Id: ";
            cin >> studId;
            while (!studTree.studentIdExists(studId))
            {
                cout << "A student with id: " << studId << " doesn't exists!\n";
                cout << "Please enter another id: ";
                cin >> studId;
            }

            cout << "Enter Course Number: ";
            cin >> coNumber;
            while (!coTree.courseNumberExists(coNumber))
            {
                cout << "A Course with course number " << coNumber << " doesn't Exists!\n";
                cout << "Please enter another course number: ";
                cin >> coNumber;
            }

            string year;
            cout << "Enter Year: ";
            cin >> year;
            while (year.length() != 4)
            {
                cout << "Enter a valid year: ";
                cin >> year;
            }

            int semester;
            cout << "Enter Semester: ";
            cin >> semester;
            while (semester < 1 || semester > 2)
            {
                cout << "Enter a valid Semester: ";
                cin >> semester;
            }

            string id = studId + coNumber + year + to_string(semester);
            if (!studCoTree.StudentCourseExists(id))
            {
                cout << "There is no student with student id " << studId << " registered to course number " << coNumber
                     << " for year " << year << " semester " << semester << endl;
                cout << "please try again!\n";
            }
            else
            {
                int grade;
                cout << "Enter New Grade: ";
                cin >> grade;
                while (grade > 100 || grade <= 0)
                {
                    cout << "Please enter a valid grade (0 - 100): ";
                    cin >> grade;
                }
                string letGrade = getLetterGrade(grade);
                studCoTree.maintainGrade(id, grade, letGrade);
                studCoTree.save();
                cout << "\nSuccessfully updated grade!\n\n";
            }
        }

        choice = menu();
    } while (choice != 10);

    cout << endl;
    cout << "\t\t****************************\n";
    cout << "\t\t**->Thank you for using!<-**\n";
    cout << "\t\t****************************\n";
    return 0;
}

/**
 * This function displays the menu contents and returns a choice.
 */
int menu()
{
    int choice;

    cout << "\t\tWelcome to Student Course Registry:\n";
    cout << "1. Register Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Search Student by Id\n";
    cout << "4. Register Student To Course\n";
    cout << "5. Display Students sorted by Name\n";
    cout << "6. Delete Student\n";
    cout << "7. Insert Courses\n";
    cout << "8. Delete Course\n";
    cout << "9. Maintain Student Grade\n";
    cout << "10. EXIT\n";
    cout << "------------------------------\n";
    cout << "Enter your Desired choice: ";
    cin >> choice;

    while (choice <= 0 || choice >= 11)
    {
        cout << "Enter your choice between 1 - 10: ";
        cin >> choice;
    }
    return choice;
}

/**
 * This function is called when a user wants to register a student.
 * accepts student information and returns the student information.
 */
Student registerStudent(string studId)
{
    Student stud;

    stud.setStudentId(studId);

    string fName, lName;
    cout << "Enter first name: ";
    cin >> fName;
    cout << "Enter last name: ";
    cin >> lName;
    stud.setFirstName(fName);
    stud.setLastName(lName);

    int age;
    cout << "Enter age of student: ";
    cin >> age;
    stud.setAge(age);
    char ch;
    cout << "Enter Sex of Student (M/f): ";
    cin >> ch;
    while (ch != 'M' && ch != 'm' && ch != 'f' && ch != 'F')
    {
        cout << "Please enter M/f: ";
        cin >> ch;
    }
    ch = toupper(ch);
    stud.setSex(ch);

    return stud;
}

/**
 * This method accepts infos needed for studentcourse class
 * and returns it.
 */
StudentCourse registerStudentToCourse(string studId, string coNumber, string &id)
{
    StudentCourse studCo;

    studCo.setStudentId(studId);
    studCo.setCourseNumber(coNumber);

    string year;
    cout << "Enter Year: ";
    cin >> year;
    while (year.length() != 4)
    {
        cout << "Enter a valid year: ";
        cin >> year;
    }
    studCo.setYear(year);

    int semester;
    cout << "Enter semester: ";
    cin >> semester;
    while (semester < 1 || semester > 2)
    {
        cout << "Enter a valid Semester: ";
        cin >> semester;
    }
    studCo.setSemester(semester);

    int grade;
    cout << "Enter grade: ";
    cin >> grade;
    while (grade > 100 || grade <= 0)
    {
        cout << "Please enter a valid grade (0 - 100): ";
        cin >> grade;
    }
    studCo.setGrade(grade);
    studCo.setLetterGrade(getLetterGrade(grade));
    id = studId + coNumber + year + to_string(semester);

    return studCo;
}

/**
 * This method accepts integer grade and returns
 * corresponding letter grade.
 */
string getLetterGrade(int grade)
{
    if (grade >= 90 && grade <= 100)
        return "A+";
    else if (grade < 90 && grade >= 83)
        return "A";
    else if (grade < 83 && grade >= 80)
        return "A-";
    else if (grade >= 75 && grade < 80)
        return "B+";
    else if (grade >= 68 && grade < 75)
        return "B";
    else if (grade >= 60 && grade < 68)
        return "B-";
    else if (grade >= 55 && grade < 60)
        return "C";
    else if (grade > 50 && grade < 55)
        return "D";
    return "F";
}
