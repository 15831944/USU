/*
 * Digit.java
 *
 * Created on October 8, 2001, 10:14 PM
 */



/**
 *
 * @author  marks
 * @version 
 */
public class Digit extends Object {

    /** Creates new Digit */
    public Digit() 
    {
        Exponent = 0;
        Value = 0;
    }
    public Digit(int newExponent, int newValue)
    {
        Exponent = newExponent;
        Value = newValue;
    }
    public boolean IsLessThan(Digit rightDigit)
    {
        if (Value == 0 && rightDigit.Value != 0) return true;
        if (rightDigit.Value == 0) return false;
        if (Exponent < rightDigit.Exponent) 
             return true;
        else if (Exponent == rightDigit.Exponent)
            return (Value < rightDigit.Value);
        else
            return false;
    }
    public boolean IsGreaterThan(Digit rightDigit)
    {
        if (Value == 0 && rightDigit.Value != 0) return false;
        if (rightDigit.Value == 0) return true;
        if (Exponent < rightDigit.Exponent) 
             return false;
        else if (Exponent == rightDigit.Exponent)
            return (Value > rightDigit.Value);
        else
            return true;
    }
    public int Exponent;
    public int Value;
}