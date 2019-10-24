//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  3-21-97
//  Problems for Algorithms with conditional Operations #3
//  test scores

#include <iostream.h>

void main() {
int StudentNum;
cout << "Enter student id number: " << flush;
cin >> StudentNum;
int Score;
cout << "Enter exam score (integer values from 0-100): " << flush;
cin >> Score;

cout << "Exam grade: " << flush;
if (Score >= 90) cout << "A";
if (Score >= 80 && Score < 90) cout << "B";
if (Score >= 70 && Score < 80) cout << "C";
if (Score >= 60 && Score < 70) cout << "D";
if (Score < 60) cout << "F";

}
