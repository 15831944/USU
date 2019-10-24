//Brad Millett, MWF 12:30, cs 1720
//Simon and Garfunkel Assignment

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

//declare the input and output files globablly
//so that all the functions can access them
ifstream finQuest("quest1.txt", ios::in);
ifstream finAdvice("advice1.txt", ios::in);
ofstream fout("assignment1.out");

void loadQuestAdvice(string [], int , string [], int );

void main(void)
{
	//the max size of the array is set
	const int questSize = 100, adviceSize = 20;
	//define the arrays to hold the questions and advice
	string questAry[questSize], adviceAry[adviceSize];
	
	loadQuestAdvice(questAry, questSize, adviceAry, adviceSize);
}

//this function loads the arrays of questions and advice from
//the input files
void loadQuestAdvice(string questAry[], int questSize, string adviceAry[], int adviceSize)
{
	if (!finQuest)
	{
		cout << "Unable to open the file \"quest1.txt\".";
		return;
	}
	else
	{
		int i = 0;
		while(!finQuest.eof() && i <= 100)
		{
			getline(finQuest, questAry[i], '$');
			i++;
		}
	}

	if (!finAdvice)
	{
		cout << "Unable to open the file \"advice1.txt\".";
		return;
	}
	else
	{
		int j = 0;
		while(!finQuest.eof() && j <= 100)
		{
			getline(finQuest, questAry[j], '$');
			j++;
		}
	}
}

 
