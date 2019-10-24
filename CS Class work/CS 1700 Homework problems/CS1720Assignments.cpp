CS1720  Assignment 1
/*
Arithmetic of complex numbers is defined by:

(a+bi) + (c+di) = (a+c) + (b+d)i                                       // addition
(a+bi) - (c+di) = (a-c) + (b-d)i                                          // subtraction
(a+bi)*(c+di) = (ac-bd) + (ad+bc)i                                   // multiplication
(a+bi)/(c+di) = (ac+bd)/(c2+d2)  + ((bc-ad)/(c2+d2))i         // division
magnitude(a+bi) = sqrt(a2 + b2)                                        // magnitude

A11. Write a complete program including prototypes, a driver program, and the implementation which uses complex numbers without a
class. This is similar to what we did first with rational numbers. The real and imaginary parts of the complex numbers should be of type
double. Be sure to include a function print that will print a complex number in the usual form. Also include a function input that will
allow the input of a complex number in the usual form. Input and output should be as you would expect for complex numbers, for
example 2.3+5.4i, -2.3+5.4i, 2.6-5.6i, -5.4-7.53i. In other words your I/O should look just as it would on a sheet of paper where you
were writing complex numbers.

CS1720 Assignment 2

A21. Write a complete program including specification, driver (client) program and implementation using the
class Complex with public attributes and functions that are not members of the class. Be sure to include a
function print that will print a complex number in the usual form. Also include a function input that will allow the
input of a complex number in the usual form.

A22. Modify your Complex class so that the attributes are private and the functions are members of the class.
Include a function, print, that will print a complex number and use it to output the complex numbers that are
calculated. Also include a function input that will allow the input of a complex number in the usual form.

A23. Modify your Complex class to include good identified output and input of complex numbers in the form a + bi, overload
the +, -, *, /, <<, >>, >, <, <=, >=, ==, !=operators so that basic complex number arithmetic can be done in the usual way such as:
z = x + y;
z = x - y,
z = x*y,
z = x/y, and 
cin >> x >> y;
cout << x << y; 
x == y; x != y; x >= y; x <= y; x < y; x > y; where x, y, and z are complex numbers.

A complex number is considered to be greater than another complex number if the magnitude of the first is greater than the
second. Two complex numbers are == only if the real1 == real2 and imaginary1 == imaginary2. Be sure you use doubles for the
real and imaginary part of the complex number.

I can now assume that your constructors work, so for A23, input several complex numbers and test all the functions with the
numbers that are input by the user.

A24. {6.8} Modify the Time class of Fig. 6.10 to include a tick member function that increments the time stored in a Time object
by one second. The time object should always remain in a consistent state. Write a driver program that tests the tick member
function in a loop that prints the time in standard format during each iteration of the loop to illustrate that the tick member
function works correctly. Be sure to test the following cases:
    a) Incrementing into the next minute.
    b) Incrementing into the next hour.
    c) Incrementing into the next day (i.e. 12:59:59 PM to 12:00:00 AM). 


	 CS1720 Assignment 3 More classes and Operator overloading

A31. {similar to 8.16} A machine with 32 bit integers can represent integers in the range of 
approximately -2 billion to + 2 billion.  This fixed-size restriction is rarely troublesome. 
But there are applications in which we would like to be able to use a much wider range of 
integers. This is what C++ was built to do, namely create powerful new data types. Consider 
class HugeInt of Fig 8.8.  Study the class carefully, then
        a. Overload the * multiplication operator.
        b. Overload all the relational and equality operators.

All of the example programs can be downloaded from http://www.deitel.com

The files from Figure 8 can also be downloaded here:

Fig08_08.cpp                Be sure to completely test your class.
Hugeint1.cpp
Hugeint1.h

Put these three files into one file as we have in the past.

CS1720 Assignment 4 More classes and Operator overloading

A41. Use your HugeInt class from A13 and overload the /, the division operator and %, the mod operator.

All of the example programs can be downloaded from http://www.deitel.com

The files from Figure 8 can also be downloaded here:

Fig08_08.cpp                Your client program must completely test your class.
Hugeint1.cpp
Hugeint1.h

Put these three files into one file as we have in the past.

Be sure to make I/O easy and intuitive.

A42.  {similiar to 8.19} Develop class Polynomial. The internal representation of a Polynomial is an array of terms. Each term
contains a coefficient and an exponent. The term

        2x4

has a coefficient of 2 and an exponent of 4. Develop a full class containing proper constructor and destructor functions as well
as set and get functions. The class should also provide the following overloaded operator capabilities:

    a. Overload the addition operator (+) to add two Polynomials.
    b. Overload the assignment operator to assign one Polynomial to another.
    c. Provide a value function that will evaluate the polynomial for a given  value of x.

Write a client program that will completely test your class.

Be sure to make I/O easy and intuitive.

CS1720 Assignment 5

See Page 161 to learn how to use the internal time clock to initialize the rand() function.

A51. Do exercise 5.33 on page 356 of your text. (Creating sentences)

For problems A52 and A53, have your program prompt for and read the phrase from the keyboard.

A52. Do the first part of exercise 5.47 on page 360 of your text, translating from English to Morse Code.

A53. Do the second part of exercise 5.47 on page 360 of your text, translating from Morse Code to English.
*/
