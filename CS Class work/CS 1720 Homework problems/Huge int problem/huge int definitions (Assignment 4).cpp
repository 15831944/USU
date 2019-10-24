#include <iostream.h>
#include <iomanip.h>
#include <stdlib.h>
#include <math.h>
#include "huge int (Assignment 4).h"

hugeint::hugeint() { 
	number = new char[1];
	number[0] = '\0'; 
	size = 0;
}

hugeint::hugeint(int s) { 
	number = new char[s + 1];
	for (int i = 0; i < s; i++)
		number[i] = '0';
	number[s] = '\0'; 
	size = s;
}

hugeint::hugeint(const char *num){
	size = 0;
	while (num[size] != '\0')
		size++;

	number = new char[size + 1];
	for (int i = 0; i < size; i++){
		number[i] = num[i];
	}
	number[i] = '\0';
}

hugeint hugeint::operator+(const hugeint &right){
	
	int bigger = (size > right.size ? size : right.size );
	hugeint sum(bigger);
	
	int carry = 0, n, n1, n2;
	for (int i = 1; i <= bigger; i++){
		n1 = (size - i < 0 ? 0 : number[size - i] - '0');
		n2 = (right.size - i < 0 ? 0 : right.number[right.size - i] - '0');
		n = n1 + n2 + carry;
		carry = (n > 9 ? 1 : 0);
		n %= 10;
		sum.number[bigger - i] = n + '0';
	}
	
	if (carry != 0){
		hugeint temp(bigger + 1);
		for (int i = 1; i < bigger + 1; i++)
			temp.number[bigger + 1 - i] = sum.number[bigger - i];
		temp.number[0] = '1';
		
		sum = temp;
	}
	return sum;
}

hugeint hugeint::operator*(const hugeint &right){
	int length = right.size + size;
	hugeint sum(length);
	hugeint temp(length);
	int carry = 0, n, n1, n2;
	for (int i = 1; i <= size; i++){
		n1 = (size - i < 0 ? 0 : number[size - i] - '0');
		for (int j = 1; j <= right.size; j++){
			n2 = (right.size - j < 0 ? 0 : right.number[right.size - j] - '0');
			n = n1 * n2 + carry;
			carry = (n > 9 ? n / 10: 0);
			n %= 10;
			temp.number[length - j - i + 1] = n + '0';
		}
		temp.number[length - j - i + 1] = carry + '0';
		carry = 0;
		sum = sum + temp;
		temp.number[length - i] = '0';
	}
	return sum;
}

hugeint hugeint::operator/(const hugeint &denominator){
	int defprec = 7; //this means divsion estimates will be performed using the first x digits of
					   //the numerator and denominator.  It cannot be greater than 9.
	int diglftden, diglftnum;
	int nprec, dprec;
	int numpos = 0;
	
	if (denominator.size >= defprec){
		diglftden = denominator.size - defprec;
		dprec = defprec;}
	else {
		diglftden = 0;
	   dprec = size;
	}
	int subden = atoi(denominator.strseg(dprec));

	if (size >= defprec){
		diglftnum = size - defprec;
		nprec = defprec;}
	else {
		diglftnum = 0;
	   nprec = size;
	}
	numpos += nprec;
	int subnum = atoi(strseg(nprec, numpos - nprec));

	
	int panswer = subnum / subden;
	panswer /= pow(10, diglftden);

	if (panswer >= 1){
		int remainder = subnum - subden * panswer;  
}

char* hugeint::strseg(int length, int start = 0){
	char *segPtr;
	segPtr = new char[length + 1];
	for (int i = 0; i < length; i++){
		segPtr[i] = number[start + i];
	}
	segPtr[i] = '\0';
	return segPtr; 
}

hugeint hugeint::operator=(const char *num){
	
	delete [] number;
	
	size = 0;
	while (num[size] != '\0')
		size++;
	
	number = new char[size + 1];
	for (int i = 0; i < size; i++){
		number[i] = num[i];
	}
	number[i] = '\0';
	return *this;
}

hugeint hugeint::operator=(const hugeint & copy){
	size = copy.size;
	number = new char[size + 1];
	for (int i = 0; i < size; i++){
		number[i] = copy.number[i];
	}
	number[i] = '\0';
	return *this;
}

int hugeint::operator==(const hugeint & right){
	int pos1 = 0;
	while !(number[pos1] != '0' || pos1 == size)
		pos1++;
	int pos2 = 0;
	while !(right.number[pos2] != '0' || pos2 == right.size)
		pos2++;
	
	while(number[pos1] == right.number[pos2]){
		if (pos1 == size && pos2 == right.size)
			return 1;
		pos1++;
		pos2++;
	}
	return 0;
}

int hugeint::operator==(const int &){
	
}

int hugeint::stringToInt(int length = size, int pos = 0){
	int n = 0;
	if (size < 10) {
		for (int i = 0; i < length; i++){
				n += (right.number[i + pos] - '0') * pow(10, length - i); 
		}
	}
	return n;
}

ostream &operator<<( ostream &output, const hugeint & thisint){
	output << thisint.number;
	return output;
}

istream &operator>>(istream &input, hugeint & inputint){
	char temp[1000];
	input >> setw(1000) >> temp;
	inputint = temp;
	return input; 
}