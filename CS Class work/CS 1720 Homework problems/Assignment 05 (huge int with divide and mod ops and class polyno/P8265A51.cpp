//Mark Salisbury
//marks
//P8265A51.cpp
//CS 1720
/* 
A51. Use your HugeInt class  and overload the /, the division operator, and %, the mod operator. 
The result of the / and % are also HugeInt's. You can limit the class so that you only work with 
positive HugeInts's. All of the example programs can be downloaded from http://www.deitel.com

The files from Figure 8 can also be downloaded here:

Fig08_08.cpp    Your client program must completely test the / and %.
Hugeint1.cpp
Hugeint1.h

Put these three files into one file as we have in the past.
Be sure to make I/O easy and intuitive.
*/

#include <iostream.h>
#include <string.h>
#include <stdlib.h>

const int maxsize = 100; // max. number of digits for a huge int
#define divide	1
#define mod		0

class hugeint {
	friend ostream & operator<<(ostream &, const hugeint &);
	friend istream & operator>>(istream &, hugeint &);
public:
	hugeint();     
	hugeint(const char *);
	hugeint(const int);
	hugeint & operator=(const hugeint &);
	hugeint operator+( const hugeint &) const ;
	hugeint operator-( const hugeint &) const ;
	hugeint operator*( const hugeint &) const ;
	hugeint operator/( const hugeint &) const ;
	hugeint operator%( const hugeint &) const ;
	int operator<( const hugeint &) const ;
	int operator==( const hugeint &) const ;
	int operator>( const hugeint &) const ;
	int operator!=( const hugeint &) const ;
	int operator>=( const hugeint &) const ;
	int operator<=( const hugeint &) const ;
private:
	//hugeint subnum(int, int = -1) const;
	int hitoi() const;
	hugeint addzeros(const hugeint &, int) const;
	hugeint divideormod(const hugeint &, int) const;
	int digits;
	char *num;
	int isNeg() const;
};

ostream & operator<<(ostream & output, const hugeint &right){
	if (right.num[0] == '-')
		output << '-';

	for (int i = right.digits; i > 0; i--){
		if (i % 3 == 0 && i != right.digits)
			output << "," << right.num[i];
		else
			output << right.num[i];
	}
	return output;

}

istream& operator>>(istream & input, hugeint &right){
	char buff[maxsize + 1];
	
	input >> buff;
	hugeint temp(buff);
	right = temp;
	return input;
}

hugeint::hugeint(){
	digits = 1;
	num = new char[maxsize + 1];
	for (int i = 1; i < maxsize + 1; i++)
		num[i] = '0';
}

hugeint::hugeint(const char *number){
	char *temp;
	num = new char[maxsize + 1];
	for (int i = 1; i < maxsize + 1; i++)
		num[i] = '0';
	temp = new char[strlen(number)];
	strcpy(temp, number);
	
	digits = strlen(temp);
	int l = digits - 1;
	i = 1;

	while (l >= 0)
		num[i++] = temp[l--];
	
	if (num[i - 1] == '-'){
		num[0] = '-';
		digits--;
	}
	i = 0;
	while (temp[i++] == '0' && digits != 1)
		digits--; 
}

hugeint::hugeint(const int n){
	int number = n;  
	num = new char[maxsize + 1];
	for (int i = 1; i < maxsize + 1; i++)
		num[i] = '0';

	if (number < 0){
		num[0] = '-';
		number *= -1;
	}
	else if( number == 0){
		num[1] = '0';
		digits = 1;
	}

	for (i = 1; number > 0; i++){
		num[i] = number % 10 + '0';
		number /= 10;
		digits = i;
	}
}
        
hugeint & hugeint::operator=( const hugeint &right){
	if (&right != this){
		delete [] num;
		digits = right.digits;
		num = new char[maxsize + 1];
		strcpy(num, right.num);
	}
	return *this;
}

hugeint hugeint::operator+( const hugeint &right) const {
	int i = 1;
	int num1 = 0, num2 = 0;
	int sum = 0, carry = 0;
	hugeint temp, tempa;
	
	if ( right.isNeg() && (!isNeg())){  // a + -b
		tempa = right;
		tempa.num[0] = '+';
		temp = *this - tempa;	
	}
	else if( isNeg() && !right.isNeg()){  // -a + b
		tempa = *this;
		tempa.num[0] = '+';
		temp = right - tempa;	
	}
	else{
		if (right.isNeg() && isNeg())   // -a + -b
			temp.num[0] = '-';

		while (i <= digits || i <= right.digits ){
			num1 = (i > digits ? 0: num[i] - '0');
			num2 = (i > right.digits ? 0: right.num[i] - '0');

			sum = num1 + num2 + carry;
			carry = 0;
			if (sum > 9){
				carry = 1;
				sum -= 10;
			}

			temp.num[i] = '0' + sum; 
			temp.digits = i; 
			i++;
					
		}
		if (carry == 1){
			temp.digits++;
			temp.num[i] = '1';
		}
	}
	return temp;

}

hugeint hugeint::operator-( const hugeint &right) const {
	int i = 1;
	int num1 = 0, num2 = 0;
	int sum = 0, subtract = 0;
	hugeint temp, tempa, tempb;

	if (!isNeg() && right.isNeg()){  //left is pos, right is negative a - (-b)
		tempa = right;
		tempa.num[0] = '+';
		temp = *this + tempa;	
	}
	else if( isNeg() && !right.isNeg()){ // left is neg, right is positive  -a - b
		tempa = *this;
		tempa.num[0] = '+';
		temp = tempa + right;
		temp.num[0] = '-';
	}
	else if ( isNeg() && right.isNeg()){ // left is neg, right is negative  -a - (-b)
			tempa = *this;
			tempb = right;
			tempa.num[0] = '+';
			tempb.num[0] = '+';
			temp = tempb - tempa;
	}
	else if (right > *this){ // both are positive, but the right operand is greater than the left
		tempa = *this;
		temp = right - tempa;
		temp.num[0] = '-';	
	}
	else{
		
		while (i <= digits || i <= right.digits ){
			num1 = (i > digits ? 0: num[i] - '0');
			num2 = (i > right.digits ? 0: right.num[i] - '0');

			num1 -= subtract;
			subtract = 0;

			if (num2 > num1){
				subtract = 1;
				num1 += 10;
			}
			sum = num1 - num2;
			if (sum != 0) {
				temp.num[i] = '0' + sum; 
				temp.digits = i; 
			}
			i++;
		}
	}
	return temp;
}

hugeint hugeint::operator*( const hugeint & right) const {

	hugeint temp, tempa;
	int product;
	int carry = 0;
	int p;
	int bnum;

	for (int i = 1; i <= digits; i++){
		bnum = (num[i] - '0');
		for (p = 1; p <= right.digits && bnum != 0; p++){
			product = bnum * (right.num[p] - '0') + carry;
			
			carry = 0;
			if (product > 9){
				carry = product / 10;
				product %= 10;
			}
			
			if (product != 0 || carry != 0) {
				temp.digits = p + i - 1;
				temp.num[p + i - 1] = '0' + product;
			}
		}
		if (carry != 0){
			temp.digits++;
			temp.num[p + i - 1] = '0' + carry;
			carry = 0;
		}
		tempa = tempa + temp;
		temp = 0;
	}

	if (isNeg() ^ right.isNeg())
		tempa.num[0] = '-';

	return tempa;
}

hugeint hugeint::operator/( const hugeint & divisor) const {
	return divideormod(divisor, divide); 
}

hugeint hugeint::operator%( const hugeint & divisor) const {
	return divideormod(divisor, mod); 
}

hugeint hugeint::divideormod(const hugeint & div, int action) const{

	hugeint remainder;
	remainder = *this;
	hugeint divisor;
	divisor = div;

	hugeint quotient(0);
	hugeint tquotient(0);
	hugeint tdivisor(0);
	char sign = '+';

	if (isNeg() ^ div.isNeg())
		sign = '-';

	if (isNeg())
		remainder.num[0] = '+';
	if (div.isNeg())
		divisor.num[0] = '+';

	int guess = 0;
	int digstq, digsq;
	int xzeros = remainder.digits - divisor.digits;
	
	while (xzeros >= 0){
		tdivisor = addzeros(divisor, xzeros);
		
		if (remainder.digits < tdivisor.digits)
			guess = 0;
		else
			guess = ((remainder.digits > 8 && tdivisor.digits > 7 && remainder.digits > tdivisor.digits) ? 10 : 1) * remainder.hitoi() / tdivisor.hitoi();
		
		if (guess == 10) guess = 9;
		
		if (guess != 0){
			digstq = tquotient.digits;
			digsq = quotient.digits;
			quotient.num[xzeros + 1] = guess + '0';
			tquotient.num[xzeros + 1] = guess + '0';
			tquotient.digits = xzeros + 1;
			if (quotient == hugeint(0))
				quotient.digits = xzeros + 1;
		}
		// now check.  The guess could be off by one if the dividend and divisor are both very long
		if (remainder - (tquotient * divisor) >= tdivisor){ //this is not the correct guess
			quotient.num[xzeros + 1] = guess + 1 + '0';
			tquotient.num[xzeros + 1] = guess + 1 + '0';
			if (guess == 9) // this should not happen unless something is logically wrong
				cout << "This program needs to be debugged. (1)" << endl;
		}
		else if (remainder - (tquotient * divisor) < 0){
			quotient.num[xzeros + 1] = guess - 1 + '0';
			tquotient.num[xzeros + 1] = guess - 1 + '0';
			if (guess == 1){
				tquotient.digits = digstq;
				quotient.digits = digsq;
			}
			if (guess == 0) // this should not happen unless something is logically wrong
				cout << "This program needs to be debugged. (2)" << endl;
		}
		remainder = remainder - tquotient * divisor;
		xzeros--;
		tquotient = 0;
	}
	
	quotient.num[0] = sign;   // the quotient receives a negative sign now if either but not both
							 // the divident and divisor are negative.
	if (isNeg())				//the remainder is negative if the dividend is negative.
		remainder.num[0] = '-';

	if (action == divide)
		return quotient;
	else
		return remainder;

}

 //equality operators
int hugeint::operator<( const hugeint & right) const {
	if (isNeg()){// left side is negative						
		if (!right.isNeg())// right side is positive
			return true;                    
		else if (right.digits != digits) //right side is also negative, and has fewer digits
			return (right.digits < digits );
		else { // same number of digits
			for (int i = digits; i > 0; i--){
				if (num[i] != right.num[i])
					return (num[i] < right.num[i]);
			}
		}
		return false;
	}
	else {
		if (right.isNeg())
			return false;
		else if (right.digits != digits)//number of digits do not match
			return (digits < right.digits);
		else if (*this == right)// test for self comparison
			return false;
		else {
			for (int i = digits; i > 0; i--){
				if (num[i] != right.num[i])
					return (num[i] < right.num[i]);
			}
		}
		return true;
	}
}

int hugeint::operator==( const hugeint & right) const {
	if ((isNeg() && !right.isNeg()) || (!isNeg() && right.isNeg()))// sides have different signs				
		return false;                    
	else if (right.digits != digits) //different number of digits
		return false;
	else {
		for (int i = digits; i > 0; i--)
			if (num[i] != right.num[i])
				return false;
	}
	
	return true;
}
	
int hugeint::operator>( const hugeint & right) const { return !(*this < right || *this == right); }

int hugeint::operator!=( const hugeint & right) const { return !(*this == right); }

int hugeint::operator>=( const hugeint & right) const { return !(*this < right); }

int hugeint::operator<=( const hugeint & right) const { return (*this < right || *this == right); }

int hugeint::hitoi() const{ //hugeint to integer
	int number = 0;
	for (int p = 0; p < digits && p < 8; p++){
		number *= 10;
		number += (num[digits - p] - '0');
	}
	return number;

}

hugeint hugeint::addzeros(const hugeint &ahugeint, int zerostoadd) const{
	hugeint temphugeint(0);
	int newdigits = ahugeint.digits + zerostoadd;
	temphugeint.digits = newdigits;
	for (int i = 0; i < newdigits || i < 9; i++){
		if ( i < ahugeint.digits)
			temphugeint.num[newdigits - i] = ahugeint.num[ahugeint.digits - i];
		}
	return temphugeint;
}

int hugeint::isNeg() const { return (num[0] == '-');}

void main(){
	hugeint a;
	hugeint b;
	
	cout << "Enter a huge int a: (can be positive or negative) ";
	cin >> a;

	cout << "Enter a huge int b: (can be positive or negative) ";
	cin >> b;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
		
	cout << "a + b = " << a + b << endl;
	cout << "a - b = " << a - b << endl;
	cout << "a * b = " << a * b << endl;
	hugeint c;
	c = a / b;
	cout << "c = a / b" << endl;
	cout << "c = " << c << endl;
	hugeint d;
	d = a % b;
	cout << "d = a % b" << endl;
	cout << "d = " << d << endl;
	cout << "b * c + d = a is " << (b * c + d == a ? "true" : "false" ) << " (this should always be true)." << endl;
	cout << "d < b is " << (d < b ? "true" : "false") << " (this should always be true)." << endl;
	cout << "a > b is " << (a > b ? "true" : "false") << endl;
	cout << "a < b is " << (a < b ? "true" : "false") << endl;
	cout << "a == b is " << (a == b ? "true" : "false") << endl;
	cout << "a != b is " << (a != b ? "true" : "false") << endl;
	cout << "a >= b is " << (a >= b ? "true" : "false") << endl;
	cout << "a <= b is " << (a <= b ? "true" : "false") << endl;
	
}

