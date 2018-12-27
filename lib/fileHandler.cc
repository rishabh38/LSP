#include "fileHandler.h"

#include <fstream>
#include <iostream>

using namespace std;

/* ifstream openInFile (string fileName):
 * takes name of the file to be opened to read,
 * returns the ifstream for the file if file
 * is opened successfull.
 * returns unattached ifstream if file doesn't exist.
 */
ifstream openInFile (string fileName){
  ifstream  input (fileName);

  if (!doesFileExist (fileName)){
    cerr << "unable to open file " << fileName << endl;
    return input;
  }

  return input;
}
