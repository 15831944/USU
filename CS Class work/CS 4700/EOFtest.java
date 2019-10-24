import java.io.*;
import java.util.*;
import javagently.*;

public class EOFtest
{
  public static void main (String [] args) throws IOException
  {
   // Open the input file and get the data
    BufferedReader fin = Text.open("hwjava1.in");
    int n, sum;
    sum = 0;
    
    try
    {
      for(int i = 1; ; ++i)
      {
        n = Text.readInt(fin);
        sum = sum + n;
      }
    }
    catch (EOFException e) {}
 
    // Open the output file, print, and close the file
    PrintWriter fout = Text.create("eoftest.out");
    fout.println("The sum is: " +  sum);
    fout.close();
  }
}


