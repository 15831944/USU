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

public class Node extends Object {

    /** Creates new Node */
    public Node(Object operator) {
        Data = operator;
        NextNode = null;
    }
    Object Data;
    Node NextNode;
}