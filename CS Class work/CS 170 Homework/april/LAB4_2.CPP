#include <iostream.h>
int main() {
	cout << "Enter a positive integer m where m < n: " << flush;
	int m;
	cin >> m;
	cout << "Enter a positive integer n where n > m: " << flush;
	int n;
	cin >> n;
	int temp;
	if (m > n)  {
		temp = m;
		m = n;
		n = temp;
	}


	int Sum = 0;
	int i;
	for (i = m; i <= n; ++i) {
		Sum = Sum + i;
	}

	cout << "The sum from " << m << " to " << n << " is "
	<< Sum << endl;
	return 0;
}
