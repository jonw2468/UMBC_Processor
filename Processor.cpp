/*******
 ** File:    Processor.cpp
 ** Project: Project 5 – Process Manager
 ** Author:  Jon Woods
 ** Date:    12/8/2022
 ** Section: 20/22
 ** Email:   jwoods6@umbc.edu
 **
 ** This file contains the syntax for all functions involving Processor objects. These functions
 ** construct Processor objects, read a file to initialize a vector of given Process objects,
 ** allocate a vector containing linked-list threads of Process pointers using the Lstack template,
 ** and control all user inputs and menus in order to run the UMBC Processor program.
*******/
#include "Lstack.cpp"
#include "Process.h"
#include "Processor.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Processor()
// Overloaded constructor. Given a string, constructs a new Processor object containing
// that string as the name of a file.
Processor::Processor(string filename) {
  m_fileName = filename;
}

// ~Processor()
// Default destructor for a Processor object. Removes all pointers in m_processes and m_threads
// and replaces the file name with an empty string.
Processor::~Processor() {
  m_processes.clear();
  m_threads.clear();
  m_fileName = "";
}

// InititalizeProcessor()
// If at least one Process object is in m_fileName, displays the title, initializes the Lstack
// threads, runs the main menu, and thanks the user after they quit the program.
// Does nothing otherwise.
void Processor::InitializeProcessor() {
  if (LoadProcesses(m_fileName)) {
    DisplayTitle();
    PopulateThreads();
    MainMenu();
    cout << "Thank you for using UMBC Processor!" << endl;
  }
}

// MainMenu()
// Displays the main menu options of the program and calls DisplayThread() or StartThreads() based
// on user input. Repeats until the user quits the program.
void Processor::MainMenu() {
  int choice;
  do {
    // User input with validation
    do {
      cout << "Choose an option.\n1. Display Threads\n2. Start Thread\n3. Quit" << endl;
      cin >> choice;
      if (choice < 0 || choice > 3) {
	cout << "Please enter a valid option." << endl;
      }
    } while (choice < 0 || choice > 3);
    switch (choice) {
    case 1:
      DisplayThread();
      break;
    case 2:
      StartThreads();
      break;
    }
  } while (choice != 3); // Repeat until user inputs 3 to quit
}

// LoadProcesses()
// Given the name of a file, returns whether data exists in that file.
// If so, reads all Process objects from the file and stores them in m_processes.
// Displays a warning message and does nothing otherwise.
bool Processor::LoadProcesses(string filename) {
  fstream reader;
  reader.open(filename);
  string name, id, call, dur;
  // Check for existence of first Process object
  if (getline(reader, name, DELIMITER)) {
    getline(reader, id, DELIMITER);
    getline(reader, call, DELIMITER);
    getline(reader, dur);
    m_processes.push_back(new Process(name, stoi(id), stoi(call), stoi(dur)));
    // Check every line in the file as separated by "|"
    while (getline(reader, name, DELIMITER) && getline(reader, id, DELIMITER)) {
      getline(reader, call, DELIMITER);
      getline(reader, dur);
      m_processes.push_back(new Process(name, stoi(id), stoi(call), stoi(dur)));
    }
    return true;
  } else {
    cout << "No processes to be loaded. Try again." << endl;
    return false;
  }
}

// GetProcessCalled()
// Given the integer ID of a Process object, returns the index in m_processes where a Process of
// that ID is pointed to or -1 if the ID does not exist.
int Processor::GetProcessCalled(int id) {
  // Check every element in vector
  for (int i = 0; i < (int)m_processes.size(); i++) {
    if (m_processes.at(i)->m_id == id) {
      return i;
    }
  }
  return -1;
}

// AddThread()
// Given a Process pointer, creates a new Lstack thread with that pointer, pushes each pointer
// linked after it to the front of the list with GetProcessCalled(), and adds the list to m_threads.
void Processor::AddThread(Process* start) {
  Lstack<Process*>* newThread = new Lstack<Process*>();
  newThread->Push(start);
  int nextCall = GetProcessCalled(start->m_call); // Next Process ID determined by m_call
  // Call and push new Process pointers until -1 (a nonexistent ID) is returned
  while (nextCall != -1) {
    Process* temp = m_processes.at(nextCall);
    newThread->Push(temp);
    nextCall = GetProcessCalled(temp->m_call);
  }
  m_threads.push_back(newThread);
}

// PopulateThreads()
// Calls AddThread to create and store an NUM_THREADS Lstack thread in the m_threads vector starting
// at each of the first NUM_THREADS elements in m_processes.
void Processor::PopulateThreads() {
  // Add NUM_THREADS Lstack elements to vector
  for (int i = 0; i < NUM_THREADS; i++) {
    AddThread(m_processes.at(i));
  }
}

// DisplayProcesses()
// A test function. Displays the Process pointer data at each index in m_processes.
void Processor::DisplayProcesses() {
  // Check every element in m_processes vector
  for (int i = 0; i < (int)m_processes.size(); i++) {
    cout << *m_processes.at(i) << endl;
  }
}

// ListThreads()
// Displays the number of Process pointers in each Lstack thread in m_threads.
void Processor::ListThreads() {
  // Check every element in m_threads vector
  for (int i = 0; i < NUM_THREADS; i++) {
    cout << "Thread " << i+1 << " (" << m_threads.at(i)->GetSize() << " processes)" << endl;
  }
}

// ChooseThreads()
// Returns an integer between 1 and NUM_THREADS.
int Processor::ChooseThread() {
  int choice;
  // User input with validation
  do {
    cout << "What thread would you like to view?" << endl;
    ListThreads();
    cin >> choice;
    // Display warning message before repeating if input is invalid
    if (choice < 1 || choice > NUM_THREADS) {
      cout << "Please enter a valid option." << endl;
    }
  } while (choice < 1 || choice > NUM_THREADS);
  return choice;
}

// DisplayThread()
// Displays the data, if it exists, at every Process pointer in the Lstack thread at an index in
// m_threads given by calling ChooseThread(). Notifies the user of the empty thread otherwise.
void Processor::DisplayThread() {
  int num = ChooseThread(); // ChooseThread() returns 1 greater than the index being displayed
  cout << "Thread " << num << endl;
  Lstack<Process*>* thread = m_threads.at(num-1);
  if (thread->IsEmpty()) {
    cout << "This thread is empty." << endl;
  } else {
    // Check every node in Lstack
    for (int i = 0; i < thread->GetSize(); i++) {
      cout << *(thread->At(i)) << endl;
    }
  }
}

// StartThreads()
// Deallocates all linked Process pointers in the Lstack threads and displays the sum of each
// thread's m_duration values.
void Processor::StartThreads() {
  // Check every element in m_threads vector
  for (int i = 0; i < NUM_THREADS; i++) {
    Lstack<Process*>* thread = m_threads.at(i);
    int durationSum = 0;
    cout << "Thread " << i+1 << " took ";
    // Deallocate every node in Lstack
    while (!(thread->IsEmpty())) {
      Process temp = *(thread->Top());
      durationSum += temp.m_duration;
      thread->Pop();
    }
    cout << durationSum << " milliseconds to complete" << endl;
  }
}

// DisplayTitle()
// Welcomes the user to the processor program.
void Processor::DisplayTitle() {
  cout << "Welcome to UMBC Processor" << endl;
}
