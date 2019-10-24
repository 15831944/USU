// 362
// marks
// Mark Salisbury
// P362A121.cpp
/*
A121. In the file scores.dat you will find the graphics students 
scores on their graphics assignments. There have been 5 assignments 
thus far and the total possible for the 5 is 200 points. Write a 
program that will read these scores into a 2 dimensional array named
scores using the function named readscores. This array will have 5
scores for each student but there may be as many as 200 students in 
the class. Your program will have to determine how many students 
there are using the eof. Your program is to sum the scores for each 
student and place that sum in the 1 dimensional array total using 
the function named sumscores. Again, there may be as many as 200 
students.

Your program will also determine the average score for 
each of the five assignments and place that average in the array of
doubles named averages using the function named average. The array 
averages should be declared to have 10 elements because the students 
still have more assignments to turn in. 

Have your program write the scores to the file total.dat in the same 
format as they were in scores.dat except each row will now have 6 
data items, the five assignment scores and the total taken from the 
array total.The writing to the file will occur in the function 
writescores.  

Your program will then output to the screen the averages of each of 
the assignments taken from the array averages using the function named 
screenoutput */

#include <fstream.h>
#include <iomanip.h>

ifstream fin("scores.dat");
ofstream fout("total.dat");

int readscores(int scores[][5], int total[]);
void average(double [][10], int, int []);
void writescores(int scores[][5], int total[], int numofstudents);
void screenoutput(double averages[][10], int numofstudents);

void main(void){

	int scores[200][5];
	int total[200] = {0};
	int numofstudents = readscores(scores, total);
	
	double averages[200][10];

	average(averages, numofstudents, total);
	writescores(scores, total, numofstudents);
	screenoutput(averages, numofstudents);

}

int readscores(int scores[][5], int total[]){

	for (int i = 0; i < 200; i++){
		for (int j = 0; j < 5 && !fin.eof(); j++){
			fin >> scores[i][j];
			total[i] += scores[i][j];
		}
		if (fin.eof())
			break;
	}
	return i + 1;
}

void average(double averages[][10], int numofstudents, int total[]){
	for (int i = 0; i < numofstudents; i++){
		averages[i][0] = total[i] / 5;
	}
}

void writescores(int scores[][5], int total[], int numofstudents){
	for (int i = 0; i < numofstudents; i++){
		for (int j = 0; j < 5; j++){
			fout << setw(3) << scores[i][j];
		}
		fout << setw(4) << total[i];
		fout << endl;
	}
}

void screenoutput(double averages[][10], int numofstudents){
	for (int i = 0; i < numofstudents; i++)
		cout << "Student " << i + 1 << " average = " << averages[i][0] << endl;
}