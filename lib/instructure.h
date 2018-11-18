/* TO DO:
 * create implementation file for this header,
 * move all functions containing loop in them.
 * Create separate header files for functions that are
 * not member of any class.
 */

#ifndef LSP_LIB_INSTRUCTURE_H
#define LSP_LIB_INSTRUCTURE_H


#include "word_utility.h"


#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

/* class Word:
 * this class stores a string element and stores mapping between
 * words of next nodes and location of next nodes which are children
 * of the given node.
 *
 * Operations:
 * Constructor: takes a string to store in its string element.
 *
 * addNextWord(string childWord):
 * takes a string and creates a new node with word as childWord
 * and returns location of the next node Word.
 *
 * giveNextWord(string wordtoLook):
 * takes a string and returns the location of the child of the node
 * if present else NULL.
 *
 * ischildPresent(string wordtoLook):
 * takes a string and returns TRUE if given word is present as this nodes
 * child, else returns FALSE.
 *
 *
 * */
class Word{
	private:
		string word;
		map <string, Word*> nextWordMap;

	public:
		Word(string wordofNode){
			word = wordofNode;
		}

//FOR TESTING PURPOSES
		inline void printWord(){
			cout << this->word;
		}

		int addNextWord(string childWord){
			if (nextWordMap.find(childWord) == nextWordMap.end()){
					Word *nextWordNode = new Word(childWord);
		   		nextWordMap.insert(make_pair(childWord, nextWordNode));
			 		return 1;
				}
			else return 0;
		}

		int addNextWord(string MapChildWord, string childWord){
			if (nextWordMap.find(MapChildWord) == nextWordMap.end()){
				Word *nextWordNode = new Word(childWord);
		       		nextWordMap.insert(make_pair(MapChildWord, nextWordNode));
			 	return 1;
			}
			else return 0;
		}

		Word *giveNextWord(string wordtoLook){
			auto childWorditr = nextWordMap.find(wordtoLook);
			if (childWorditr != nextWordMap.end())
				return childWorditr->second;
			else return NULL;
		}

		Word *addWord(string wordtoAdd){
			this->addNextWord(wordtoAdd);
			return this->giveNextWord(wordtoAdd);
		}

		bool ischildPresent(string wordtoLook){
			auto nextWordptr = nextWordMap.find(wordtoLook);
			return nextWordptr != nextWordMap.end();
		}

		string giveWord(){
			return word;
		}

		Word *look4word (string word, map<string, string> &varMap){
			Word *nextNode = NULL;

			for (auto& nextWord : this->nextWordMap){
				map <string, string> temp;

				if (wordMatch (nextWord.first, word, temp)){
					nextNode = nextWord.second;

					varMap.insert (temp.begin(), temp.end());
					break;
				}
			}
			return nextNode;
		}



//FOR TESTING PURPOSES ONLY
		bool isitEnd(){
			if(this->nextWordMap.begin() == this->nextWordMap.end())
				return 1;

			return 0;
		}

//FOR TESTING PURPOSES ONLY
		Word *getFirstChild(){
			cout << "nextWordMap size :" << this->nextWordMap.size() << endl;
			cout << endl;

			auto temp = this->nextWordMap.begin();
			if (++temp != this->nextWordMap.end()){
				cout << temp->first << ": ";
				return temp->second;
			}
			cout << (this->nextWordMap.begin())->first << ": ";
			return (this->nextWordMap.begin())->second;
		}
};



class instructure{
	private:
		map<string, Word*> firstWordMap;
	public:
		/* addFirstWord(string firstWord):
		 * takes firstWord, creates new child Word with word = firstWord.
		 * returns True if there wasn't a child with that word,
		 * else returns False.
		 * */
		int addFirstWord(string firstWord){
			auto ptrtoFirstWord = new Word(firstWord);

			if (firstWordMap.find(firstWord) == firstWordMap.end()){
				firstWordMap.insert(make_pair(firstWord, ptrtoFirstWord));
				return 1;
			}
			else return 0;
		}

		/* giveFirstWord(string wordtoLook):
		 * takes string wordtoLook, if there is a child
		 * Word of the root containing wordtoLook
		 * word in it, then returns the locatin of
		 * the child Word, else returns NULL.
		 * */
		Word *giveFirstWord(string wordtoLook){
			auto nextWordItr = firstWordMap.find(wordtoLook);
			if (nextWordItr != firstWordMap.end())
				return nextWordItr->second;
			else return NULL;
		}

		Word *addWord(string word){
			this->addFirstWord(word);
			return this->giveFirstWord(word);
		}

		/* addInstruction(vector<string> stringSeq):
		 * takes a vector of stirng representing sequence
		 * of words, adds it to the isntructure structure
		 * (which is actually a class), and returns success
		 * code(int) if succeeded(i.e. it was able to add
		 * new bitstring in the structure), else returns 0.
		 * */
		int addInstruction(vector<string> stringSeq){
			if(stringSeq.size() <= 1){
				cout << "ERROR:" << endl;
				cout << "string sequence too short" << endl;
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

//FOR TESTING PURPOSES ONLY
		void testprintInst(){
			if (this->firstWordMap.begin() == this->firstWordMap.end())
				return;

			cout << "firstWordMap size: " << firstWordMap.size() << endl;

			Word *WordIter = (this->firstWordMap.begin())->second;
			WordIter->printWord();
			cout << " ";

			while(!WordIter->isitEnd()){
				WordIter = WordIter->getFirstChild();
				WordIter->printWord();
				cout << " ";
			}

			cout << endl;
		}


		/* checkInstruction(vector<string> stringSeq):
		 * takes vector of string, and checks if there
		 * exist a path from root to leaf
		 * that matches the sequence of strings.
		 * */
		string checkInstruction(vector<string> stringSeq){
			if (stringSeq.size() < 2){
				cout << "Invalid instruction" << endl;
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
						cout << "Invalid instruction" << endl;
						return "EII";
			}

		//	return getBitString (nodeBeingMatched->giveWord(), varMap);
		return nodeBeingMatched->giveWord();
		}
	};

#endif
