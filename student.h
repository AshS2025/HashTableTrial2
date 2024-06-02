#ifndef STUDENT
#define STUDENT

#include <iostream>
#include <cstring>

using namespace std;

class Student {
public:
    // Functions for Student class
    char* getFirstName();
    char* getLastName();
    int getStudentID();
    float getGPA();

    // Setters
    void setFirstName(const char* first);
    void setLastName(const char* last);
    void setStudentID(int id);
    void setGPA(float gpa);

    // All variables are public
    char firstName[81];
    char lastName[81];
    int studentID = 0;
    float GPA = 0;

    // Constructor
    Student(char first[], char last[], int id, float gpa);
};

#endif
