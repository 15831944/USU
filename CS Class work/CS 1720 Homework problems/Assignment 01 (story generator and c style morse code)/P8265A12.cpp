//P8265A12.CPP
//Mark Salisbury
//Assignment 1.2
//CS 1720 
/*For problems A52 and A53, have your program prompt for and read the 
phrase from the keyboard.

A52. Do the first part of exercise 5.47 on page 360 of your text, 
translating from English to Morse Code.

A53. Do the second part of exercise 5.47 on page 360 of your text, 
translating from Morse Code to English.
*/

//#include <fstream.h>
#include <iostream.h>
#include <math.h>
#include <string.h>

void loadMorseData(char [][6], char []);
void convertStringToMorse(char *, ostream &, char [][6]);
void convertMorseToString(char *, ostream &, char []);

// this data was originally contained in "morse.dat"
const char data[124][6] = {"A",".-",  "B","-...","C","-.-.","D","-..", "E",".",   "F","..-.",
						   "G","--.", "H","....","I","..",  "J",".---","K","-.-", "L",".-..",
					  	   "M","--",  "N","-.",  "O","---", "P",".--.","Q","--.-","R",".-.",
						   "S","...", "T","-",   "U","..-", "V","...-","W",".--", "X","-..-",
						   "Y","-.--","Z","--..",
					       "a",".-",  "b","-...","c","-.-.","d","-..", "e",".",   "f","..-.",
						   "g","--.", "h","....","i","..",  "j",".---","k","-.-", "l",".-..",
						   "m","--",  "n","-.",  "o","---", "p",".--.","q","--.-","r",".-.",
						   "s","...", "t","-",   "u","..-", "v","...-","w",".--", "x","-..-",
						   "y","-.--","z","--..",
						   "1",".----","2","..---","3","...--","4","....-","5",".....",
						   "6","-....","7","--...","8","---..","9","----.","0","-----" };

//ifstream fin("morse.dat");

void main(void){

	int i;
	char morsecodes[128][6];//morse sequences referenced by the ascii value of their character
	for (i = 0; i < 128; morsecodes[i++][0] = '\0'); //initialize all elements to NULL

	char characters[243];   //(3^5) letters and numbers are stored at the index of their morse value
	for (i = 0; i < 243; characters[i++] = '\0');  //initialize all elements to NULL

	loadMorseData(morsecodes, characters);

	cout << "This program converts sentences into morse code, and morse code into sentences." << endl
		 << "Punctuation will be ingnored.  When entering morse code, two or more spaces is " << endl
		 << "required to designate a space.  One space is required to begin a new letter.   " << endl
//		 << "morse.dat is required to run the program.										" << endl
		 << "Please enter a sentence or morse sequence up to 100 characters long:			" << endl;
	char sentence[101]; 
	cin.getline(sentence, 101);

	if (sentence[0] == '.' || sentence[0] == '-') 
		convertMorseToString(sentence, cout, characters);
	else
		convertStringToMorse(sentence, cout, morsecodes);
}

void loadMorseData(char lettertomorse[][6], char morsetoletter[]){

	char input[6];
	char letter;
	char *letterPtr = &letter;
	int digitvalue, morsevalue;

	//while (fin >> letter >> input){
	for (int pos = 0; pos < 124; pos+= 2){
		strcpy(letterPtr, data[pos]); 
		strcpy(input, data[pos + 1]);
		morsevalue = 0;
		for (int i = 0; input[i] != '\0'; i++){
			switch(input[i]){
			case '.': digitvalue = 1; break;
			case '-': digitvalue = 2; break;
			case ' ': digitvalue = 0; break;
			}
			morsevalue += int(digitvalue * pow(3, i));
		}
		morsetoletter[morsevalue] = letter;
		strcpy(lettertomorse[letter], input);
	}
}

void convertStringToMorse(char *sentence, ostream & output, char lettertomorse[][6]){

	for (int i = 0; sentence[i] != '\0'; i++){
		if (sentence[i] == ' ')
			output << "   ";
		else {
			output << lettertomorse[sentence[i]] << ' ';
		}
	}
	output << endl;
}

void convertMorseToString(char *sentence, ostream & output, char morsetoletter[]){
	int wordpos = 0, morsevalue = 0;
	for (int i = 0; sentence[i] != '\0'; i++){
		switch(sentence[i]){
			case '.': morsevalue += int(1 * pow(3, wordpos++)); break;
			case '-': morsevalue += int(2 * pow(3, wordpos++)); break;
			case ' ':  
				if (morsevalue != 0){
					if (morsetoletter[morsevalue] != '\0')
						output << morsetoletter[morsevalue];
					else 
						output << "Invalid morse sequence encountered." << endl;
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
	if (morsetoletter[morsevalue] != '\0')
		output << morsetoletter[morsevalue] << endl;
	else 
		output << "Invalid morse sequence encountered." << endl;
}