/*
 * LinkedList.java
 *
 * Created on October 3, 2001, 10:06 PM
 */

/**
 *
 * @author  marks
 * @version 
 */

import Node;

public class LinkedList extends Object {

    /** Creates new LinkedList */
    public LinkedList()
    {
        Head = null;
        Current = null;
        Tail = null;
    }
    
    Node Head;
    Node Current;
    Node Tail;
    void InsertAtFront(Object Data)
    {
        Node PrevHeadNode = Head;
        Head = new Node(Data);
        Head.NextNode = PrevHeadNode;
        if (Tail == null)
        {
            Tail = Head;
        }
    }
    void InsertAtBack(Object Data)
    {
        if (Tail == null)
            InsertAtFront(Data);
        else
        {
            Tail.NextNode = new Node(Data);
            Tail = Tail.NextNode;
        }
    }
    Object RemoveFromFront()
    {
        if (Head == null)
            return 0;
        else
        {
            Object Data = Head.Data;
            Head = Head.NextNode;
            if (Head == null)
                Tail = null;
            return Object;
        }
    }
    char RemoveFromBack()
    {
        if (Head == null)
            return 0;
        else
        {
            Object Data = Tail.Data;
            if (Head.NextNode == null)
            {
                Head = null;
                Tail = null;
            }
            else
            {
                Node cNode;
                cNode = Head;
                while (cNode.NextNode != Tail)
                {
                    cNode = cNode.NextNode;
                }
                cNode.NextNode = null;
                Tail = cNode;
            }
            return Data;
        }
    }
    void BeginEnumeration()
    {
        Current = Head;
    }
    boolean IsEmpty()
    {
        return Head == null;
    }
    char GetNextData()
    {
        if (Current == null)
            return 0;
        else
        {
            Object Data = Current.Data;
            Current = Current.NextNode;
            return Data;
        }
    }
    void DeleteAllNodes()
    {
        Current = null;
        Tail = null;
        Head = null;
    }
}