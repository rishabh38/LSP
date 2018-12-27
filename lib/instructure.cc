#include "instructure.h"
#include "word_utility.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

Word::Word(string wordofNode){
  word = wordofNode;
}

int Word::addNextWord(string childWord){
  if (nextWordMap.find(childWord) == nextWordMap.end()){
      Word *nextWordNode = new Word(childWord);
      nextWordMap.insert(make_pair(childWord, nextWordNode));
      return 1;
    }
  else return 0;
}

int Word::addNextWord(string MapChildWord, string childWord){
  if (nextWordMap.find(MapChildWord) == nextWordMap.end()){
    Word *nextWordNode = new Word(childWord);
          nextWordMap.insert(make_pair(MapChildWord, nextWordNode));
    return 1;
  }
  else return 0;
}

Word* Word::giveNextWord(string wordtoLook){
  auto childWorditr = nextWordMap.find(wordtoLook);
  if (childWorditr != nextWordMap.end())
    return childWorditr->second;
  else return NULL;
}

Word* Word::addWord(string wordtoAdd){
  this->addNextWord(wordtoAdd);
  return this->giveNextWord(wordtoAdd);
}

bool Word::ischildPresent(string wordtoLook){
  auto nextWordptr = nextWordMap.find(wordtoLook);
  return nextWordptr != nextWordMap.end();
}

string Word::giveWord(){
  return word;
}


Word* Word::look4word (string word, map<string, string> &varMap){
  Word *nextNode = NULL;

  for (auto& nextWord : nextWordMap){
    map <string, string> temp;

    if (wordMatch (nextWord.first, word, temp)){
      nextNode = nextWord.second;

      varMap.insert (temp.begin(), temp.end());
      break;
    }
  }
  return nextNode;
}


int instructure::addFirstWord(string firstWord){
  auto ptrtoFirstWord = new Word(firstWord);

  if (firstWordMap.find(firstWord) == firstWordMap.end()){
    firstWordMap.insert(make_pair(firstWord, ptrtoFirstWord));
    return 1;
  }
  else return 0;
}

Word* instructure::giveFirstWord(string wordtoLook){
  auto nextWordItr = firstWordMap.find(wordtoLook);
  if (nextWordItr != firstWordMap.end())
    return nextWordItr->second;
  else return NULL;
}


Word* instructure::addWord(string word){
  this->addFirstWord(word);
  return this->giveFirstWord(word);
}

int instructure::addInstruction(vector<string> stringSeq){
  if(stringSeq.size() <= 1){
    cerr << "ERROR:" << endl;
    cerr << "string sequence too short" << endl;
    return 0;
  }

  Word *wordIter = this->addWord(stringSeq[0]);

  size_t index;
  for (index = 1; index < stringSeq.size() - 2; index++){
    wordIter = wordIter->addWord(stringSeq[index]);
  }

  wordIter->addNextWord("BitString", stringSeq[index + 1]);

  return 1;
}


string instructure::checkInstruction(vector<string> stringSeq){
  if (!stringSeq.size()){
    cerr << "Invalid instruction" << endl;
    return "EII";
  }

  Word *nodeBeingMatched = NULL;
  map<string, string> varMap;

  for (auto nextWord : firstWordMap){
     map <string, string> temp;

    if (wordMatch (nextWord.first, stringSeq[0], temp)){
      nodeBeingMatched = nextWord.second;

      varMap.insert (temp.begin(), temp.end());
      break;
    }
  }

  for (unsigned i = 1; i < stringSeq.size(); i++){
    if (!nodeBeingMatched)
      break;

    nodeBeingMatched = nodeBeingMatched->look4word(stringSeq[i], varMap);
  }

  if ((!nodeBeingMatched) || (nodeBeingMatched &&
      !(nodeBeingMatched = nodeBeingMatched->look4word("BitString", varMap)))){
        cerr << "Invalid instruction" << endl;
        return "EII";
  }

  return generateBitString (nodeBeingMatched->giveWord(), varMap);
}
