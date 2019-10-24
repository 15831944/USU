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
    
    private int ParseLine( String vName1, String vName2)  throws IOException
    {
        int rValue = -1;
        String c;
        try
        {
            c = Text.readString(fin);
            if (c.equals("set"))
            {
                vName1 = Text.readString(fin);
                c = Text.readString(fin); // read an equals
                vName2 = Text.readString(fin);
                if (vName2.equals("new"))
                {
                    c = Text.readString(fin); // read in "object"
                    rValue = 0;
                }
                else
                {
                    rValue = 1;
                }
            }
            else if (c.equals("delete"))
            {
                vName1 = Text.readString(fin);
                rValue = 2;            
            }
        }
        catch (EOFException e)
        {
            fin.close();
        }
        return rValue;
    }
    
    private void ParseInput() throws IOException
    {
        
        int command = 0; // -1 = unrecognized command, 0 = allocate, 1 = set, 2 = deallocate
        String varName1, varName2;
        varName1 = new String();
        varName2 = new String();
        
        PrintWriter fout = Text.create("expression.out");
        try
        {
            fin = Text.open("expression.in");
            // read input file
            while(command != -1)
            {
                command = ParseLine(varName1, varName2);
                switch (command)
                {
                    case 0:
                        break;
                    case 1:
                        break;
                    case 2:
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
        HeapSimulator c = new HeapSimulator();
        try
        {
            c.ParseInput();
        }
        catch(IOException e)
        {
            
        }
    }

}