#ifndef LSP_LIB_INSTRUCTURE_H
#define LSP_LIB_INSTRUCTURE_H

#include <unordered_map>
#include <string>

using std::string;
using std::unordered_map;

class Word{
	private:
		string word;
		unordered_map <string, Word*> children;
	public:
		Word(string wordofNode){
			word = wordofNode;
		}
		
		int addChild(string childWord){
			if (children.find(childWord) == children.end()){
				Word *child = new Word(childWord);
		       		children.insert(make_pair(childWord, child));
			 	return 1;
			}
			else return 0;
		}	

		Word* giveChild(string wordtoLook){
			auto childWorditr = children.find(wordtoLook);
			if (childWorditr != children.end())
				return childWorditr->second;
			else return NULL;
		}
		
		bool ischildPresent(string wordtoLook){
			auto childWordptr = children.find(wordtoLook);
			return childWordptr != children.end();
		}
};

#endif
