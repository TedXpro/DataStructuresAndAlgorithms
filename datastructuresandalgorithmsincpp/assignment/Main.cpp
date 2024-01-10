#include <iostream>
#include "Student.cpp"

using namespace std;

int main(){
    StudentTree scTree = readFromStudentFile();
    scTree.displayInOrder();

    // scTree.deleteStudent(4);
    // scTree.save();
    Student s1;
    s1.setStudentId(4);
    s1.setAge(20);
    s1.setFirstName("Dagmawi");
    s1.setLastName("Belay");
    s1.setSex('M');
    scTree.insertStudent(4, s1);

    scTree.displayInOrder();
    scTree.save();
}