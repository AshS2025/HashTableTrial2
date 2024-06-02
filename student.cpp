#include <iostream>
#include "Student.h"
#include <cstring>

using namespace std;
//getters for student
//return functions from Student.h
Student::Student(char* first, char* last, int id, float gpa) {
  strcpy(firstName, first);
  strcpy(lastName, last);
  studentID = id;
  GPA = gpa;
}


char* Student::getFirstName() {
  return firstName;

}

char* Student::getLastName() {
  return lastName;
  
}

int Student::getStudentID() {
  return studentID;
}

float Student:: getGPA() {
  return GPA;

}

// Setters
void Student::setFirstName(const char* first) {
    strncpy(firstName, first, 81);
}

void Student::setLastName(const char* last) {
    strncpy(lastName, last, 81);
}

void Student::setStudentID(int id) {
    studentID = id;
}

void Student::setGPA(float gpa) {
    GPA = gpa;
}
