//Mark Salisbury
//marks
//P8265A144.cpp
//CS 1720
/*
CS1720 Assignment 14

Put code for each program in one file and turn in the .cpp. 
A144. (Morse code again) Use the Morse Code data from the file morse.txt. Since Morse 
code consists of dots (.) and dashes (-) it is simple to represent Morse code with MorseTrees. 
Have the right pointer represent a dot, the the left pointer represent a dash.
Create a MorseTree in which the data in a node is the character represented by the order of 
dots and dashes used to reach that node. Have a separte function to create the Morse Code 
MorseTree. Then have the user enter a sentence in Morse code and have your program output the 
English translation.

*/

#include <iostream.h>
#include <iomanip.h>
#include <assert.h>
#include <fstream.h>

//*******************************************************************************
//************************|  Class MorseTreeNode  |***********************************
//*******************************************************************************

template< class NODETYPE > class MorseTree;  // forward declaration

template< class NODETYPE >
class MorseTreeNode {
   friend class MorseTree< NODETYPE >;
public:
   MorseTreeNode( const NODETYPE &d )   
      : leftPtr( 0 ), data( d ), rightPtr( 0 ) { }
   NODETYPE getData() const { return data; }
private:
   MorseTreeNode< NODETYPE > *leftPtr;  // pointer to left subMorseTree
   NODETYPE data;
   MorseTreeNode< NODETYPE > *rightPtr; // pointer to right subMorseTree
};

//*******************************************************************************
//************************|    Class MorseTree    |***********************************
//*******************************************************************************

template <class NODETYPE>
class MorseTree {
public:
   MorseTree();
   void buildMorseTree(ifstream &);
   char getLetter(char morse[]); 
   void printSentence(char morseline[]);
private:
   MorseTreeNode< NODETYPE > *rootPtr;
};

template <class NODETYPE>
MorseTree< NODETYPE >::MorseTree() { 
	rootPtr = new MorseTreeNode<NODETYPE>(0); 
}

bool readLetter(ifstream &inputfile, char & letter, char morseSeq[]){
	return bool(inputfile >> letter >> morseSeq);
}

template <class NODETYPE>
void MorseTree<NODETYPE>::buildMorseTree(ifstream &inputfile){
	char letter;
	char morseSeq[10];
	char *pos;
	MorseTreeNode<NODETYPE> *currPos;

	while (readLetter(inputfile, letter, morseSeq)){
		pos = morseSeq;
		currPos = rootPtr;
		
		do {
			if (*pos == '.'){
				if (currPos->leftPtr == 0)
					currPos->leftPtr = new MorseTreeNode<NODETYPE>(0);
				currPos = currPos->leftPtr;
			}
			else if(*pos == '-'){
				if (currPos->rightPtr == 0)
					currPos->rightPtr = new MorseTreeNode<NODETYPE>(0);
				currPos = currPos->rightPtr;
			}
			pos++;
			if (*pos == '\0') currPos->data = letter;
		} while (*pos != '\0');
	}
}

template <class NODETYPE>
char MorseTree<NODETYPE>::getLetter(char morse[]){ 
	char *pos = morse;
	MorseTreeNode<NODETYPE> *currPos = rootPtr;

	do {
		if (*pos == '.'){
			if (currPos->leftPtr == 0) return NULL;
			currPos = currPos->leftPtr;
		}
		else if(*pos == '-'){
			if (currPos->rightPtr == 0) return NULL;
			currPos = currPos->rightPtr;
		}
		pos++;
		if (*pos == '\0') return currPos->data;
	} while (*pos != '\0');
	return NULL;
}

template <class NODETYPE>
void MorseTree<NODETYPE>::printSentence(char morseline[]){ 
	int spaces = 0;
	int wordpos = 0;
	char morseword[10];
	char letter;
	int i = 0;

	do {
		if (morseline[i] == ' ' || morseline[i] == '\0'){
			spaces++;
			if (wordpos > 0){
				letter = this->getLetter(morseword);
				wordpos = 0;
				cout << letter;
				if (morseline[i] != '\0' && morseline[i + 1] == ' ')
					cout << ' ';
			}
		}		
		else {
			morseword[wordpos++] = morseline[i];
			morseword[wordpos] = '\0';
			spaces = 0;
		}

	} while (morseline[i++] != '\0');

}

void main()
{
	MorseTree < char > mTree;
	char morseline[81];
	ifstream fin("morse.txt");

	mTree.buildMorseTree( fin );
	cout << "Enter a sentence in morse code: ";
	cin.getline(morseline, 80);
	//char sentence[] = ".-   -.. --- --.   .-. .- -.   --- ...- . .-.   -- .   - --- -.. .- -.--";
	cout << "Your sentence translated into english is: " << endl;
	mTree.printSentence(morseline);
	cout << endl;

}

