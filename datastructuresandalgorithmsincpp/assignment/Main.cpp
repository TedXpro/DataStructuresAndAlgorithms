#include <iostream>
#include "Student.cpp"
#include "Course.cpp"

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

    CourseTree coBinTree = readFromCourseFile();
    Course c1;
    c1.setCourseNumber("Co1");
    c1.setCourseTitle("Data Structure and Algorithm");
    c1.setCreditHour("7");
    Course c2;
    c2.setCourseNumber("Co2");
    c2.setCourseTitle("Numerial Analysis");
    c2.setCreditHour("5");
    Course c3;
    c3.setCourseNumber("Co3");
    c3.setCourseTitle("Networking");
    c3.setCreditHour("5");
    Course c4;
    c4.setCourseNumber("Co4");
    c4.setCourseTitle("Discrete Mathematics");
    c4.setCreditHour("7");
    Course c5;
    c5.setCourseNumber("Co6");
    c5.setCourseTitle("SoftwareEngineering");
    c5.setCreditHour("6");

    coBinTree.insertCourse("Co3", c3);
    coBinTree.insertCourse("Co4", c4);
    coBinTree.insertCourse("Co6", c5);
    coBinTree.insertCourse("Co2", c2);
    coBinTree.insertCourse("Co1", c1);
    coBinTree.displayCourses();
    coBinTree.save();
}