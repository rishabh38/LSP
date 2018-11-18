
#include "word_utility.h"

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
