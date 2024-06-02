#ifndef NODE
#define NODE

#include <iostream>
#include "student.h"
#include <cstring>

using namespace std;

class Node {

 public:
  
  //Constructor
  Node(Student*);
  
  //Get next node pointer
  Node* getNext();
  
  //Get student pointer
  Student* getStudent();
  
  //Set next pointer to node pointer
  void setNext(Node*);
  
  //Destructor
  ~Node();

 protected:
  //Pointers
  Node* next;
  Student* student;


};

#endif
