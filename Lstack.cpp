/*******
 ** File:    Lstack.cpp
 ** Project: Project 5 – Process Manager
 ** Author:  Jon Woods
 ** Date:    12/8/2022
 ** Section: 20/22
 ** Email:   jwoods6@umbc.edu
 **
 ** This file contains the syntax for all template classes and functions for Lstack linked lists.
 ** These functions provide templates for constructing, deconstructing, and manipulating data from
 ** Lstacks and the Node pointers they store.
*******/
#ifndef LSTACK_CPP
#define LSTACK_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated node class used in templated linked list
template <class T>
class Node {
   public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data; //Templated data for node
  Node<T>* m_next; //Templated node pointer to next node
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = nullptr;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
   return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lstack {
 public:
  // Name: Lstack() (Linked List Stack) - Default Constructor
  // Desc: Used to build a new templated stack (as a linked list) m_head = top
  // Preconditions: None
  // Postconditions: Creates a new lstack where m_head points to nullptr and m_size = 0
  // Required
  Lstack();
  // Name: ~Lstack() - Destructor
  // Desc: Used to destruct a Lstack
  // Preconditions: There is an existing lstack with at least one node
  // Postconditions: An lstack is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks. (Allowed to use Clear in this function)
  // Required
 ~Lstack();
  // Name: Lstack (Copy Constructor)
  // Preconditions: Creates a copy of existing LStack
  //                Requires an existing Lstack
  // Hint: Make sure that the copy is not inverted
  // Postconditions: Copy of existing Lstack
  // Required
  Lstack(const Lstack&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Requires two Lstacks holding the same type of data
  //                After running, both stacks are identical with no memory loss
  //                Requires an existing Lstack
  // Postconditions: Two identical Lstack
  // Hint: Make sure that the destination Lstack has the same data in the same order as source
  // Required
  Lstack<T>& operator= (Lstack&);
  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires an existing Lstack
  // Postconditions: Adds a new node to the top of the lstack.
  // Required
  void Push(const T&);
  // Name: Pop
  // Preconditions: Requires an existing Lstack with at least one node 
  // Postconditions: Removes top node in the lstack.
  // Assume that the Lstack has at least one node (Will check prior to call)
  // Required
  void Pop();
  // Name: Display
  // Preconditions: Outputs the lstack.
  // Postconditions: Displays the data in each node of lstack
  // Required (used only for testing lstack_test)
  void Display();
  // Name: Top
  // Preconditions: Requires an existing Lstack
  // Postconditions: Returns whatever data is on top
  // Required
  T Top();
  // Name: IsEmpty
  // Preconditions: Requires an existing Lstack
  // Postconditions: Returns true if the Lstack is empty else false.
  // Required
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires an existing Lstack
  // Postconditions: Returns m_size
  // Required
  int GetSize();
  // Name: Find()
  // Preconditions:  Requires an existing Lstack
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
  // Required
  int Find(T&);
  // Name: Clear
  // Preconditions:  Requires an existing Lstack
  // Postconditions: Removes all nodes in Lstack
  // Required
  void Clear();
  // Name: At(int)
  // Preconditions:  Requires an existing Lstack
  // Postconditions: Returns the data at a specific index;
  //                 Index will be checked prior to call (assume int is valid)
  // Required
  T At (int x);
private:
  Node <T> *m_head; //Node pointer for the head
  int m_size; //Number of nodes in stack
};

//**********Implement Lstack Class Here***********
//**********All Functions Are Required Even If Not Used for Processor**************

// Lstack()
// Default constructor for a new Lstack list.
template <class T>
Lstack<T>::Lstack() {
  m_head = nullptr;
  m_size = 0;
}

// ~Lstack()
// Default destructor for an Lstack list. Resets the Lstack to an empty one with a size of 0.
template <class T>
Lstack<T>::~Lstack() {
  Clear();
  m_size = 0;
}

// Lstack() copy constructor
// Given an Lstack list of reference, constructs a new one identical to the reference.
template <class T>
Lstack<T>::Lstack(const Lstack& source) {
  Node<T>* currSource = source.m_head;
  m_head = new Node<T>(currSource->GetData());
  m_size++;
  currSource = currSource->GetNext();
  Node<T>* curr = m_head;
  // Check and add every node in the source list
  while (currSource != nullptr) {
    Node<T>* temp = new Node<T>(currSource->GetData());
    curr->SetNext(temp);
    curr = curr->GetNext();
    currSource = currSource->GetNext();
    m_size++;
  }
  curr->SetNext(nullptr);
}

// IsEmpty()
// Returns a boolean of whether an Lstack list is empty, as signified by m_head being null.
template <class T>
bool Lstack<T>::IsEmpty() {
  return (m_head == nullptr);
}

// Operator = overload
// Given an Lstack list of reference, clears the current Lstack and replaces it with a list
// identical to the reference.
template <class T>
Lstack<T>& Lstack<T>::operator= (Lstack& source) {
  Clear(); // Deallocate the Lstack so source can be copied more easily
  Node<T>* currSource = source.m_head;
  m_head = new Node<T>(currSource->GetData());
  m_size++;
  currSource = currSource->GetNext();
  Node<T>* curr = m_head;
  // Check and add every node in the source list
  while (currSource != nullptr) {
    Node<T>* temp = new Node<T>(currSource->GetData());
    curr->SetNext(temp);
    curr = curr->GetNext();
    currSource = currSource->GetNext();
    m_size++;
  }
  curr->SetNext(nullptr);
  return *this;
}

// Top()
// Returns the data value of the head node of an Lstack list or NULL if the list is empty.
template <class T>
T Lstack<T>::Top() {
  if (IsEmpty()) {
    return NULL;
  } else {
    return m_head->GetData();
  }
}

// Push()
// Given a value of reference, constructs a new Node object containing that value and adds it
// to the beginning of the current Lstack list.
template <class T>
void Lstack<T>::Push(const T& data) {
  Node<T>* newNode = new Node(data);
  newNode->SetNext(m_head);
  m_head = newNode;
  m_size++;
}

// Pop()
// Deletes the first node of an Lstack object if it exists. Does nothing otherwise.
template <class T>
void Lstack<T>::Pop() {
  if (m_head != nullptr) {
    Node<T>* pop = m_head;
    m_head = m_head->GetNext();
    delete pop;
    m_size--;
  }
}

// GetSize()
// Returns the number of nodes in an Lstack list.
template <class T>
int Lstack<T>::GetSize() {
  return m_size;
}

// Find()
// Given a value of reference, checks whether that value is stored in a Node of an Lstack list.
// Returns the index from m_head where that object is found or -1 otherwise.
template <class T>
int Lstack<T>::Find(T& data) {
  Node<T>* curr = m_head;
  int index = 0;
  // Check every node in the list
  while (curr->GetNext() != nullptr) {
    if (curr->GetData() == data) {
      return index;
    }
    index++;
    curr = curr->GetNext();
  }
  // Return -1, a nonexistent index, if the parameter is not found
  return -1;
}

// Clear()
// Using the Pop() and IsEmpty() functions, deletes every node in an Lstack list from newest to
// oldest until only the nullptr is left. Does nothing for an empty list.
template <class T>
void Lstack<T>::Clear() {
  while (!(IsEmpty())) {
    Pop();
  }
}

// At()
// Given an index, returns the data value of the Node at that index from m_head or NULL if that
// index does not exist.
template <class T>
T Lstack<T>::At(int x) {
  // Return a null template if the index is invalid
  if (x > m_size) {
    return NULL;
  }
  // Else check and return the xth node in the list
  Node<T>* curr = m_head;
  for (int i = 0; i < x; i++) {
    curr = curr->GetNext();
  }
  return curr->GetData();
}

// Display()
// A test function. Displays the template value at each node in an Lstack list in order.
template <class T>
void Lstack<T>::Display() {
  Node<T>* curr = m_head;
  // Check every node in the list
  while (curr->GetNext() != nullptr) {
    cout << curr->GetData() << "->";
    curr = curr->GetNext();
  }
  cout << "END" << endl;
}
#endif
