/*
 * MemObject.java
 *
 * Created on November 30, 2001, 2:50 PM
 */



/**
 *
 * @author  marks
 * @version 
 */

import LinkedList;

public class MemObject extends Object {

    /** Creates new MemObject */
    
    public MemObject() {
        referenceCount = 0;
    }
    public MemObject(String vName)
    {
        referenceCount = 1;
        ReferenceNames.Insert(vName);
    }

    private int referenceCount;

    private LinkedList ReferenceNames;
   
    private boolean ReferenceExists(String vName)
    {
         // parse through the linked list, looking for a reference of name vName
    }
    private void RemoveReference(String vName)
    {
         // parse through the linked list, looking for a reference of name vName
    }
}