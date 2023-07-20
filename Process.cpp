/*******
 ** File:    Process.cpp
 ** Project: Project 5 – Process Manager
 ** Author:  Jon Woods
 ** Date:    12/8/2022
 ** Section: 20/22
 ** Email:   jwoods6@umbc.edu
 **
 ** This file contains the syntax for all functions involving Process objects. These functions
 ** create and store objects with a process name, IDs for the process and a call, and the duration
 ** of the call as well as an overload operator that provides output of the data within Process
 ** objects.
*******/
#include "Process.h"
#include <iostream>
#include <string>
using namespace std;

// Process()
// Default constructor for a new Process object.
Process::Process() {
  m_name = "test";
  m_id = -1;
  m_call = -1;
  m_duration = -1;
}

// Process() overload constructor
// Given a string, 2 ID integers, and a duration integer, constructs a new Process object
// containing that data.
Process::Process(string name, int id, int call, int duration) {
  m_name = name;
  m_id = id;
  m_call = call;
  m_duration = duration;
}

// Operator << overload
// Given a Process object, returns the data in that object as an output.
ostream &operator<< (ostream &output, Process& process){
  output << process.m_name << " " << process.m_id
	 << " " << process.m_call << " " << process.m_duration;
  return output;
}
