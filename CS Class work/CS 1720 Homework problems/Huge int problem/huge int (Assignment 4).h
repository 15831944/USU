#include <iostream.h>
#include <iomanip.h>

class hugeint{
	friend ostream & operator<<( ostream&, const hugeint &);
	friend istream & operator>>( istream&, hugeint &);
public:
	hugeint();
	hugeint(int);
	hugeint(const char *);
	hugeint operator+(const hugeint &);
	hugeint operator=(const hugeint &);
	hugeint operator=(const char *);
	hugeint operator*(const hugeint &);
	hugeint operator/(const hugeint &);
	int operator==(const hugeint &);
	int operator==(const int &);
private:
	int stringToInt(int length = size, int pos = 0);
	char * strseg(int length, int start = 0) const;
	char * number;
	static int size;
};