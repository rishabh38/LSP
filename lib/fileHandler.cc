#include "fileHandler.h"

#include <fstream>
#include <iostream>

using namespace std;

ifstream openInFile (string fileName){
  ifstream  input (fileName);

  if (!doesFileExist (fileName)){
    cerr << "unable to open file " << fileName << endl;
    return input;
  }

  return input;
}
