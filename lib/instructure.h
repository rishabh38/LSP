#ifndef LSP_LIB_INSTRUCTURE_H
#define LSP_LIB_INSTRUCTURE_H



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
 * */
class Word{
  private:
    string word;
    map <string, Word*> nextWordMap;

  public:
    Word(string wordofNode);

/* addNextWord(string childWord):
 * takes a string and creates a new node with word as childWord
 * and returns location of the next node Word.
 * */
    int addNextWord(string childWord);

/* addNextWord (string MapChildWord, string childWord):
 * takes two string parameters, writes MapChildWord(string) to
 * the map string-*Word and write childWord(string) in the
 * Word being pointed to by the mapped "Word pointer".
 * returns 1 if successful else returns 0.
 * */
    int addNextWord(string MapChildWord, string childWord);

/* giveNextWord(string wordtoLook):
 * takes a string and returns the location of the child of the node
 * if present else NULL.
 * */
    Word *giveNextWord(string wordtoLook);

/* Word *addWord (string wordtoAdd):
 * takes a word(string), creates a child Word object with the same word
 * if child doesn't exist with that Word, else doesn't adds the
 * child Word.
 * returns pointer to the child Word mapped to that (string)word
 * either newly created or pre-existing.
 * */
    Word *addWord(string wordtoAdd);

/* ischildPresent(string wordtoLook):
 * takes a string and returns TRUE if given word is present as this nodes
 * child, else returns FALSE.
 * */
    bool ischildPresent(string wordtoLook);

/* string giveWord():
 * returns the word associated with the current object of Word.
 * */
    string giveWord();

 /* Word *look4word (string word, map<string, string> &varMap):
  * takes string(word), string-string map (varMap), find a
  * matching(based on prefixed rules) string in the list of
  * strings associated with string-Word* map of the current node
  * if matching string is found, returns mapped "pointer to word".
  * */
    Word *look4word (string word, map<string, string> &varMap);

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

   /* Word *addWord (string wordtoAdd):
    * takes a word(string), creates a child Word object with the same word
    * if child doesn't exist with that Word, else doesn't adds the
    * child Word.
    * returns pointer to the child Word mapped to that (string)word
    * either newly created or pre-existing.
    * */
    Word *addWord(string word);

    /* addInstruction(vector<string> stringSeq):
     * takes a vector of stirng representing sequence
     * of words, adds it to the isntructure structure
     * (which is actually a class), and returns success
     * code(int) if succeeded(i.e. it was able to add
     * new bitstring in the structure), else returns 0.
     * */
    int addInstruction(vector<string> stringSeq);

    /* checkInstruction(vector<string> stringSeq):
     * takes vector of string, and checks if there
     * exist a path from root to leaf
     * that matches the sequence of strings.
     * */
    string checkInstruction(vector<string> stringSeq);
};

#endif
