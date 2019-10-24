// 362
// marks
// Mark Salisbury
// P362A63.cpp

#include <iostream.h>
#include <math.h>
#include <iomanip.h> 

inline int isperfect(int n);

void main(){

	int n;
	int PNCounter = 0;
	cout << "To what number would you like to test for perfect numbers?: ";
	cin >> n;
	cout << "Perfect numbers up to " << n << ":" << endl;

	for (int i = 1;i <= n + 1; i ++){
		
		if (isperfect(i)){
			cout << i << " ";
			++PNCounter;
			if (PNCounter % 8 == 0)
			cout << endl;
		}
	}
	cout << endl;


}

int isperfect(int n){
	int FactSum = 1;
	for (int i = 2; i <= sqrt(n); i++){
		if (n % i == 0){ //then counter is a factor of n
			FactSum += i + n / i;
		}
	}
	return (FactSum == n);
}