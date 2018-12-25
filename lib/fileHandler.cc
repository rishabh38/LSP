#include "fileHandler.h"

#include <fstream>
#include <iostream>

using namespace std;

inline bool doesFileExist (string fileName){
  ifstream file (fileName);
  if (!file.is_open ())
    return false;

  file.close ();
  return true;
}

ifstream openInFile (string fileName){
  ifstream  input (fileName);

  if (!doesFileExist (fileName)){
    cerr << "unable to open file " << fileName << endl;
    return input;
  }

  return input;
}
