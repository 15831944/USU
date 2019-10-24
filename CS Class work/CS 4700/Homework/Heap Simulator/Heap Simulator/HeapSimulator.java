/*
 * HeapSimulator.java
 *
 * Created on November 29, 2001, 11:04 AM
 */



/**
 *
 * @author  marks
 * @version 
 */

import LinkedList;
import Text;

import java.io.*;
import java.util.*;
import java.lang.*;

public class HeapSimulator extends Object {

    /** Creates new HeapSimulator */
    
    public HeapSimulator() {
    }
    
    private LinkedList Heap;
    private BufferedReader fin;
    
    private MemObject FindMemObject(String vName)
    {

    }

    private void CreateNewObject(String vName)
    {

    }
    private void RemoveReference(String vName)
    {

    }
    private void AddReference(String vName1, String vName2)
    {

    }

    private boolean ParseLine(int command, String vName1, String vName2)  throws IOException
    {
        command = -1;
        String c;
        try
        {
            c = Text.readString(fin);
            if (c == "set")
            {
                vName1 = Text.readString(fin);
                c = Text.readString(fin); // read an equals
                vName2 = Text.readString(fin);
                if (vName2 == "new")
                {
                    c = Text.readString(fin); // read in "object"
                    command = 0;
                }
                else
                {
                    command = 1;
                }
            }
            else if (c == "delete")
            {
                vName1 = Text.readString(fin);
                command = 2;
            }
            return true;
        }
        catch (EOFException e)
        {
            fin.close();
            return false;
        }
        
    }
    
    private void ParseInput()  throws IOException
    {
        
        int command = -1; // -1 = unrecognized command, 0 = allocate, 1 = set, 2 = deallocate
        String varName1, varName2;
        varName1 = new String();
        varName2 = new String();
        
        PrintWriter fout = Text.create("expression.out");
        try
        {
            fin = Text.open("expression.in");
            // read input file
            while(ParseLine(command, varName1, varName2))
            {
            
                switch (command)
                {
                    case 0:
 			 	RemoveReference(varName1);
                        CreateNewObject(varName1);
                        break;
                    case 1:
                        if (!AddReference(varName1,varName2))
				{
					// no object with name 'varName1' was found
				}
                        break;
                    case 2:
                        RemoveReference(varName1);
                        break;
                    default:
                        break;
                }
            
            }
        }
        catch (FileNotFoundException f)
        {
            return;
        }
        catch (EOFException e)
        {
               
            fout.close();
        }
        
    }
    
    public static void main (String args[]) {
    }

}