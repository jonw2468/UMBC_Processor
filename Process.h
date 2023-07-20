/*****************************************************************************
 ** File: Process.h
 ** Project: CMSC 202 Project 5, Fall 2022
 ** Author:  Jeremy Dixon
 ** Date:    11/11/2022
 ** Email:   jdixon@umbc.edu
 **
 Description: Header file for Process struct.
*****************************************************************************/

#ifndef PROCESS_H
#define PROCESS_H
#include <iostream>
#include <string>
using namespace std;

// Global constants

struct Process {
public:
  // Name: Default Constructor
  // Desc: Constructs a process struct with default (-1, test, -1, -1)
  // Precondition: None
  // Postcondition: A new Process struct is created for use.
  Process();
  // Name: Overloaded Constructor
  // Desc: Constructs a process struct given all fields.
  // Precondition: Process created using passed data
  // Postcondition: A new Process struct is created for use.
  Process(string name, int id, int call, int duration);
  // Name: Overloaded insertion operator
  // Desc: Returns ostream object for the process struct.
  //       Should display name, id, call, duration i.e. Process A 1 2 82696
  // Precondition: Process object exists
  // Postcondition: Returns ostream of process prompt.
  friend ostream& operator<< (ostream& output, Process&);

  //Member variables (all public)
  string m_name; //Name of process
  int m_id; // Process ID
  int m_call; //Process called
  int m_duration; //Duration of process
};

#endif
