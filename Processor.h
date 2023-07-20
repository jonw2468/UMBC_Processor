/*****************************************************************************
 ** File: Processor.h
 ** Project: CMSC 202 Project 5, Fall 2022
 ** Author:  Jeremy Dixon
 ** Date:    11/11/2022
 ** Email:   jdixon@umbc.edu
 **
 Description: Header file for Processor class.
*****************************************************************************/

#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "Lstack.cpp"
#include "Process.h"
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//constants
const char DELIMITER = '|'; //delimiter between input lines
const int NUM_THREADS = 4; //constant for number of threads (we will test for 1-6)
//Your code should work if NUM_THREADS is anything between 1 and 6

class Processor {
public:
  // Name: Overloaded Constructor
  // Desc: Sets m_fileName based on passed string
  // Precondition: None
  // Postcondition: m_fileName is populated
  Processor(string filename);
  // Name: Destructor
  // Desc: Deallocates memory allocated for the Processes.
  // Precondition: A Processor exists.
  // Postcondition: All dynamically allocated memory in Processor is deleted.
  ~Processor();
  // Name: InitializeProcessor
  // Desc: Starts the processor. Calls DisplayTitle and LoadProcesses.
  //       Then calls PopulateThreads which adds all processes to each thread based on their calls
  //       Calls MainMenu until quit. When quit, thanks user for using tool.
  // Precondition: A Processor exists.
  // Postcondition: Exits
  void InitializeProcessor();
  // Name: LoadProcesses
  // Desc: Input file contains process name, id, call_id, and duration
  //       Loads all processes into m_processes dynamically
  //       For each thread defined in NUM_THREADS (which can be 1-6 for testing),
  //       call AddThread and add the corresponding Process to that thread
  //       For example, for 2 threads, AddThread(Process 0), AddThread (Process 1) would be called
  //       Input files can have ANY number of processes (not limited to 52)
  //       Assume input file will have processes >= number of threads)
  // Precondition: m_fileName populated
  // Postcondition: Returns true if file was read. Otherwise, it returns false.
  bool LoadProcesses(string filename);
  // Name: AddThread
  // Desc: Each Thread uses an Lstack. This function adds a new Thread to m_threads
  //       The passed process is the "base" process that triggers all other function calls
  //       For each thread in NUM_THREADS, a new thread is inserted into m_threads
  // Precondition: m_threads isn't at capacity
  // Postcondition: Add thread to m_threads with starting process
  void AddThread(Process*);
  // Name: GetProcessCalled
  // Desc: Passed process ID and returns index of location in m_processes
  //       Used with PopulateThreads
  // Precondition:
  // Postcondition: Returns index of location or -1 if not found
  int GetProcessCalled(int id);
  // Name: PopulateThreads
  // Desc: Starting with provided process, follows the m_call to push next process onto stack
  //       Uses GetProcessCalled to find the index of the process to add to the stack
  //       Keeps adding processes until the m_call == -1
  // Precondition: m_processes populated and first process of thread populated
  // Postcondition: Populates number of threads provided in (NUM_THREADS)
  void PopulateThreads();
  // Name: MainMenu
  // Desc: Presents user with menu options for showing threads and allowing
  // user to start the threads to processes.
  // Precondition: Processes and threads have been loaded.
  // Postcondition: The main menu is presented (Display Thread, Start Threads, Quit)
  void MainMenu();
  // Name: DisplayProcesses
  // Desc: Displays all processes loaded from file (TESTING ONLY)
  //       Used to make sure that all processes have been loaded correctly (Not used otherwise)
  // Precondition: m_processes has been populated
  // Postcondition: All processes are printed to the screen.
  void DisplayProcesses();
  // Name: ListThreads
  // Desc: Displays a numbered list of all threads listed with the number of processes
  // Precondition: m_threads is populated
  // Postcondition: None
  void ListThreads();
  // Name: ChooseThread
  // Desc: Allows a user to choose one of the threads to view. Calls ListThreads and
  //       allows use to choose one. Returns value - 1 (location in vector)
  // Precondition: A Thread exists.
  // Postcondition: Returns value entered minus one
  int ChooseThread();
  // Name: DisplayThreads
  // Desc: Calls ChooseThread then Displays all processes in thread chosen
  // Precondition: m_threads populated
  // Postcondition: All processes for chosen thread displayed to screen
  void DisplayThread();
  // Name: StartThread
  // Desc: Starts all populated threads (based on size of m_threads)
  // Keeps running total of duration of each process being processed
  // Adds the duration from the "Top" of the thread then removes the process from the thread
  // After all processes have been managed for all threads
  //       displays total duration, in milliseconds, for each thread
  // Precondition: m_processes has been populated
  // Postcondition: Returns to main menu but all threads have 0 processes each
  void StartThreads();
  // Name: DisplayTitle
  // Desc: Displays opening Welcome message
  // Precondition: None.
  // Postcondition: Title is displayed.
  void DisplayTitle();
private:
  vector<Process* > m_processes; //Holds all processes loaded from file
  vector<Lstack<Process*>* > m_threads; //A vector of multiple Lstacks (threads)
  string m_fileName; //Filename to be loaded
};
#endif
