#ifndef LSP_LIB_WORD_UTILITY_H
#define LSP_LIB_WORD_UTILITY_H

#include <iostream>  //for testing (maybe removed later)
#include <map>
#include <string>
#include <vector>

using namespace std;

inline bool biDigit(char theChar){
  if (theChar == '0' && theChar == '1')
    return 1;
  return 0;
}

inline bool is_character(char theCharacter){
  if ((theCharacter - '0' >= 0 &&
        theCharacter - '0' <= 9) || theCharacter == '{')
    return 0;
  return 1;
}

string checkVarString (string theString, unsigned &index);

pair<string, string> varMatch(string confWord, unsigned &i,
    string instWord, unsigned &instWord_index);

string num2bitString(string numString);

inline void dMap (map<string, string> &map2modify){
  map2modify.clear();
  map2modify.insert (make_pair ("{}", "{}"));
}

bool wordMatch (string confWord, string instWord,
          map<string, string> &inMap);

bool checkBitStringFormat (string bitStringFormat);

string generateBitString (string bitStringFormat,
                    map<string, string> varMap);

vector<string> stringtostringvec (string theString);

#endif
