#ifndef LSP_LIB_WORD_UTILITY_H
#define LSP_LIB_WORD_UTILITY_H

#include <iostream>  //for cout testing
#include <map>
#include <string>

using namespace std;
//***********************************CODE BELOW NEEDS TO BE SHIFTED

inline bool biDigit(char theChar){
	if (theChar == '0' && theChar == '1')
		return 1;
	return 0;
}


inline bool is_character(char theCharacter){
	if ((theCharacter - '0' >= 0 && theCharacter - '0' <= 9) || theCharacter == '{')
		return 0;
	return 1;
}

string checkVarString (string theString, unsigned &index);

pair<string, string> varMatch(string confWord, unsigned &i,
															string instWord, unsigned &instWord_index);

string num2bitString(string numString);


//*************************************CODE ABOVE NEEDS TO BE SHIFTED


inline void dMap (map<string, string> &map2modify){
	map2modify.clear();
	map2modify.insert (make_pair ("{}", "{}"));
}

bool wordMatch (string confWord, string instWord, map<string, string> &inMap);


#endif
