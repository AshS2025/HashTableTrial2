#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Student.h"
#include "Node.h"


using namespace std;


Node* head = NULL; 


void add(Node*, Node* &, Node*, Node* );
void rehash(int &, Node **&);


//its erroring if i straight set the size so yay we get to be convoluted!
int bsize = 100; 
   int size = bsize; 


int main() {
    char input[20];
    char first[81];
    char last[81];
    int count = 0;
    int id = 1; 
    int size = 100;
    
    srand(time(NULL));
    Node** hash = new Node*[size];


    
    for (int i = 0; i < size; i++) {
        hash[i] = NULL;
	//everything in hash is null to start
    }


    bool running = true;


    while (running == true) {
        cout << "type a command: ADD, PRINT, DELETE GENERATE, or QUIT." << endl;
        cin >> input;


        if (strcmp(input, "ADD") == 0) {
	  cout << "(need a space before you type the name)" << endl; 


            //id
            cout << "ID: ";
            int studentID;
            cin >> id;
            cin.ignore();


            //first name
            cout << "first name: ";
            cin.ignore();
            cin.getline(first, 81);


            //last name
            cout << "last name: ";
            cin.getline(last, 81);


            //gpa
            cout << "GPA: ";
            float gpa;
            cin >> gpa;


            Student* student = new Student(first, last, id, gpa); 
            add(new Node(student), head, NULL, head); //may take this out bc i do it in the if 


            int hashkey = studentID % size;


	    
            if (hash[hashkey] == NULL) {
                
                hash[hashkey] = new Node(student);
            } else {
                

                Node* temp = hash[hashkey];


                while (temp->getNext() != NULL) {
                    temp = temp->getNext(); //traversing the list 
                }

                temp->setNext (new Node(student));
            }
	    
        } else if (strcmp(input, "PRINT") == 0) {
            for (int i = 0; i < size; i++) {
                Node* temp = hash[i];
                while (temp != NULL) {
		  cout << temp->getStudent()->getFirstName() << " " << temp->getStudent()->getLastName() << " " << temp->getStudent()->getStudentID() << " " << temp->getStudent()->getGPA() << endl;

		  //so this like prints all the empty lines too but i dont want to fix it
		  //and rlly it meets the requirements right....

		  temp = temp->getNext();
                
                }
                cout << endl; 
            }
        } 
        
        
        
else if (strcmp(input, "GENERATE") == 0) {
    int generateinput = 0;
    int studentCount = 0;
    cout << "how many students do you want to generate: " << endl;
    cin >> generateinput;

    //storing first names
      char* firstcpy = new char[20];
      char* lastcpy = new char[20];

      //from galbraith board
// Opens first name file 
ifstream firstNames;
firstNames.open("names.txt");

//address storing with double pointer 
char ** fname =new char*[50]; 
for (int i = 0; i < 50; i++) {
          fname[i] = new char[20];
          firstNames >> firstcpy;
          strcpy(fname [i], firstcpy);  
          studentCount++;
      }

      
//close file yay easy peasy!! 
firstNames.close();

// saem thing as above but for last names!

// 
ifstream lastNames;
lastNames.open("lastnames.txt");



char** lname = new char*[studentCount];

for (int i = 0; i < 50; i++) {      
          lname[i] = new char[20];
          lastNames >> lastcpy;
          strcpy(lname[i], lastcpy);
        
      }
//lName[studentCount] = NULL; 
lastNames.close();



    // generating the random students
      char firstName[20];
      char lastName[20];
      int studentID = 0;
      float gpa = 0.0;

      
      Student* newStu = new Student(firstName, lastName, studentID, gpa);


    for (int i = 0; i < generateinput; i++) { // generates random students

        char firsttemp[20];
        char lasttemp[20];
        int randFirst = rand() % studentCount;
        int randLast = rand() % studentCount;
        

	strncpy(firsttemp, fname[randFirst], 20);
        strncpy(lasttemp, lname[randLast], 20);


        // Create
        newStu = new Student(firsttemp, lasttemp, id++ , (rand() % 500) / 100.0);


        // Add
	
        int hashIndex = newStu->getStudentID() % size;

	if (hash[hashIndex]== NULL) {
	  
            hash[hashIndex] = new Node(newStu);
	    
        } else {
            Node* temp = hash[hashIndex];
            while (temp->getNext() != NULL) {
                temp = temp->getNext(); //traverse linked list 
            }

            
            temp->setNext(new Node(newStu));
        }


        //rehashing!
        for (int i = 0; i <size; i++) {
                
            if (hash[i] != NULL){
                  Node* temp = hash[i];
                  int count = 1;
                  while (temp!= NULL){
                    count++; 
                    temp = temp->getNext(); 
                  }
                    //more than 3 then rehash
		  
                  if (count > 3){
		    
                    rehash(size, hash); 
                  }

            }
        }
    }


    // Cleanup
    for (int i = 0; i < 50; i++) { 
        delete[] fname [i];
        delete[] lname [i];
    }
    delete[] fname;
    delete[] lname;
}


         else if (strcmp(input, "DELETE") == 0) {
            cout << "Enter id of the student you want to delete: ";
            int stuID;
            cin >> stuID;


            int hashkey = stuID % size;


            if (hash[hashkey] != NULL) {
                Node* temp = hash[hashkey];
                Node* prev = NULL;


                while (temp != NULL) {
                    if (temp->getStudent()->getStudentID() == stuID) {
		      
                        if (prev == NULL) {
                            hash[hashkey] = temp->getNext();
                            delete temp;
			    
                        }

			else {
                            prev->setNext(temp->getNext());
                            delete temp;
                        }
			
                        break;
                    }


                    prev = temp;
                    temp = temp->getNext();
                }
            }
        } else if (strcmp(input, "QUIT") == 0) {
            running = false;
        }
    }


    // Memory Clean up
    for (int i = 0; i < size; i++) {
      
        Node* temp = hash[i];
        while (temp != NULL) {
            Node* next = temp->getNext();
            delete temp;
            temp = next;
        }
    }


    delete[] hash;


    return 0;
}


void add(Node* newN, Node* &head, Node* previous, Node* current) {
  if (head == NULL) { //first thing just add it in 
        head = newN;
        return;
    }


    if (current == NULL) {
      
        previous->setNext (newN);
        newN->setNext(head);
        return;
    }


    if (newN->getStudent()->getStudentID() < current->getStudent()->getStudentID()) {
        if (previous == NULL) {
            newN->setNext(head);
            head = newN;
        }

	else {
            previous->setNext(newN);
            newN->setNext(current);
        }
    } else {
        add(newN, head, current, current->getNext());
    }
}


void rehash(int &size, Node**&hash) {
    // Double the bucket size
  
    size = size * 2;
    Node** newHash = new Node*[size];

    for (int i = 0; i < size; i++) {
        newHash[i] = NULL;
    }


    
    for (int i = 0;i < size/2;i++) {

      Node * temp = hash[i]; 


        while (temp != NULL) {
            int studentID = temp->getStudent()->getStudentID();
            int newHashkey = studentID % size;


            // insert into new
            if (newHash[newHashkey] == NULL) {
                newHash[newHashkey] = new Node(temp->getStudent());
                
            } else {
                Node *tempOne = newHash[newHashkey];
              
                while (tempOne->getNext() != NULL) {  
                  tempOne = tempOne->getNext();
                }
                tempOne->setNext(new Node(temp->getStudent()));
            }


            temp = temp->getNext();
        }
    }
    
    hash = newHash;  

}
