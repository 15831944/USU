/*
 * HugeInteger.java
 *
 * Created on October 8, 2001, 10:09 PM
 */



/**
 *
 * @author  marks
 * @version 
 */
import java.io.*;
import Text;

public class HugeInteger extends LinkedList {

    /** Creates new HugeInteger */
    private int DigitCount;
   
    public HugeInteger() 
    {
        DigitCount = 0;
    }
   
    public String toString()
    {
        int curExp;
        String result = new String();
        for (curExp = 1; curExp <= DigitCount; curExp++)
            result = GetDigit(curExp) + result;
        return result;
    }
    public boolean ReadInteger(BufferedReader inputFile) throws IOException
    {
        DeleteAllNodes();
        DigitCount = 0;
        String newString = new String();
        try
        {
            newString = Text.readString(inputFile);
        }
        catch (EOFException e)
        {
            return false;
        }
        int i;
        for (i = 0; i < newString.length(); i++)
            SetDigit(newString.length()-i, newString.charAt(i) - '0');
        return true;
    }
    
    public int GetDigitCount()
    {
        return DigitCount;
    }
    
    public static HugeInteger AddAndStore(HugeInteger a, HugeInteger b)
    {
        HugeInteger result = new HugeInteger();
        int nDigits;
        int curExponent = 1;
        int carry = 0;
        
        while (curExponent <= a.GetDigitCount() || curExponent <= b.GetDigitCount())
        {
            int newDigit = carry + a.GetDigit(curExponent) + b.GetDigit(curExponent);
            if (newDigit > 9)
            {
                newDigit = newDigit - 10;
                carry = 1;
            }
            else
                carry = 0;
            result.SetDigit(curExponent, newDigit);
            curExponent++;
        }
        if (carry != 0)
            result.SetDigit(curExponent, 1);
        return result;
    }
    
    public void Assign(HugeInteger rValue)
    {
        DigitCount = rValue.DigitCount;
        Node curNode = rValue.Head;
        Node leftCurNode = null;
        if (curNode != null)
        {
            Head = new Node(curNode.Data);
            leftCurNode = Head;
            curNode = curNode.NextNode;
        }
        while (curNode != null)
        {
            leftCurNode.NextNode = new Node(curNode.Data);
            leftCurNode = leftCurNode.NextNode;
            curNode = curNode.NextNode;
        }
        Tail = leftCurNode;
    }
    
    private void SetDigit(int exponent, int value)
    {
        if (value == 0)
            return;
        Digit newDigit = new Digit(exponent, value);
        if (exponent > DigitCount)
            DigitCount = exponent;
        if (Head == null)
            InsertAtFront(newDigit);
        else
        {
            Node curNode = Head;
            if (curNode.Data.IsGreaterThan(newDigit))
            {
                InsertAtFront(newDigit);
                return;
            }
            while (true)
            {
                if (curNode.NextNode == null)
                {
                    InsertAtBack(newDigit);
                    break;
                }
                else if (newDigit.IsLessThan(curNode.NextNode.Data))
                {
                    Node tempNode = curNode.NextNode;
                    curNode.NextNode = new Node(newDigit);
                    curNode.NextNode.NextNode = tempNode;
                    break;
                }
                else
                    curNode = curNode.NextNode;
            }
        }
    }
    int GetDigit(int exp)
    {
        Digit currentDigit;
        BeginEnumeration();
        while ((currentDigit = GetNextData())!= null)
        {
            if (currentDigit.Exponent == exp)
                return currentDigit.Value;
            else if (exp < currentDigit.Exponent)
                return 0;
        }
        return 0;
    }
        
}