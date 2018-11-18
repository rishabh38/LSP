/* TO DO:
 * create implementation file for this header,
 * move all functions containing loop in them.
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
		Word(string wordofNode);

		//TEST FUNCTION
		void printWord();

		int addNextWord(string childWord);

		int addNextWord(string MapChildWord, string childWord);

		Word *giveNextWord(string wordtoLook);

		Word *addWord(string wordtoAdd);

		bool ischildPresent(string wordtoLook);

		string giveWord();

		Word *look4word (string word, map<string, string> &varMap);

		//TEST FUNCTION
		bool isitEnd();

		//TEST FUNCTION
		Word *getFirstChild();
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
		int addFirstWord(string firstWord);

		/* giveFirstWord(string wordtoLook):
		 * takes string wordtoLook, if there is a child
		 * Word of the root containing wordtoLook
		 * word in it, then returns the locatin of
		 * the child Word, else returns NULL.
		 * */
		Word *giveFirstWord(string wordtoLook);

		Word *addWord(string word);

		/* addInstruction(vector<string> stringSeq):
		 * takes a vector of stirng representing sequence
		 * of words, adds it to the isntructure structure
		 * (which is actually a class), and returns success
		 * code(int) if succeeded(i.e. it was able to add
		 * new bitstring in the structure), else returns 0.
		 * */
		int addInstruction(vector<string> stringSeq);

		//TEST FUNCTION
		void testprintInst();

		/* checkInstruction(vector<string> stringSeq):
		 * takes vector of string, and checks if there
		 * exist a path from root to leaf
		 * that matches the sequence of strings.
		 * */
		string checkInstruction(vector<string> stringSeq);
};

#endif
