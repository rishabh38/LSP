#ifndef LIB_FILEHANDLER_H
#define LIB_FILEHANDLER_H

#include <fstream>

using namespace std;

/* bool doesFileExist (string fileName):
 * takes a string denoting name of the file.
 * returns true if the file with the given name
 * exist, else returns false.
 */
inline bool doesFileExist (string fileName){
  ifstream file (fileName);
  if (!file.is_open ())
    return false;

  file.close ();
  return true;
}

ifstream openInFile (string fileName);

#endif
