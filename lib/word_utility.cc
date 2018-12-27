#include "word_utility.h"

#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define ENCLOSING_SYMBOL_LEFT '{'
#define ENCLOSING_SYMBOL_RIGHT '}'
#define ENCLOSING_SYMBOL (string)"{}"

using namespace std;

string checkVarString (string theString, unsigned &index){
  string varString;
  size_t stringSize = theString.size();

  if (theString[index] != ENCLOSING_SYMBOL_LEFT)
    return varString;

  string tempString;
  for (index += 1; index < stringSize; index++){
    if(theString[index] == ENCLOSING_SYMBOL_RIGHT){
      varString = tempString;
      break;
    }

    tempString.push_back(theString[index]);
  }

  return varString;
}


pair<string, string> varMatch(string confWord, unsigned &i,
    string instWord, unsigned &instWord_index){
  pair<string, string> error_return_value = make_pair(ENCLOSING_SYMBOL,ENCLOSING_SYMBOL);

  string conf_string;
  string matched_string;
  size_t confWordSize = confWord.size();
  size_t instWordSize = instWord.size();

  if ((conf_string = checkVarString (confWord, i)).empty()){
    cerr << "ERROR:confWord is not a varString" << endl;
    return error_return_value;
  }

  if (!isdigit(instWord[instWord_index])){
    cerr << "ERROR: instWord doesn't have any digit" << endl;
    return error_return_value;
  }

  matched_string.push_back (instWord[instWord_index]);
  instWord_index++;

  if ((i + 1 < confWordSize && !isdigit(confWord[i + 1]))
      || (i + 1 == confWordSize)){
    unsigned virtInstSize = instWordSize;

    if (confWord[i + 1] == ENCLOSING_SYMBOL_LEFT) //Will make below while loop
      virtInstSize = instWord_index;    //check and push only one char(digit)
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
    else if (TheString[index] != ' ' && TheString[index] != '\t')
      break;

    index++;
  }

  return 0;
}

int lookString4 (vector <char> validChars, string theString, unsigned &index){
  size_t strSize = theString.size();

  while (index <strSize){
    for (auto validChar : validChars){
      if (validChar == theString[index])  return 1;
    }
    if (theString[index] != ' ' && theString[index] != '\t')
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
    else if (TheString[index] != ' ' && TheString[index] != '\t')
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

  if (proposedBitString[strSize - 1] != ']')
    goodGoing &= false;

  return goodGoing;
}

inline string stripBraces (string bitString){
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
    bitString = bitString.substr (strSize - newSize);
  }
  else if (strSize < newSize){
    string temp (newSize - strSize, '0');
    temp.append (bitString);
    bitString = temp;
  }

  return bitString;
}

string generateBitString (string bitStringFormat, map<string, string> varMap){
  string icode;
  map<pair<unsigned, unsigned>, string> format = parseBitStringFormat (bitStringFormat);

  for (auto cell : format){
    string string2copy;

    if (cell.first.first >= cell.first.second){
      icode.clear();
      break;
    }

    if (cell.first.second >= icode.size())
      icode.resize(cell.first.second + 1, '0');

    if (isbitString(cell.second)){
      string2copy = stripBraces (cell.second);
    }
    else {
      if (!varMap[cell.second].size()){
        icode.clear();
        break;
      }

      string2copy = num2bitString (varMap[cell.second]);
    }


    string2copy = resizeBitString (string2copy,
        cell.first.second - cell.first.first + 1);

    for (unsigned index = cell.first.first, i2 = 0;
        index <= cell.first.second && i2 < string2copy.size();
        index++, i2++){
      icode[index] = string2copy[i2];
    }

  }

  return icode;
}

bool checkBitStringFormat (string bitStringFormat){
  bool goodGoing = 1;
  size_t strSize = bitStringFormat.size();
  for (unsigned index = 0; index < strSize; index++){
    size_t processedNumSize;

    goodGoing = lookString4 ('[', bitStringFormat, index);
    goodGoing &= lookString4Digit (bitStringFormat, ++index);

    if (!goodGoing){
      break;
    }

    stoull (bitStringFormat.substr (index), &processedNumSize);
    index += processedNumSize;

    goodGoing = lookString4 ('-', bitStringFormat, index);
    goodGoing &= lookString4Digit (bitStringFormat, ++index);

    if (!goodGoing){
      break;
    }

    stoull (bitStringFormat.substr (index), &processedNumSize);
    index += processedNumSize;

    goodGoing = lookString4 (']', bitStringFormat, index);
    goodGoing &= lookString4 (':', bitStringFormat, ++index);

    if (!goodGoing){
      break;
    }

    while (isspace(bitStringFormat[++index])){
      continue;
    }

    unsigned oldIndex = index;
    while (index < strSize && bitStringFormat[index] != ' ' &&
           bitStringFormat[index] != '|' && bitStringFormat[index] != '\n')
      index++;

    if (oldIndex == index){
      goodGoing = 0;
      break;
    }

    vector <char> expectedChars = {'|', '\n'};
    int codeforLook = lookString4 (expectedChars, bitStringFormat, index);
    if (!codeforLook && index == bitStringFormat.size()){
      break;
    }
    else if (!codeforLook && index < bitStringFormat.size()){
      goodGoing = 0;
      break;
    }

  }

  return goodGoing;
}

/* vector <string> stringtostringvec (string theString):
 * takes space separated string i.e. theString,
 * puts space separated strings into a vector of strings
 * returns the generated vector of string.
 */
vector<string> stringtostringvec (string theString){
  vector<string> stringVector;
  string temp;
  for (auto character : theString){
    if (isspace(character)){
      if (temp.size() > 0){
        stringVector.push_back (temp);
      }
      temp.clear();
    }
    else temp.push_back(character);
  }

  if (temp.size() > 0){
    stringVector.push_back (temp);
  }

  return stringVector;
}
