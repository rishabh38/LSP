
#include "word_utility.h"

#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

string checkVarString (string theString, unsigned &index){
	string varString;
	size_t stringSize = theString.size();

	if (theString[index] != '{')
		return varString;

	string tempString;
	for (index += 1; index < stringSize; index++){
		if(theString[index] == '}'){
			varString = tempString;
			break;
		}

		tempString.push_back(theString[index]);
	}

	return varString;
}


pair<string, string> varMatch(string confWord, unsigned &i,
		string instWord, unsigned &instWord_index){
	pair<string, string> error_return_value = make_pair("{}","{}");

	string conf_string;
	string matched_string;
	size_t confWordSize = confWord.size();
	size_t instWordSize = instWord.size();

	if ((conf_string = checkVarString (confWord, i)).empty()){
		cout << "ERROR:confWord is not a varString" << endl;
		return error_return_value;
	}

	if (!isdigit(instWord[instWord_index])){
		cout << "ERROR: instWord doesn't have any digit" << endl;
		return error_return_value;
	}

	matched_string.push_back (instWord[instWord_index]);
	instWord_index++;

	if ((i + 1 < confWordSize && !isdigit(confWord[i + 1]))
			|| (i + 1 == confWordSize)){
		unsigned virtInstSize = instWordSize;

		if (confWord[i + 1] == '{')				//Will make below while loop
			virtInstSize = instWord_index;		//check and push only one char(digit)
									//else checks till its size
		while (instWord_index < virtInstSize && isdigit(instWord[instWord_index])){
			matched_string.push_back(instWord[instWord_index]);
			instWord_index++;
		}
	}
	else if (i + 1 < confWordSize && isdigit(confWord[i + 1])){

		uint64_t conf_index,  anchor_index;
		anchor_index = conf_index = i + 1;
		string tempMatch;

		for ( ; conf_index < confWord.size() && isdigit(confWord[conf_index]); instWord_index++){
			if(instWord_index >= instWordSize){
				conf_index = anchor_index;
				matched_string.append(tempMatch);
				break;
			}
			if(!isdigit(instWord[instWord_index])){
				matched_string.clear();
				break;
			}
			if(instWord[instWord_index] == confWord[conf_index]){
				conf_index++;
				tempMatch.push_back(instWord[instWord_index]);
			}
			else{
				conf_index = anchor_index;
				matched_string.append(tempMatch);
				tempMatch.clear();
				matched_string.push_back(instWord[instWord_index]);
			}
		}
		instWord_index = instWord_index - (conf_index - anchor_index);
	}

	instWord_index -= 1;
	return make_pair(conf_string, matched_string);
}

string num2bitString(string numString){
	uint64_t number = 0;

	for (unsigned i = 0; i < numString.size(); i++)
		number = number*10 + (numString[i] - '0');

	string bitString;
	while (number > 0){
		string a;
		a.push_back(number % 2 + '0');
		bitString.insert(0, a);
		number /= 2;
	}

	return bitString;
}


bool wordMatch (string confWord, string instWord, map<string, string> &inMap){
	map<string, string> varMap;
	bool goodGoing = true;

	for (unsigned iA = 0, iB = 0; (iB < instWord.size() || iA < confWord.size()) ; iA++, iB++){
		if ((iB >= instWord.size() && iA < confWord.size())
				|| (iB < instWord.size() && iA >= confWord.size())){
			dMap (varMap);
			goodGoing = false;
			break;
		}
		if (confWord[iA] != '{' && confWord[iA] != instWord[iB]){
			dMap (varMap);
			goodGoing = false;
			break;
		}
		else if (confWord[iA] == '{'){
			pair<string, string> tempPair = varMatch (confWord, iA, instWord, iB);

			if (tempPair == make_pair ((string)"{}", (string)"{}")){
				dMap (varMap);
				goodGoing = false;
				break;
			}

			varMap.insert (tempPair);
		}
	}

	inMap.insert (varMap.begin(), varMap.end());
	return goodGoing;
}

int lookString4 (char validChar, string TheString, unsigned &index){
	size_t strSize = TheString.size();

	while (index < strSize){
		if (TheString[index] == validChar)
			return 1;
		else if (!isspace(TheString[index]))
			break;

		index++;
	}

	return 0;
}

int lookString4Digit (string TheString, unsigned &index){
	size_t strSize = TheString.size();

	while (index < strSize){
		if (TheString[index] - '0' >= 0 && TheString[index] - '0' <= 9)
		       return 1;
		else if (!isspace(TheString[index]))
			break;
		index++;
	}

	return 0;
}	

map<pair<unsigned, unsigned>, string> parseBitStringFormat (string bitStringFormat){
	size_t strSize = bitStringFormat.size();
	map<pair<unsigned, unsigned>, string> strData;

	for (unsigned index = 0; index < strSize; index++){
		bool goodGoing = 1;
		size_t processedNumSize;
		
		goodGoing = lookString4 ('[', bitStringFormat, index);
		goodGoing &= lookString4Digit (bitStringFormat, ++index);

		if (!goodGoing){
			strData.clear();
			break;
		}

		unsigned number1;
		number1 = stoull (bitStringFormat.substr (index), &processedNumSize);
		index += processedNumSize;

		goodGoing = lookString4 ('-', bitStringFormat, index);
		goodGoing &= lookString4Digit (bitStringFormat, ++index);
		
		if (!goodGoing){
			strData.clear();
			break;
		}

		unsigned number2;
		number2 = stoull (bitStringFormat.substr (index), &processedNumSize);
		index += processedNumSize;

		pair<unsigned, unsigned> range (number1, number2);

		goodGoing = lookString4 (']', bitStringFormat, index);
		goodGoing &= lookString4 (':', bitStringFormat, ++index);
		
		if (!goodGoing){
			strData.clear();
			break;
		}

		while (isspace(bitStringFormat[++index]))
			continue;
		
		string rangeValue;
		while (index < strSize && bitStringFormat[index] != ' ' && bitStringFormat[index] != '|')
			rangeValue.push_back (bitStringFormat[index++]);

		if (!rangeValue.size()){
			strData.clear();
			break;
		}

		strData.insert(make_pair(range, rangeValue));

		if (!lookString4 ('|', bitStringFormat, index))
			break;
	}

	return strData;

}

bool isbitString (string proposedBitString){
	size_t strSize = proposedBitString.size();
	string finalString;
	bool goodGoing = true;
	if (!strSize)
		goodGoing &= false;

	if (proposedBitString[0] != '[')
		goodGoing &= false;

	for (unsigned index = 1; index < strSize - 1; index++){
		if ( proposedBitString[index] != '0' && proposedBitString[index] != '1'){
			goodGoing &= false;
			break;
		}

	}

	if (propopsedBitString[strSize - 1] != ']')
		goodGoing &= false;

	return goodGoing;
}

inline string srtipBraces (string bitString){
	size_t strSize = bitString.size();

	return bitString.substr (1, strSize - 2);
}


/* string resizeBitString (string bitString, size_t newSize):
 * converts a bitstring of different size into a string of 
 * particular size by either truncating the string or by
 * adding string of 0s at the beginning of the string.
 * returns same string if the new size is same  as old size.
 * */
string resizeBitString (string bitString, size_t newSize){
	size_t strSize = bitString.size();

	if (strSize > newSize){
		bitString = substr (strSize - newSize);
	}
	else if (strSize < newSize){
		string temp (newSize - strSize, '0');
		temp.append (bitString);
		bitString = temp;
	}

	return bitString;
}

string generateBitString (string bitStringFormat, map<string, string> varMap){
	
}
