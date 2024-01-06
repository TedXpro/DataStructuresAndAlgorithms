#include <iostream>

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
    Student(int id){
        studentId = id;
    }
    // ~Student();

    int getId(){
        return studentId;
    }

    string getFirstName(){
        return firstName;
    }
    string getLastName(){
        return lastName;
    }

    int getAge(){
        return age;
    }

    char getSex(){
        return sex;
    }

    void setFirstName(string fName){
        firstName = fName;
    }

    void setLastName(string lName){
        lastName = lName;
    }

    void setAge(int a){
        age = a;
    }

    void setSex(char s){
        sex = s;
    }

};

class Course{
private:
    string courseNumber;
    string courseTitle;
    int creditHour;

public:
    Course(string courseNum){
        courseNumber = courseNum;
    }

    string getCourseNumber(){
        return courseNumber;
    }

    string getCourseTitle(){
        return courseTitle;
    }

    int getCreditHour(){
        return creditHour;
    }

    void setCourseTitle(string coTitle){
        courseTitle = coTitle;
    }

    void setCreditHour(int creditHr){
        creditHour = creditHr;
    }
};

