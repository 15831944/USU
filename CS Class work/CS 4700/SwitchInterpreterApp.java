/*
 * SwitchInterpreterApp.java
 *
 * Created on Oct 30, 2001, 10:33 AM
 */

import java.io.*;
import java.util.*;
import java.lang.*;
import Text;
import MyException;

/**
 *
 * @author  marks
 * @version 
 */
public class SwitchInterpreterApp extends Object {

    /** Creates new SwitchInterpreterApp */
    public SwitchInterpreterApp() {
    }

    /**
    * @param args the command line arguments
    */
    
    PrintWriter fout;
    
    public static void main (String args[]) throws IOException
    {
        BufferedReader fin;
        fout = Text.create("expression.out");
       
        try
        {
            fin = Text.open("expression.in");
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
            fin.close();    
        }
        catch (FileNotFoundException f)
        {
            return;
        }
        catch (EOFException e)
        {
               
        }
        fout.close();
        
    }

    private boolean varValueDefined = false;
    private int varValue;
    private String varName;
    private int switchValue;
  
    private boolean IsWhiteSpace(char c)
    {
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
    }

    private void CountParenthesis(String text, char c1, char c2, int &count)
    {
	for (int i = 0; i < text.length(); i++)
	{
            if (text.charAt(i) == c1)
                    count++;
            else if (text.charAt(i) == c2)
            {
                count--;
                if (count < 0)
                {
                    MyException m("Error: mismatched parenthesis, missing " + c2);
                    throw (m);
                }
            }
            if (c2 == '}' && text[i] == 'c' && strncmp(&text[i],"case ",5) == 0 && count != 1)
            {
                MyException m("Error: Invalid case statement");
                throw (m);
            }
	}
    }

    
    bool parseStatement(istream & input)
    {
	char line[80];
	input.getline(line,80);
	line.trim();
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

    boolean parseIntStatement(string text)
    {
        String line;
        line = text.substring(4);
        line.trim();

        if (isalpha(line.charAt(0)))
        {
            for (int i = 1; isalnum(line.charAt(i)) && i < line.length(); i++);
            varName = line.substring(0,i);
            string nextToken = line.substring(i);
            nextToken.trim();
            if (nextToken.charAt(0)=='=')
            {
                nextToken = nextToken.substring(1);
                varValue = atoi(nextToken);
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

    private boolean parseCaseStatements(BufferedReader input, int &PCount, int &CCount)
    {
        // rule - the CCount (curly brace count) must be 0 whenever a case statement is encountered.
        string line;
        string line2;
        try
        {
            while (true)
            {
                line = input.readLine();
                line2 = line;
                line.Trim();
                CountParenthesis(line,'(',')',PCount);
                CountParenthesis(line,'{','}',CCount);
                for (int i = 0; i < line.length(); i++)
                {
                    if (line.substring(i,i+4) ==  "case ")
                    {
                        boolean dotFound = false;
                        for (int j = i + 5; line.charAt(j) != ':' && j < line.length(); j++);
                        if (j == line.length())
                        {
                            MyException e("no colon found for case statement");
                            throw (e);
                        }

                        int minBound;
                        int maxBound;

                        for (int q = i + 5; q <= j; q++)
                        {
                            if (line.charAt(q) == '.' || line.charAt(q) == ':')
                            {
                                if (line.charAt(q) == '.')
                                    dotFound = true;
                                line = line.substring(q+1);
                                minBound = atoi(line.substring(5));
                            }
                        }
                        if (dotFound)
                        {
                            int z = q;
                            for (; q <= j; q++)
                            {
                                if (line.charAt(q) == '.')
                                {
                                    z = q + 1;
                                    continue;
                                }

                                else if(line(q) == ':')
                                {
                                    maxBound = atoi(line.substring(z));
                                    if (maxBound <= minBound)
                                    {
                                        MyException e("max bound on case statement must be greater than min bound");
                                        throw (e);
                                    }
                                }
                            }
                        }
                        else 
                            maxBound = minBound;
                        if (switchValue >= minBound && switchValue <= maxBound)
                            fout.print( "case statement found: "+ line2 + "\n");
                    }
                }
            }
        }
        catch (IOExcepetion e)
        {

        }
        return true;
    }

    boolean parseSwitchStatement(BufferedReader input, string line)
    {
	int PCount = 0;
	int CCount = 0;
        line = line.substring(6);
	line.trim();
	try 
	{
            CountParenthesis(line,'(',')',PCount);
            CountParenthesis(line,'{','}',CCount);

            if (line.charAt(6)=='(')
            {
                if (PCount == 0)
                {
                    for (int i = line.length() - 1; i >= 6; i--)
                    {
                        if (line.charAt(i) == ')')
                        {
                            line = line.substring(0,i-1);
                            break;
                        }
                    }
                    string vname = line;
                    
                    if (vname.charAt(7) >= '0' && vname.charAt(7) <= '9')
                    {
                        switchValue = atoi(vname);
                    }
                    else
                    {
                        if (vname==varName)
                        {
                            if (!varValueDefined)
                            {
                                fout.print("No value defined for variable in switch statement.");
                                return false;
                            }
                            else
                            {
                                switchValue = varValue;
                            }
                        }
                        else
                        {
                            fout.print( "No value defined for variable in switch statement.");
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
	catch (MyException e)
	{
            return false;
	}

	return true;
    }
}