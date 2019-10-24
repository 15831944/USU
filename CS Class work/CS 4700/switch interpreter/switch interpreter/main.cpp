#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>

int errCode = 0;
bool varValueDefined = false;
int varValue;
char varName[32] = {0};
int switchValue;

#define UNDEFINED_STATEMENT		1

bool parseIntStatement(char * line);
bool parseSwitchStatement(istream & input, char * line);

bool IsWhiteSpace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
}

class exception
{
public:
	exception() { errMessage[0] = '\0'; }
	exception(const char * m)
	{
		strcpy(errMessage,m);
	}
	void printErrMessage()
	{
		cout << errMessage << endl;
	}
private:
	char errMessage[100];
};

void CountParenthesis(char * text, char c1, char c2, int &count)
{
	for (int i = 0; text[i] != '\0'; i++)
	{
		if (text[i] == c1)
			count++;
		else if (text[i] == c2)
		{
			count--;
			if (count < 0)
			{
				char errmessage[100];
				wsprintf(errmessage,"Error: mismatched parenthesis, missing %c",c2);
				exception e(errmessage);
				throw (e);
			}
		}
		if (c2 == '}' && text[i] == 'c' && strncmp(&text[i],"case ",5) == 0 && count != 1)
		{
			exception e("Invalid case statement");
		}
	}
}

void TrimWhiteSpace(char * text)
{
	for (int w = 0; IsWhiteSpace(text[w]); w++);
	if (w != 0)
	{
		for (int p = 0; text[w] != '\0'; p++)
		{
			text[p] = text[w];
			w++;
		}
		text[p] = '\0';
	}
	for (w = strlen(text) - 1; IsWhiteSpace(text[w]) && w >= 0; w--)
	{
		text[w] = '\0';
	}
}

bool parseStatement(istream & input)
{
	char line[80];
	input.getline(line,80);
	TrimWhiteSpace(line);
	if (strncmp(line,"int ",4)==0)
	{
		return parseIntStatement(line);
	}
	else if (strncmp(line, "switch",6)==0)
	{
		return parseSwitchStatement(input,line);
	}
	else
	{
		errCode = UNDEFINED_STATEMENT;
		return false;
	}
}

bool parseIntStatement(char * line)
{
	TrimWhiteSpace(&line[4]);
	if (isalpha(line[4]))
	{
		for (int i = 1; isalnum(line[4 + i]) && line[4 + i] != '\0'; i++);
		strncpy(varName,&line[4],i);
		TrimWhiteSpace(&line[4+i]);
		if (line[4+i]=='=')
		{
			varValue = atoi(&line[5+i]);
			varValueDefined = true;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

}

bool parseCaseStatements(istream & input, int & PCount, int & CCount)
{
	// rule - the CCount (curly brace count) must be 0 whenever a case statement is encountered.
	char line[80];
	char line2[80];
	while (input.getline(line,80))
	{
		strcpy(line2,line);
		TrimWhiteSpace(line);
		CountParenthesis(line,'(',')',PCount);
		CountParenthesis(line,'{','}',CCount);
		for (int i = 0; line[i] != '\0'; i++)
		{
			if (line[i] == 'c' && strncmp(&line[i],"case ",5) == 0)
			{
				bool dotFound = false;
				for (int j = i + 5; line[j] != ':' && line[j] != '\0'; j++);
				if (line[j] == '\0')
				{
					exception e("no colon found for case statement");
					throw (e);
				}

				int minBound;
				int maxBound;

				for (int q = i + 5; q <= j; q++)
				{
					if (line[q] == '.' || line[q] == ':')
					{
						if (line[q] == '.')
							dotFound = true;
						line[q] = '\0';
						minBound = atoi(&line[5]);
					}
				}
				if (dotFound)
				{
					int z = q;
					for (; q <= j; q++)
					{
						if (line[q] == '.')
						{
							z = q + 1;
							continue;
						}
							
						else if(line[q] == ':')
						{
							maxBound = atoi(&line[z]);
							if (maxBound <= minBound)
							{
								exception e("max bound on case statement must be greater than min bound");
								throw (e);
							}
						}
					}
				}
				else 
					maxBound = minBound;
				if (switchValue >= minBound && switchValue <= maxBound)
					cout << "case statement found:" << endl
						 << line2 << endl;
			}
		}

	}
	return true;
}

bool parseSwitchStatement(istream & input, char * line)
{
	int PCount = 0;
	int CCount = 0;

	TrimWhiteSpace(&line[6]);
	try 
	{
		CountParenthesis(line,'(',')',PCount);
		CountParenthesis(line,'{','}',CCount);

		if (line[6]=='(')
		{
			if (PCount == 0)
			{
				for (int i = strlen(line) - 1; i >= 6; i--)
				{
					if (line[i] == ')')
					{
						line[i] = '\0';
						break;
					}
				}
				char vname[30];
				TrimWhiteSpace(&line[7]);
				strcpy(vname,&line[7]);
				if (vname[7] >= '0' && vname[7] <= '9')
				{
					switchValue = atoi(vname);
				}
				else
				{
					if (strcmp(vname,varName)==0)
					{
						if (!varValueDefined)
						{
							cout << "No value defined for variable in switch statement." << endl;
							return false;
						}
						else
						{
							switchValue = varValue;
						}
					}
					else
					{
						cout << "No value defined for variable in switch statement." << endl;
						return false;
					}
					
				}
				return parseCaseStatements(input,PCount,CCount);

			}
			else
			{


			}


		}
	}
	catch (exception e)
	{
		e.printErrMessage();
		return false;
	}

	return true;
}

void main()
{
	ifstream fin("input.dat");
	while (parseStatement(fin));
	// input file format:
	// first line is an integer defining the test value to be used in the switch statement
	// like this: int x = 12;
	// data following is switch statement:
	// switch (x)
	// {
	//		case 1:{ } break;
	//		case 2:
	//		case 3:
	//		{
	//
	//
	//		} break;
	//		case 4..12:
	//		{
	//		}
	//		default:
	//
	//}
	// this program should make sure that the syntax of a switch statement is correct.
	// it is correct if 
	// after that it should check to 
	int l = 1;
	switch (l)
	{
	case 2:
		break;
	}
}