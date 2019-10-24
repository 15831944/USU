//  Mark Salisbury
//  Chapter 2- #25
//  This program is for aerobic workout heartrates

#include <iostream.h>
int age = 0;
void main() {
cout << "This program computes your suggested" << endl;
cout << "pulse rate during aerobic exercise." << endl;
cout << "What is your age?\t" << flush;
cin >> age;
cout << "In an aerobic workout your pulse should range from:" << endl;
cout << (220-age)*0.72 << " to " << (220-age)* 0.87 << " beats per minute.";
}