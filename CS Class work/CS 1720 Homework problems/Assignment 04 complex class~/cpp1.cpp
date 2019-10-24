
/*
A42.  Create a class HugeInt that uses a 64 element array of digits to store integers as large as 64 digits each.   Since only the
digits 0-9 will be stored in each array element, this can easily be accomplished using an array of char. To output or work with the
digits stored in an array of char you simply cast them to int. For example: 

char a = 1, b = 2;
cout << int(a) << "   " << int(b) << endl; 

You can  use an array of short if you want. Overload the +,  -,  *,  /,  %,  <<, >>, >, <, <=, >=, ==, !=operators so that basic HugeInt
arithmetic can be done in the usual way such as: 

z = x + y;
z = x - y,
z = x*y,
z = x/y,
z = x%y, and 
cin >> x >> y,
cout << x << y, and 
x == y; x != y; x >= y; x <= y; x < y; x > y; where x, y, and z are each an instance of the class HugeInt.

Input (from the keyboard) the HugeInt as a string (string class) so the comparison operators and I/O are easy to implement.
Provide a function to convert the string to a HugeInt and a function to convert a HugeInt to a string. 
