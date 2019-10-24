#include <string>
#include <fstream>
#include <iostream>

using namespace std;

char* convertStr(string s)
{
   int i;
   char* tempPtr = new char[s.length() + 1]; 
	for (i = 0; i < s.length(); i++)
		tempPtr[i] = s[i];
	tempPtr[i] = '\0';
   return tempPtr;
}

void readFile(istream & input)
{
   string word;   
   while (input >> word)	
		cout << word << " contains " << word.length() << " characters." << endl;
}

void main(void){
	string sfilename;
	cout << "Which file contains the data? ";
	cin >> sfilename;
	char *cfilename = new char[sfilename.length() + 1]; 
	cfilename = convertStr(sfilename);
	ifstream infile(cfilename);
	readFile(infile);
	infile.close();
}