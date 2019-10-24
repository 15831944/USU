// 362
// marks
// Mark Salisbury
// P362A64.cpp

#include <iostream.h>
#include <math.h>
inline int isprime(int n);
void main(){
	int n;
	int PNCounter = 0;
	cout << "To what number would you like to test for prime numbers?: ";
	cin >> n;
	cout << "Prime numbers up to " << n << ":" << endl;
	for (int i = 1; i <= n; i += 2){
		if (isprime(i)){
			cout << i << " ";
			++PNCounter;
			if (PNCounter % 8 == 0)
			cout << endl;
		}
	}
}

int isprime(int n){
	
	for (int i = 2; i <= sqrt(n); i++){
		if (n % i == 0){ //then counter is not prime
			return 0;
		}
	}
	return 1;
}