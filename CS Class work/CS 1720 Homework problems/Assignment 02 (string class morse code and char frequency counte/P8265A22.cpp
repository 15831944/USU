//P8265A22.CPP
//Mark Salisbury
//Assignment 2.2
//CS 1720 
/*
CS1720 Assignment 2    The string class

You must use the string class  to solve these problems. Do not use Cstyle 
strings!

A21. Do the   (english -> morse) conversion using the string class.  
Implement the translation using  a table lookup to locate the
correct morse for a particular character. Take your input from a 
file A21.dat and write the morse conversion to the screen. Use
the full screen for your output. Convert all lowercase letters 
to uppercase before analyzing them. Submit just the .cpp file

A22. Do the   (morse -> english) conversion using the string class.  
Implement the translation using  a table lookup to locate the
correct character for a particular morse code. Take your input 
from a file A22.dat and write the english conversion to the
screen.   Submit just the .cpp file.
*/
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

void loadMorseData(string [], string []);
void convertStringToMorse(string, string [], ostream & = cout);
void convertMorseToString(string, string [], ostream & = cout);

const string data[124] =  {"a",".-",  "b","-...","c","-.-.","d","-..", "e",".",   "f","..-.",
						   "g","--.", "h","....","i","..",  "j",".---","k","-.-", "l",".-..",
						   "m","--",  "n","-.",  "o","---", "p",".--.","q","--.-","r",".-.",
						   "s","...", "t","-",   "u","..-", "v","...-","w",".--", "x","-..-",
						   "y","-.--","z","--..",
						   "A",".-",  "B","-...","C","-.-.","D","-..", "E",".",   "F","..-.",
						   "G","--.", "H","....","I","..",  "J",".---","K","-.-", "L",".-..",
					  	   "M","--",  "N","-.",  "O","---", "P",".--.","Q","--.-","R",".-.",
						   "S","...", "T","-",   "U","..-", "V","...-","W",".--", "X","-..-",
						   "Y","-.--","Z","--..",
						   "1",".----","2","..---","3","...--","4","....-","5",".....",
						   "6","-....","7","--...","8","---..","9","----.","0","-----" };
			   
void main(void){

	
	string morsecodes[128];//morse sequences referenced by the ascii value of their character
	string characters[243];   //(3^5) letters and numbers are stored at the index of their morse value
	
	loadMorseData(morsecodes, characters);

	
	cout << "This program converts sentences into morse code, and morse code into sentences." << endl
		 << "Punctuation will be ingnored.  When entering morse code, two or more spaces is " << endl
		 << "required to designate a new word.  One space is required to begin a new letter." << endl
		 << "a '.' or a '*' is recognized as a dot, a '-' or a '_' is recognized as a dash. " << endl
		 << "Enter the name of the file to convert: ";
	char filename[20];
	cin >> filename;
	
	ifstream fin(filename);
	string sentence; 
	getline(fin, sentence);

	int isEnglish = false;
	for (int i = 0; i < sentence.length() && isEnglish == false; i++){
		if (isalpha(sentence[i]))
			isEnglish = true;
	}

	if (isEnglish){
		convertStringToMorse(sentence, morsecodes);
		while (getline(fin, sentence))
			convertStringToMorse(sentence, morsecodes);
	}
	else{
		convertMorseToString(sentence, characters);
		while (getline(fin, sentence))
			convertMorseToString(sentence, characters);				
	}	
}

void loadMorseData(string lettertomorse[], string morsetoletter[]){

	string input;
	string letter;
	int digitvalue, morsevalue;

	for (int pos = 0; pos < 124; pos+= 2){
		letter = data[pos];
		input = data[pos + 1];
		morsevalue = 0;
		for (unsigned int i = 0; i < input.length(); i++){
			switch(input[i]){ 
			case '.': digitvalue = 1; break;
			case '-': digitvalue = 2; break;
			case ' ': digitvalue = 0; break;
			case '\0': digitvalue = 0; break;
			}
			morsevalue += int(digitvalue * pow(3, i));
		}
		morsetoletter[morsevalue] = letter;
		lettertomorse[letter[0]] = input; 

	}
}

void convertStringToMorse(string sentence, string lettertomorse[], ostream & output){
	for (int i = 0; i < sentence.length(); i++){
		if (sentence[i] == ' ')
			output << "   ";
		else {
			output << lettertomorse[sentence[i]] << ' ';
		}
	}
	output << endl;
}

void convertMorseToString(string sentence, string morsetoletter[], ostream & output){
	int wordpos = 0, morsevalue = 0;
	for (int i = 0; i < sentence.length(); i++){
		switch(sentence[i]){
		case '.': case '*': morsevalue += int(1 * pow(3, wordpos++)); break;
		case '-': case '_': morsevalue += int(2 * pow(3, wordpos++)); break;
			case ' ':  
				if (morsevalue != 0){
					if (morsetoletter[morsevalue] != "")
						output << morsetoletter[morsevalue];
					else 
						output << "?";
					morsevalue = 0;
					wordpos = 0;
				}
				else if (sentence[i + 1] != ' ')
					output << ' ';
				break;
			default:
				output << "Non-morse character encountered." << endl;
		}
	}
	if (morsevalue != 0)
		if (morsetoletter[morsevalue] != "")
			output << morsetoletter[morsevalue] << endl;
		else 
			output << "Invalid morse sequence encountered." << endl;
	output << endl;
}
