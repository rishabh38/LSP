#ifndef LIB_FILEHANDLER_H
#define LIB_FILEHANDLER_H

#include <fstream>

using namespace std;

inline bool doesFileExist (string fileName);

ifstream openInFile (string fileName);

#endif
