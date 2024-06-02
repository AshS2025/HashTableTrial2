#include <iostream>
#include <cstring>
#include "Node.h"
#include "Student.h"

using namespace std;

//Construct node given a student
Node::Node(Student* newStudent) {
  student = newStudent;
  next = NULL;

}

//Get next node
Node* Node::getNext() {
  return next;
}

//Get student
Student* Node::getStudent() {
  return student;
}

//Set next node given node
void Node::setNext(Node* nextNode){
    next = nextNode;

}

//Destructor for node
Node::~Node() {
  delete student;
}
