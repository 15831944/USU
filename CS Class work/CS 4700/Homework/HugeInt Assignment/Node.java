/*
 * Node.java
 *
 * Created on October 3, 2001, 10:07 PM
 */



/**
 *
 * @author  marks
 * @version 
 */
import Digit;

public class Node extends Object {

    /** Creates new Node */
    public Node(Digit newData) {
        Data = new Digit();
        Data.Value = newData.Value;
        Data.Exponent = newData.Exponent;
        NextNode = null;
    }
    Digit Data;
    Node NextNode;
}