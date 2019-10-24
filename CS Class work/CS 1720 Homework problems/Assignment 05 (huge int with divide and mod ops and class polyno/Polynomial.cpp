/*
A52.  {similiar to 8.19} Develop class Polynomial. The internal representation of a 
Polynomial is an array of terms. Each term contains a coefficient and an exponent. 
The term (a struct, thus the attribute of your class should be an array of struct.)
(what for???????) 
Allow for up to 20 terms.

2.45x4

has a coefficient of 2.45 (a double) and an exponent of 4 (and int). Develop a full 
class containing proper constructor and destructor functions as well as set and get 
(what for????????)
functions. The class should also provide the following overloaded operator capabilities:

a. Overload the addition operator (+) to add two Polynomials.
b. Provide a value function that will evaluate the polynomial for a given  value of x.
  
Write a client program that will completely test your class.

Be sure to make I/O easy and intuitive.
*/

#include <iostream.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

const int maxterms = 20;

class polynomial {
	friend ostream & operator<<(ostream &, const polynomial &);
	friend istream & operator>>(istream &, polynomial &);
public:
	polynomial();
	double eval(const double) const;
	//polynomial & operator=(const polynomial &);
	polynomial operator+(const polynomial &) const;
private:
	double term[maxterms];
};


ostream & operator<<(ostream & output, const polynomial &p){
	bool firstnum = true;
	for (int i = (maxterms - 1); i >= 0; i--){
		if (p.term[i] != 0.0){
			
			if (p.term[i] > 0.0 && firstnum == false)
				cout << "+ ";
			else if (p.term[i] < 0.0)
				cout << "- ";
			cout << (p.term[i] > 0.0 ? p.term[i] : -1.0 * p.term[i]);
			if (i > 0){
				cout << "x";
				if (i > 1)
					cout << "^" << i;
			}
			cout << " ";
			firstnum = false;
		}
	}
	return output;
}

istream & operator>>(istream & input, polynomial &p){
	//Begin by inputing the highest term.  Input can be in one of two forms:
	//Form 1:
	//	a1x^8 + a2x^7 + a3x^6 + ... + a9.  If a term is 0, it does not need to be input.
	//Form 2:
	//	a1 a2 a3 -a4 ... a9.  If a coefficient is 0, 0 must be entered.
	//In this case the program will decide the degree of the polynomial by the number of terms entered.  
	char istring[200];
	char tnum[15];
	char sdegree[3];

	double tterms[maxterms] = {0};
	int pos = 0, terms = 0;
	bool readnum = false;
	int inputform = 0;
	int degree;
	cin.getline(istring, 200);
	int ilength = strlen(istring);
	
	for (int i = 0; i < ilength || readnum == true; i++){
		if (isdigit(istring[i]) || istring[i] == '.' || istring[i] == '+' || istring[i] == '-'){
			tnum[pos++] = istring[i];
			tnum[pos] = '\0';
			if (isdigit(istring[i])) readnum = true;
		}
		else if(readnum == true){
			
			if (inputform == 0){
				if (istring[i] == 'x') 
					inputform = 1; 
				else 
					inputform = 2;
			}
			
			if (inputform == 1){
				if (istring[i] != 'x') degree = 0;
				else{
					i++;
					if (istring[i] == '^'){ //degree should be higher than 1 (or equal to 1)
						i++;
						sdegree[0] = istring[i];
						sdegree[1] = '\0';
						if (isdigit(istring[i + 1])){
							sdegree[1] = istring[i];
							sdegree[2] = '\0';
							i++;
						}
						degree = atoi(sdegree);
					}
					else degree = 1;
				}
				
				p.term[degree] = atof(tnum);
				pos = 0;
			}
			else { //input form = 2
				tterms[terms] = atof(tnum);
				pos = 0;
			}
			terms++;
			readnum = false;
		}
	}
	if (inputform == 2){
		pos = 0;
		for(i = terms - 1; i >= 0; i--){
			p.term[i] = tterms[pos++];
		}
	}
	return input;
}

polynomial::polynomial(){
	for (int i = 0; i < maxterms; i++){
		term[i] = 0.0;
	}
}

double polynomial::eval(const double x) const{
	double sum;
	for (int i = 0; i < maxterms; i++){
		sum += term[i] * pow(x, i);
	}
	return sum;
}

polynomial polynomial::operator+(const polynomial & right) const{
	polynomial temp;
	for (int i = 0; i < maxterms; i++){
		temp.term[i] = term[i] + right.term[i];
	}
	return temp;
}

void main(){
	cout << "This program allows input, addition, and evaluation of polynomials." << endl
	     << "Begin by inputing the highest term.  Input may be in 1 of 2 forms: " << endl
		 << "Form 1:                                                            " << endl
		 << "	a1x^8 + a2x^7 + a3x^6 + ... + a9.                               " << endl
		 << "	If a term is 0, it does not need to be input.                   " << endl
		 << "Form 2:                                                            " << endl
		 << "	a1 a2 a3 -a4 ... a9.                                            " << endl
		 << "	If a coefficient is 0, 0 must be entered.  In this case the     " << endl
		 << "	program will decide the degree of the polynomial by the number  " << endl
		 << "	of terms entered.                                               " << endl;
	cout << endl << "Enter a polynomial now: ";
	polynomial a, b;
	double x;
	cin >> a;
	cout << endl << "Enter a polynomial now: ";
	cin >> b;
	cout << "You entered " << a << endl << "and " << b << endl;
	cout << "At what value should these polynomials be evaluated? ";
	cin >> x;
	cout << "a at x is: " << a.eval(x) << endl;
	cout << "b at x is: " << b.eval(x) << endl;
	//polynomial c;
	//c = a + b;

}
