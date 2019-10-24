// 362
// marks
// Mark Salisbury
// P362A131.cpp
/*
A131. (Simple Encryption) some information on the Internet may be encrypted 
with a simple algorithm know as "rot13"--which rotates each character by 13
positions in the alphabet. thus, 'a' corresponds to 'n', 'x' corresponds to 
'k';. rot13 is an example of symmetric key encryption. With symmetric key 
encryption, both the encrypter and decrypter use the same key. Punctuation 
is not encrypted but is carried with the text. Capital letter are modified 
to lowercase letters before the encryption occurs. The encryption and 
decryption take place by determining if the character is alphabetic and if 
it is, making it a lowercase letter, then rotating its ascii value with a % 
operator. Care must be taken in this so the rotation produces the ascii 
value of a letter. The ascii value of a letter is an integer, you can add 
and subtract from this value to get it into the range you want and then add 
or subtract to it to make it again a valid letter. Please refer to problem 
19.7 of your text.

    Write a program that will encrypt or decrypt a message using rot13. 
Have your program prompt for the filename of the file to encrypt and then 
prompt for the filename of the file to which your program will write the 
encrypted message. Your message file should be about 1/2 page long. The 
file message.txt will serve as an example but your program must work with 
any text file..*/

#include <fstream.h>
#include <ctype.h>

void encrypt(istream &input, ostream &output);
void showfile(istream &input);

void main(void){
	
	char filename1[20];
	char filename2[20];

	cout << "Enter the file you wish to encrypt / decrypt: ";
	cin >> filename1;
	cout << "Enter the file you wish to output to: ";
	cin >> filename2;
	
	ifstream fin(filename1);
	ofstream fout(filename2);

	encrypt(fin, fout);

	fin.close();
	fout.close();

}
void encrypt(istream &input, ostream &output){

	
	char c;
	while (input.get(c)){
		c = tolower(c);
		if (isalpha(c)){
			c = (c - 'a' + 13) % 26 + 'a';
		}
		output << c;
		cout << c;
	}
}

