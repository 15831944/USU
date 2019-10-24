#include <fstream.h>

void main()
{
	ifstream fin("input.txt");

	int count = 0;
	int x;

	while (!fin.eof())
	{
		fin >> x;
		count++;
	}

	cout << "count = " << count;


}