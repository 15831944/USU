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
import Digit;

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
    void InsertAtFront(Digit Data)
    {
        Node PrevHeadNode = Head;
        Head = new Node(Data);
        Head.NextNode = PrevHeadNode;
        if (Tail == null)
        {
            Tail = Head;
        }
    }
    void InsertAtBack(Digit Data)
    {
        if (Tail == null)
            InsertAtFront(Data);
        else
        {
            Tail.NextNode = new Node(Data);
            Tail = Tail.NextNode;
        }
    }
    Digit RemoveFromFront()
    {
        if (Head == null)
            return null;
        else
        {
            Digit Data = Head.Data;
            Head = Head.NextNode;
            if (Head == null)
                Tail = null;
            return Data;
        }
    }
    Digit RemoveFromBack()
    {
        if (Head == null)
            return null;
        else
        {
            Digit Data = Tail.Data;
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
    Digit GetNextData()
    {
        if (Current == null)
            return null;
        else
        {
            Digit Data = Current.Data;
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