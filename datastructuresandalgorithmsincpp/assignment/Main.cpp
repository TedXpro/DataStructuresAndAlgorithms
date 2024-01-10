#include <iostream>
#include "Student.cpp"
#include "Course.cpp"
#include "StudentCourse.cpp"

using namespace std;

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

int main(){
    cout << "displaying students\n\n";
    StudentTree scTree = readFromStudentFile();
    scTree.displayInOrder();

    cout << "displaying courses\n\n";
    CourseTree coTree = readFromCourseFile();
    coTree.displayCourses();

    cout << "displaying student courses\n\n";
    StudentCourseTree scoTree = readFromStudentCourseFile();
    scoTree.display();

    cout << "Displaying contents for student 1\n";
    scoTree.displayCourseofStudent(1);
}