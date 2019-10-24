/*
 * LinkedListTestApp.java
 *
 * Created on October 3, 2001, 10:03 PM
 */



/**
 *
 * @author  marks
 * @version 
 */

import java.io.*;
import java.util.*;
import java.lang.*;
//import javagently.*;
import HugeInteger;
import Text;

public class HugeIntTestApp extends Object {

    /** Creates new LinkedListTestApp */
    public HugeIntTestApp() {
    }

    /**
    * @param args the command line arguments
    */
    public static void main (String args[]) throws IOException

    {
        HugeInteger curSum = new HugeInteger();
        HugeInteger curNumber = new HugeInteger();
        
        BufferedReader fin;
        try
        {
            fin = Text.open("C:\\forte4j\\Homework\\HugeInt Assignment\\hugenumbers.in");
        }
        catch (FileNotFoundException f)
        {
            return;
        }
    
        while(curNumber.ReadInteger(fin))
        {
            curSum.Assign(HugeInteger.AddAndStore(curSum,curNumber));
        }
        fin.close();    
        
        // Open the output file, print, and close the file
        PrintWriter fout = Text.create("hugenumbers.out");
                
        fout.println("The total is: " + curSum.toString());
        
        fout.close();
    }

}