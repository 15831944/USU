//P8265A11.CPP
//Mark Salisbury
//Assignment 1.1
//CS 1720
/*
CS1720 Assignment 1: Using C style strings

See Page 161 to learn how to use the internal time clock to 
initialize the rand() function.

For all problems in Assignment 1 you must use C style strings.
DO NOT USE THE STRING CLASS!!

A51. Do exercise 5.33 on page 356 of your text. (Creating sentences)
*/


#include <stdlib.h>
#include <iostream.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

enum PartsOfSpeech {article, noun, verb, preposition};

const int yes = 1;
const int no = 0;
char *art[10] = {"a","a","a","the","the","one","some","another","every","each"};
char *nou[9] = {"boy","girl","dog","town","car", "book","pizza","computer","spider"};
char *ver[7] = {"drove","jumped","ran","walked","skipped","ate","destroyed"};
char *pre[8] = {"to","from","over","under","on","before","around","on top of"};
const int maxitems[4] = {10,9,7,8};

char *getword(PartsOfSpeech wordtype){
	int n = rand() % maxitems[wordtype];
	
	switch(wordtype){
		case article: return art[n];
		case noun: return nou[n];
		case verb: return ver[n]; 
		case preposition: return pre[n]; 
	}
	return NULL;
}

char* addword(char *str1, char *str2, int capital = no){
	char tempPtr[40];
	if (capital == yes){
		strcpy(tempPtr, "  ");
	str2[0] = char(toupper(str2[0]));
	}
	else
		strcpy(tempPtr, " ");
	
	strcat(str1, tempPtr);
	return strcat(str1, str2);
}

void generateSentence(int numSentences = 1){
	char *sentence;
	char period[] = ".";
	char tempWord[20];
	PartsOfSpeech wordSequence[6] = {article, noun, verb, preposition, article, noun};
	
	for (int iteration = 0; iteration < numSentences; iteration++){
		sentence = new char[100];
		sentence[0] = '\0';
		for (int i = 0; i < 6; i++){
			strcpy(tempWord, getword(wordSequence[i]));
			addword(sentence, tempWord, (i == 0 ? yes : no));
		}
		strcat(sentence, period); 
		cout << sentence;
		delete [] sentence;
	}
}

void main(void){
	srand(time(0));
	generateSentence(5);
	cout << endl;
	generateSentence(5);
	cout << endl;
}



