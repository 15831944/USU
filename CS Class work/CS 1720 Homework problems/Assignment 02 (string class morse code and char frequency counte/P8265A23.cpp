//P8265A23.CPP
//Mark Salisbury
//Assignment 2.3
//CS 1720 
//Enter the name of the file
//count the occurences of each letter in the file
//output the results to the screen

#include <fstream.h>
#include <string.h>
#include <ctype.h>
#include <iomanip.h>

void main(){

	double charFreq[128] = {0};
	char filename[20];
		
	cout << "Enter the name of the file to analyze: ";
	cin >> filename;

	ifstream fin(filename);
	
	char linedata[80];
	char c;
	double totalchars = 0;

	while (fin.getline(linedata, 80)){
		for (int i = 0; i < 80; i++){
			c = linedata[i];
			if (isalpha(c)){
				c = tolower(c);
				charFreq[c]++;
				totalchars++;
			}
		}
	}
	
	cout << "The total alphabetic character count in " << filename << " is: " << totalchars << endl;
	cout << "The frequency of individual characters in " << filename << " is: " << endl;
	for (char i = 'a'; i <= 'z'; i+= 2)
		cout << setiosflags( ios:: fixed) 
			 << i << " = " << setw(5) << setprecision(2) 
		     << charFreq[i] / totalchars * 100 << "%   "
	         << char( i + 1 ) << " = " << setw(5) << setprecision(2) 
			 << charFreq[i + 1] / totalchars * 100 << '%' << endl;

}