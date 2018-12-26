#ifndef LIB_FILEHANDLER_H
#define LIB_FILEHANDLER_H

#include <fstream>

using namespace std;

inline bool doesFileExist (string fileName){
  ifstream file (fileName);
  if (!file.is_open ())
    return false;

  file.close ();
  return true;
}

ifstream openInFile (string fileName);

#endif
