/*****************************************************************************
 ** File: proj5.cpp
 ** Project: CMSC 202 Project 5, Fall 2022
 ** Author:  Jeremy Dixon
 ** Date:    11/11/2022
 ** Email:   jdixon@umbc.edu
 **
 Description: CPP file for main.
*****************************************************************************/

// Include basic io functions, strings, and the processor class
#include <iostream>
#include <string>
#include "Processor.h"
#include "Process.h"
#include "Lstack.cpp"

using namespace std;

int main(int argc, char**argv) {
  const int EXPECTED_ARGS = 2;
  const int FILENAME = 1;
  string filename;
  
  //Usage ./proj5 [FILENAME] [DATATYPE]
  if (argc == EXPECTED_ARGS) { //Compares count of arguments vs EXPECTED_ARGS
    filename = argv[FILENAME]; //Pull filename from arguments
    Processor* newProcessor = new Processor(argv[FILENAME]); //Passes filename to Processor
    newProcessor->InitializeProcessor();
    delete newProcessor; //Deallocates Processor
  }
  else {
    cout << "ERROR: Expected usage is ./proj5 [FILENAME]" << endl;
    return -1;
  }
  return 0;
}
