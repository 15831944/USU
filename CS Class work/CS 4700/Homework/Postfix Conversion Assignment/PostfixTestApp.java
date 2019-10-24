/*
 * PostfixTestApp.java
 *
 * Created on October 15, 2001, 4:12 PM
 */

/**
 *
 * @author  marks
 * @version 
 */

import java.io.*;
import java.util.*;
import java.lang.*;
import Text;
import LinkedList;

public class PostfixTestApp extends Object {

    /** Creates new PostfixTestApp */
    public static int Precedence(char c)
    {
        if (c == '+' || c == '-')
            return 1;
        if (c == '*' || c == '/')
            return 2;
        if (c == '(' || c == ')')
            return 0;
        else
            return 0;
    }
    public PostfixTestApp() {
    }

    /**
    * @param args the command line arguments
    */
    public static void main (String args[]) throws IOException
    {
        LinkedList eStack = new LinkedList();
        BufferedReader fin;
        PrintWriter fout = Text.create("expression.out");
        char c = 'a';
        char d;
        boolean isnumber = false;
        int curNumber = 0;
        try
        {
            fin = Text.open("expression.in");
            while (c != 0)
            {
                c = Text.readChar(fin);
                if (c==' ') continue;
                
                if (c >= '0' && c <= '9')
                {
                    curNumber *= 10;
                    curNumber += (c - '0');
                    isnumber = true;
                }
                else
                {
                    if (isnumber)
                    {
                        fout.print(curNumber + " ");
                        curNumber = 0;
                        isnumber = false;
                    }
                    if(c == '+' || c == '-' || c == '*' || c == '/')
                    {
                        if (eStack.IsEmpty())
                        {
                            eStack.InsertAtFront(c);
                        }
                        else
                        {
                            while (true)
                            {
                                d = eStack.RemoveFromFront();
                                if (d == 0)
                                    break;
                                if (Precedence(d) >= Precedence(c))
                                    fout.print(d + " ");
                                else
                                {
                                    eStack.InsertAtFront(d);
                                    break;
                                }
                            }
                            eStack.InsertAtFront(c);
                        }
                    }
                    else if(c == '(')
                    {
                           eStack.InsertAtFront(c);
                    }
                    else if(c == ')')
                    {
                        while (true)
                        {
                            d = eStack.RemoveFromFront();
                            if (d == 0)
                                break;
                            if (d == '(')
                                break;
                            else
                                fout.print(d + " ");
                        }
                    }
                }
            }
            fin.close();    
        }
        catch (FileNotFoundException f)
        {
            return;
        }
        catch (EOFException e)
        {
            if (isnumber)
            {
                fout.print(curNumber + " ");
                curNumber = 0;
                isnumber = false;
            }
            while (true)
            {
                d = eStack.RemoveFromFront();
                if (d == 0)
                    break;
                else
                    fout.print(d + " ");
            }        
            fout.close();
        }
    }

}